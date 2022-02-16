//filter.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "filter.h"

using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OnePole::OnePole()
{
	coef = 0;
	xState = 0;
	yState = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OnePole::process(vector<float>& x)
{
    lowPassArray.resize(x.size());
    hiPassArray.resize(x.size());
   
    for(int i=0; i < x.size(); i++)
    {
        float y = (x[i] + xState - yState * (1-coef)) / (1+coef);
        xState = x[i];
        yState = y;

        lowPassArray[i] = yState;
        hiPassArray[i] = xState - yState;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Biquad::Biquad()
{
	level = 1;
    aCoef.resize(ORDER);
    bCoef.resize(ORDER);
    xState.resize(ORDER);
    type = LOWPASS_1POLE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Biquad::initFilter(float cutOff, float resonance)
{
    float f = cutOff/sampleRate;
    float K = tanf(M_PI * f); 
    float Q = resonance;
    float V = level;

    switch (type)
    {
        case LOWPASS_1POLE:
        {
            aCoef[0] = 1;
            aCoef[1] = -expf(-2.f * M_PI * f);
            aCoef[2] = 0.f;
            bCoef[0] = 1.f + aCoef[1];
            bCoef[1] = 0.f;
            bCoef[2] = 0.f;
        }break;
        
        case HIGHPASS_1POLE:
        {
            aCoef[0] = 1;
            aCoef[1] = expf(-2.f * M_PI * (0.5 - f));
            aCoef[2] = 0.f;
            bCoef[0] = 1.f - aCoef[1];
            bCoef[1] = 0.f;
            bCoef[2] = 0.f;
        }break;
        
        case LOWPASS:
        {
            float norm = 1.f / (1.f + K / Q + K * K);
            bCoef[0] = K * K * norm;
            bCoef[1] = 2.f * bCoef[0];
            bCoef[2] = bCoef[0];
            aCoef[0] = 1;
            aCoef[1] = 2.f * (K * K - 1.f) * norm;
            aCoef[2] = (1.f - K / Q + K * K) * norm;
        }break;
        
        case HIGHPASS:
        {
            float norm = 1.f / (1.f + K / Q + K * K);
            bCoef[0] = norm;
            bCoef[1] = -2.f * bCoef[0];
            bCoef[2] = bCoef[0];
            aCoef[0] = 1;
            aCoef[1] = 2.f * (K * K - 1.f) * norm;
            aCoef[2] = (1.f - K / Q + K * K) * norm;
        }break;
        
        case LOWSHELF: 
        {
			float sqrtV = sqrtf(V);
			if (V >= 1.f) 
            {
                float norm = 1.f / (1.f + M_SQRT2 * K + K * K);
                bCoef[0] = (1.f + M_SQRT2 * sqrtV * K + V * K * K) * norm;
                bCoef[1] = 2.f * (V * K * K - 1.f) * norm;
                bCoef[2] = (1.f - M_SQRT2 * sqrtV * K + V * K * K) * norm;
                aCoef[0] = 1; 
                aCoef[1] = 2.f * (K * K - 1.f) * norm;
                aCoef[2] = (1.f - M_SQRT2 * K + K * K) * norm;
			}
			else 
            {
                float norm = 1.f / (1.f + M_SQRT2 / sqrtV * K + K * K / V);
                bCoef[0] = (1.f + M_SQRT2 * K + K * K) * norm;
                bCoef[1] = 2.f * (K * K - 1) * norm;
                bCoef[2] = (1.f - M_SQRT2 * K + K * K) * norm;
                aCoef[0] = 1; 
                aCoef[0] = 2.f * (K * K / V - 1.f) * norm;
                aCoef[1] = (1.f - M_SQRT2 / sqrtV * K + K * K / V) * norm;
            }
        } break;

        case HIGHSHELF: 
        {
            float sqrtV = sqrtf(V);
            if (V >= 1.f) 
            {
                float norm = 1.f / (1.f + M_SQRT2 * K + K * K);
                bCoef[0] = (V + M_SQRT2 * sqrtV * K + K * K) * norm;
                bCoef[1] = 2.f * (K * K - V) * norm;
                bCoef[2] = (V - M_SQRT2 * sqrtV * K + K * K) * norm;
                aCoef[0] = 1; 
                aCoef[1] = 2.f * (K * K - 1.f) * norm;
                aCoef[2] = (1.f - M_SQRT2 * K + K * K) * norm;
            }
            else 
            {
                float norm = 1.f / (1.f / V + M_SQRT2 / sqrtV * K + K * K);
                bCoef[0] = (1.f + M_SQRT2 * K + K * K) * norm;
                bCoef[1] = 2.f * (K * K - 1.f) * norm;
                bCoef[2] = (1.f - M_SQRT2 * K + K * K) * norm;
                aCoef[0] = 1;
                aCoef[1] = 2.f * (K * K - 1.f / V) * norm;
                aCoef[2] = (1.f / V - M_SQRT2 / sqrtV * K + K * K) * norm;
            }
        } break;

		case BANDPASS: 
        {
            float norm = 1.f / (1.f + K / Q + K * K);
            bCoef[0] = K / Q * norm;
            bCoef[1] = 0.f;
            bCoef[2] = -bCoef[0];
            aCoef[0] = 1;
            aCoef[1] = 2.f * (K * K - 1.f) * norm;
            aCoef[2] = (1.f - K / Q + K * K) * norm;
		} break;

        case PEAK: 
        {
            if (V >= 1.f) 
            {
                float norm = 1.f / (1.f + K / Q + K * K);
                bCoef[0] = (1.f + K / Q * V + K * K) * norm;
                bCoef[1] = 2.f * (K * K - 1.f) * norm;
                bCoef[2] = (1.f - K / Q * V + K * K) * norm;
                aCoef[0] = 1;
                aCoef[1] = bCoef[1];
                aCoef[2] = (1.f - K / Q + K * K) * norm;
            }
            else 
            {
                float norm = 1.f / (1.f + K / Q / V + K * K);
                bCoef[0] = (1.f + K / Q + K * K) * norm;
                bCoef[1] = 2.f * (K * K - 1.f) * norm;
                bCoef[2] = (1.f - K / Q + K * K) * norm;
                aCoef[0] = 1;
                aCoef[1] = bCoef[1];
                aCoef[2] = (1.f - K / Q / V + K * K) * norm;
            }
        } break;

        case NOTCH: 
        {
            float norm = 1.f / (1.f + K / Q + K * K);
            bCoef[0] = (1.f + K * K) * norm;
            bCoef[1] = 2.f * (K * K - 1.f) * norm;
            bCoef[2] = bCoef[0];
            aCoef[0] = 1;
            aCoef[1] = bCoef[1];
            aCoef[2] = (1.f - K / Q + K * K) * norm;
        } break;

        default: break;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Biquad::process(vector<float>& inOutBuff)
{  
    for(int i = 0; i < inOutBuff.size(); i++)
    {
        //feedback coefficients
        xState[0] = inOutBuff[i] + (xState[1] * -aCoef[1]) + (xState[2] * -aCoef[2]);
        //feedfoward coefficients
        inOutBuff[i] = (xState[0] * bCoef[0]) + (xState[1] * bCoef[1]) + (xState[2] * bCoef[2]);
        //shift delay blocks
        xState[2] = xState[1];
        xState[1] = xState[0];
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Biquad::process(const vector<float>& inBuff, std::vector<float>& outBuff)
{
    if(inBuff.size() != outBuff.size()) outBuff.resize(inBuff.size());
    
    for(int i = 0; i < inBuff.size(); i++)
    {
        //feedback coefficients
        xState[0] = inBuff[i] + (xState[1] * -aCoef[1]) + (xState[2] * -aCoef[2]);
        //feedfoward coefficients
        outBuff[i]  = (xState[0] * bCoef[0]) + (xState[1] * bCoef[1]) + (xState[2] * bCoef[2]);
        //shift delay blocks
        xState[2] = xState[1];
        xState[1] = xState[0];
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////