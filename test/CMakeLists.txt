project(test_some_project LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main.cpp
)

include(Catch)
catch_discover_tests(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Catch2
        pegtl
        some_project
)
