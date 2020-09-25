#include "gtest/gtest.h"
#include "constants.h"
#include "sexpr/oop_parser.h"

using sexpr::oop::parse;

namespace
{
    TEST(OOPParser, NominalCase)
    {
        std::ostringstream oss;
        oss << *parse(NOMINAL_INPUT);
        EXPECT_EQ(NOMINAL_EXPECTED_OUTPUT, oss.str());
    }

    TEST(OOPParser, SingleSymbol)
    {
        std::ostringstream oss;
        oss << *parse("abcde\\ sdf!#$$\n");
        EXPECT_EQ("Symbol: abcde\\ sdf!#$$\n", oss.str());
    }

    TEST(OOPParser, SingleString)
    {
        std::ostringstream oss;
        oss << *parse("\"sdfj fgl gdgjkj_uhj2345hgjh \\\"  fd\"\n");
        EXPECT_EQ("String: \"sdfj fgl gdgjkj_uhj2345hgjh \\\"  fd\"\n", oss.str());
    }

    TEST(OOPParser, Integer)
    {
        std::ostringstream oss;
        oss << *parse("12348784548\n");
        EXPECT_EQ("Integer: 12348784548\n", oss.str());
    }

    TEST(OOPParser, NegativeInteger)
    {
        std::ostringstream oss;
        oss << *parse("-712384887\n");
        EXPECT_EQ("Integer: -712384887\n", oss.str());
    }

    TEST(OOPParser, Floating)
    {
        std::ostringstream oss;
        oss << *parse("12.4745\n");
        EXPECT_EQ("Floating: 12.4745\n", oss.str());
    }

    TEST(OOPParser, Empty)
    {
        std::ostringstream oss;
        oss << *parse("");
        EXPECT_EQ("", oss.str());
    }
}