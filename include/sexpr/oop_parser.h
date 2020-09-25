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

        sexpr::common::Token next();

    private:
        std::istream &stream;

        sexpr::common::Token collect_string();

        sexpr::common::Token collect_symbol_number(char first_char);


    };

    class Sexpression
    {
    public:
        virtual void write_repr(std::ostream &stream, const std::string &indent) const = 0;

        virtual ~Sexpression() = default;
    };

    std::ostream &operator<<(std::ostream &os, const Sexpression &expression);

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


    std::shared_ptr<Sexpression> parse(Tokenizer &tokenizer);

    std::shared_ptr<Sexpression> parse(std::istream &stream);

    std::shared_ptr<Sexpression> parse(const std::string &text);
}

