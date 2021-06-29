#include <unistd.h>  /* getopt */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  /* system */
#include <string>
#include <iostream>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <sys/socket.h>
#include <time.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <fstream>
using namespace std;

void pcap_callback(unsigned char* arg, const struct pcap_pkthdr* packet_header, const unsigned char* packet_content);
void terminate_process(int signum);
void show_usage(std::string name);

string bashCommand = "";
string optarg_f = "";
string optarg_i = "";
string saveFilePath = "";

char* dev;
char errbuf[1024];
pcap_t* pcap_handle;
pcap_dumper_t* dumpfp;

int main(int argc, char* argv[])
{
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
            break;
        case 'f':
            optarg_f += string(optarg);
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

    // check if outputfile path is valid.
    saveFilePath = optarg_f + ".pcap";
    ofstream myfile(saveFilePath.c_str());
    if (myfile.is_open())
    {
        myfile.close();
    }
    else
    {
        cout << "ERROR: " << optarg_f << " No such file or directory" << endl;
        return -1;
    }

    // check if interface is valid.
    dev = (char*)optarg_i.c_str();
    pcap_handle = pcap_open_live(dev, 65535, 1, 0, errbuf);

    if (pcap_handle == NULL)
    {
        printf("%s\n", errbuf);
        return 0;
    }

    struct bpf_program filter;
    if (pcap_compile(pcap_handle, &filter, "tcp", 1, 0) < 0) 
    {
        printf("error\n");
        return 0;
    }
    if (pcap_setfilter(pcap_handle, &filter) < 0) 
    {
        printf("error\n");
        return 0;
    }

    dumpfp = pcap_dump_open(pcap_handle, saveFilePath.c_str());

    signal(SIGINT, terminate_process);
    //pcap_loop(pcap_handle,-1,pcap_callback,(unsigned char *)dumpfp);
    pcap_loop(pcap_handle, -1, pcap_callback, (unsigned char*)dumpfp);

    pcap_dump_close(dumpfp);
    pcap_close(pcap_handle);

    //restore parsing data to file.
    bashCommand = "";
    bashCommand += "#/bin/bash \nERROR=$( { sudo tcpdump -r " + optarg_f + ".pcap" + ">" + optarg_f + "; } 2>&1 )";
    system(bashCommand.c_str());

    //delete the ${outputfileName}.pcap
    bashCommand = "";
    bashCommand += "#/bin/bash \nERROR=$( { sudo rm -fr " + optarg_f + ".pcap" + "; } 2>&1 ) ";
    system(bashCommand.c_str());

    return 0;
}


void pcap_callback(unsigned char* arg, const struct pcap_pkthdr* packet_header, const unsigned char* packet_content)
{
    pcap_dump(arg, packet_header, packet_content);
}

void terminate_process(int signum)
{
    pcap_breakloop(pcap_handle);
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

