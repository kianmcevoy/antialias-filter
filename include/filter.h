// filter.h
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _FILTER_H_
#define _FILTER_H_
#include <stdlib.h>
#include <math.h>
#include <vector>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Filter
{
    private:
        float coef;
        float xState;
        float yState;
        std::vector<float> lowPassArray;
        std::vector<float> hiPassArray; 

    public:
        Filter();
        
        inline std::vector<float>&  getLowpass()                    {return lowPassArray;}
        inline std::vector<float>&  getHipass()                     {return hiPassArray;}
        inline void setCutoff(float f)                              {if(f>0){coef=1.f/(M_PI * f);}}
        
        void process(std::vector<float>& x);    
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif