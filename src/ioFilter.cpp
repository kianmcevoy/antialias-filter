//ioFilter.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ioFilter.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IoFilter::IoFilter()
{
    for(auto& f : filters)
    {
        f.setType(Biquad::LOWPASS_1POLE);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IoFilter::init(int sampleRate)
{
    filters[0].initFilter((float)13000.f/sampleRate);
    filters[1].initFilter((float)12000.f/sampleRate);
    filters[2].initFilter((float)11000.f/sampleRate);
    filters[3].initFilter((float)9000.f/sampleRate);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IoFilter::process(std::vector<float>& inOutBuff)
{
    for(auto& f : filters)
    {
        f.process(inOutBuff);
    }   
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////