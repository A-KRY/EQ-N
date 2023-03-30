/*
  ==============================================================================

    FreqOscilloscope.h
    Created: 29 Mar 2023 5:43:34pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FreqOscilloscope  : public juce::Component
{
public:
    FreqOscilloscope();
    ~FreqOscilloscope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:



    juce::Path freqDomainCurve, overallFreqRespCurve, singleFreqRespCurve;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreqOscilloscope)
};
