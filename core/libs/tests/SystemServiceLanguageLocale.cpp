#include "prx/libSceSystemService/LanguageLocale.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string_view>

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

}

int main() {
    RequireBcp47Parsing();
}
