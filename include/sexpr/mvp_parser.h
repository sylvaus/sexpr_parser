#pragma once

#include <istream>
#include <ostream>

namespace sexpr::mvp
{
    void write_repr(std::ostream &os, const std::string& text);
    void write_repr(std::ostream &os, std::istream &is);
}


