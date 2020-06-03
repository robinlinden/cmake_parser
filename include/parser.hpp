#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "grammar.hpp"

#include <tao/pegtl.hpp>

#include <string>
#include <vector>

namespace parser {

namespace peg = tao::pegtl;

struct command_invocation {
    std::string identifier{};
    std::vector<std::string> arguments{};
};

struct my_state {
    std::vector<command_invocation> calls{};
};

template<typename Rule>
struct my_action : peg::nothing<Rule> {};

template<>
struct my_action<grammar::identifier> {
    template<typename Input>
    static void apply(
            const Input &in,
            my_state *s) {
        s->calls.push_back(command_invocation{in.string()});
    }
};

template<>
struct my_action<grammar::argument> {
    template<typename Input>
    static void apply(
            const Input &in,
            my_state *s) {
        s->calls.back().arguments.push_back(in.string());
    }
};

template<typename T>
constexpr my_state parse(T *in) {
    my_state s;
    peg::parse<grammar::file, my_action>(*in, &s);
    return s;
}

} // namespace parser

#endif
