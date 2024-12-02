#include "PluginProcessor.h"
#include "PluginEditor.h"

ReplikatorAudioProcessor::ReplikatorAudioProcessor()
    : AudioProcessor (BusesProperties()
                     .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                     .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
}

ReplikatorAudioProcessor::~ReplikatorAudioProcessor() {}

void ReplikatorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    audioEngine.prepare(sampleRate, samplesPerBlock);
}

void ReplikatorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    audioEngine.process(buffer);
}

juce::AudioProcessorEditor* ReplikatorAudioProcessor::createEditor() { return new ReplikatorAudioProcessorEditor (*this); }
bool ReplikatorAudioProcessor::hasEditor() const { return true; }
const juce::String ReplikatorAudioProcessor::getName() const { return JucePlugin_Name; }
bool ReplikatorAudioProcessor::acceptsMidi() const { return false; }
bool ReplikatorAudioProcessor::producesMidi() const { return false; }
double ReplikatorAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int ReplikatorAudioProcessor::getNumPrograms() { return 1; }
int ReplikatorAudioProcessor::getCurrentProgram() { return 0; }
void ReplikatorAudioProcessor::setCurrentProgram (int index) {}
const juce::String ReplikatorAudioProcessor::getProgramName (int index) { return {}; }
void ReplikatorAudioProcessor::changeProgramName (int index, const juce::String& newName) {}
void ReplikatorAudioProcessor::releaseResources() {}

void ReplikatorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = profileLoader.getState();
    destData.append(state.toUTF8(), state.getNumBytesAsUTF8());
}

void ReplikatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    profileLoader.setState(juce::String::createStringFromData(data, sizeInBytes));
    audioEngine.updateFromProfile(profileLoader.getCurrentProfile());
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReplikatorAudioProcessor();
}