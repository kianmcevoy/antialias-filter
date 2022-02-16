// #include <iostream>
// #include <string>
#include "AudioFile.h"
//#include "filter.h"


// void loadAudio(AudioFile<float> &inputFile, std::string &pathToFile)
// {
//     inputFile.load(pathToFile);

//     std::cout << "Sample Rate = " << inputFile.getSampleRate() << '\n';
//     std::cout << "Bit Depth = " << inputFile.getBitDepth() << '\n';
//     std::cout << "Number of Samples = " << inputFile.getNumSamplesPerChannel() << '\n';
//     std::cout << "Length in Seconds = " << inputFile.getLengthInSeconds() << '\n';
//     std::cout << "Number of Channels = " << inputFile.getNumChannels() << '\n';
//     //std::cout << "Mono? = " << inputFile.isMono() << '\n';
//     //std::cout << "Stereo? = " << inputFile.isStereo() << '\n';
// }

int main()
{
    // AudioFile<float> inputFile;
    // AudioFile<float> outputFile;
    // AudioFile<float>::AudioBuffer buffer;

    // Biquad antiAlias;
    // int sr = inputFile.getSampleRate();

    // std::string pathToFile = "/home/kian/instruo/newLubadh/antiAlias/audio/input.wav";
    // loadAudio(inputFile, pathToFile);
    // auto numChannels = inputFile.getNumChannels();
    // auto numSamples = inputFile.getNumSamplesPerChannel();
    // auto sampleRate = inputFile.getSampleRate();

    // buffer.resize(numChannels);
    // for(auto& b : buffer)
    // b.resize (numSamples);
    // outputFile.setBitDepth (inputFile.getBitDepth());
    // outputFile.setSampleRate (inputFile.getSampleRate());

    // antiAlias.setType(Biquad::LOWPASS);
    // antiAlias.setSampleRate(sr);
    // antiAlias.initFilter(500, 0.2);

    // for(int c = 0; c < numChannels; c++)
    // {
    //     antiAlias.process(inputFile.samples[c], buffer[c]);   
    // }
  
    // outputFile.setAudioBuffer(buffer);
    // outputFile.save ("/home/kian/instruo/newLubadh/antiAlias/audio/output.wav");

    return 0;
}