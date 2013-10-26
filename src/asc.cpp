#include <iostream>
#include <unistd.h>
#include <iostream>
#include <string>
#include "Parser.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


int main(int argc, char ** argv)
{
    Parser parser;
    std::string line;
    getline(std::cin, line);
    parser.setSource(line);
    parser.parse();
}
