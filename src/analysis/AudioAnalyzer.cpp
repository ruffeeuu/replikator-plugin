#include "AudioAnalyzer.h"

AudioAnalyzer::AudioAnalyzer()
    : fft(std::make_unique<juce::dsp::FFT>(13)) // 8192 points
{
    formatManager.registerBasicFormats();
}

AudioAnalyzer::~AudioAnalyzer() = default;

AnalysisParameters AudioAnalyzer::analyzeAudioFiles(
    const juce::File& cleanFile,
    const juce::File& processedFile,
    std::function<void(double)> progressCallback)
{
    AnalysisParameters params;
    
    std::unique_ptr<juce::AudioFormatReader> cleanReader(
        formatManager.createReaderFor(cleanFile));
    std::unique_ptr<juce::AudioFormatReader> processedReader(
        formatManager.createReaderFor(processedFile));
        
    if (cleanReader == nullptr || processedReader == nullptr)
        return params;

    const int numSamples = static_cast<int>(cleanReader->lengthInSamples);
    const int blockSize = 4096;
    
    juce::AudioBuffer<float> cleanBuffer(2, numSamples);
    juce::AudioBuffer<float> processedBuffer(2, numSamples);
    
    cleanReader->read(&cleanBuffer, 0, numSamples, 0, true, true);
    processedReader->read(&processedBuffer, 0, numSamples, 0, true, true);
    
    progressCallback(0.1);
    analyzeSpectralContent(cleanBuffer, processedBuffer, params);
    
    progressCallback(0.4);
    analyzeDynamics(cleanBuffer, processedBuffer, params);
    
    progressCallback(0.7);
    analyzeTransients(cleanBuffer, processedBuffer, params);
    
    progressCallback(1.0);
    
    return params;
}

void AudioAnalyzer::analyzeSpectralContent(
    const juce::AudioBuffer<float>& clean,
    const juce::AudioBuffer<float>& processed,
    AnalysisParameters& params)
{
    const int fftSize = fft->getSize();
    std::vector<float> cleanWindow(fftSize * 2, 0.0f);
    std::vector<float> processedWindow(fftSize * 2, 0.0f);
    
    // Standard EQ frequencies
    const std::vector<float> frequencies = {
        20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000
    };
    
    for (auto freq : frequencies)
    {
        AnalysisParameters::EQBand band;
        band.frequency = freq;
        band.gain = 0.0f; // Calculate actual gain difference here
        params.eqBands.push_back(band);
    }
    
    // Initialize harmonics array
    params.harmonics.resize(256, 0.0f);
}

void AudioAnalyzer::analyzeDynamics(
    const juce::AudioBuffer<float>& clean,
    const juce::AudioBuffer<float>& processed,
    AnalysisParameters& params)
{
    params.dynamics.threshold = -18.0f;
    params.dynamics.ratio = 2.0f;
    params.dynamics.attack = 10.0f;
    params.dynamics.release = 100.0f;
}

void AudioAnalyzer::analyzeTransients(
    const juce::AudioBuffer<float>& clean,
    const juce::AudioBuffer<float>& processed,
    AnalysisParameters& params)
{
    params.transients.attack = 2.0f;
    params.transients.sustain = -1.0f;
}