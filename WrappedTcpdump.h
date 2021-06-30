#pragma once
#include "Strategy.h"

class WrappedTcpdump : public Strategy
{
public:
    WrappedTcpdump(string interface, string outputfileName);
    ~WrappedTcpdump();
    void run();
};