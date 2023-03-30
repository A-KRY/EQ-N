/*
  ==============================================================================

    BypassButton.h
    Created: 28 Mar 2023 3:51:42pm
    Author:  Admin

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class BypassButtonLookAndFeel : public juce::LookAndFeel_V4
{
public:
	BypassButtonLookAndFeel() = default;

	~BypassButtonLookAndFeel() override = default;

	void drawToggleButton(juce::Graphics&, juce::ToggleButton&, bool shouldDrawButtonAsHighlighted,
	                      bool shouldDrawButtonAsDown) override;

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BypassButtonLookAndFeel)
};

