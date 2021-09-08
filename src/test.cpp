#include <iostream>
#include <string>
#include "AudioFile.h"
#include "antiAlias.h"
#include "filter.h"


void loadAudio(AudioFile<float> &inputFile, std::string &pathToFile)
{
    inputFile.load(pathToFile);

    std::cout << "Sample Rate = " << inputFile.getSampleRate() << '\n';
    std::cout << "Bit Depth = " << inputFile.getBitDepth() << '\n';
    std::cout << "Number of Samples = " << inputFile.getNumSamplesPerChannel() << '\n';
    std::cout << "Length in Seconds = " << inputFile.getLengthInSeconds() << '\n';
    std::cout << "Number of Channels = " << inputFile.getNumChannels() << '\n';
    //std::cout << "Mono? = " << inputFile.isMono() << '\n';
    //std::cout << "Stereo? = " << inputFile.isStereo() << '\n';
}

int main()
{
    AudioFile<float> inputFile;
    AudioFile<float> outputFile;
    AudioFile<float>::AudioBuffer buffer;

    AntiAlias antiAlias;

    std::string pathToFile = "/home/kian/instruo/newLubadh/antiAlias/audio/input.wav";
    loadAudio(inputFile, pathToFile);
    auto numChannels = inputFile.getNumChannels();
    auto numSamples = inputFile.getNumSamplesPerChannel();
    auto sampleRate = inputFile.getSampleRate();

    buffer.resize (numChannels);
    buffer[0].resize (numSamples);
    outputFile.setBitDepth (inputFile.getBitDepth());
    outputFile.setSampleRate (inputFile.getSampleRate());

    antiAlias.setSampleRate(sampleRate);
    float nyquist = sampleRate/2.f;
    
    for(int channel = 0; channel < numChannels; channel++)
    {
        for(int n = 0; n < numSamples; n++)
        {
            float cutoff = ((float(n+1)/float(numSamples))*nyquist);  
            buffer[0][n] = antiAlias.process(inputFile.samples[channel][n], cutoff);   
            // std::cout << "cutoff = " << cutoff << '\n';
        }
    }
  
    outputFile.setAudioBuffer(buffer);
    outputFile.save ("/home/kian/instruo/newLubadh/antiAlias/audio/output.wav");

    return 0;
}