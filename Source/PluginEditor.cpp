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
    
    leftDelayLabel.setText( DelaySettingIDs::LEFT_DELAY_TIME, juce::NotificationType::dontSendNotification );
    leftDelayLabel.setJustificationType( juce::Justification::Flags::horizontallyCentred );
    addAndMakeVisible( leftDelayLabel );
    rightDelayLabel.setText( DelaySettingIDs::RIGHT_DELAY_TIME, juce::NotificationType::dontSendNotification );
    rightDelayLabel.setJustificationType( juce::Justification::Flags::horizontallyCentred );
    addAndMakeVisible( rightDelayLabel );
    feedbackLabel.setText( DelaySettingIDs::FEEDBACK, juce::NotificationType::dontSendNotification );
    feedbackLabel.setJustificationType( juce::Justification::Flags::horizontallyCentred );
    addAndMakeVisible( feedbackLabel );
    wetLevelLabel.setText( DelaySettingIDs::WET_LEVEL, juce::NotificationType::dontSendNotification );
    wetLevelLabel.setJustificationType( juce::Justification::Flags::horizontallyCentred );
    addAndMakeVisible( wetLevelLabel );
    gainLabel.setText( DelaySettingIDs::GAIN, juce::NotificationType::dontSendNotification );
    gainLabel.setJustificationType( juce::Justification::Flags::horizontallyCentred );
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

void SimpleDELAYAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // x, y, width, height
    //resetButton.setBounds (0, 0, getWidth() / 2, 50 );
    //resetButton.centreWithSize(100,50);
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
    
    
    //auto labelHeight = bounds.getHeight() * 0.1;
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
    /*
    wetLevelLabel.setBounds( bounds.removeFromTop( bounds.getHeight() * 0.1 ) );
    wetLevelSlider.setBounds( bounds.removeFromTop( bounds.getHeight() * 0.5 ) );
    gainLabel.setBounds( bounds.removeFromTop( bounds.getHeight() * 0.1 ) );
    gainSlider.setBounds( bounds.removeFromTop( bounds.getHeight() * 0.5 ) );
     */
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
