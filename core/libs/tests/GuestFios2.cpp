#include "prx/libSceFios2/include/Api.hpp"
#include "prx/libkernel/include/Api.hpp"
#include "prx/libc/include/General.hpp"
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

static void Require(bool condition, int line) {
    if (!condition) {
        std::fprintf(stderr, "guest_fios2 check failed at line %d\n", line);
        std::abort();
    }
}
#define REQUIRE(condition) Require((condition), __LINE__)

static std::atomic<int> g_completed{0};
static std::atomic<int> g_deleted{0};
static std::atomic<int> g_lastError{0};
static std::atomic<int> g_lastOp{0};

static int APS5_VABI CountEvents(void* context, SceFiosOp op, SceFiosOpEvent event, int error) {
    REQUIRE(context == reinterpret_cast<void*>(0x1234));
    g_lastOp = op;
    if (event == SCE_FIOS_OPEVENT_COMPLETE) {
        g_lastError = error;
        ++g_completed;
    } else if (event == SCE_FIOS_OPEVENT_DELETE) {
        ++g_deleted;
    }
    return 0;
}

static SceFiosOpAttr CountingAttr() {
    SceFiosOpAttr attr{};
    attr.pCallback = CountEvents;
    attr.pCallbackContext = reinterpret_cast<void*>(0x1234);
    return attr;
}

static void CheckInitialization() {
    REQUIRE(!sceFiosIsInitialized(nullptr));
    std::uint32_t params[16] = {};
    params[0] = (sizeof(params) << 1) | 0u;
    params[3] = 0xfeedbeef;
    REQUIRE(sceFiosInitialize(reinterpret_cast<const SceFiosParams*>(params)) == SCE_FIOS_OK);
    REQUIRE(sceFiosIsInitialized(nullptr));
    std::uint32_t copy[16] = {};
    REQUIRE(sceFiosIsInitialized(reinterpret_cast<SceFiosParams*>(copy)));
    REQUIRE(copy[3] == 0xfeedbeef);
    params[3] = 0x1;
    sceFiosUpdateParameters(reinterpret_cast<const SceFiosParams*>(params));
    REQUIRE(sceFiosIsInitialized(reinterpret_cast<SceFiosParams*>(copy)) && copy[3] == 0x1);
}

static void CheckQueries(const std::string& directory, const std::string& file) {
    REQUIRE(sceFiosExistsSync(nullptr, file.c_str()));
    REQUIRE(sceFiosExistsSync(nullptr, directory.c_str()));
    REQUIRE(!sceFiosExistsSync(nullptr, (directory + "/missing").c_str()));
    REQUIRE(sceFiosFileExistsSync(nullptr, file.c_str()));
    REQUIRE(!sceFiosFileExistsSync(nullptr, directory.c_str()));
    REQUIRE(sceFiosDirectoryExistsSync(nullptr, directory.c_str()));
    REQUIRE(!sceFiosDirectoryExistsSync(nullptr, file.c_str()));
    REQUIRE(!sceFiosExistsSync(nullptr, nullptr));
    REQUIRE(!sceFiosExistsSync(nullptr, ""));

    REQUIRE(sceFiosFileGetSizeSync(nullptr, file.c_str()) == 10);
    REQUIRE(sceFiosFileGetSizeSync(nullptr, directory.c_str()) == SCE_FIOS_ERROR_NOT_A_FILE);
    REQUIRE(sceFiosFileGetSizeSync(nullptr, (directory + "/missing").c_str()) == SCE_FIOS_ERROR_BAD_PATH);
    REQUIRE(sceFiosFileGetSizeSync(nullptr, nullptr) == SCE_FIOS_ERROR_BAD_PTR);
    REQUIRE(sceFiosFileGetSizeSync(nullptr, "") == SCE_FIOS_ERROR_BAD_PATH);
    const std::string tooLong(2000, 'a');
    REQUIRE(sceFiosFileGetSizeSync(nullptr, tooLong.c_str()) == SCE_FIOS_ERROR_PATH_TOO_LONG);

    SceFiosStat stat{};
    std::memset(&stat, 0xaa, sizeof(stat));
    REQUIRE(sceFiosStatSync(nullptr, file.c_str(), &stat) == SCE_FIOS_OK);
    REQUIRE(stat.fileSize == 10 && (stat.statFlags & SCE_FIOS_STAT_DIRECTORY) == 0);
    REQUIRE(stat.modificationDate > 1000000000ull * 1000000000ull);
    REQUIRE((stat.mode & 0170000) == 0100000);
    REQUIRE(sceFiosStatSync(nullptr, directory.c_str(), &stat) == SCE_FIOS_OK);
    REQUIRE((stat.statFlags & SCE_FIOS_STAT_DIRECTORY) != 0);
    REQUIRE(sceFiosStatSync(nullptr, (directory + "/missing").c_str(), &stat) == SCE_FIOS_ERROR_BAD_PATH);
    REQUIRE(sceFiosStatSync(nullptr, file.c_str(), nullptr) == SCE_FIOS_ERROR_BAD_PTR);
}

static void CheckOperationLifecycle(const std::string& file) {
    const SceFiosOp op = sceFiosFileGetSize(nullptr, file.c_str());
    REQUIRE(op > 0);
    REQUIRE(sceFiosIsValidHandle(op));
    REQUIRE(sceFiosOpIsDone(op));
    REQUIRE(sceFiosOpGetError(op) == SCE_FIOS_OK);
    REQUIRE(sceFiosOpWait(op) == SCE_FIOS_OK);
    REQUIRE(sceFiosOpGetActualCount(op) == 10);
    REQUIRE(sceFiosOpGetPath(op) != nullptr && file == sceFiosOpGetPath(op));
    REQUIRE(sceFiosOpGetAttr(op) != nullptr && !sceFiosOpIsCancelled(op));
    REQUIRE(sceFiosOpGetOffset(op) == 0);
    std::vector<SceFiosOp> listed(8);
    REQUIRE(sceFiosGetAllOps(listed.data(), static_cast<std::uint32_t>(listed.size())) >= 1);
    REQUIRE(listed[0] == op);
    REQUIRE(sceFiosOpSyncWaitForIO(op) == 10);
    REQUIRE(!sceFiosIsValidHandle(op));
    REQUIRE(sceFiosOpGetError(op) == SCE_FIOS_ERROR_BAD_OP);
    REQUIRE(sceFiosOpWait(op) == SCE_FIOS_ERROR_BAD_OP);
    REQUIRE(sceFiosOpSyncWait(op) == SCE_FIOS_ERROR_BAD_OP);
    REQUIRE(sceFiosOpGetActualCount(op) == SCE_FIOS_ERROR_BAD_OP);
    REQUIRE(sceFiosOpGetPath(op) == nullptr);
    sceFiosOpDelete(op);

    bool exists = false;
    const SceFiosOp existsOp = sceFiosExists(nullptr, file.c_str(), &exists);
    REQUIRE(exists && sceFiosOpGetActualCount(existsOp) == 1);
    REQUIRE(sceFiosOpSyncWait(existsOp) == 1);
    const SceFiosOp missingOp = sceFiosExists(nullptr, "fios2_probe/none", &exists);
    REQUIRE(!exists && sceFiosOpSyncWait(missingOp) == 0);

    const SceFiosOp failed = sceFiosFileGetSize(nullptr, "fios2_probe/none");
    REQUIRE(sceFiosOpGetError(failed) == SCE_FIOS_ERROR_BAD_PATH);
    REQUIRE(sceFiosOpSyncWait(failed) == SCE_FIOS_ERROR_BAD_PATH);
}

static void CheckCallbacks(const std::string& file) {
    g_completed = 0;
    g_deleted = 0;
    const SceFiosOpAttr attr = CountingAttr();
    const SceFiosOp op = sceFiosFileExists(&attr, file.c_str(), nullptr);
    REQUIRE(g_completed == 1 && g_lastOp == op && g_lastError == SCE_FIOS_OK);
    REQUIRE(g_deleted == 0);
    sceFiosOpDelete(op);
    REQUIRE(g_deleted == 1);
    REQUIRE(sceFiosFileExistsSync(&attr, file.c_str()));
    REQUIRE(g_completed == 2 && g_deleted == 2);

    const SceFiosOp failed = sceFiosFileGetSize(&attr, "fios2_probe/none");
    REQUIRE(g_completed == 3 && g_lastError == SCE_FIOS_ERROR_BAD_PATH);
    sceFiosOpDelete(failed);

    SceFiosOpAttr stored{};
    REQUIRE(!sceFiosGetGlobalDefaultOpAttr(&stored));
    SceFiosOpAttr global = CountingAttr();
    global.userTag = 77;
    sceFiosSetGlobalDefaultOpAttr(&global);
    REQUIRE(sceFiosGetGlobalDefaultOpAttr(&stored) && stored.userTag == 77);
    SceFiosOpAttr effective{};
    sceFiosGetDefaultOpAttr(&effective);
    REQUIRE(effective.userTag == 77);
    const SceFiosOp usesGlobal = sceFiosFileExists(nullptr, file.c_str(), nullptr);
    REQUIRE(sceFiosOpGetAttr(usesGlobal)->userTag == 77 && g_completed == 4);
    sceFiosOpDelete(usesGlobal);

    SceFiosOpAttr thread = CountingAttr();
    thread.userTag = 88;
    sceFiosSetThreadDefaultOpAttr(&thread);
    REQUIRE(sceFiosGetThreadDefaultOpAttr(&stored) && stored.userTag == 88);
    std::thread other([&] {
        SceFiosOpAttr seen{};
        REQUIRE(!sceFiosGetThreadDefaultOpAttr(&seen));
        sceFiosGetDefaultOpAttr(&seen);
        REQUIRE(seen.userTag == 77);
    });
    other.join();
    const SceFiosOp usesThread = sceFiosFileExists(nullptr, file.c_str(), nullptr);
    REQUIRE(sceFiosOpGetAttr(usesThread)->userTag == 88);
    sceFiosOpDelete(usesThread);
    sceFiosSetThreadDefaultOpAttr(nullptr);
    REQUIRE(!sceFiosGetThreadDefaultOpAttr(&stored));
    sceFiosSetGlobalDefaultOpAttr(nullptr);
    REQUIRE(!sceFiosGetGlobalDefaultOpAttr(&stored));
}

static void CheckSuspension(const std::string& file) {
    REQUIRE(!sceFiosIsSuspended() && sceFiosGetSuspendCount() == 0 && sceFiosIsIdle());
    g_completed = 0;
    const SceFiosOpAttr attr = CountingAttr();
    sceFiosSuspend();
    sceFiosSuspend();
    REQUIRE(sceFiosIsSuspended() && sceFiosGetSuspendCount() == 2);
    const SceFiosOp first = sceFiosFileGetSize(&attr, file.c_str());
    const SceFiosOp second = sceFiosFileGetSize(&attr, file.c_str());
    REQUIRE(!sceFiosOpIsDone(first) && !sceFiosOpIsDone(second) && !sceFiosIsIdle());
    REQUIRE(sceFiosOpGetError(first) == 1 && g_completed == 0);
    sceFiosResume();
    REQUIRE(!sceFiosOpIsDone(first) && sceFiosGetSuspendCount() == 1);
    std::thread resumer([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        sceFiosResume();
    });
    REQUIRE(sceFiosOpWait(first) == SCE_FIOS_OK);
    resumer.join();
    REQUIRE(sceFiosOpIsDone(second) && sceFiosIsIdle() && g_completed == 2);
    REQUIRE(sceFiosOpGetActualCount(first) == 10 && sceFiosOpGetActualCount(second) == 10);
    sceFiosOpDelete(first);
    sceFiosOpDelete(second);
    sceFiosResume();
    REQUIRE(sceFiosGetSuspendCount() == 0);

    sceFiosSuspend();
    const SceFiosOp cancelled = sceFiosFileGetSize(&attr, file.c_str());
    const SceFiosOp alsoCancelled = sceFiosFileGetSize(&attr, file.c_str());
    sceFiosOpCancel(cancelled);
    REQUIRE(sceFiosOpIsDone(cancelled) && sceFiosOpIsCancelled(cancelled));
    REQUIRE(sceFiosOpGetError(cancelled) == SCE_FIOS_ERROR_CANCELLED);
    REQUIRE(g_lastError == SCE_FIOS_ERROR_CANCELLED);
    sceFiosCancelAllOps();
    REQUIRE(sceFiosOpGetError(alsoCancelled) == SCE_FIOS_ERROR_CANCELLED && sceFiosIsIdle());
    sceFiosResume();
    REQUIRE(sceFiosOpSyncWaitForIO(cancelled) == SCE_FIOS_ERROR_CANCELLED);
    sceFiosOpDelete(alsoCancelled);

    sceFiosSuspend();
    const SceFiosOp abandoned = sceFiosFileGetSize(nullptr, file.c_str());
    sceFiosOpDelete(abandoned);
    REQUIRE(!sceFiosIsValidHandle(abandoned));
    sceFiosResume();
    sceFiosResume();
    REQUIRE(sceFiosGetSuspendCount() == 0);
}

int main() {
    const std::filesystem::path directory = "fios2_probe";
    std::filesystem::remove_all(directory);
    std::filesystem::create_directories(directory);
    const std::string file = (directory / "data.bin").generic_string();
    {
        std::ofstream out(file, std::ios::binary);
        out << "0123456789";
    }
    CheckInitialization();
    CheckQueries(directory.generic_string(), file);
    CheckOperationLifecycle(file);
    CheckCallbacks(file);
    CheckSuspension(file);
    sceFiosTerminate();
    REQUIRE(!sceFiosIsInitialized(nullptr));
    std::filesystem::remove_all(directory);
    std::puts("guest_fios2 ok");
    return 0;
}
