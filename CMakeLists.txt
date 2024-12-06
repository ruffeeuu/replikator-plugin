cmake_minimum_required(VERSION 3.15)
project(ReplikatorSuite VERSION 1.0.0)

# Set deployment target for macOS
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment version" FORCE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for OSX" FORCE)
endif()

# Add JUCE as a subdirectory
add_subdirectory(JUCE)

# Set AAX SDK path
if(DEFINED ENV{AAX_SDK_PATH})
    set(AAX_SDK_PATH $ENV{AAX_SDK_PATH})
else()
    set(AAX_SDK_PATH "${CMAKE_SOURCE_DIR}/SDKs/AAX_SDK")
endif()

# Configure Replikator Loader Plugin
juce_add_plugin(ReplikatorLoader
    VERSION "1.0.0"
    COMPANY_NAME "Audio Alcazar"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE "AuAl"
    PLUGIN_CODE "RpLd"
    FORMATS VST3 AU AAX Standalone
    AAX_IDENTIFIER "com.audioalcazar.replikatorloader"
    AAX_CATEGORY "AAX_ePlugInCategory_Effect"
    PRODUCT_NAME "Replikator Loader"
)

target_sources(ReplikatorLoader
    PRIVATE
        src/loader/PluginProcessor.cpp
        src/loader/PluginEditor.cpp
        src/loader/AudioEngine.cpp
        src/loader/ProfileLoader.cpp
)

target_include_directories(ReplikatorLoader
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/loader
        ${CMAKE_SOURCE_DIR}/JUCE/modules
        ${AAX_SDK_PATH}
)

target_link_libraries(ReplikatorLoader
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_core
        juce::juce_data_structures
        juce::juce_graphics
        juce::juce_gui_basics
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# Configure Replikator Analysis Application
juce_add_gui_app(ReplikatorAnalysis
    VERSION "1.0.0"
    COMPANY_NAME "Audio Alcazar"
    PRODUCT_NAME "Replikator Analysis"
)

target_sources(ReplikatorAnalysis
    PRIVATE
        src/analysis/Main.cpp
        src/analysis/MainComponent.cpp
        src/analysis/AudioAnalyzer.cpp
        src/analysis/WaveformDisplay.cpp
        src/analysis/AnalysisEngine.cpp
)

target_include_directories(ReplikatorAnalysis
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/analysis
        ${CMAKE_SOURCE_DIR}/JUCE/modules
)

target_link_libraries(ReplikatorAnalysis
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_core
        juce::juce_data_structures
        juce::juce_graphics
        juce::juce_gui_basics
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)