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

    /**
     * @param c  character to check if it is a parenthesis
     * @return True if c is a parenthesis
     */
    bool isparenthesis(char c);

    /**
     * Try to convert the given text to int64
     *
     * @param text Text to convert to int64
     * @return a tuple (success, value) where success is True if the conversion was successful else false
     *      and value is the converted value if the conversion was successful
     */
    std::tuple<bool, int64_t> convert_to_int64(const std::string& text);

    /**
     * Try to convert the given text to double
     *
     * @param text Text to convert to double
     * @return a tuple (success, value) where success is True if the conversion was successful else false
     *      and value is the converted value if the conversion was successful
     */
    std::tuple<bool, double> convert_to_double(const std::string& text);
}



