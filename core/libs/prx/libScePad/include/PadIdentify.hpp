#ifndef CORE_LIBS_PRX_LIBSCEPAD_PADIDENTIFY_HPP
#define CORE_LIBS_PRX_LIBSCEPAD_PADIDENTIFY_HPP

#include <array>
#include <cstdint>

namespace Pad {

constexpr unsigned kIdentifyMaxPlayer = 4;
constexpr std::uint32_t kIdentifyPulseMs = 150;
constexpr std::uint32_t kIdentifyPeriodMs = 400;
constexpr std::uint8_t kIdentifyStrength = 255;

struct IdentifyPulse {
    std::uint32_t startMs = 0;
    std::uint32_t durationMs = 0;
    std::uint8_t strength = 0;
};

struct IdentifyPattern {
    std::array<IdentifyPulse, kIdentifyMaxPlayer> pulses{};
    unsigned count = 0;
};

constexpr IdentifyPattern MakeIdentifyPattern(unsigned player) {
    IdentifyPattern pattern;
    if (player < 1 || player > kIdentifyMaxPlayer) return pattern;
    pattern.count = player;
    for (unsigned index = 0; index < player; ++index) {
        pattern.pulses[index] = IdentifyPulse{index * kIdentifyPeriodMs, kIdentifyPulseMs, kIdentifyStrength};
    }
    return pattern;
}

}

#endif
