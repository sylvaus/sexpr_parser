#include <stdexcept>
#include "sexpr/common.h"

namespace sexpr::common
{
    const std::string INDENT{'\t'};

    bool isparenthesis(char c)
    {
        return c == '(' || c == ')';
    }

    std::tuple<bool, int64_t> convert_to_int64(const std::string& text)
    {
        std::size_t pos;
        try
        {
            int64_t value = std::stol(text, &pos);
            if (pos == text.size())  return {true, value};
        }
        catch (std::invalid_argument &)
        {}
        catch (std::out_of_range &)
        {}
        return {false, 0};

    }

    std::tuple<bool, double> convert_to_double(const std::string& text)
    {
        std::size_t pos;
        try
        {
            double value = std::stod(text, &pos);
            if (pos == text.size())  return {true, value};
        }
        catch (std::invalid_argument &)
        {}
        catch (std::out_of_range &)
        {}
        return {false, 0};
    }
}

