#include <sstream>
#include "sexpr/common.h"
#include "sexpr/mvp_parser.h"

namespace sexpr::mvp
{
    void write_string(std::ostream &os, std::istream &is)
    {
        os << "String: \"";
        char c;
        bool escaped = false;
        while (is.get(c) && ((c != '\"') || escaped))
        {
            os << c;
            escaped = '\\' == c;
        }

        if (escaped || (c != '\"'))
        {
            throw std::runtime_error(
                    "Invalid string detected, we reached the end of the stream without a closing quote"
            );
        }
        os << c << '\n';
    }

    void write_symbol_number(std::ostream & os, std::istream &is, char first_char)
    {
        std::string text{first_char};
        char c;
        bool escaped = '\\' == first_char;
        while (is.get(c))
        {
            bool parenthesis = sexpr::common::isparenthesis(c);
            if ((std::isspace(c) || parenthesis) && !escaped)
            {
                if (parenthesis) is.putback(c);
                break;
            }
            text += c;
            escaped = '\\' == c;
        }

        const auto[success_int, value_int] = sexpr::common::convert_to_int64(text);
        if (success_int)
        {
            os << "Integer: " << value_int << "\n";
            return;
        }
        const auto[success_double, value_double] = sexpr::common::convert_to_double(text);
        if (success_double)
        {
            os << "Floating: " << value_double << "\n";
            return;
        }

        os << "Symbol: " << text << "\n";
    }

    void write_repr(std::ostream &os, const std::string& text)
    {
        std::istringstream stream{text};
        return write_repr(os, stream);
    }

    void write_repr(std::ostream &os, std::istream &is)
    {
        char c;
        std::string indent;
        while (is >> c)
        {
            switch (c)
            {
                case '(':
                    os << indent << "(\n";
                    indent += sexpr::common::INDENT;
                    break;
                case ')':
                    indent.erase(indent.end() - sexpr::common::INDENT.size());
                    os << indent << ")\n";
                    break;
                case '\"':
                    os << indent;
                    write_string(os, is);
                    break;
                default:
                    os << indent;
                    write_symbol_number(os, is, c);
            }
        }
    }

}