#pragma once

#include <JuceHeader.h>
#include "ProcessingProfile.h"

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();
    
    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer);
    void updateFromProfile(const ProcessingProfile& profile);
    
private:
    void processEQ(juce::AudioBuffer<float>& buffer);
    void processDynamics(juce::AudioBuffer<float>& buffer);
    void processTransients(juce::AudioBuffer<float>& buffer);
    void processHarmonics(juce::AudioBuffer<float>& buffer);
    
    ProcessingProfile currentProfile;
    double sampleRate;
    int samplesPerBlock;
};