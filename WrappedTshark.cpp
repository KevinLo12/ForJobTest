#include "WrappedTshark.h"

WrappedTshark::WrappedTshark(string interface, string outputfileName) :Strategy(interface, outputfileName)
{

}

WrappedTshark::~WrappedTshark()
{

}

void WrappedTshark::run()
{
    //run command
    _bashCommand = "";
    _bashCommand += "#/bin/bash \nERROR=$( { tshark -i " + _interface + " -w " + _outputfileName + ".pcap" + " tcp; } 2>&1 ) ; echo ${ERROR} | sed -e 's/tshark/tcp_sniffer/g'";
    runBashCommand();

    //restore parsing data to file.
    _bashCommand = "";
    _bashCommand += "#/bin/bash \nERROR=$( { sudo tshark -r " + _outputfileName + ".pcap" + ">" + _outputfileName + "; } 2>&1 )";
    runBashCommand();

    //delete the ${outputfileName}.pcap
    _bashCommand = "";
    _bashCommand += "#/bin/bash \nERROR=$( { sudo rm -fr " + _outputfileName + ".pcap" + "; } 2>&1 ) ";
    runBashCommand();
}