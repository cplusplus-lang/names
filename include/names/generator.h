#pragma once

#include <string>
#include <random>
#include <vector>

namespace names {

class Generator {
public:
    Generator();
    explicit Generator(unsigned int seed);
    explicit Generator(const std::vector<std::string>& adjectives, const std::vector<std::string>& nouns);
    Generator(const std::vector<std::string>& adjectives, const std::vector<std::string>& nouns, unsigned int seed);

    std::string next();
    std::string next_numbered();

    static Generator create_default();

private:
    const std::vector<std::string>& adjectives_;
    const std::vector<std::string>& nouns_;
    std::mt19937 rng_;

    std::string generate_name(bool with_number = false);
};

} // namespace names