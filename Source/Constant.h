/*
  ==============================================================================

    Constant.h
    Created: 25 Mar 2023 5:44:40pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace Constant
{
    namespace PluginEditor
    {
        extern const int spacing;

        extern const int editorWidth;

        extern const int editorHeight;
    }

    namespace Knob
    {
        extern const int nameLabelWidth;

        extern const int nameLabelHeight;

        extern const double sensitivity;

        extern const double threshold;

        extern const double offset;
    }

    namespace KnobLookAndFeel
    {
    	extern const int sliderWidth;

        extern const int sliderHeight;

        extern const double fontSize;

        extern const int textBoxWidth;

        extern const int textBoxHeight;
    }

    namespace FilterComponent {

        extern const double gainDefaultVal;

        extern const double qualityDefaultVal;

        extern const double lpfDefaultVal;

        extern const double hpfDefaultVal;

        extern const double pfDefaultVal;

        extern const double lsfDefaultVal;

        extern const double hsfDefaultVal;

        extern const int spacing;

        extern const int width;

        extern const int height;

        extern const int orderLabelWidth;

        extern const int orderLabelHeight;

        extern const int knobWidth;

        extern const int knobHeight;

        extern const int modeBoxWidth;

        extern const int modeBoxHeight;

        extern const int orderLabelWidth;

        extern const int orderLabelHeight;

        extern const int bypassButtonWidth;

        extern const int bypassButtonHeight;

        extern const int bypassLabelWidth;

        extern const int bypassLabelHeight;

        extern const float bypassLabelFontSize;
    }

    namespace FilterBank
    {
        extern const int width;

        extern const int height;

        extern const int filterNumber;

        extern const int spacing;
    }

    namespace DefaultVal::Filter
    {
        extern const double lowPass;

        extern const double highPass;

        extern const double peak;

        extern const double lowShelf;

        extern const double highShelf;

        extern const double gain;

        extern const double quality;
    }

    namespace FreqOscilloscope
    {
        extern const int width;

        extern const int height;

        extern const int spacing;
    }

    namespace Colours
    {
        extern const juce::Colour backgroundInner, backgroundOuter;

        extern const juce::Colour filterBankBackground;

        extern const juce::Colour filterComponentBackground;

        extern const juce::Colour filterComponentThemeColour[];
    }
}
