# Names

A C++ library and CLI tool for generating random names in the format "adjective-noun". This is a C++ port of the Rust [names](https://github.com/fnichol/names) project.

## Features

- Generate random names like "happy-dog" or "clever-fox"
- Optional 4-digit number suffixes: "brave-lion-1234"
- Cross-platform support (Windows, macOS, Linux)
- Both library and CLI interfaces
- FetchContent compatible for easy integration
- Custom word list support

## Quick Start

### CLI Usage

```bash
# Generate one name
./names
# Output: selfish-change

# Generate 5 names
./names 5

# Generate names with 4-digit numbers
./names --number
# Output: selfish-change-1234

# Generate multiple numbered names
./names 3 --number

# Show version
./names --version
# Output: names 0.1.0
```

### Library Usage

```cpp
#include <names/names.h>
#include <names/version.h>
#include <iostream>

int main() {
    // Version information
    std::cout << "Names library version: " << names::version() << std::endl;
    
    // Simple usage
    std::cout << names::generate() << std::endl;           // "happy-dog"
    std::cout << names::generate_numbered() << std::endl;  // "clever-fox-1234"
    
    // Using Generator class for more control
    names::Generator generator;
    for (int i = 0; i < 5; ++i) {
        std::cout << generator.next() << std::endl;
    }
    
    // Custom word lists
    std::vector<std::string> adjectives = {"red", "blue", "green"};
    std::vector<std::string> nouns = {"car", "house", "tree"};
    names::Generator custom_generator(adjectives, nouns);
    std::cout << custom_generator.next() << std::endl;  // "red-car"
    
    return 0;
}
```

## Building

### Requirements

- CMake 3.14+
- C++17 compatible compiler
- Internet connection (for downloading dependencies)

### Build Instructions

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Build Options

```bash
# Disable tests
cmake -DNAMES_BUILD_TESTS=OFF ..

# Disable CLI
cmake -DNAMES_BUILD_CLI=OFF ..
```

## Integration with CMake Projects

### Using FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
    names
    GIT_REPOSITORY https://github.com/your-username/names.git
    GIT_TAG main
)

FetchContent_MakeAvailable(names)

target_link_libraries(your_target PRIVATE names::names)
```

### Using find_package (after installation)

```cmake
find_package(names REQUIRED)
target_link_libraries(your_target PRIVATE names::names)
```

## Installation

```bash
mkdir build && cd build
cmake ..
cmake --build .
cmake --install .
```

## Testing

```bash
mkdir build && cd build
cmake ..
cmake --build .
ctest
```

## API Reference

### Generator Class

```cpp
namespace names {
    class Generator {
    public:
        Generator();                              // Random seed, default words
        explicit Generator(unsigned int seed);    // Fixed seed, default words
        Generator(const std::vector<std::string>& adjectives,
                 const std::vector<std::string>& nouns);    // Custom words, random seed
        Generator(const std::vector<std::string>& adjectives,
                 const std::vector<std::string>& nouns,
                 unsigned int seed);                        // Custom words, fixed seed
        
        std::string next();            // Generate "adjective-noun"
        std::string next_numbered();   // Generate "adjective-noun-0000"
        
        static Generator create_default();
    };
}
```

### Convenience Functions

```cpp
namespace names {
    std::string generate();          // Generate one name
    std::string generate_numbered(); // Generate one numbered name
}
```

## License

MIT License - see LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.