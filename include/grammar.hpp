#ifndef GRAMMAR_HPP_
#define GRAMMAR_HPP_

#include <tao/pegtl.hpp>

namespace grammar {

namespace ascii = tao::pegtl::ascii;
using tao::pegtl::identifier_first;
using tao::pegtl::identifier_other;
using tao::pegtl::one;
using tao::pegtl::opt;
using tao::pegtl::plus;
using tao::pegtl::seq;
using tao::pegtl::sor;
using tao::pegtl::star;

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

#endif
