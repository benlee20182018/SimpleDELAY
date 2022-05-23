/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleDELAYAudioProcessorEditor::SimpleDELAYAudioProcessorEditor (SimpleDELAYAudioProcessor& p)
    : AudioProcessorEditor (&p),
    leftDelaySliderAttachment  ( p.getState(), DelaySettingIDs::LEFT_DELAY_TIME,  leftDelaySlider  ),
    rightDelaySliderAttachment ( p.getState(), DelaySettingIDs::RIGHT_DELAY_TIME, rightDelaySlider ),
    feedbackSliderAttachment   ( p.getState(), DelaySettingIDs::FEEDBACK,         feedbackSlider   ),
    wetLevelSliderAttachment   ( p.getState(), DelaySettingIDs::WET_LEVEL,        wetLevelSlider   ),
    gainSliderAttachment       ( p.getState(), DelaySettingIDs::GAIN,             gainSlider       ),
    audioProcessor (p)
{
    resetButton.setButtonText( "Reset Delay Settings");
    resetButton.addListener( this );
    addAndMakeVisible( &resetButton );
    for (auto * slider : getSliders() ) {
        addAndMakeVisible( slider );
    }
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
}

SimpleDELAYAudioProcessorEditor::~SimpleDELAYAudioProcessorEditor()
{
}

//==============================================================================
void SimpleDELAYAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SimpleDELAYAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // x, y, width, height
    //resetButton.setBounds (0, 0, getWidth() / 2, 50 );
    //resetButton.centreWithSize(100,50);
    auto bounds = getLocalBounds();
    
    bounds.removeFromBottom( 25 );
    
    auto resetButtonArea = bounds.removeFromBottom( 50 ).removeFromRight( bounds.getWidth() / 2 );
    resetButtonArea.setX( bounds.getWidth() / 4 );
    resetButton.setBounds( resetButtonArea );
    
    bounds.removeFromBottom( 50 );
    
    auto leftDelayArea = bounds.removeFromLeft( bounds.getWidth() * 0.33 );
    auto rightDelayArea = bounds.removeFromRight( bounds.getWidth() * 0.5 );
    
    leftDelaySlider.setBounds( leftDelayArea );
    rightDelaySlider.setBounds( rightDelayArea );
    
    feedbackSlider.setBounds( bounds.removeFromTop( bounds.getHeight() * 0.33) );
    wetLevelSlider.setBounds( bounds.removeFromTop( bounds.getHeight() * 0.5 ) );
    gainSlider.setBounds( bounds );
}

void SimpleDELAYAudioProcessorEditor::buttonClicked(juce::Button *button) {
    if (button == &resetButton) {
        std::cout << "Hello Reset Button" << std::endl;
        //audioProcessor.resetDelaySettings();
        leftDelaySlider.setValue( DEFAULT_DELAY_SETTINGS.leftDelayTime );
        rightDelaySlider.setValue( DEFAULT_DELAY_SETTINGS.rightDelayTime );
        feedbackSlider.setValue( DEFAULT_DELAY_SETTINGS.feedback );
        wetLevelSlider.setValue( DEFAULT_DELAY_SETTINGS.wetLevel );
        gainSlider.setValue( DEFAULT_DELAY_SETTINGS.gain );
    }
}

std::vector<RotarySlider*> SimpleDELAYAudioProcessorEditor::getSliders() {
    return {
        &leftDelaySlider,
        &rightDelaySlider,
        &feedbackSlider,
        &wetLevelSlider,
        &gainSlider
    };
}
