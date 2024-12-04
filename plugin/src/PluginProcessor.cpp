#include "PluginProcessor.h"
#include "PluginEditor.h"

ReplikatorAudioProcessor::ReplikatorAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

ReplikatorAudioProcessor::~ReplikatorAudioProcessor() = default;

void ReplikatorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    audioEngine.prepare(sampleRate, samplesPerBlock);
}

void ReplikatorAudioProcessor::releaseResources()
{
}

void ReplikatorAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    // Clear any unused channels
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    audioEngine.process(buffer);
}

juce::AudioProcessorEditor* ReplikatorAudioProcessor::createEditor() 
{ 
    return new ReplikatorAudioProcessorEditor(*this); 
}

bool ReplikatorAudioProcessor::hasEditor() const { return true; }
const juce::String ReplikatorAudioProcessor::getName() const { return JucePlugin_Name; }
bool ReplikatorAudioProcessor::acceptsMidi() const { return false; }
bool ReplikatorAudioProcessor::producesMidi() const { return false; }
double ReplikatorAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int ReplikatorAudioProcessor::getNumPrograms() { return 1; }
int ReplikatorAudioProcessor::getCurrentProgram() { return 0; }
void ReplikatorAudioProcessor::setCurrentProgram(int) {}
const juce::String ReplikatorAudioProcessor::getProgramName(int) { return {}; }
void ReplikatorAudioProcessor::changeProgramName(int, const juce::String&) {}
void ReplikatorAudioProcessor::getStateInformation(juce::MemoryBlock&) {}
void ReplikatorAudioProcessor::setStateInformation(const void*, int) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReplikatorAudioProcessor();
}