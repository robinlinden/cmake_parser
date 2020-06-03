include(FetchContent)

FetchContent_Declare(pegtl
    GIT_REPOSITORY https://github.com/taocpp/PEGTL
    GIT_TAG 47e878ad4fd72c91253c9d47b6f17e001ca2dfcf # 2.8.3
)
set(PEGTL_BUILD_TESTS OFF CACHE INTERNAL "")
set(PEGTL_BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(pegtl)
