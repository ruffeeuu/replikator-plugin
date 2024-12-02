#pragma once

#include <JuceHeader.h>
#include "AudioEngine.h"
#include "ProfileLoader.h"

class ReplikatorAudioProcessor : public juce::AudioProcessor {
public:
    ReplikatorAudioProcessor();
    ~ReplikatorAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;
    
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    AudioEngine audioEngine;
    ProfileLoader profileLoader;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReplikatorAudioProcessor)
};