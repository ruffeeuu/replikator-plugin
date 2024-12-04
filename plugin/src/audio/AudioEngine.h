#pragma once

#include <JuceHeader.h>

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();
    
    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer);
    
private:
    double sampleRate{44100.0};
    int samplesPerBlock{0};
    
    void processBlock(juce::AudioBuffer<float>& buffer);
    void applyGain(juce::AudioBuffer<float>& buffer);
};