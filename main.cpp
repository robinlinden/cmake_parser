#include <tao/pegtl.hpp>

#include <iostream>
#include <string_view>

using namespace tao::pegtl;

namespace grammar {

struct lparen : one<'('> {};
struct rparen : one<')'> {};

struct space : plus<one<' ', '\t'>> {};
struct newline : one<'\n'> {};
struct identifier : seq<identifier_first, star<identifier_other>> {};

struct line_ending : newline {};

struct separation : sor<space, line_ending> {};

struct unquoted_argument :
        plus<ascii::not_one<'(', ')', '#', '\\', '\'', '>', ' ', '\t'>> {};
struct argument : unquoted_argument {};
struct arguments;
struct separated_arguments :
        sor<seq<plus<separation>, opt<argument>>,
            seq<star<separation>, lparen, arguments, rparen>> {};
struct arguments : seq<opt<argument>, star<separated_arguments>> {};

struct command_invocation :
        seq<star<space>, identifier, star<space>, one<'('>, arguments, one<')'>> {};

struct file_element : seq<command_invocation> {};

struct file : star<file_element> {};

} // namespace grammar

namespace {

struct my_state {
    std::vector<std::string> identifiers{};
    std::vector<std::string> arguments{};
};

template<typename Rule>
struct my_action : nothing<Rule> {};

template<>
struct my_action<grammar::identifier> {
    template<typename Input>
    static void apply(
            const Input &in,
            my_state *s) {
        s->identifiers.push_back(in.string());
    }
};

template<>
struct my_action<grammar::argument> {
    template<typename Input>
    static void apply(
            const Input &in,
            my_state *s) {
        s->arguments.push_back(in.string());
    }
};

constexpr std::string_view str{
        "identifier(arg1 arg2) Another_one() _this_too(Hello) 5not_this()"};

} // namespace

int main(int argc, char **argv) {
    my_state s;

    if (argc > 1) {
        argv_input<> in(argv, 1);
        parse<grammar::file, my_action>(in, &s);
    } else {
        memory_input<> in(str.begin(), str.end(), "");
        parse<grammar::file, my_action>(in, &s);
    }

    std::cout << "Identifiers:";
    for (const auto &i : s.identifiers) {
        std::cout << ' ' << i << ',';
    }

    std::cout << '\n' << "Arguments:";

    for (const auto &i : s.arguments) {
        std::cout << ' ' << i << ',';
    }

    std::cout << std::endl;

    return 0;
}
