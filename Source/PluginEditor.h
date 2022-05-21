/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class SimpleDELAYAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Button::Listener
{
public:
    SimpleDELAYAudioProcessorEditor (SimpleDELAYAudioProcessor&);
    ~SimpleDELAYAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    /*
    class ResetListener : public juce::Button::Listener {
        void buttonClicked(juce::Button* button) override {
            //audioProcessor.resetDelaySettings();
        }
        juce::TextButton resetButton;
    };
     */
    
    juce::TextButton resetButton;
    
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDELAYAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDELAYAudioProcessorEditor)
};
