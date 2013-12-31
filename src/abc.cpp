#include <unistd.h>
#include <iostream>
#include <string>
#include <getopt.h>
#include "targets/Target.h"
#include "targets/linux/LinuxTarget.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

int main(int argc, char ** argv)
{
    int optionIndex = 0;
    int c;
    Target * target;
    static struct option long_options[] =
    {
		{"target",  required_argument, 0, 't'},
		{"main",  required_argument, 0, 'm'},
		{0, 0, 0, 0}
    };
    
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
                break;
                
            case 'm':
                break;
        }
    }
    
    while(optind < argc)
    {
        target->addSource(argv[optind++], true);
    }
    
    target->build();
}
