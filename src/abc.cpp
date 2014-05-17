#include <unistd.h>
#include <iostream>
#include <string>
#include <getopt.h>
#include "targets/Target.h"
#include "targets/linux/LinuxTarget.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#include "Parser.h"
#endif

int main(int argc, char ** argv)
{
    int optionIndex = 0;
    int c;
    Target * target;
    std::string mainSource = "";
    
    static struct option long_options[] =
    {
		{"target",  required_argument, 0, 't'},
		{"main",  required_argument, 0, 'm'},
		{0, 0, 0, 0}
    };
    
    Parser::init();
    
    while(true)
    {
        c = getopt_long (argc, argv, "t:m:", long_options, &optionIndex);
        if(c == -1) break;
        
        switch(c)
        {            
            case 't':
                if(((std::string)optarg) == "linux")
                {
                    target = new LinuxTarget();
                }
                else
                {
                    std::cerr<<"Please specify a target with the -t switch"<<std::endl;
                }
                break;
                
            case 'm':
                mainSource = (std::string)optarg;
                break;
        }
    }
    
    // Treat the first source file as the main source if none is added
    if(mainSource == "")
    {
        mainSource = argv[optind++];
    }
    
    // Loop through the remaining sources if any
    while(optind < argc)
    {
        target->addOtherSource(argv[optind++]);
    }
    target->addMainSource(mainSource);
    
    target->build();
}
