#include "../src/Lexer.h"
#include "gtest/gtest.h"

TEST(LexerTest, Tokens) {
    Lexer * lexer = new Lexer("dims.bas");
    EXPECT_EQ(DIM, lexer->getNextToken());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}