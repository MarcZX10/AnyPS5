#ifndef CORE_LIBS_PRX_LIBC_INCLUDE_RENAMEDOT_HPP
#define CORE_LIBS_PRX_LIBC_INCLUDE_RENAMEDOT_HPP

#include <filesystem>
#include <string>
#include "FilesystemError.hpp"

inline std::string TrimTrailingSeparatorsPreservingRoot_nid_no_patch(std::string path) {
    const auto separator = [](char character) { return character == '/' || character == '\\'; };
    const auto root = std::filesystem::path(path).root_path();
    while (path.size() > 1 && separator(path.back())) {
        const auto candidate = std::filesystem::path(path.substr(0, path.size() - 1));
        if (candidate == root) break;
        path.pop_back();
    }
    return path;
}

inline int RenameDotError_nid_no_patch(const char* path) {
    std::size_t length = std::char_traits<char>::length(path);
    const auto separator = [](char character) { return character == '/' || character == '\\'; };
    while (length > 1 && separator(path[length - 1])) --length;
    std::size_t start = length;
    while (start > 0 && !separator(path[start - 1])) --start;
    const std::size_t name = length - start;
    const bool dot = name == 1 && path[start] == '.';
    const bool dotDot = name == 2 && path[start] == '.' && path[start + 1] == '.';
    if (!dot && !dotDot) return 0;
    std::string parent = start == 0 ? std::string(".") : std::string(path, start);
    parent = TrimTrailingSeparatorsPreservingRoot_nid_no_patch(parent);
    std::filesystem::path resolved;
    if (const int error = ResolvePathError_nid_no_patch(parent.c_str(), resolved)) return error;
    std::error_code status;
    if (!std::filesystem::exists(resolved, status)) return 2;
    return std::filesystem::is_directory(resolved, status) ? 22 : 20;
}

#endif
