#include <catch2/catch_test_macros.hpp>
#include <names/names.h>
#include <names/generator.h>
#include <regex>

TEST_CASE("Generator produces valid names") {
    names::Generator generator(42); // Fixed seed for reproducible tests
    
    std::string name = generator.next();
    
    CHECK(!name.empty());
    CHECK(name.find('-') != std::string::npos);
    
    // Should match pattern: word-word
    std::regex pattern(R"([a-z]+-[a-z]+)");
    CHECK(std::regex_match(name, pattern));
}

TEST_CASE("Generator produces valid numbered names") {
    names::Generator generator(42); // Fixed seed for reproducible tests
    
    std::string name = generator.next_numbered();
    
    CHECK(!name.empty());
    
    // Should match pattern: word-word-0000 to word-word-9999
    std::regex pattern(R"([a-z]+-[a-z]+-\d{4})");
    CHECK(std::regex_match(name, pattern));
}

TEST_CASE("Multiple names are different") {
    names::Generator generator;
    
    std::string name1 = generator.next();
    std::string name2 = generator.next();
    std::string name3 = generator.next();
    
    // Very unlikely to get the same name 3 times
    CHECK(!(name1 == name2 && name2 == name3));
}

TEST_CASE("Static generate functions work") {
    std::string name1 = names::generate();
    std::string name2 = names::generate_numbered();
    
    CHECK(!name1.empty());
    CHECK(!name2.empty());
    CHECK(name1.find('-') != std::string::npos);
    CHECK(name2.find('-') != std::string::npos);
    
    std::regex pattern_plain(R"([a-z]+-[a-z]+)");
    std::regex pattern_numbered(R"([a-z]+-[a-z]+-\d{4})");
    
    CHECK(std::regex_match(name1, pattern_plain));
    CHECK(std::regex_match(name2, pattern_numbered));
}

TEST_CASE("Custom word lists work") {
    std::vector<std::string> custom_adjectives = {"red", "blue"};
    std::vector<std::string> custom_nouns = {"car", "house"};
    
    names::Generator generator(custom_adjectives, custom_nouns, 42);
    
    std::string name = generator.next();
    
    CHECK(!name.empty());
    CHECK((name == "red-car" || name == "red-house" || name == "blue-car" || name == "blue-house"));
}