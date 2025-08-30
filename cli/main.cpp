#include <names/names.h>
#include <names/version.h>
#include <fmt/format.h>
#include <iostream>
#include <string>

void print_usage(const char* program_name) {
    fmt::print("Usage: {} [count] [--number]\n", program_name);
    fmt::print("\n");
    fmt::print("Generate random names in the format 'adjective-noun'.\n");
    fmt::print("\n");
    fmt::print("Arguments:\n");
    fmt::print("  count      Number of names to generate (default: 1)\n");
    fmt::print("\n");
    fmt::print("Options:\n");
    fmt::print("  --number   Add a 4-digit number suffix to each name\n");
    fmt::print("  --version  Show version information\n");
    fmt::print("  --help     Show this help message\n");
    fmt::print("\n");
    fmt::print("Examples:\n");
    fmt::print("  {}           Generate one name: 'happy-dog'\n", program_name);
    fmt::print("  {} 5         Generate 5 names\n", program_name);
    fmt::print("  {} --number  Generate one name with number: 'happy-dog-1234'\n", program_name);
    fmt::print("  {} 3 --number Generate 3 names with numbers\n", program_name);
}

int main(int argc, char* argv[]) {
    int count = 1;
    bool with_numbers = false;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "--help" || arg == "-h") {
            print_usage(argv[0]);
            return 0;
        } else if (arg == "--version" || arg == "-v") {
            fmt::print("names {}\n", names::version());
            return 0;
        } else if (arg == "--number" || arg == "-n") {
            with_numbers = true;
        } else {
            try {
                count = std::stoi(arg);
                if (count <= 0) {
                    fmt::print(stderr, "Error: count must be a positive number\n");
                    return 1;
                }
            } catch (const std::exception&) {
                fmt::print(stderr, "Error: invalid argument '{}'\n", arg);
                print_usage(argv[0]);
                return 1;
            }
        }
    }
    
    names::Generator generator;
    
    for (int i = 0; i < count; ++i) {
        if (with_numbers) {
            fmt::print("{}\n", generator.next_numbered());
        } else {
            fmt::print("{}\n", generator.next());
        }
    }
    
    return 0;
}