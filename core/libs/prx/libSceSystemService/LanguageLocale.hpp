#ifndef CORE_LIBS_PRX_LIBSCESYSTEMSERVICE_LANGUAGELOCALE_HPP
#define CORE_LIBS_PRX_LIBSCESYSTEMSERVICE_LANGUAGELOCALE_HPP

#include <cstddef>
#include <span>
#include <string>
#include <string_view>
#include <utility>

namespace SystemServiceLocale {

struct Tag {
    std::string language;
    std::string script;
    std::string region;
};

enum ConsoleLanguage : int {
    Japanese = 0,
    EnglishUs = 1,
    French = 2,
    Spanish = 3,
    German = 4,
    Italian = 5,
    Dutch = 6,
    PortuguesePortugal = 7,
    Russian = 8,
    Korean = 9,
    ChineseTraditional = 10,
    ChineseSimplified = 11,
    Finnish = 12,
    Swedish = 13,
    Danish = 14,
    Norwegian = 15,
    Polish = 16,
    PortugueseBrazil = 17,
    EnglishUk = 18,
    Turkish = 19,
    SpanishLatinAmerica = 20,
    Arabic = 21,
    FrenchCanada = 22,
    Czech = 23,
    Hungarian = 24,
    Greek = 25,
    Romanian = 26,
    Thai = 27,
    Vietnamese = 28,
    Indonesian = 29,
    Ukrainian = 30,
};

constexpr int NoConsoleLanguage = -1;

struct Row {
    std::string_view language;
    std::string_view script;
    std::string_view region;
    int id;
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

constexpr bool EqualsIgnoringCase(std::string_view left, std::string_view right) {
    if (left.size() != right.size()) return false;
    for (std::size_t i = 0; i < left.size(); ++i) {
        if (Lower(left[i]) != Lower(right[i])) return false;
    }
    return true;
}

inline constexpr Row LatinEuropeanRows[] = {
    {"en", "", "", EnglishUs},
    {"en", "", "GB", EnglishUk},
    {"en", "", "IE", EnglishUk},
    {"en", "", "AU", EnglishUk},
    {"en", "", "NZ", EnglishUk},
    {"fr", "", "", French},
    {"fr", "", "CA", FrenchCanada},
    {"de", "", "", German},
    {"it", "", "", Italian},
    {"nl", "", "", Dutch},
    {"ro", "", "", Romanian},
    {"mo", "", "", Romanian},
};

inline constexpr std::span<const Row> RowGroups[] = {
    LatinEuropeanRows,
};

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

inline std::string NormalizePosixLocale(std::string_view text) {
    std::string_view modifier;
    if (const std::size_t at = text.find('@'); at != std::string_view::npos) {
        modifier = text.substr(at + 1);
        text = text.substr(0, at);
    }
    text = text.substr(0, text.find('.'));
    std::string name;
    for (char c : text) name += c == '_' ? '-' : c;
    if (name.empty() || Detail::EqualsIgnoringCase(name, "C") || Detail::EqualsIgnoringCase(name, "POSIX")) return {};
    std::string_view script;
    if (Detail::EqualsIgnoringCase(modifier, "latin")) script = "Latn";
    if (Detail::EqualsIgnoringCase(modifier, "cyrillic")) script = "Cyrl";
    if (!script.empty()) {
        const std::size_t dash = name.find('-');
        const std::string_view second = dash == std::string::npos ? std::string_view{} : std::string_view(name).substr(dash + 1, 4);
        const bool hasScript = second.size() == 4 && Detail::AllOf(second, Detail::IsAlpha) && (dash + 5 == name.size() || name[dash + 5] == '-');
        if (!hasScript) name.insert(dash == std::string::npos ? name.size() : dash, std::string("-") + std::string(script));
    }
    return name;
}

inline bool ParseLocale(std::string_view text, Tag& tag) {
    const std::string normalised = NormalizePosixLocale(text);
    return !normalised.empty() && ParseTag(normalised, tag);
}

inline int ConsoleLanguageForTag(const Tag& tag) {
    int best = NoConsoleLanguage;
    int bestScore = -1;
    for (const std::span<const Row> group : Detail::RowGroups) {
        for (const Row& row : group) {
            if (row.language != tag.language) continue;
            if (!row.script.empty() && row.script != tag.script) continue;
            if (!row.region.empty() && row.region != tag.region) continue;
            const int score = (row.script.empty() ? 0 : 2) + (row.region.empty() ? 0 : 1);
            if (score > bestScore) {
                best = row.id;
                bestScore = score;
            }
        }
    }
    return best;
}

}

#endif
