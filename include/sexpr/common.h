#pragma once

#include <string>

namespace sexpr::common
{
    extern const std::string INDENT;

    enum class TokenType
    {
        open_bracket, close_bracket, symbol_number, string, end
    };

    struct Token
    {
        TokenType type;
        std::string text;
    };

    bool isparenthesis(char c);
}



