#include "gtest/gtest.h"
#include "constants.h"
#include "sexpr/oop_parser.h"
#include "sexpr/mvp_parser.h"
#include "sexpr/func_parser.h"

namespace
{
    using ::testing::TestWithParam;
    using ::testing::Values;

    class AllParsersTests : public TestWithParam<std::function<void(std::ostream &os, const std::string& text)>>
    {

    };

    TEST_P(AllParsersTests, NominalCase)
    {
        auto func = GetParam();
        std::ostringstream oss;
        func(oss, NOMINAL_INPUT);
        EXPECT_EQ(NOMINAL_EXPECTED_OUTPUT, oss.str());
    }

    TEST_P(AllParsersTests, SingleSymbol)
    {
        auto func = GetParam();
        std::ostringstream oss;
        func(oss, "abcde\\ sdf!#$$\n");
        EXPECT_EQ("Symbol: abcde\\ sdf!#$$\n", oss.str());
    }

    TEST_P(AllParsersTests, SingleString)
    {
        auto func = GetParam();
        std::ostringstream oss;
        func(oss, "\"sdfj fgl gdgjkj_uhj2345hgjh \\\"  fd\"\n");
        EXPECT_EQ("String: \"sdfj fgl gdgjkj_uhj2345hgjh \\\"  fd\"\n", oss.str());
    }

    TEST_P(AllParsersTests, Integer)
    {
        auto func = GetParam();
        std::ostringstream oss;
        func(oss, "12348784548\n");
        EXPECT_EQ("Integer: 12348784548\n", oss.str());
    }

    TEST_P(AllParsersTests, NegativeInteger)
    {
        auto func = GetParam();
        std::ostringstream oss;
        func(oss, "-712384887\n");
        EXPECT_EQ("Integer: -712384887\n", oss.str());
    }

    TEST_P(AllParsersTests, Floating)
    {
        auto func = GetParam();
        std::ostringstream oss;
        func(oss, "12.4745\n");
        EXPECT_EQ("Floating: 12.4745\n", oss.str());
    }

    TEST_P(AllParsersTests, Empty)
    {
        auto func = GetParam();
        std::ostringstream oss;
        func(oss, "");
        EXPECT_EQ("", oss.str());
    }

    TEST_P(AllParsersTests, NonClosedString)
    {
        auto func = GetParam();
        std::ostringstream oss;

        EXPECT_THROW({func(oss, "(() (a \"b\" x) (\"dfjsdf jksdjfk))");} , std::runtime_error);
    }

    INSTANTIATE_TEST_SUITE_P(AllPrasers, AllParsersTests, Values(
            [](std::ostream &os, const std::string& text) {os << *sexpr::oop::parse(text);},
            [](std::ostream &os, const std::string& text) {sexpr::mvp::write_repr(os, text);},
            [](std::ostream &os, const std::string& text) {sexpr::func::write_repr(os, sexpr::func::parse(text));}
    ));
}