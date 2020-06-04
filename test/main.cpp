#include "parser.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <tao/pegtl.hpp>

#include <string_view>

namespace {

constexpr std::string_view str{
        "identifier(arg1 arg2) Another_one() _this_too(Hello) 5not_this()"};

TEST_CASE("Function calls can be parsed") {
    tao::pegtl::memory_input<> in(str.begin(), str.end(), "");
    parser::my_state s = parser::parse(&in);

    REQUIRE(s == parser::my_state{{
            {"identifier", {"arg1", "arg2"}},
            {"Another_one", {}},
            {"_this_too", {"Hello"}}}});
}

} // namespace
