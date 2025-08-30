add_library(names
    generator.cpp
)

target_include_directories(names
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(names
    PUBLIC
        fmt::fmt
)

target_compile_features(names PUBLIC cxx_std_17)

# Install targets
install(TARGETS names
    EXPORT namesTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/../include/names/version.h
    DESTINATION include/names
)

install(EXPORT namesTargets
    FILE namesTargets.cmake
    NAMESPACE names::
    DESTINATION lib/cmake/names
)

# Create config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "namesConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/namesConfig.cmake.in
    "namesConfig.cmake"
    INSTALL_DESTINATION lib/cmake/names
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/namesConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/namesConfigVersion.cmake"
    DESTINATION lib/cmake/names
)