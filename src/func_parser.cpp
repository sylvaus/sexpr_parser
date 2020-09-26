#include <sstream>
#include "sexpr/common.h"
#include "sexpr/func_parser.h"

using sexpr::common::Token;
using sexpr::common::TokenType;

namespace sexpr::func
{
    Sexpression parse(const std::string& text)
    {
        std::istringstream stream{text};
        return parse(stream);
    }


    Token collect_string(std::istream &stream)
    {
        std::string text{'\"'};
        char c;
        bool escaped = false;
        while (stream.get(c) && ((c != '\"') || escaped))
        {
            text += c;
            escaped = '\\' == c;
        }

        if (escaped || (c != '\"'))
        {
            throw std::runtime_error(
                    "Invalid string detected, we reached the end of the stream without a closing quote"
            );
        }

        return Token{TokenType::string, text + c};
    }

    Token collect_symbol_number(std::istream &stream, char first_char)
    {
        std::string text{first_char};
        char c;
        bool escaped = '\\' == first_char;
        while (stream.get(c))
        {
            bool parenthesis = sexpr::common::isparenthesis(c);
            if ((std::isspace(c) || parenthesis) && !escaped)
            {
                if (parenthesis) stream.putback(c);
                break;
            }
            text += c;
            escaped = '\\' == c;
        }

        return Token{TokenType::symbol_number, text};
    }

    Token get_next_token(std::istream &stream)
    {
        char c;
        if (!(stream >> c)) return Token{TokenType::end, ""};

        switch (c)
        {
            case '(':
                return Token{TokenType::open_bracket, "("};
            case ')':
                return Token{TokenType::close_bracket, ")"};
            case '\"':
                return collect_string(stream);
            default:
                return collect_symbol_number(stream, c);
        }
    }

    Sexpression get_atom_from_token(const Token &token)
    {
        if (token.type == TokenType::string)
        {
            return {SexprType::string, token.text};
        }
        if (token.type == TokenType::symbol_number)
        {
            const auto[success_int, value_int] = sexpr::common::convert_to_int64(token.text);
            if (success_int) return {SexprType::integer, value_int};

            const auto[success_double, value_double] = sexpr::common::convert_to_double(token.text);
            if (success_double) return {SexprType::floating, value_double};

            return {SexprType::symbol, token.text};
        }
        throw std::runtime_error("Given token was not an s-expression atom");
    }

    Sexpression parse_list(std::istream &stream)
    {
        bool done = false;
        std::vector<Sexpression> sexprs;
        while (!done)
        {
            const auto token = get_next_token(stream);
            switch (token.type)
            {
                case TokenType::open_bracket:
                    sexprs.push_back(parse_list(stream));
                    break;
                case TokenType::close_bracket:
                    done = true;
                    break;
                case TokenType::symbol_number:
                case TokenType::string:
                    sexprs.push_back(get_atom_from_token(token));
                    break;
                case TokenType::end:
                    throw std::runtime_error("The end was reached before a closing parenthesis could be found");
            }
        }
        return {SexprType::list, sexprs};
    }

    Sexpression parse(std::istream &stream)
    {
        const auto token = get_next_token(stream);
        switch (token.type)
        {
            case TokenType::open_bracket:
                return parse_list(stream);
            case TokenType::close_bracket:
                throw std::runtime_error("A closing bracket cannot start an s-expression");
            case TokenType::symbol_number:
            case TokenType::string:
                return get_atom_from_token(token);
            case TokenType::end:
                return Sexpression{SexprType::none, 0l};
            default:
                throw std::runtime_error("Unhandled token type");
        }
    }

    void write_repr(std::ostream &os, const Sexpression& sexpression, const std::string& indent)
    {
        switch (sexpression.type)
        {
            case SexprType::list:
            {
                const std::string new_indent = indent + sexpr::common::INDENT;
                os << indent << "(\n";
                for (const auto &sub_elem: std::get<std::vector<Sexpression>>(sexpression.value))
                {
                    write_repr(os, sub_elem, new_indent);
                }
                os << indent << ")\n";
                break;
            }
            case SexprType::string:
                os << indent << "String: " << std::get<std::string>(sexpression.value) << "\n";
                break;
            case SexprType::integer:
                os << indent << "Integer: " << std::get<int64_t>(sexpression.value) << "\n";
                break;
            case SexprType::floating:
                os << indent << "Floating: " << std::get<double>(sexpression.value) << "\n";
                break;
            case SexprType::symbol:
                os << indent << "Symbol: " << std::get<std::string>(sexpression.value) << "\n";
                break;
            case SexprType::none:
                break;
        }

    }

    void write_repr(std::ostream &os, const Sexpression& sexpression)
    {
        write_repr(os, sexpression, "");
    }
}
