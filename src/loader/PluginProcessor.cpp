#include "PluginProcessor.h"
#include "PluginEditor.h"

ReplikatorLoaderProcessor::ReplikatorLoaderProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

ReplikatorLoaderProcessor::~ReplikatorLoaderProcessor() = default;

void ReplikatorLoaderProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    audioEngine.prepare(sampleRate, samplesPerBlock);
}

void ReplikatorLoaderProcessor::releaseResources()
{
}

void ReplikatorLoaderProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    audioEngine.process(buffer);
}

bool ReplikatorLoaderProcessor::loadProfile(const juce::File& file)
{
    if (profileLoader.loadProfile(file))
    {
        currentProfileFile = file;
        audioEngine.updateParameters(profileLoader.getParameters());
        return true;
    }
    return false;
}

juce::AudioProcessorEditor* ReplikatorLoaderProcessor::createEditor() 
{ 
    return new ReplikatorLoaderEditor(*this); 
}

bool ReplikatorLoaderProcessor::hasEditor() const { return true; }
const juce::String ReplikatorLoaderProcessor::getName() const { return JucePlugin_Name; }
bool ReplikatorLoaderProcessor::acceptsMidi() const { return false; }
bool ReplikatorLoaderProcessor::producesMidi() const { return false; }
double ReplikatorLoaderProcessor::getTailLengthSeconds() const { return 0.0; }
int ReplikatorLoaderProcessor::getNumPrograms() { return 1; }
int ReplikatorLoaderProcessor::getCurrentProgram() { return 0; }
void ReplikatorLoaderProcessor::setCurrentProgram(int) {}
const juce::String ReplikatorLoaderProcessor::getProgramName(int) { return {}; }
void ReplikatorLoaderProcessor::changeProgramName(int, const juce::String&) {}

void ReplikatorLoaderProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    if (currentProfileFile.existsAsFile())
    {
        juce::XmlElement xml("ReplikatorState");
        xml.setAttribute("profilePath", currentProfileFile.getFullPathName());
        copyXmlToBinary(xml, destData);
    }
}

void ReplikatorLoaderProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml && xml->hasTagName("ReplikatorState"))
    {
        juce::File file(xml->getStringAttribute("profilePath"));
        if (file.existsAsFile())
            loadProfile(file);
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReplikatorLoaderProcessor();
}