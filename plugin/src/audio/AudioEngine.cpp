#include "AudioEngine.h"

AudioEngine::AudioEngine() = default;
AudioEngine::~AudioEngine() = default;

void AudioEngine::prepare(double newSampleRate, int newSamplesPerBlock)
{
    sampleRate = newSampleRate;
    samplesPerBlock = newSamplesPerBlock;
}

void AudioEngine::process(juce::AudioBuffer<float>& buffer)
{
    if (buffer.getNumChannels() == 0 || buffer.getNumSamples() == 0)
        return;

    processBlock(buffer);
    applyGain(buffer);
}

void AudioEngine::processBlock(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] *= 0.5f; // Simple gain reduction
        }
    }
}

void AudioEngine::applyGain(juce::AudioBuffer<float>& buffer)
{
    buffer.applyGain(0.8f); // Apply additional gain reduction
}