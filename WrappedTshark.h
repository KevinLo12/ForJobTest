#pragma once
#include "Strategy.h"

class WrappedTshark : public Strategy
{
public:
    WrappedTshark(string interface, string outputfileName);
    ~WrappedTshark();
    void run();
};