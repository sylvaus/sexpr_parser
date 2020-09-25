#include <algorithm>
#include "sexpr/oop_parser.h"

using sexpr::common::TokenType;
using sexpr::common::Token;

namespace sexpr::oop
{

    Tokenizer::Tokenizer(std::istream &stream) : stream(stream)
    {}

    Token Tokenizer::Tokenizer::next()
    {
        char c;
        while (stream && std::isspace(c = stream.get()));
        if (!stream) return Token{TokenType::end, ""};


        switch (c)
        {
            case '(':
                return Token{TokenType::open_bracket, "("};
            case ')':
                return Token{TokenType::close_bracket, ")"};
            case '\"':
                return collect_string();
            default:
                return collect_symbol_number(c);
        }
    }


    Token Tokenizer::collect_string()
    {
        std::string text{'\"'};
        while (stream)
        {
            text += static_cast<char>(stream.get());
            if ((text[text.size() - 1] == '\"') && (text[text.size() - 2] != '\\'))
            {
                break;
            }
        }

        if ((text[text.size() - 1] != '\"') || (text[text.size() - 2] == '\\'))
        {
            throw std::runtime_error(
                    "Invalid string detected, we reached the end of the stream without a closing quote"
            );
        }

        return Token{TokenType::string, text};
    }

    Token Tokenizer::collect_symbol_number(char first_char)
    {
        std::string text{first_char};
        char c;
        bool escaped = false;
        while (stream)
        {
            c = stream.get();
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


    std::ostream &operator<<(std::ostream &os, const Sexpression &expression)
    {
        expression.write_repr(os, "");
        return os;
    }


    String::String(std::string text) : text{std::move(text)}
    {}

    void String::write_repr(std::ostream &stream, const std::string &indent) const
    {
        stream << indent << "String: " << text << '\n';
    }


    Symbol::Symbol(std::string text) : text{std::move(text)}
    {}

    void Symbol::write_repr(std::ostream &stream, const std::string &indent) const
    { stream << indent << "Symbol: " << text << '\n'; }


    Integer::Integer(int64_t value) : value{value}
    {}

    void Integer::write_repr(std::ostream &stream, const std::string &indent) const
    {
        stream << indent << "Integer: " << value << '\n';
    }


    Floating::Floating(double value) : value{value}
    {}

    void Floating::write_repr(std::ostream &stream, const std::string &indent) const
    {
        stream << indent << "Floating: " << value << '\n';
    }


    List::List(std::vector<std::shared_ptr<Sexpression>> sexprs) : sexprs(std::move(sexprs))
    {}


    void List::write_repr(std::ostream &stream, const std::string &indent) const
    {
        stream << indent << "(\n";
        const std::string new_indent = indent + sexpr::common::INDENT;
        std::for_each(
                sexprs.cbegin(), sexprs.cend(),
                [&](const auto &atom) {atom->write_repr(stream, new_indent);}
        );
        stream << indent << ")\n";
    }


    std::shared_ptr<Sexpression> get_atom_from_token(const Token &token)
    {
        if (token.type == TokenType::string)
        {
            return std::make_shared<String>(token.text);
        }
        if (token.type == TokenType::symbol_number)
        {
            std::size_t pos;
            try
            {
                int64_t value = std::stol(token.text, &pos);
                if (pos == token.text.size())  return std::make_shared<Integer>(value);
            }
            catch (std::invalid_argument &)
            {}
            try
            {
                double value = std::stod(token.text, &pos);
                if (pos == token.text.size())  return std::make_shared<Floating>(value);
            }
            catch (std::invalid_argument &)
            {}
            //TODO: the out of range exception is let go but adding a proper handling could be welcomed
            return std::make_shared<Symbol>(token.text);
        }
        throw std::runtime_error("Given token was not an s-expression atom");
    }

    std::shared_ptr<Sexpression> parse_list(Tokenizer &tokenizer)
    {
        bool done = false;
        std::vector<std::shared_ptr<Sexpression>> sexprs;
        while (!done)
        {
            const auto token = tokenizer.next();
            switch (token.type)
            {
                case TokenType::open_bracket:
                    sexprs.push_back(parse_list(tokenizer));
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
        return std::make_shared<List>(sexprs);
    }

    std::shared_ptr<Sexpression> parse(Tokenizer &tokenizer)
    {
        const auto token = tokenizer.next();
        switch (token.type)
        {
            case TokenType::open_bracket:
                return parse_list(tokenizer);
            case TokenType::close_bracket:
                throw std::runtime_error("A closing bracket cannot start an s-expression");
            case TokenType::symbol_number:
            case TokenType::string:
                return get_atom_from_token(token);
            case TokenType::end:
                return nullptr;
            default:
                throw std::runtime_error("Unhandled token type");
        }
    }

    std::shared_ptr<Sexpression> parse(std::istream &stream)
    {
        Tokenizer tokenizer{stream};
        return parse(tokenizer);
    }

    std::shared_ptr<Sexpression> parse(const std::string &text)
    {
        std::istringstream stream{text};
        return parse(stream);
    }

}