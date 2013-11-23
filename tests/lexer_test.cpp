#include "../src/Lexer.h"
#include "gtest/gtest.h"

TEST(LexerTest, Tokens) {
    Lexer * lexer = new Lexer("tokens.bas");
    EXPECT_EQ(NEW_LINE, lexer->getNextToken());
    EXPECT_EQ(INTEGER, lexer->getNextToken());
    EXPECT_EQ(12, lexer->getIntegerValue());
    EXPECT_EQ(PLUS, lexer->getNextToken());
    EXPECT_EQ(MINUS, lexer->getNextToken());
    EXPECT_EQ(MULTIPLY, lexer->getNextToken());
    EXPECT_EQ(DIVIDE, lexer->getNextToken());
    EXPECT_EQ(EQUALS, lexer->getNextToken());
    EXPECT_EQ(COMMA, lexer->getNextToken());
    EXPECT_EQ(IDENTIFIER, lexer->getNextToken());
    EXPECT_EQ("hello", lexer->getIdentifierValue());
    EXPECT_EQ(BRACKET_OPEN, lexer->getNextToken());
    EXPECT_EQ(BRACKET_CLOSE, lexer->getNextToken());
    EXPECT_EQ(DIM, lexer->getNextToken());
    EXPECT_EQ(DIM, lexer->getNextToken());
    EXPECT_EQ(DIM, lexer->getNextToken());
    EXPECT_EQ(AS, lexer->getNextToken());
    EXPECT_EQ(PERCENT, lexer->getNextToken());
    EXPECT_EQ(AMPERSAND, lexer->getNextToken());
    EXPECT_EQ(UNKNOWN, lexer->getNextToken());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

