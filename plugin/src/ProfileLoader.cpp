#include "ProfileLoader.h"

ProfileLoader::ProfileLoader() {}
ProfileLoader::~ProfileLoader() {}

void ProfileLoader::loadProfile(const juce::String& path)
{
    // Profile loading implementation
}

juce::String ProfileLoader::getState() const
{
    return currentState;
}

void ProfileLoader::setState(const juce::String& state)
{
    currentState = state;
}