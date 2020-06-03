#include "parser.hpp"

#include <tao/pegtl.hpp>

#include <iostream>
#include <string_view>

namespace {

constexpr std::string_view str{
        "identifier(arg1 arg2) Another_one() _this_too(Hello) 5not_this()"};

std::ostream& operator<<(std::ostream &os, const parser::my_state &s) {
    for (const auto &call : s.calls) {
        os << call.identifier;
        for (const auto &arg : call.arguments) {
            os << " " << arg;
        }
        os << '\n';
    }

    return os;
}

} // namespace

int main(int argc, char **argv) {
    parser::my_state s;

    if (argc > 1) {
        tao::pegtl::argv_input<> in(argv, 1);
        s = parser::parse(&in);
    } else {
        tao::pegtl::memory_input<> in(str.begin(), str.end(), "");
        s = parser::parse(&in);
    }

    std::cout << s;

    return 0;
}
