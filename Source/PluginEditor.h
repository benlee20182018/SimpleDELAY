/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
struct RotarySlider : juce::Slider {
    RotarySlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                  juce::Slider::TextEntryBoxPosition::TextBoxBelow ) {
        
    }
};

//==============================================================================
/**
*/
class SimpleDELAYAudioProcessorEditor :
public juce::AudioProcessorEditor,
public juce::Button::Listener//,
//public juce::Slider::Listener
{
public:
    SimpleDELAYAudioProcessorEditor (SimpleDELAYAudioProcessor&);
    ~SimpleDELAYAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    std::vector<RotarySlider*> getSliders();
    
    RotarySlider leftDelaySlider;
    RotarySlider rightDelaySlider;
    RotarySlider feedbackSlider;
    RotarySlider wetLevelSlider;
    RotarySlider gainSlider;
    
    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;
    
    Attachment leftDelaySliderAttachment;
    Attachment rightDelaySliderAttachment;
    Attachment feedbackSliderAttachment;
    Attachment wetLevelSliderAttachment;
    Attachment gainSliderAttachment;
    
    juce::TextButton resetButton;
    //juce::ButtonParameterAttachment resetButtonAttachment;
    
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDELAYAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDELAYAudioProcessorEditor)
};
