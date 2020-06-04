include(FetchContent)

FetchContent_Declare(catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG b1b5cb812277f367387844aab46eb2d3b15d03cd # 2.12.2
)
set(CATCH_BUILD_TESTING OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(catch2)
