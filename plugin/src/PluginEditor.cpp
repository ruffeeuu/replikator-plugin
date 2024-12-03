#include "PluginEditor.h"

ReplikatorAudioProcessorEditor::ReplikatorAudioProcessorEditor(ReplikatorAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    setSize(400, 300);
}

ReplikatorAudioProcessorEditor::~ReplikatorAudioProcessorEditor()
{
}

void ReplikatorAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void ReplikatorAudioProcessorEditor::resized()
{
}