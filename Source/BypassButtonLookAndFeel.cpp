/*
  ==============================================================================

    BypassButton.cpp
    Created: 28 Mar 2023 3:51:42pm
    Author:  Admin

  ==============================================================================
*/

#include "BypassButtonLookAndFeel.h"

void BypassButtonLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& toggleButton,
	bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	LookAndFeel_V4::drawToggleButton(g, toggleButton, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
	if (toggleButton.getToggleState())
    {
        const juce::ColourGradient gradient(juce::Colours::yellow, static_cast<float>(toggleButton.getLocalBounds().getCentreX()), 
            static_cast<float>(toggleButton.getLocalBounds().getY()),
            juce::Colours::orange, 
            static_cast<float>(toggleButton.getLocalBounds().getCentreX()), 
           static_cast<float>( toggleButton.getLocalBounds().getBottom()), true);
        g.setGradientFill(gradient);
        g.fillEllipse(toggleButton.getLocalBounds().toFloat());
    }
    else
    {
        g.setColour(juce::Colours::white);
        g.drawEllipse(toggleButton.getLocalBounds().toFloat(), 1.0f);
    }
}
