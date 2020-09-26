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

    Sexpression parse(const std::string& text);
    Sexpression parse(std::istream &is);

    void write_repr(std::ostream &os, const Sexpression& sexpression);
}

