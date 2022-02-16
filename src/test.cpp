#include <iostream>
#include <string>
#include "AudioFile.h"
#include "../include/antiAlias.h"


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

    int sr = inputFile.getSampleRate();

    std::string pathToFile = "/home/kian/instruo/newLubadh/antiAlias/audio/input.wav";
    loadAudio(inputFile, pathToFile);
    auto numChannels = inputFile.getNumChannels();
    auto numSamples = inputFile.getNumSamplesPerChannel();
    auto sampleRate = inputFile.getSampleRate();

    buffer.resize(numChannels);
    for(auto& b : buffer)
    b.resize (numSamples);
    outputFile.setBitDepth (inputFile.getBitDepth());
    outputFile.setSampleRate (inputFile.getSampleRate());

    antiAlias.setCutoff(0.05);

    for(auto& c : inputFile.samples)
    {
        antiAlias.process(c);   
    }
  
    outputFile.setAudioBuffer(inputFile.samples);
    outputFile.save ("/home/kian/instruo/newLubadh/antiAlias/audio/output.wav");

    return 0;
}