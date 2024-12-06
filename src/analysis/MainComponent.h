#pragma once

#include <JuceHeader.h>
#include "WaveformDisplay.h"
#include "AudioAnalyzer.h"
#include "AnalysisEngine.h"

class MainComponent : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void loadCleanFile();
    void loadProcessedFile();
    void startAnalysis();
    void saveProfile();

    juce::TextButton cleanFileButton;
    juce::TextButton processedFileButton;
    juce::TextButton analyzeButton;
    juce::TextButton saveButton;

    std::unique_ptr<WaveformDisplay> cleanWaveform;
    std::unique_ptr<WaveformDisplay> processedWaveform;
    
    juce::Label statusLabel;
    juce::ProgressBar progressBar;
    
    AudioAnalyzer audioAnalyzer;
    AnalysisEngine analysisEngine;
    
    juce::File cleanFile;
    juce::File processedFile;
    
    double progress{0.0};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};