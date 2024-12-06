#pragma once

#include <JuceHeader.h>
#include "AudioAnalyzer.h"

class AnalysisEngine {
public:
    AnalysisEngine();
    ~AnalysisEngine();

    void analyze(const juce::File& cleanFile,
                const juce::File& processedFile,
                std::function<void(double)> progressCallback,
                std::function<void(const juce::String&)> completionCallback);

    bool saveProfile(const juce::File& file);
    
private:
    AudioAnalyzer analyzer;
    std::unique_ptr<AnalysisParameters> currentResults;
    
    juce::String createProfileJson(const AnalysisParameters& params);
};