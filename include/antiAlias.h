// antiAlias.h
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ANTIALIAS_H_
#define _ANTIALIAS_H_
#include "biquad.h"
#include <array>

class AntiAlias
{
    public: 
        AntiAlias();
        void setCutoff(float f);
        void process(std::vector<float>& inOutBuff);   
   
    private:
        std::array<Biquad,4> filters;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif