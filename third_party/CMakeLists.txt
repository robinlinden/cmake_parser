add_subdirectory(catch2)
FetchContent_GetProperties(catch2 SOURCE_DIR catch2_SOURCE_DIR)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)

add_subdirectory(pegtl)
