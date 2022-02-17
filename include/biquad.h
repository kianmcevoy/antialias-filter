// biquad.h
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BIQUAD_H_
#define _BIQUAD_H_
#include <stdlib.h>
#include <math.h>
#include <vector>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Biquad
{
    public:
        Biquad();
        enum Type 
        {
            LOWPASS_1POLE,
            HIGHPASS_1POLE,
            LOWPASS,
            HIGHPASS,
            LOWSHELF,
            HIGHSHELF,
            BANDPASS,
            PEAK,
            NOTCH
        };
        inline void setlevel(float f)                           {level = f;}
        inline void setType(Type t)                             {type = t;}
        void initFilter(float freq);
        void initFilter(float freq, float resonance);
        void process(std::vector<float>& inOutBuff);   
        void process(const std::vector<float>& inBuff, std::vector<float>& outBuff);   

    private:
        float level;
        std::vector<float> aCoef;
        std::vector<float> bCoef;
        std::vector<float> xState;
        Type type;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif