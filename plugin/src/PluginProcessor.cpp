#include "PluginProcessor.h"
#include "PluginEditor.h"

ReplikatorAudioProcessor::ReplikatorAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

ReplikatorAudioProcessor::~ReplikatorAudioProcessor() {}

void ReplikatorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
}

void ReplikatorAudioProcessor::releaseResources()
{
}

void ReplikatorAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Process audio here
}

juce::AudioProcessorEditor* ReplikatorAudioProcessor::createEditor() { return nullptr; }
bool ReplikatorAudioProcessor::hasEditor() const { return false; }
const juce::String ReplikatorAudioProcessor::getName() const { return JucePlugin_Name; }
bool ReplikatorAudioProcessor::acceptsMidi() const { return false; }
bool ReplikatorAudioProcessor::producesMidi() const { return false; }
double ReplikatorAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int ReplikatorAudioProcessor::getNumPrograms() { return 1; }
int ReplikatorAudioProcessor::getCurrentProgram() { return 0; }
void ReplikatorAudioProcessor::setCurrentProgram(int index) {}
const juce::String ReplikatorAudioProcessor::getProgramName(int index) { return {}; }
void ReplikatorAudioProcessor::changeProgramName(int index, const juce::String& newName) {}
void ReplikatorAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {}
void ReplikatorAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReplikatorAudioProcessor();
}