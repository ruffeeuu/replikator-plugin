#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(const juce::String& name)
    : displayName(name),
      thumbnail(512, formatManager, thumbnailCache)
{
    formatManager.registerBasicFormats();
    thumbnail.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
    thumbnail.removeChangeListener(this);
}

void WaveformDisplay::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.drawText(displayName, getLocalBounds().removeFromTop(20), juce::Justification::centred);

    if (fileLoaded)
    {
        g.setColour(juce::Colours::lightgreen);
        auto bounds = getLocalBounds();
        bounds.removeFromTop(20);
        thumbnail.drawChannel(g, bounds, 0.0, thumbnail.getTotalLength(), 0, 1.0f);
    }
    else
    {
        g.setColour(juce::Colours::white);
        g.drawText("No File Loaded", getLocalBounds(), juce::Justification::centred);
    }
}

void WaveformDisplay::resized()
{
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster*)
{
    repaint();
}

void WaveformDisplay::loadFile(const juce::File& file)
{
    auto* reader = formatManager.createReaderFor(file);
    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReader> newReader(reader);
        thumbnail.setReader(newReader.get(), juce::Time::getMillisecondCounter());
        fileLoaded = true;
        repaint();
    }
}