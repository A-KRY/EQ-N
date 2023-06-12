/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "FilterBank.h"
#include "FilterComponent.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class EQNAudioProcessor;

class EQNAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EQNAudioProcessorEditor (EQNAudioProcessor&);
    ~EQNAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    // void updateFilterCoefficients();

    // void filterPrepare(const juce::dsp::ProcessSpec& spec);

    // void filterProcess(const juce::dsp::ProcessContextReplacing<float> context[]);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EQNAudioProcessor& audioProcessor;

    FilterBank* filterBank;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQNAudioProcessorEditor)
};
