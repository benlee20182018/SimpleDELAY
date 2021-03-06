/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
static const juce::NormalisableRange<float> DELAY_RANGE { 0.01f, 20.0f, 0.01f, 1.0f };

//==============================================================================
SimpleDELAYAudioProcessor::SimpleDELAYAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

SimpleDELAYAudioProcessor::~SimpleDELAYAudioProcessor()
{
}

//==============================================================================
const juce::String SimpleDELAYAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleDELAYAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleDELAYAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleDELAYAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleDELAYAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleDELAYAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleDELAYAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleDELAYAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleDELAYAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleDELAYAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SimpleDELAYAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::dsp::ProcessSpec spec;
    
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = 2;
    
    delay.prepare( spec );

    updateDelaySettings( );
}

void SimpleDELAYAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleDELAYAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleDELAYAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    updateDelaySettings();
    
    juce::dsp::AudioBlock<float> block(buffer);
    
    juce::dsp::ProcessContextReplacing<float> context(block);
    
    delay.process( context );
}

//==============================================================================
bool SimpleDELAYAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleDELAYAudioProcessor::createEditor()
{
    return new SimpleDELAYAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void SimpleDELAYAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::MemoryOutputStream mos( destData, true );
    apvts.state.writeToStream(mos);
}

void SimpleDELAYAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    auto tree = juce::ValueTree::readFromData(data,sizeInBytes);
    if (tree.isValid()) {
        apvts.replaceState(tree);
        updateDelaySettings();
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDELAYAudioProcessor();
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout
SimpleDELAYAudioProcessor::CreateParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    layout.add(
       std::make_unique<juce::AudioParameterFloat>(
          DelaySettingIDs::LEFT_DELAY_TIME,
          DelaySettingIDs::LEFT_DELAY_TIME,
          DELAY_RANGE,
          DEFAULT_DELAY_SETTINGS.leftDelayTime ));
               
    layout.add(
       std::make_unique<juce::AudioParameterFloat>(
          DelaySettingIDs::RIGHT_DELAY_TIME,
          DelaySettingIDs::RIGHT_DELAY_TIME,
          DELAY_RANGE,
          DEFAULT_DELAY_SETTINGS.rightDelayTime ));
               
    layout.add(
       std::make_unique<juce::AudioParameterFloat>(
          DelaySettingIDs::FEEDBACK,
          DelaySettingIDs::FEEDBACK,
          juce::NormalisableRange<float>( 0.0f, 1.0f, 0.01f, 1.0f ),
          DEFAULT_DELAY_SETTINGS.feedback ));
               
    layout.add(
       std::make_unique<juce::AudioParameterFloat>(
          DelaySettingIDs::WET_LEVEL,
          DelaySettingIDs::WET_LEVEL,
          juce::NormalisableRange<float>( 0.0f, 1.0f, 0.01f, 1.0f ),
          DEFAULT_DELAY_SETTINGS.wetLevel ));
    
    layout.add(
       std::make_unique<juce::AudioParameterFloat>(
          DelaySettingIDs::GAIN,
          DelaySettingIDs::GAIN,
          juce::NormalisableRange<float>( 0.0f, 1.0f, 0.01f, 1.0f ),
          DEFAULT_DELAY_SETTINGS.gain ));
    
    layout.add(
       std::make_unique<juce::AudioParameterFloat>(
          DelaySettingIDs::TEMPO_SYNC,
          DelaySettingIDs::TEMPO_SYNC,
          juce::NormalisableRange<float>( 1.0f, 7.0f, 1.0f, 1.0f ),
          DEFAULT_DELAY_SETTINGS.tempoSync ));
    
    return layout;
}

//==============================================================================
DelaySettings GetDelaySettings(juce::AudioProcessorValueTreeState& apvts) {
    DelaySettings delaySettings;
    
    delaySettings.leftDelayTime = apvts.getRawParameterValue( DelaySettingIDs::LEFT_DELAY_TIME )->load();
    delaySettings.rightDelayTime = apvts.getRawParameterValue( DelaySettingIDs::RIGHT_DELAY_TIME )->load();
    delaySettings.feedback = apvts.getRawParameterValue( DelaySettingIDs::FEEDBACK )->load();
    delaySettings.wetLevel = apvts.getRawParameterValue( DelaySettingIDs::WET_LEVEL )->load();
    delaySettings.gain = apvts.getRawParameterValue( DelaySettingIDs::GAIN )->load();
    delaySettings.tempoSync = apvts.getRawParameterValue( DelaySettingIDs::TEMPO_SYNC )->load();
    
    return delaySettings;
}

//==============================================================================
float MapSyncFactor(int option) {
    switch (option) {
        case TempoSyncOptions::half: return 2.0;
        case TempoSyncOptions::quarter: return 4.0;
        case TempoSyncOptions::eighth: return 8.0;
        case TempoSyncOptions::sixteenth: return 16.0;
        case TempoSyncOptions::thirtysecond: return 32.0;
        default: return 1.0;
    }
}

float CalculateDelayTime(const juce::AudioPlayHead::CurrentPositionInfo & info, int option) {
    float factor = MapSyncFactor( option );
    float secondsPerBeat = 60.0 / info.bpm;
    float numBeats = info.timeSigDenominator / factor;
    float result = numBeats * secondsPerBeat;
    return result;
}

//==============================================================================
void SimpleDELAYAudioProcessor::updateDelaySettings() {
    auto delaySettings = GetDelaySettings( apvts );
    updateDelaySettings(delaySettings);
}

enum Channel {
    left=0,
    right=1
};

void SimpleDELAYAudioProcessor::updateDelaySettings(const DelaySettings & delaySettings) {
    auto leftDelayTime = delaySettings.leftDelayTime;
    auto rightDelayTime = delaySettings.rightDelayTime;
    
    if ( delaySettings.tempoSync != TempoSyncOptions::off ) {
        if (auto * playHead = getPlayHead() ) {
            juce::AudioPlayHead::CurrentPositionInfo info;
            playHead->getCurrentPosition( info );
            
            if ( info.bpm > 0 ) {
                auto time = CalculateDelayTime( info, delaySettings.tempoSync );
                
                leftDelayTime = time;
                rightDelayTime = time * 2;
                
                apvts.getParameter( DelaySettingIDs::LEFT_DELAY_TIME )->setValueNotifyingHost( DELAY_RANGE.convertTo0to1( leftDelayTime ) );
                apvts.getParameter( DelaySettingIDs::RIGHT_DELAY_TIME )->setValueNotifyingHost( DELAY_RANGE.convertTo0to1( rightDelayTime ) );
            }
        }
    }
   
    delay.setDelayTime( Channel::left, leftDelayTime );
    delay.setDelayTime( Channel::right, rightDelayTime );
    delay.setFeedback( delaySettings.feedback );
    delay.setWetLevel( delaySettings.wetLevel );
    delay.setGain( delaySettings.gain );
}
