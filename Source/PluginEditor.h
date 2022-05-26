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
   Extensions for streamlining construction.
 */
struct RotarySlider : juce::Slider {
    RotarySlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                  juce::Slider::TextEntryBoxPosition::TextBoxBelow ) {
        
    }
};

struct Label : juce::Label {
    Label() : juce::Label() {
        setJustificationType( juce::Justification::Flags::horizontallyCentred );
    }
    
    void setText(const std::string & text) {
        juce::Label::setText( text, juce::NotificationType::dontSendNotification );
    }
};

//==============================================================================
/**
*/
class SimpleDELAYAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    SimpleDELAYAudioProcessorEditor (SimpleDELAYAudioProcessor&);
    ~SimpleDELAYAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    RotarySlider leftDelaySlider;
    RotarySlider rightDelaySlider;
    RotarySlider feedbackSlider;
    RotarySlider wetLevelSlider;
    RotarySlider gainSlider;
    
    using APVTS = juce::AudioProcessorValueTreeState;
    using SliderAttachment = APVTS::SliderAttachment;
    
    SliderAttachment leftDelaySliderAttachment;
    SliderAttachment rightDelaySliderAttachment;
    SliderAttachment feedbackSliderAttachment;
    SliderAttachment wetLevelSliderAttachment;
    SliderAttachment gainSliderAttachment;
    
    Label leftDelayLabel;
    Label rightDelayLabel;
    Label feedbackLabel;
    Label wetLevelLabel;
    Label gainLabel;
    
    using ButtonAttachment = APVTS::ButtonAttachment;
    
    juce::ToggleButton tempoSyncButton;
    ButtonAttachment tempoSyncButtonAttachment;
    
    juce::TextButton resetButton;
    
    std::vector<RotarySlider*> getSliders();
    void onResetButtonClicked();
    void updateTempoSyncToggleState();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDELAYAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDELAYAudioProcessorEditor)
};
