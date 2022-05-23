/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
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
    juce::Slider leftDelaySlider;
    /*
    juce::Label  leftDelayLabel;
    juce::SliderParameterAttachment leftDelaySliderAttachment;
    
    juce::Slider rightDelaySlider;
    juce::Label  rightDelayLabel;
    juce::SliderParameterAttachment rightDelaySliderAttachment;
    
    juce::Slider feedbackSlider;
    juce::Label  feedbackLabel;
    juce::SliderParameterAttachment feedbackSliderAttachment;
    
    juce::Slider wetLevelSlider;
    juce::Label  wetLevelLabel;
    juce::SliderParameterAttachment wetLevelSliderAttachment;
    
    juce::Slider gainSlider;
    juce::Label  gainLabel;
    juce::SliderParameterAttachment gainSliderAttachment;
    //void sliderValueChanged(juce::Slider* slider) override;
     */
    
    juce::TextButton resetButton;
    //juce::ButtonParameterAttachment resetButtonAttachment;
    
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDELAYAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDELAYAudioProcessorEditor)
};
