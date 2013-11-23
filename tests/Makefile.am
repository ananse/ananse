check_LIBRARIES = libgtest.a
libgtest_a_SOURCES = ../gtest/src/gtest-all.cc
libgtest_a_CXXFLAGS = -I../gtest/include -I../gets/include/gtest/internal -I../gtest

check_PROGRAMS = lexer_test
lexer_test_SOURCES = ../src/Lexer.cpp ../src/Lexer.h lexer_test.cpp
lexer_test_CXXFLAGS = -I../gtest/include -I../gtest/include/gtest/internal -L.
lexer_test_LDADD = -lgtest -lpthread


TESTS = lexer_test