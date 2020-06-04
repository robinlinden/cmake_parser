#include "parser.hpp"

#include <tao/pegtl.hpp>

#include <iostream>

namespace {

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
    if (argc != 2) {
        return 1;
    }

    tao::pegtl::argv_input<> in(argv, 1);
    parser::my_state s = parser::parse(&in);
    std::cout << s;

    return 0;
}
