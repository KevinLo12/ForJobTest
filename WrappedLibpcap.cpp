#include "WrappedLibpcap.h"
#include <iostream>
using namespace std;

void pcap_callback(unsigned char* arg, const struct pcap_pkthdr* packet_header, const unsigned char* packet_content);
void terminate_process(int signum);
pcap_t* pcap_handle;

WrappedLibpcap::WrappedLibpcap(string interface, string outputfileName) :Strategy(interface, outputfileName)
{

}

WrappedLibpcap::~WrappedLibpcap()
{

}

void WrappedLibpcap::run()
{
    // check if outputfile path is valid.
    saveFilePath = _outputfileName + ".pcap";
    ofstream myfile(saveFilePath.c_str());
    if (myfile.is_open())
    {
        myfile.close();
    }
    else
    {
        cout << "ERROR: " << _outputfileName << " No such file or directory" << endl;
        return;
    }

    // check if interface is valid.
    dev = (char*)_interface.c_str();
    pcap_handle = pcap_open_live(dev, 65535, 1, 0, errbuf);

    if (pcap_handle == NULL)
    {
        printf("%s\n", errbuf);
        return;
    }

    if (pcap_compile(pcap_handle, &filter, "tcp", 1, 0) < 0)
    {
        printf("error\n");
        return;
    }
    if (pcap_setfilter(pcap_handle, &filter) < 0)
    {
        printf("error\n");
        return;
    }

    dumpfp = pcap_dump_open(pcap_handle, saveFilePath.c_str());

    signal(SIGINT, terminate_process);
    pcap_loop(pcap_handle, -1, pcap_callback, (unsigned char*)dumpfp);

    pcap_dump_close(dumpfp);
    pcap_close(pcap_handle);

    //restore parsing data to file.
    _bashCommand = "";
    _bashCommand += "#/bin/bash \nERROR=$( { sudo tcpdump -r " + _outputfileName + ".pcap" + ">" + _outputfileName + "; } 2>&1 )";
    runBashCommand();

    //delete the ${outputfileName}.pcap
    _bashCommand = "";
    _bashCommand += "#/bin/bash \nERROR=$( { sudo rm -fr " + _outputfileName + ".pcap" + "; } 2>&1 ) ";
    runBashCommand();
}

void pcap_callback(unsigned char* arg, const struct pcap_pkthdr* packet_header, const unsigned char* packet_content)
{
    pcap_dump(arg, packet_header, packet_content);
}

void terminate_process(int signum)
{
    pcap_breakloop(pcap_handle);
}