// filter.h
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _FILTER_H_
#define _FILTER_H_
#include <stdlib.h>
#include <math.h>
#include <vector>
#define ORDER 3
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class OnePole
{
    private:
        float coef;
        float xState;
        float yState;
        std::vector<float> lowPassArray;
        std::vector<float> hiPassArray; 

    public:
        OnePole();
        
        inline std::vector<float>&  getLowpass()                    {return lowPassArray;}
        inline std::vector<float>&  getHipass()                     {return hiPassArray;}
        inline void setCutoff(float f)                              {if(f>0){coef=1.f/(M_PI * f);}}
        
        void process(std::vector<float>& x);    
};
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
        inline void setSampleRate(int i)                        {sampleRate = i;}
        void initFilter(float cutOff, float resonance);
        void process(std::vector<float>& inOutBuff);   
        void process(const std::vector<float>& inBuff, std::vector<float>& outBuff);   

    private:
        float level;
        std::vector<float> aCoef;
        std::vector<float> bCoef;
        std::vector<float> xState;
        Type type;
        int sampleRate;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif