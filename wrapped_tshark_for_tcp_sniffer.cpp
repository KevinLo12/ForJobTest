#include <unistd.h>  /* getopt */
#include <stdio.h>
#include <stdlib.h>  /* system */
#include <string>
#include <iostream>
using namespace std;

void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " -i interface -f outputfile \n"
        << "Options:\n"
        << "\t-h Show this help message\n"
        << "\t-i interface\n"
        << "\t-f outputfile\n"
        << std::endl;
}

int main(int argc, char* argv[])
{
    string bashCommand = "";
    string optarg_f = "";
    string optarg_i = "";
    bashCommand += "#/bin/bash \nERROR=$( { tshark";

    int cmd_opt = 0;

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
            optarg_i += string(optarg);
            bashCommand += " -i " + string(optarg);
            break;
        case 'f':
            optarg_f += string(optarg);
            bashCommand += " -w " + string(optarg) + ".pcap";
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
    if (optarg_f == "" || optarg_i == "")
    {
        show_usage(argv[0]);
        return -1;
    }

    bashCommand += " tcp; } 2>&1 ) ; echo ${ERROR} | sed -e 's/tshark/tcp_sniffer/g'";
    system(bashCommand.c_str());

    //restore parsing data to file.
    bashCommand = "";
    bashCommand += "#/bin/bash \nERROR=$( { sudo tshark -r " + optarg_f + ".pcap" + ">" + optarg_f + "; } 2>&1 )";
    system(bashCommand.c_str());

    //delete the ${outputfileName}.pcap
    bashCommand = "";
    bashCommand += "#/bin/bash \nERROR=$( { sudo rm -fr " + optarg_f + ".pcap" + "; } 2>&1 ) ";
    system(bashCommand.c_str());
    return 0;
}
