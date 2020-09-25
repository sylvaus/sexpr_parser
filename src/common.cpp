#include "sexpr/common.h"

namespace sexpr::common
{
    const std::string INDENT{'\t'};

    bool isparenthesis(char c)
    {
        return c == '(' || c == ')';
    }
}

