/*
  ==============================================================================

    KnobLookAndFeel.cpp
    Created: 22 Mar 2023 7:27:04pm
    Author:  Admin

  ==============================================================================
*/

#include "KnobLookAndFeel.h"

#include "Constant.h"

KnobLookAndFeel::KnobLookAndFeel()
{
}

KnobLookAndFeel::~KnobLookAndFeel()
{
}

juce::Slider::SliderLayout KnobLookAndFeel::getSliderLayout(juce::Slider& slider)
{
#define C(constant) Constant::KnobLookAndFeel::constant

	const auto localBounds = slider.getLocalBounds();

	juce::Slider::SliderLayout layout;

	layout.textBoxBounds = juce::Rectangle<int>((slider.getWidth()-C(textBoxWidth))/2, slider.getHeight() * 0.9 - C(textBoxHeight) * 0.6, C(textBoxWidth), C(textBoxHeight));
	layout.sliderBounds = juce::Rectangle<int>(0, 0, C(sliderWidth), C(sliderHeight)*0.9);

	return layout;

#undef C
}

void KnobLookAndFeel::drawRotarySlider(juce::Graphics& graphics, int x, int y, int width, int height,
	float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
	LookAndFeel_V4::drawRotarySlider(graphics, x, y, width, height, sliderPosProportional, rotaryStartAngle,
		rotaryEndAngle, slider);
}

juce::Label* KnobLookAndFeel::createSliderTextBox(juce::Slider& slider)
{
#define C(constant) Constant::KnobLookAndFeel::constant

	auto label = new juce::Label();

	label->setFont(juce::Font(C(fontSize)));
	label->setJustificationType(juce::Justification::centred);
	label->setColour(juce::Label::textColourId, slider.findColour(juce::Slider::textBoxTextColourId));
	label->setColour(juce::Label::textWhenEditingColourId, slider.findColour(juce::Slider::textBoxTextColourId));
	label->setColour(juce::Label::outlineWhenEditingColourId, slider.findColour(juce::Slider::textBoxOutlineColourId));
	label->setInterceptsMouseClicks(true, false);
	label->setEditable(false, true);

	return label;
#undef C
}
