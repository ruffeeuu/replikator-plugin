#include "ProfileLoader.h"

ProfileLoader::ProfileLoader() = default;
ProfileLoader::~ProfileLoader() = default;

void ProfileLoader::loadProfile(const juce::String& path)
{
    // Profile loading implementation will be added later
    currentState = "default";
}

juce::String ProfileLoader::getState() const
{
    return currentState;
}

void ProfileLoader::setState(const juce::String& state)
{
    currentState = state;
}