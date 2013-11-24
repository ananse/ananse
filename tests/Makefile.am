if HAVE_GTEST
    check_LIBRARIES = libgtest.a
    libgtest_a_SOURCES = $(GTEST)/src/gtest-all.cc
    libgtest_a_CXXFLAGS = -I$(GTEST)/include -I$(GTEST)/include/gtest/internal -I$(GTEST)

    check_PROGRAMS = lexer_test
    lexer_test_SOURCES = ../src/Lexer.cpp ../src/Lexer.h lexer_test.cpp
    lexer_test_CXXFLAGS = -I$(GTEST)/include -I$(GTEST)/include/gtest/internal -L.
    lexer_test_LDADD = -lgtest -lpthread

    TESTS = lexer_test
endif
