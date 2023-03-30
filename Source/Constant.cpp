/*
  ==============================================================================

    Constant.cpp
    Created: 25 Mar 2023 5:44:40pm
    Author:  Admin

  ==============================================================================
*/

#include "Constant.h"

namespace Constant
{
    namespace Knob
    {

        const int nameLabelWidth = 30;

        const int nameLabelHeight = 15;

        const double sensitivity = 2.0;

        const double threshold = 1.0;

        const double offset = 0.1;
    }

    namespace FilterComponent {

        const double gainDefaultVal = 0.5;

        const double qualityDefaultVal = 0.5;

        const double lpfDefaultVal = 1.0;

        const double hpfDefaultVal = 0.0;

        const double pfDefaultVal = 0.5;

        const double lsfDefaultVal = 0.25;

        const double hsfDefaultVal = 0.75;

        const int spacing = 20;

        const int orderLabelWidth = 30;

        const int orderLabelHeight = 30;

        const int knobWidth = 60;

        const int knobHeight = 60;

        const int modeBoxWidth = 120;

        const int modeBoxHeight = 20;

        const int bypassButtonWidth = 15;

        const int bypassButtonHeight = 15;

        const int bypassLabelWidth = 60;

        const int bypassLabelHeight = 20;

        const float bypassLabelFontSize = 15.0f;

        const int width = 500;

        const int height = 100;
    }

    namespace KnobLookAndFeel
    {
        const int sliderWidth = FilterComponent::knobWidth;

        const int sliderHeight = FilterComponent::knobHeight;

        const double fontSize = 15.0;

        const int textBoxWidth = sliderWidth;

        const int textBoxHeight = static_cast<int>(sliderHeight * 0.25);
    }

    namespace FilterBank
    {
        const int filterNumber = 6;

        const int spacing = 20;

        const int width = 2 * spacing + Constant::FilterComponent::width;

        const int height = (filterNumber + 1) * spacing + filterNumber * Constant::FilterComponent::height;
    }

    namespace DefaultVal::Filter
    {
        const double lowPass = 1.0;

        const double highPass = 0.0;

        const double peak = 0.5;

        const double lowShelf = 0.25;

        const double highShelf = 0.75;

        const double gain = 0.5;

        const double quality = 0.5;
    }

    namespace FreqOscilloscope
    {
        const int spacing = 20;

        const int width = FilterComponent::width;

        const int height = (FilterBank::height - spacing) / 2;
    }

    namespace PluginEditor
    {
        const int spacing = 20;

        const int editorWidth = FilterBank::width+3*spacing;

        const int editorHeight = FilterBank::height + spacing * 2;
    }

    namespace Colours
    {
        const juce::Colour backgroundInner = juce::Colour(0xff161616), backgroundOuter = juce::Colour(0xff3b3b3b);

        const juce::Colour filterBankBackground = juce::Colours::dimgrey;

        const juce::Colour filterComponentBackground = juce::Colour(0xff2c2c2c);

        const juce::Colour filterComponentThemeColour[] = {
            juce::Colour(0xff00bfff), // 深天蓝
		    juce::Colour(0xff00ced1), // 暗青色
		    juce::Colour(0xff00ff00), // 酸橙色
		    juce::Colour(0xffffde2b), // 黄色
		    juce::Colour(0xff9b92ff), // 紫色
		    juce::Colour(0xffff6f86)  // 洋红色
        };
    }
}