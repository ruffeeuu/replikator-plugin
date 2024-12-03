cmake_minimum_required(VERSION 3.15)
project(Replikator VERSION 1.0.0)

# Set deployment target for macOS Snow Leopard compatibility
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.6" CACHE STRING "Minimum OS X deployment version" FORCE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for OSX" FORCE)
endif()

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

# Set compiler flags for older system compatibility
if(APPLE)
    target_compile_options(Replikator PRIVATE
        -mmacosx-version-min=10.6
        -stdlib=libc++
    )
    set_target_properties(Replikator PROPERTIES
        LINK_FLAGS "-mmacosx-version-min=10.6 -stdlib=libc++"
    )
endif()

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