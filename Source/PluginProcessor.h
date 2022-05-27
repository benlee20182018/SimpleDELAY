/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Delay.h"

//==============================================================================

enum TempoSyncOptions {
    off=1,
    whole=2,
    half=3,
    quarter=4,
    eighth=5,
    sixteenth=6,
    thirtysecond=7
};

static const std::vector<std::string> TEMPO_SYNC_OPTIONS {
    std::string("Off"),
    std::string("Whole note"),
    std::string("1/2 note"),
    std::string("1/4 note"),
    std::string("1/8 note"),
    std::string("1/16 note"),
    std::string("1/32 note")
};

struct DelaySettings {
    float leftDelayTime  { 1.0f };
    float rightDelayTime { 2.0f };
    float feedback       { 0.5f };
    float wetLevel       { 0.8f };
    float gain           { 1.0f };
    float tempoSync      { 1.0f };
};

static const DelaySettings DEFAULT_DELAY_SETTINGS;

namespace DelaySettingIDs
{
    const std::string LEFT_DELAY_TIME  = "Left Delay Time";
    const std::string RIGHT_DELAY_TIME = "Right Delay Time";
    const std::string FEEDBACK         = "Feedback";
    const std::string WET_LEVEL        = "Wet Level";
    const std::string GAIN             = "Gain";
    const std::string TEMPO_SYNC       = "Tempo Sync";
    const std::string RESET            = "Reset to Defaults";
};


//==============================================================================
/**
*/
class SimpleDELAYAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleDELAYAudioProcessor();
    ~SimpleDELAYAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //===========================
    juce::AudioProcessorValueTreeState & getState() { return apvts; };
    
private:
    //===========================
    Delay<float> delay;
    void updateDelaySettings();
    void updateDelaySettings(const DelaySettings& delaySettings);
    
    static juce::AudioProcessorValueTreeState::ParameterLayout CreateParameterLayout();
    
    juce::AudioProcessorValueTreeState apvts {
        *this,
        nullptr,
        "Parameters",
        CreateParameterLayout()
    };
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDELAYAudioProcessor)
};
