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
class SimpleDELAYAudioProcessorEditor : public juce::AudioProcessorEditor, public juce::Button::Listener
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
    using Attachment = APVTS::SliderAttachment;
    
    Attachment leftDelaySliderAttachment;
    Attachment rightDelaySliderAttachment;
    Attachment feedbackSliderAttachment;
    Attachment wetLevelSliderAttachment;
    Attachment gainSliderAttachment;
    
    Label leftDelayLabel;
    Label rightDelayLabel;
    Label feedbackLabel;
    Label wetLevelLabel;
    Label gainLabel;
    
    juce::TextButton resetButton;
    
    std::vector<RotarySlider*> getSliders();
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDELAYAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDELAYAudioProcessorEditor)
};
