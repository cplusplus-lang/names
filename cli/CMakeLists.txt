add_executable(names-cli
    main.cpp
)

target_link_libraries(names-cli
    PRIVATE
        names
        fmt::fmt
)

set_target_properties(names-cli PROPERTIES
    OUTPUT_NAME names
)

install(TARGETS names-cli
    RUNTIME DESTINATION bin
)