/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleDELAYAudioProcessorEditor::SimpleDELAYAudioProcessorEditor (SimpleDELAYAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    resetButton.setButtonText( "Reset Delay Settings");
    resetButton.addListener( this );
    addAndMakeVisible( &resetButton );
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

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("SimpleDELAY", getLocalBounds(), juce::Justification::centred, 1);
}

void SimpleDELAYAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // x, y, width, height
    //resetButton.setBounds (0, 0, getWidth() / 2, 50 );
    //resetButton.centreWithSize(100,50);
    auto bounds = getLocalBounds();
    
    auto resetButtonArea = bounds.removeFromBottom( 50 ).removeFromRight( bounds.getWidth() / 2 );
    resetButtonArea.setX( bounds.getWidth() / 4 );
    resetButton.setBounds( resetButtonArea );
}

void SimpleDELAYAudioProcessorEditor::buttonClicked(juce::Button *button) {
    if (button == &resetButton) {
        std::cout << "Hello Rest Button" << std::endl;
        audioProcessor.resetDelaySettings();
    }
}
