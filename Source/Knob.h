/*
  ==============================================================================

    Knob.h
    Created: 22 Mar 2023 7:19:28pm
    Author:  Admin

  ==============================================================================
*/

#pragma once
#ifndef KNOB_H_
#define KNOB_H_

#include <JuceHeader.h>

#include "KnobLookAndFeel.h"

#include "Constant.h"

class Knob : public juce::Slider
{
public:
    Knob();
    ~Knob() override;

    void paint(juce::Graphics&) override;
    // void resized() override;
    void mouseUp(const juce::MouseEvent& event) override;
    void mouseDown(const juce::MouseEvent& event) override;

    // ¸设置拖动条颜色
    void setBarColour(juce::Colour newColour);

    // 设置名称标签
    void setNameLabelText(const juce::String& name);

private:

    juce::Label nameLabel;

    KnobLookAndFeel knobLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
};

#endif