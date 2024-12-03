cmake_minimum_required(VERSION 3.15)
project(Replikator VERSION 1.0.0)

# Set deployment target for macOS
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment version" FORCE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for OSX" FORCE)
endif()

# Add JUCE as a subdirectory
add_subdirectory(JUCE)

# Configure JUCE
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
    FORMATS VST3 AU Standalone
    PRODUCT_NAME "Replikator"
)

# Add source files
target_sources(Replikator
    PRIVATE
        plugin/src/PluginProcessor.cpp
        plugin/src/PluginEditor.cpp
        plugin/src/AudioEngine.cpp
        plugin/src/ProfileLoader.cpp
)

# Setup target
target_compile_features(Replikator PRIVATE cxx_std_14)

# Configure include directories
target_include_directories(Replikator
    PRIVATE
        ${CMAKE_SOURCE_DIR}/plugin/src
)

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