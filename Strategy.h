#pragma once
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  /* system */
using namespace std;

class Strategy
{
protected:
    string _interface;
    string _outputfileName;
    string _bashCommand;
public:
    Strategy(string interface, string outputfileName) : _interface(interface), _outputfileName(outputfileName) { _bashCommand = ""; }
    virtual ~Strategy() {}
    virtual void run() = 0;
    void runBashCommand() { system(_bashCommand.c_str()); }
};