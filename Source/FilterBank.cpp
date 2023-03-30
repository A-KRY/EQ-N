/*
  ==============================================================================

    FilterBank.cpp
    Created: 27 Mar 2023 3:49:09pm
    Author:  Admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterBank.h"


//==============================================================================
#define C(constant) Constant::FilterBank::constant
FilterBank::FilterBank() :
	filters(C(filterNumber))
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(C(width), C(height));

    for (int i = 0; i < C(filterNumber); ++i)
    {
        filters[i].setOrder(i+1);

        filters[i].setFilterMode(i == 0 ? FilterComponent::FilterMode::HighPass : (i == C(filterNumber) - 1 ? FilterComponent::FilterMode::LowPass : FilterComponent::FilterMode::Peak));

#define FREQ(mode) Constant::DefaultVal::Filter::mode
        filters[i].setDefaultFreq(i == 0 ? FREQ(highPass) : (i == C(filterNumber) - 1 ? FREQ(lowPass) : FREQ(peak)));
#undef FREQ

        filters[i].setThemeColour(Constant::Colours::filterComponentThemeColour[i]);

        addAndMakeVisible(filters[i]);
    }

}
#undef C

FilterBank::~FilterBank()
{
}

void FilterBank::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll(Constant::Colours::backgroundInner);
    g.setColour(Constant::Colours::filterBankBackground);
    g.fillRoundedRectangle(0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight()), 10);

    g.setColour(juce::Colours::darkgrey);
    g.setFont(15.0f);
    g.drawText("By A-KRY", getWidth() - 70, getHeight() - 20, 70, 20, juce::Justification::centred);
}

void FilterBank::resized()
{
#define C(constant) Constant::FilterBank::constant
    // This method is where you should set the bounds of any child
    // components that your component contains..
    if (0 != filters.size())
	{
        for (int i = 0; i < C(filterNumber); ++i)
        {
            const auto filterWidth = Constant::FilterComponent::width, filterHeight = Constant::FilterComponent::height;
            filters[i].setBounds((getWidth() - filterWidth) / 2, (i + 1) * C(spacing) + i * filterHeight, filterWidth, filterHeight);
        }
    }

#undef C
}

std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> FilterBank::createSliderAttachment(const int filterIndex, juce::AudioProcessorValueTreeState& stateToUse,
    const juce::String& parameterID, FilterComponent::AttachmentType type)
{
	return filters[filterIndex].createSliderAttachment(stateToUse, parameterID, type);
}

std::shared_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> FilterBank::createComboBoxAttachment(
    const int filterIndex, juce::AudioProcessorValueTreeState& stateToUse, const juce::String& parameterID)
{
    return filters[filterIndex].createComboBoxAttachment(stateToUse, parameterID);
}

void FilterBank::prepare(const juce::dsp::ProcessSpec& spec)
{
    for (auto& filter : filters)
    {
        filter.prepare(spec);
    }
}

void FilterBank::process(const juce::dsp::ProcessContextReplacing<float> context[])
{
    for (auto& filter : filters)
    {
        filter.process(context);
    }
}

void FilterBank::reset()
{
    for (auto& filter : filters)
    {
        filter.reset();
    }
}

void FilterBank::updateCoefficients(const int filterIndex, const FilterComponent::Settings& settings)
{
    filters[filterIndex].updateCoefficients(settings);
}
