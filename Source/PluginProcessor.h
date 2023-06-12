/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginEditor.h"
#include "Convert.h"

class EQNAudioProcessorEditor;

//==============================================================================
/**
*/
class EQNAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    EQNAudioProcessor();
    ~EQNAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // 声道枚举
    enum Channels { LeftChannel = 0, RightChannel = 1 };

    // AudioProcessorParameterTree
    juce::AudioProcessorValueTreeState apvts;

    FilterBank* getFilterBank()
    {
        return &filterBank;
    }

private:

    // 创建参数
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    // FilterBank
    FilterBank filterBank;

#define SLIDER_ATTACHMENT juce::AudioProcessorValueTreeState::SliderAttachment
    std::vector<std::shared_ptr<SLIDER_ATTACHMENT>> freqKnobAttachment, gainKnobAttachment, qualityKnobAttachment;
#undef SLIDER_ATTACHMENT

    void updateFilterCoefficients();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQNAudioProcessor)
};
