#ifndef CORE_LIBS_PRX_LIBSCESYSTEMSERVICE_LANGUAGELOCALE_HPP
#define CORE_LIBS_PRX_LIBSCESYSTEMSERVICE_LANGUAGELOCALE_HPP

#include <cstddef>
#include <string>
#include <string_view>
#include <utility>

namespace SystemServiceLocale {

struct Tag {
    std::string language;
    std::string script;
    std::string region;
};

namespace Detail {

constexpr bool IsAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
constexpr bool IsDigit(char c) { return c >= '0' && c <= '9'; }
constexpr char Lower(char c) { return c >= 'A' && c <= 'Z' ? static_cast<char>(c - 'A' + 'a') : c; }
constexpr char Upper(char c) { return c >= 'a' && c <= 'z' ? static_cast<char>(c - 'a' + 'A') : c; }

constexpr bool AllOf(std::string_view text, bool (*predicate)(char)) {
    for (char c : text) {
        if (!predicate(c)) return false;
    }
    return true;
}

constexpr bool IsAlphanumeric(char c) { return IsAlpha(c) || IsDigit(c); }

}

inline bool ParseTag(std::string_view text, Tag& tag) {
    Tag parsed;
    std::size_t index = 0;
    bool seenScript = false;
    bool seenRegion = false;
    bool tail = false;
    std::size_t position = 0;
    while (true) {
        const std::size_t end = text.find('-', position);
        const std::string_view subtag = text.substr(position, end == std::string_view::npos ? std::string_view::npos : end - position);
        if (subtag.empty() || subtag.size() > 8 || !Detail::AllOf(subtag, Detail::IsAlphanumeric)) return false;
        if (index == 0) {
            if ((subtag.size() != 2 && subtag.size() != 3) || !Detail::AllOf(subtag, Detail::IsAlpha)) return false;
            for (char c : subtag) parsed.language += Detail::Lower(c);
        } else if (!tail) {
            if (subtag.size() == 1) {
                tail = true;
            } else if (!seenScript && !seenRegion && subtag.size() == 4 && Detail::AllOf(subtag, Detail::IsAlpha)) {
                seenScript = true;
                parsed.script += Detail::Upper(subtag[0]);
                for (std::size_t i = 1; i < subtag.size(); ++i) parsed.script += Detail::Lower(subtag[i]);
            } else if (!seenRegion && ((subtag.size() == 2 && Detail::AllOf(subtag, Detail::IsAlpha)) || (subtag.size() == 3 && Detail::AllOf(subtag, Detail::IsDigit)))) {
                seenRegion = true;
                for (char c : subtag) parsed.region += Detail::Upper(c);
            } else {
                tail = true;
            }
        }
        ++index;
        if (end == std::string_view::npos) break;
        position = end + 1;
    }
    tag = std::move(parsed);
    return true;
}

}

#endif
