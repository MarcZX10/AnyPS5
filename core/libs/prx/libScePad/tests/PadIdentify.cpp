#include "prx/libScePad/include/PadIdentify.hpp"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace {

void Require(bool condition, const char* message) {
    if (condition) return;
    std::fprintf(stderr, "pad_identify: %s\n", message);
    std::exit(1);
}

void PatternHasOnePulsePerPlayer() {
    for (unsigned player = 1; player <= Pad::kIdentifyMaxPlayer; ++player) {
        const auto pattern = Pad::MakeIdentifyPattern(player);
        Require(pattern.count == player, "player N gets exactly N pulses");
        for (unsigned index = 0; index < player; ++index) {
            const auto& pulse = pattern.pulses[index];
            Require(pulse.startMs == index * 400u, "pulses start 400 ms apart from the bind point");
            Require(pulse.durationMs == 150u, "each pulse lasts 150 ms");
            Require(pulse.strength == 255, "each pulse is at full strength before the user scale");
        }
    }
}

void OutOfRangePlayersGetNoPattern() {
    for (const unsigned player : {0u, 5u, 6u, 0xFFFFFFFFu}) {
        const auto pattern = Pad::MakeIdentifyPattern(player);
        Require(pattern.count == 0, "a player outside 1 to 4 gets no pulses");
    }
}

}

int main() {
    PatternHasOnePulsePerPlayer();
    OutOfRangePlayersGetNoPattern();
    return 0;
}
