#pragma once

#include <JuceHeader.h>

struct AnalysisParameters {
    struct EQBand {
        float frequency;
        float gain;
    };

    struct DynamicsParams {
        float threshold;
        float ratio;
        float attack;
        float release;
    };

    struct TransientParams {
        float attack;
        float sustain;
    };

    std::vector<EQBand> eqBands;
    DynamicsParams dynamics;
    TransientParams transients;
    std::vector<float> harmonics;
};

class AudioAnalyzer {
public:
    AudioAnalyzer();
    ~AudioAnalyzer();

    AnalysisParameters analyzeAudioFiles(const juce::File& cleanFile, 
                                       const juce::File& processedFile,
                                       std::function<void(double)> progressCallback);

private:
    void analyzeSpectralContent(const juce::AudioBuffer<float>& clean,
                               const juce::AudioBuffer<float>& processed,
                               AnalysisParameters& params);
                               
    void analyzeDynamics(const juce::AudioBuffer<float>& clean,
                        const juce::AudioBuffer<float>& processed,
                        AnalysisParameters& params);
                        
    void analyzeTransients(const juce::AudioBuffer<float>& clean,
                          const juce::AudioBuffer<float>& processed,
                          AnalysisParameters& params);

    std::unique_ptr<juce::dsp::FFT> fft;
    juce::AudioFormatManager formatManager;
};