#include "MainComponent.h"

MainComponent::MainComponent()
    : progressBar(progress)
{
    addAndMakeVisible(cleanFileButton);
    addAndMakeVisible(processedFileButton);
    addAndMakeVisible(analyzeButton);
    addAndMakeVisible(saveButton);
    addAndMakeVisible(statusLabel);
    addAndMakeVisible(progressBar);

    cleanFileButton.setButtonText("Load Clean Audio");
    processedFileButton.setButtonText("Load Processed Audio");
    analyzeButton.setButtonText("Analyze");
    saveButton.setButtonText("Save Profile");

    cleanFileButton.onClick = [this] { loadCleanFile(); };
    processedFileButton.onClick = [this] { loadProcessedFile(); };
    analyzeButton.onClick = [this] { startAnalysis(); };
    saveButton.onClick = [this] { saveProfile(); };

    cleanWaveform = std::make_unique<WaveformDisplay>("Clean Audio");
    processedWaveform = std::make_unique<WaveformDisplay>("Processed Audio");

    addAndMakeVisible(cleanWaveform.get());
    addAndMakeVisible(processedWaveform.get());

    analyzeButton.setEnabled(false);
    saveButton.setEnabled(false);

    setSize(1024, 768);
}

MainComponent::~MainComponent() = default;

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto topArea = area.removeFromTop(area.getHeight() / 2);
    
    auto buttonArea = area.removeFromTop(40);
    cleanFileButton.setBounds(buttonArea.removeFromLeft(200));
    buttonArea.removeFromLeft(10);
    processedFileButton.setBounds(buttonArea.removeFromLeft(200));
    buttonArea.removeFromLeft(10);
    analyzeButton.setBounds(buttonArea.removeFromLeft(100));
    buttonArea.removeFromLeft(10);
    saveButton.setBounds(buttonArea.removeFromLeft(100));

    cleanWaveform->setBounds(topArea.reduced(0, 10));
    processedWaveform->setBounds(area.reduced(0, 10));
}

void MainComponent::loadCleanFile()
{
    juce::FileChooser chooser("Select Clean Audio File",
                             juce::File{},
                             "*.wav");

    if (chooser.browseForFileToOpen())
    {
        cleanFile = chooser.getResult();
        cleanWaveform->loadFile(cleanFile);
        analyzeButton.setEnabled(cleanFile.existsAsFile() && processedFile.existsAsFile());
    }
}

void MainComponent::loadProcessedFile()
{
    juce::FileChooser chooser("Select Processed Audio File",
                             juce::File{},
                             "*.wav");

    if (chooser.browseForFileToOpen())
    {
        processedFile = chooser.getResult();
        processedWaveform->loadFile(processedFile);
        analyzeButton.setEnabled(cleanFile.existsAsFile() && processedFile.existsAsFile());
    }
}

void MainComponent::startAnalysis()
{
    if (!cleanFile.existsAsFile() || !processedFile.existsAsFile())
        return;

    statusLabel.setText("Analyzing...", juce::dontSendNotification);
    progress = 0.0;
    
    analysisEngine.analyze(cleanFile, processedFile, 
        [this](double newProgress) {
            progress = newProgress;
            progressBar.repaint();
        },
        [this](const juce::String& error) {
            if (error.isEmpty())
            {
                statusLabel.setText("Analysis Complete", juce::dontSendNotification);
                saveButton.setEnabled(true);
            }
            else
            {
                statusLabel.setText("Error: " + error, juce::dontSendNotification);
            }
        });
}

void MainComponent::saveProfile()
{
    juce::FileChooser chooser("Save Profile",
                             juce::File{},
                             "*.reprof");

    if (chooser.browseForFileToSave(true))
    {
        auto file = chooser.getResult();
        if (analysisEngine.saveProfile(file))
            statusLabel.setText("Profile saved successfully", juce::dontSendNotification);
        else
            statusLabel.setText("Error saving profile", juce::dontSendNotification);
    }
}