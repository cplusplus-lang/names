CPMAddPackage("gh:catchorg/Catch2@3.4.0")

add_executable(names-tests
    test_generator.cpp
)

target_link_libraries(names-tests
    PRIVATE
        names
        Catch2::Catch2WithMain
)

include(CTest)
add_test(NAME names-tests COMMAND names-tests)