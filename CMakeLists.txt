cmake_minimum_required(VERSION 3.16) # FetchContent_MakeAvailable

project(some_project LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(pegtl
    GIT_REPOSITORY https://github.com/taocpp/PEGTL
    GIT_TAG 47e878ad4fd72c91253c9d47b6f17e001ca2dfcf # 2.8.3
)
set(PEGTL_BUILD_TESTS OFF CACHE INTERNAL "")
set(PEGTL_BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(pegtl)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE pegtl)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
