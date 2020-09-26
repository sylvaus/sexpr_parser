#pragma once

#include <istream>
#include <ostream>

namespace sexpr::mvp
{
    /**
     * Write the representation of the S-expression described in
     * the text into the output stream
     *
     * @param os output stream to write the S-expression expression to
     * @param text Text containing a description of an S-expression
     * @throw runtime_error if an error is detected in the parsing
     */
    void write_repr(std::ostream &os, const std::string& text);

    /**
     * Write the representation of the S-expression described in
     * the input stream into the output stream
     *
     * @param os output stream to write the S-expression expression to
     * @param is Stream containing a description of an S-expression
     * @throw runtime_error if an error is detected in the parsing
     */
    void write_repr(std::ostream &os, std::istream &is);
}


