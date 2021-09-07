#include "antiAlias.h"
#include "filter.h"

AntiAlias::AntiAlias()
{   //Anti-Alias Filter Constructor
    sampleRate = 48000.f;
    in.resize(1);
}

float AntiAlias::process(float input, float cutoff)
{
     in[0] = input;

    float sr = getSampleRate();
    lopA.setCutoff(cutoff/sr);
    lopB.setCutoff(cutoff/sr);
   
    lopA.process(in);
    lopB.process(lopA.getLowpass());
    
    return lopB.getLowpass()[0];
}
