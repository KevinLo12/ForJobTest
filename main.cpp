#include "WrappedTcpdump.h"
#include "WrappedTshark.h"
#include "WrappedLibpcap.h"
#include <iostream>
#include <unistd.h>  /* getopt */
using namespace std;

void show_usage(std::string name);

int main(int argc, char* argv[])
{
    int cmd_opt = 0;
    string outputfileName = "";
    string interface = "";

    if (argc != 5)
    {
        show_usage(argv[0]);
        return 1;
    }

    while (1)
    {
        cmd_opt = getopt(argc, argv, "hi:f:");

        /* End condition always first */
        if (cmd_opt == -1)
        {
            break;
        }

        /* Lets parse */
        switch (cmd_opt)
        {
            /* No args */
        case 'h':
            show_usage(argv[0]);
            break;

            /* Single arg */
        case 'i':
            interface += string(optarg);
            break;
        case 'f':
            outputfileName += string(optarg);
            break;

            /* Error handle: Mainly missing arg or illegal option */
        case '?':
            fprintf(stderr, "Illegal option:-%c\n", isprint(optopt) ? optopt : '#');
            return -1;
        default:
            fprintf(stderr, "Not supported option\n");
            return -1;
        }
    }

    // check Single arg for -i -f 
    if (outputfileName == "" || interface == "")
    {
        show_usage(argv[0]);
        return -1;
    }

    Strategy* strategy = new WrappedTcpdump(interface, outputfileName);
    //Strategy* strategy = new WrappedTshark(interface, outputfileName);
    //Strategy* strategy = new WrappedLibpcap(interface, outputfileName);

    strategy->run();
}

void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " -i interface -f outputfile \n"
        << "Options:\n"
        << "\t-h Show this help message\n"
        << "\t-i interface\n"
        << "\t-f outputfile\n"
        << std::endl;
}