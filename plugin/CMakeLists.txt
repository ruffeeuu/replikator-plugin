cmake_minimum_required(VERSION 3.15)
project(Replikator VERSION 1.0.0)

# Add JUCE as a subdirectory
add_subdirectory(JUCE)

# Create the plugin
juce_add_plugin(Replikator
    VERSION "1.0.0"
    COMPANY_NAME "AudioTools"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE "AtRp"
    PLUGIN_CODE "RepK"
    FORMATS VST3 AU AAX Standalone
    PRODUCT_NAME "Replikator"
)

# Add source files
target_sources(Replikator
    PRIVATE
        src/PluginProcessor.cpp
        src/PluginEditor.cpp
        src/AudioEngine.cpp
        src/ProfileLoader.cpp
)

# Setup target
target_compile_features(Replikator PRIVATE cxx_std_17)

# Link JUCE modules
target_link_libraries(Replikator
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