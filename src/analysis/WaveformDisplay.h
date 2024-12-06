#pragma once

#include <JuceHeader.h>

class WaveformDisplay : public juce::Component,
                       public juce::ChangeListener
{
public:
    WaveformDisplay(const juce::String& name);
    ~WaveformDisplay() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster*) override;

    void loadFile(const juce::File& file);

private:
    juce::String displayName;
    std::unique_ptr<juce::AudioFormatReader> reader;
    juce::AudioThumbnail thumbnail;
    juce::AudioFormatManager formatManager;
    bool fileLoaded{false};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};