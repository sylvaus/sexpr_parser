#pragma once

#include <string>
#include <vector>
#include <variant>
#include <cstdint>

namespace sexpr::func
{
    enum class SexprType {list, string, integer, floating, symbol, none};

    struct Sexpression
    {
        SexprType type;
        std::variant<int64_t, double, std::string, std::vector<Sexpression>> value;
    };

    /**
     * Parse the given text into an S-expression
     *
     * @param text Text to be parsed
     * @return the parsed S-expression
     * @throw runtime_error if an error is detected in the parsing
     */
    Sexpression parse(const std::string& text);

    /**
     * Parse the given stream into an S-expression
     *
     * @param is stream to be parsed
     * @return the parsed S-expression
     * @throw runtime_error if an error is detected in the parsing
     */
    Sexpression parse(std::istream &is);

    /**
     * Write the given Sexpression representation into the given stream
     *
     * @param os Stream to write the representation into
     * @param sexpression Sexpression to write the representation of
     */
    void write_repr(std::ostream &os, const Sexpression& sexpression);
}

