#include "AnalysisEngine.h"

AnalysisEngine::AnalysisEngine() = default;
AnalysisEngine::~AnalysisEngine() = default;

void AnalysisEngine::analyze(
    const juce::File& cleanFile,
    const juce::File& processedFile,
    std::function<void(double)> progressCallback,
    std::function<void(const juce::String&)> completionCallback)
{
    juce::Thread::launch([this, 
                         cleanFile, 
                         processedFile, 
                         progressCallback, 
                         completionCallback]
    {
        try
        {
            currentResults = std::make_unique<AnalysisParameters>(
                analyzer.analyzeAudioFiles(cleanFile, processedFile, progressCallback));
            
            juce::MessageManager::callAsync([completionCallback]
            {
                completionCallback({});
            });
        }
        catch (const std::exception& e)
        {
            juce::MessageManager::callAsync([completionCallback, e]
            {
                completionCallback(e.what());
            });
        }
    });
}

bool AnalysisEngine::saveProfile(const juce::File& file)
{
    if (!currentResults)
        return false;

    try
    {
        if (file.hasWriteAccess())
        {
            file.replaceWithText(createProfileJson(*currentResults));
            return true;
        }
    }
    catch (const std::exception&) {}

    return false;
}

juce::String AnalysisEngine::createProfileJson(const AnalysisParameters& params)
{
    juce::var json(new juce::DynamicObject());
    auto* obj = json.getDynamicObject();
    
    // Version
    obj->setProperty("version", "1.0");
    
    // EQ Bands
    juce::Array<juce::var> eqArray;
    for (const auto& band : params.eqBands)
    {
        auto* eqObj = new juce::DynamicObject();
        eqObj->setProperty("frequency", band.frequency);
        eqObj->setProperty("gain", band.gain);
        eqArray.add(eqObj);
    }
    obj->setProperty("eq", eqArray);
    
    // Dynamics
    auto* dynamicsObj = new juce::DynamicObject();
    dynamicsObj->setProperty("threshold", params.dynamics.threshold);
    dynamicsObj->setProperty("ratio", params.dynamics.ratio);
    dynamicsObj->setProperty("attack", params.dynamics.attack);
    dynamicsObj->setProperty("release", params.dynamics.release);
    obj->setProperty("dynamics", dynamicsObj);
    
    // Transients
    auto* transientsObj = new juce::DynamicObject();
    transientsObj->setProperty("attack", params.transients.attack);
    transientsObj->setProperty("sustain", params.transients.sustain);
    obj->setProperty("transients", transientsObj);
    
    // Harmonics
    juce::Array<juce::var> harmonicsArray;
    for (float harmonic : params.harmonics)
        harmonicsArray.add(harmonic);
    obj->setProperty("harmonics", harmonicsArray);
    
    return juce::JSON::toString(json, true);
}