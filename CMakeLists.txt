cmake_minimum_required(VERSION 3.16)

project(some_project LANGUAGES CXX)

add_subdirectory(third_party)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include/)
target_link_libraries(${PROJECT_NAME} INTERFACE pegtl)

enable_testing()

add_subdirectory(example)
add_subdirectory(test)
