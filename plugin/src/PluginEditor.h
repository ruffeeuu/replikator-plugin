#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class ReplikatorAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit ReplikatorAudioProcessorEditor(ReplikatorAudioProcessor&);
    ~ReplikatorAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    ReplikatorAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReplikatorAudioProcessorEditor)
};