#pragma once

#include <JuceHeader.h>

class ProfileLoader {
public:
    ProfileLoader();
    ~ProfileLoader();
    
    void loadProfile(const juce::String& path);
    juce::String getState() const;
    void setState(const juce::String& state);
    
private:
    juce::String currentState;
};