// ioFilter.h
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _IOFILTER_H_
#define _IOFILTER_H_
#include "biquad.h"
#include <array>

class IoFilter
{
    public: 
        IoFilter();
        void init(int sampleRate);
        void process(std::vector<float>& inOutBuff);   
   
    private:
        std::array<Biquad,4> filters;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif