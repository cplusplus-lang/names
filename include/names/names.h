#pragma once

#include "names/generator.h"
#include "names/words.h"

namespace names {

inline std::string generate() {
    static Generator generator = Generator::create_default();
    return generator.next();
}

inline std::string generate_numbered() {
    static Generator generator = Generator::create_default();
    return generator.next_numbered();
}

} // namespace names