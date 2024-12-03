#include "AudioEngine.h"

AudioEngine::AudioEngine() {}
AudioEngine::~AudioEngine() {}

void AudioEngine::prepare(double newSampleRate, int newSamplesPerBlock)
{
    sampleRate = newSampleRate;
    samplesPerBlock = newSamplesPerBlock;
}

void AudioEngine::process(juce::AudioBuffer<float>& buffer)
{
    // Audio processing implementation
}