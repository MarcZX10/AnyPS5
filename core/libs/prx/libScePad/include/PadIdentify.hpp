#ifndef CORE_LIBS_PRX_LIBSCEPAD_PADIDENTIFY_HPP
#define CORE_LIBS_PRX_LIBSCEPAD_PADIDENTIFY_HPP

#include <array>
#include <cstdint>
#include <cstdlib>
#include <stdexcept>
#include <string>

namespace Pad {

enum class IdentifyMode : std::uint8_t { Off, Connect, Always };

inline IdentifyMode ParseIdentifyMode(const char* text) {
    if (text == nullptr) return IdentifyMode::Off;
    const std::string value(text);
    if (value == "off") return IdentifyMode::Off;
    if (value == "connect") return IdentifyMode::Connect;
    if (value == "always") return IdentifyMode::Always;
    throw std::runtime_error("ANYPS5_PAD_IDENTIFY must be off, connect or always, got '" + value + "'");
}

inline IdentifyMode IdentifyModeFromEnvironment() {
    static const IdentifyMode mode = ParseIdentifyMode(std::getenv("ANYPS5_PAD_IDENTIFY"));
    return mode;
}

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
