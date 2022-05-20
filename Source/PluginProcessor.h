/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Delay.h"

//==============================================================================
struct DelaySettings {
    float delayTime { 0.25f };
    float wetLevel { 0.8f };
    float gain { 1.0f };
};

namespace DelaySettingNames {
const std::string DELAY_TIME = "Delay Time";
const std::string WET_LEVEL  = "Wet Level";
const std::string GAIN       = "Gain";
};

DelaySettings GetDelaySettings(juce::AudioProcessorValueTreeState& apvts);


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
    Delay<float> delay;
    
    void setDelayTime(float delayTime);
    
    void configureDelay();
    
    //===========================
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    juce::AudioProcessorValueTreeState apvts {
        *this,
        nullptr,
        "Parameters",
        createParameterLayout()
    };
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDELAYAudioProcessor)
};
