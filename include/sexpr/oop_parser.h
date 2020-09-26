#pragma once

#include <memory>
#include <vector>
#include <sstream>

#include "sexpr/common.h"

namespace sexpr::oop
{
    class Tokenizer
    {
    public:
        explicit Tokenizer(std::istream &stream);

        /**
         * @return next token in the stream; TokenType::end is returned when end is reached
         */
        sexpr::common::Token next();

    private:
        std::istream &stream;


        sexpr::common::Token collect_string();
        sexpr::common::Token collect_symbol_number(char first_char);


    };

    class Sexpression
    {
    public:
        /**
         * Write the representation of the S-expression to the stream
         *
         * @param stream Stream to write the S-expression representation to
         */
        void write_repr(std::ostream &stream) const;

        /**
         * Write the representation of the S-expression to the stream indented with the given indentation
         *
         * @param stream Stream to write the S-expression representation to
         */
        virtual void write_repr(std::ostream &stream, const std::string &indent) const = 0;

        virtual ~Sexpression() = default;
    };

    std::ostream &operator<<(std::ostream &os, const Sexpression &expression);

    class Empty : public Sexpression
    {
    public:
        explicit Empty();

        void write_repr(std::ostream &stream, const std::string &indent) const override;
    };

    class String : public Sexpression
    {
    public:
        explicit String(std::string text);

        void write_repr(std::ostream &stream, const std::string &indent) const override;

    protected:
        std::string text;
    };

    class Symbol : public Sexpression
    {
    public:
        explicit Symbol(std::string text);

        void write_repr(std::ostream &stream, const std::string &indent) const override;

    protected:
        std::string text;
    };

    class Integer : public Sexpression
    {
    public:
        explicit Integer(int64_t value);

        void write_repr(std::ostream &stream, const std::string &indent) const override;

    protected:
        int64_t value;
    };

    class Floating : public Sexpression
    {
    public:
        explicit Floating(double value);

        void write_repr(std::ostream &stream, const std::string &indent) const override;

    protected:
        double value;
    };

    class List : public Sexpression
    {
    public:

        explicit List(std::vector<std::shared_ptr<Sexpression>> sexprs);

    public:
        void write_repr(std::ostream &stream, const std::string &indent) const override;

    protected:
        std::vector<std::shared_ptr<Sexpression>> sexprs;
    };


    /**
     * Parse the S-expression text in the input stream
     *
     * @param stream Input stream containing the S-expression text
     * @return Shared pointer to the parsed S-expression
     * @throw runtime_error if an error is detected in the parsing
     */
    std::shared_ptr<Sexpression> parse(std::istream &stream);

    /**
     * Parse the S-expression text
     *
     * @param text Text containing the S-expression
     * @return Shared pointer to the parsed S-expression
     * @throw runtime_error if an error is detected in the parsing
     */
    std::shared_ptr<Sexpression> parse(const std::string &text);
}

