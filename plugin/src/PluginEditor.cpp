#include "PluginEditor.h"

ReplikatorAudioProcessorEditor::ReplikatorAudioProcessorEditor(ReplikatorAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    setSize(400, 300);
}

ReplikatorAudioProcessorEditor::~ReplikatorAudioProcessorEditor() = default;

void ReplikatorAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void ReplikatorAudioProcessorEditor::resized()
{
    // Layout code will be added later
}