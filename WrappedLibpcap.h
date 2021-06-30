#pragma once
#include "Strategy.h"
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <sys/socket.h>
#include <time.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <fstream>

class WrappedLibpcap : public Strategy
{
public:
    string saveFilePath;
    char* dev;
    char errbuf[1024];
    pcap_dumper_t* dumpfp;
    struct bpf_program filter;

    WrappedLibpcap(string interface, string outputfileName);
    ~WrappedLibpcap();
    void run();
    
    // friend fuction
    friend void pcap_callback(unsigned char* arg, const struct pcap_pkthdr* packet_header, const unsigned char* packet_content);
    friend void terminate_process(int signum);
};