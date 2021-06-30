#include "WrappedTcpdump.h"

WrappedTcpdump::WrappedTcpdump(string interface, string outputfileName) :Strategy(interface, outputfileName)
{

}

WrappedTcpdump::~WrappedTcpdump()
{

}

void WrappedTcpdump::run()
{
    //run command
    _bashCommand = "";
    _bashCommand += "#/bin/bash \nERROR=$( { tcpdump -i " + _interface + " -w " + _outputfileName + ".pcap" + "; } 2>&1 ) ; echo ${ERROR} | sed -e 's/tcpdump/tcp_sniffer/g'";;
    runBashCommand();

    //restore parsing data to file.
    _bashCommand = "";
    _bashCommand += "#/bin/bash \nERROR=$( { sudo tcpdump -r " + _outputfileName + ".pcap" + ">" + _outputfileName + "; } 2>&1 )";
    runBashCommand();

    //delete the ${outputfileName}.pcap
    _bashCommand = "";
    _bashCommand += "#/bin/bash \nERROR=$( { sudo rm -fr " + _outputfileName + ".pcap" + "; } 2>&1 ) ";
    runBashCommand();
}

