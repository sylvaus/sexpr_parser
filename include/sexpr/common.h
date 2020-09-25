#pragma once

#include <tuple>
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

    std::tuple<bool, int64_t> convert_to_int64(const std::string& text);
    std::tuple<bool, double> convert_to_double(const std::string& text);
}



