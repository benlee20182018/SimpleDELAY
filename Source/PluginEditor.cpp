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
    
    leftDelayLabel.setText( DelaySettingIDs::LEFT_DELAY_TIME );
    rightDelayLabel.setText( DelaySettingIDs::RIGHT_DELAY_TIME );
    feedbackLabel.setText( DelaySettingIDs::FEEDBACK );
    wetLevelLabel.setText( DelaySettingIDs::WET_LEVEL );
    gainLabel.setText( DelaySettingIDs::GAIN );
    
    addAndMakeVisible( leftDelayLabel );
    addAndMakeVisible( rightDelayLabel );
    addAndMakeVisible( feedbackLabel );
    addAndMakeVisible( wetLevelLabel );
    addAndMakeVisible( gainLabel );
    
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

/**
 ASSUMPTION: setSize( 800,600 ).
 */
void SimpleDELAYAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    
    auto center = bounds.getWidth() / 2;
    
    bounds.removeFromBottom( 25 );
    
    auto resetButtonArea = bounds.removeFromBottom( 50 ).removeFromRight( bounds.getWidth() / 2 );
    resetButtonArea.setX( bounds.getWidth() / 4 );
    resetButton.setBounds( resetButtonArea );
    
    bounds.removeFromBottom( 50 );
    
    auto leftDelayArea = bounds.removeFromLeft( bounds.getWidth() * 0.33 );
    auto rightDelayArea = bounds.removeFromRight( bounds.getWidth() * 0.5 );
    
    auto leftDelayLabelArea = leftDelayArea.removeFromTop( bounds.getHeight() * 0.1 );
    auto rightDelayLabelArea = rightDelayArea.removeFromTop( bounds.getHeight() * 0.1 );
    
    leftDelayArea.removeFromBottom( bounds.getHeight() * 0.33 );
    rightDelayArea.removeFromBottom( bounds.getHeight() * 0.33 );
    
    leftDelaySlider.setBounds( leftDelayArea );
    rightDelaySlider.setBounds( rightDelayArea );
    
    leftDelayLabel.setBounds( leftDelayLabelArea );
    rightDelayLabel.setBounds( rightDelayLabelArea );
    
    auto labelHeight = 20;
    auto pad = 20;
    auto width = bounds.getHeight() * 0.20;
    auto x = center - (width/2);
    
    auto y = pad * 3;
    feedbackLabel.setBounds( x, y, width, labelHeight );
    y += labelHeight;
    feedbackSlider.setBounds( x, y, width, width );
    y += labelHeight + width + pad;
    wetLevelLabel.setBounds( x, y, width, labelHeight );
    y += labelHeight;
    wetLevelSlider.setBounds( x, y, width, width );
    y += labelHeight + width + pad;
    gainLabel.setBounds( x, y, width, labelHeight );
    y += labelHeight;
    gainSlider.setBounds( x, y, width, width );
}

void SimpleDELAYAudioProcessorEditor::buttonClicked(juce::Button *button) {
    if (button == &resetButton) {
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
