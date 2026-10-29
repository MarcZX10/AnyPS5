#include "prx/libSceSystemService/LanguageLocale.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string_view>
#include <utility>

namespace {

void Require(bool value, std::string_view what) {
    if (value) return;
    std::fprintf(stderr, "check failed: %.*s\n", static_cast<int>(what.size()), what.data());
    std::abort();
}

struct ParsedTag {
    std::string_view text;
    std::string_view language;
    std::string_view script;
    std::string_view region;
};

void RequireBcp47Parsing() {
    constexpr ParsedTag accepted[] = {
        {"en", "en", "", ""},
        {"en-US", "en", "", "US"},
        {"EN-us", "en", "", "US"},
        {"pt-BR", "pt", "", "BR"},
        {"es-419", "es", "", "419"},
        {"zh-Hant-TW", "zh", "Hant", "TW"},
        {"zh-hans-cn", "zh", "Hans", "CN"},
        {"ZH-HANT", "zh", "Hant", ""},
        {"sr-Latn-RS", "sr", "Latn", "RS"},
        {"fil", "fil", "", ""},
        {"en-US-u-ca-gregory", "en", "", "US"},
        {"de-DE-1996", "de", "", "DE"},
        {"ca-ES-valencia", "ca", "", "ES"},
        {"en-x-private", "en", "", ""},
        {"en-Latn-US-x-a", "en", "Latn", "US"},
    };
    for (const auto& expected : accepted) {
        SystemServiceLocale::Tag tag;
        Require(SystemServiceLocale::ParseTag(expected.text, tag), expected.text);
        Require(tag.language == expected.language, expected.text);
        Require(tag.script == expected.script, expected.text);
        Require(tag.region == expected.region, expected.text);
    }
    for (std::string_view rejected : {"", "-", "en-", "-en", "en--US", "e", "english", "e1", "12", "en_US", "en-US.UTF-8", "en US", "en-U$", "en-abcdefghi", "C", "x-foo"}) {
        SystemServiceLocale::Tag tag{"keep", "keep", "keep"};
        const bool parsed = SystemServiceLocale::ParseTag(rejected, tag);
        Require(!parsed, rejected);
        Require(tag.language == "keep" && tag.script == "keep" && tag.region == "keep", rejected);
    }
}

void RequirePosixNormalisation() {
    constexpr std::pair<std::string_view, std::string_view> names[] = {
        {"en_US.UTF-8", "en-US"},
        {"en_GB.UTF-8@euro", "en-GB"},
        {"de_DE.ISO-8859-15@euro", "de-DE"},
        {"pt_BR", "pt-BR"},
        {"zh_TW", "zh-TW"},
        {"zh_Hant_TW", "zh-Hant-TW"},
        {"ca_ES@valencia", "ca-ES"},
        {"sr_RS@latin", "sr-Latn-RS"},
        {"sr@latin", "sr-Latn"},
        {"sr_Latn_RS@latin", "sr-Latn-RS"},
        {"uz_UZ@Cyrillic", "uz-Cyrl-UZ"},
        {"fr", "fr"},
        {"en-US", "en-US"},
        {"EN_us.utf8", "EN-us"},
        {"C", ""},
        {"POSIX", ""},
        {"c", ""},
        {"posix", ""},
        {"C.UTF-8", ""},
        {"C.utf8@euro", ""},
        {"", ""},
        {"@latin", ""},
        {".UTF-8", ""},
    };
    for (const auto& [name, expected] : names) {
        Require(SystemServiceLocale::NormalizePosixLocale(name) == expected, name);
    }
}

void RequireEitherForm() {
    constexpr ParsedTag locales[] = {
        {"en_US.UTF-8", "en", "", "US"},
        {"en-US", "en", "", "US"},
        {"zh_Hant_TW.UTF-8", "zh", "Hant", "TW"},
        {"zh-Hans-CN", "zh", "Hans", "CN"},
        {"sr_RS@latin", "sr", "Latn", "RS"},
        {"pt_BR.utf8", "pt", "", "BR"},
        {"es_419", "es", "", "419"},
        {"fr", "fr", "", ""},
    };
    for (const auto& expected : locales) {
        SystemServiceLocale::Tag tag;
        Require(SystemServiceLocale::ParseLocale(expected.text, tag), expected.text);
        Require(tag.language == expected.language && tag.script == expected.script && tag.region == expected.region, expected.text);
    }
    for (std::string_view none : {"", "C", "POSIX", "C.UTF-8", "@latin", "garbage!", "english", "e", "en__US", "_US", "123"}) {
        SystemServiceLocale::Tag tag{"keep", "keep", "keep"};
        Require(!SystemServiceLocale::ParseLocale(none, tag), none);
        Require(tag.language == "keep" && tag.script == "keep" && tag.region == "keep", none);
    }
}

}

int main() {
    RequireBcp47Parsing();
    RequirePosixNormalisation();
    RequireEitherForm();
}
