#include "names/generator.h"
#include "names/words.h"
#include <fmt/format.h>
#include <chrono>

namespace names {

Generator::Generator() 
    : adjectives_(adjectives), nouns_(nouns), rng_(std::chrono::steady_clock::now().time_since_epoch().count()) {
}

Generator::Generator(unsigned int seed) 
    : adjectives_(adjectives), nouns_(nouns), rng_(seed) {
}

Generator::Generator(const std::vector<std::string>& adj, const std::vector<std::string>& n)
    : adjectives_(adj), nouns_(n), rng_(std::chrono::steady_clock::now().time_since_epoch().count()) {
}

Generator::Generator(const std::vector<std::string>& adj, const std::vector<std::string>& n, unsigned int seed)
    : adjectives_(adj), nouns_(n), rng_(seed) {
}

std::string Generator::next() {
    return generate_name(false);
}

std::string Generator::next_numbered() {
    return generate_name(true);
}

Generator Generator::create_default() {
    return Generator();
}

std::string Generator::generate_name(bool with_number) {
    std::uniform_int_distribution<size_t> adj_dist(0, adjectives_.size() - 1);
    std::uniform_int_distribution<size_t> noun_dist(0, nouns_.size() - 1);
    
    const std::string& adjective = adjectives_[adj_dist(rng_)];
    const std::string& noun = nouns_[noun_dist(rng_)];
    
    if (with_number) {
        std::uniform_int_distribution<int> number_dist(0, 9999);
        int number = number_dist(rng_);
        return fmt::format("{}-{}-{:04d}", adjective, noun, number);
    } else {
        return fmt::format("{}-{}", adjective, noun);
    }
}

} // namespace names