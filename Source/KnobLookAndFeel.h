/*
  ==============================================================================

    KnobLookAndFeel.h
    Created: 22 Mar 2023 7:27:04pm
    Author:  Admin

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class KnobLookAndFeel :
    public juce::LookAndFeel_V4
{
public:
    KnobLookAndFeel();
    ~KnobLookAndFeel() override;

    juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override;

    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider&) override;

    juce::Label* createSliderTextBox(juce::Slider& slider) override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobLookAndFeel)
};

