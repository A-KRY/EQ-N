/*
  ==============================================================================

    Knob.cpp
    Created: 22 Mar 2023 7:19:28pm
    Author:  Admin

  ==============================================================================
*/

#include "Knob.h"

Knob::Knob()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

#define C(constant) Constant::Knob::constant

    setLookAndFeel(&knobLookAndFeel);
    setSliderStyle(RotaryHorizontalVerticalDrag);

    setRotaryParameters(juce::MathConstants<float>::pi * 1.25f,
        juce::MathConstants<float>::pi * 2.75f, true);
    setVelocityBasedMode(true);
    setVelocityModeParameters(Constant::Knob::sensitivity,
         C(threshold),
        C(offset), false);
    setWantsKeyboardFocus(true);
    setColour(thumbColourId, juce::Colours::transparentBlack);
    setColour(ColourIds::rotarySliderOutlineColourId, juce::Colours::grey);

    // 设置名称标签

    nameLabel.setSize(C(nameLabelWidth), C(nameLabelHeight));
    nameLabel.attachToComponent(this, false);
    nameLabel.setEditable(false);
    nameLabel.setJustificationType(juce::Justification::centred);

#undef C
}

Knob::~Knob()
{
    setLookAndFeel(nullptr);
}

void Knob::paint(juce::Graphics& g)
{
    juce::Slider::paint(g);
    if (hasKeyboardFocus(false))
    {
        auto bounds = getLocalBounds().toFloat();
        auto h = bounds.getHeight();
        auto w = bounds.getWidth();
        auto len = juce::jmin(h, w) * 0.07f;
        auto thick = len / 1.8f;

        g.setColour(findColour(juce::Slider::textBoxOutlineColourId));

        // Left top
        g.drawLine(0.0f, 0.0f, 0.0f, len, thick);
        g.drawLine(0.0f, 0.0f, len, 0.0f, thick);

        // Left bottom
        g.drawLine(0.0f, h, 0.0f, h - len, thick);
        g.drawLine(0.0f, h, len, h, thick);

        // Right top
        g.drawLine(w, 0.0f, w, len, thick);
        g.drawLine(w, 0.0f, w - len, 0.0f, thick);

        // Right bottom
        g.drawLine(w, h, w, h - len, thick);
        g.drawLine(w, h, w - len, h, thick);
    }
}

/*void Knob::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}*/

void Knob::mouseUp(const juce::MouseEvent& event)
{
    Slider::mouseUp(event);

    juce::Desktop::getInstance().getMainMouseSource().setScreenPosition(event.source.getLastMouseDownPosition());

    // 抬起时显示鼠标
    setMouseCursor(juce::MouseCursor::NormalCursor);
}

void Knob::mouseDown(const juce::MouseEvent& event)
{
    Slider::mouseDown(event);
    // 按下时鼠标消失
    setMouseCursor(juce::MouseCursor::NoCursor);
}

void Knob::setBarColour(juce::Colour newColour)
{
    setColour(ColourIds::rotarySliderFillColourId, newColour);
}

void Knob::setNameLabelText(const juce::String& name)
{
    nameLabel.setText(name, juce::sendNotification);
}
