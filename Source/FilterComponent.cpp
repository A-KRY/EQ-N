/*
  ==============================================================================

    FilterComponent.cpp
    Created: 22 Mar 2023 10:53:50pm
    Author:  Admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
#define C(constant) Constant::FilterComponent::constant
FilterComponent::FilterComponent(const int newOrder) :
	order(newOrder),
	themeColour(juce::Colours::white),
	defaultColour(juce::Colours::lightgrey)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    // 设置序号标签

    orderLabel.setFont({ "Consolas", 20.0f ,juce::Font::plain});
    orderLabel.setText(juce::String(order), juce::dontSendNotification);
    orderLabel.setJustificationType(juce::Justification::centred);
    orderLabel.setSize(Constant::FilterComponent::orderLabelWidth, Constant::FilterComponent::orderLabelHeight);
    // orderLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::white);

    // 设置频率旋钮参数
	freqKnob.setNameLabelText("Freq");
    freqKnob.setTextValueSuffix(" Hz");
    freqKnob.setNumDecimalPlacesToDisplay(0);

    // 设置增益旋钮参数
    gainKnob.setNameLabelText("Gain");
    gainKnob.setTextValueSuffix(" dB");
    gainKnob.setNumDecimalPlacesToDisplay(1);
    gainKnob.setDoubleClickReturnValue(true, C(gainDefaultVal), juce::ModifierKeys::noModifiers);
    gainKnob.setValue(Constant::FilterComponent::gainDefaultVal);

    // 设置品质因数旋钮
    qualityKnob.setNameLabelText("Q");
    qualityKnob.setNumDecimalPlacesToDisplay(1);
    qualityKnob.setDoubleClickReturnValue(true, C(qualityDefaultVal), juce::ModifierKeys::noModifiers);
    qualityKnob.setValue(Constant::FilterComponent::qualityDefaultVal);

    // 设置滤波模式栏
	filterModeBox.addItemList(juce::StringArray(
        { "Low-Cut", "High-Cut", "Peak",	"Low-Shelf", "High-Shelf"}),
        1);
    filterModeBox.setJustificationType(juce::Justification::centred);
    filterModeBox.setColour(juce::ComboBox::ColourIds::backgroundColourId, Constant::Colours::filterComponentBackground);
    filterModeBox.setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colours::white);
    filterModeBox.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::white);

    // 设置旁通按钮
    bypassButton.setLookAndFeel(&bypassLookAndFeel);
    bypassButton.setSize(C(bypassButtonWidth), C(bypassButtonHeight));
    bypassButton.setColour(juce::ToggleButton::ColourIds::tickColourId, juce::Colours::transparentBlack);
    bypassButton.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, juce::Colours::transparentBlack);
    bypassButton.setToggleable(true);
    bypassButton.onStateChange = [&]()
    {
        for (auto* child : getChildren())
        {
            if (child != &bypassButton)
            {
                child->setEnabled(!bypassButton.getToggleState());
            }
        }

        bypassLabel.setEnabled(bypassButton.getToggleState());

        filter[Convert::toUType(Channel::Left)].setBypassed<0>(bypassButton.getToggleState());
        filter[Convert::toUType(Channel::Right)].setBypassed<0>(bypassButton.getToggleState());
    };

    // 设置旁通标签
    bypassLabel.setFont(juce::Font(C(bypassLabelFontSize)));
    bypassLabel.setText("Bypass", juce::dontSendNotification);
    bypassLabel.setJustificationType(juce::Justification::centred);
    bypassLabel.setSize(C(bypassLabelWidth), C(bypassLabelHeight));
    bypassLabel.setEnabled(false);

    // 将子组件绑定
    addAndMakeVisible(orderLabel);
    addAndMakeVisible(freqKnob);
    addAndMakeVisible(gainKnob);
    addAndMakeVisible(qualityKnob);
    addAndMakeVisible(filterModeBox);
    addAndMakeVisible(bypassButton);
    addAndMakeVisible(bypassLabel);

    updateColour();

    setSize(C(width), C(height));
}
#undef C

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    #1#
    */

    g.setColour(Constant::Colours::filterComponentBackground);
    g.fillRoundedRectangle(0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight()), 5);
}

void FilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

#define C(constant) Constant::FilterComponent::constant

    orderLabel.setBounds(C(spacing), getBounds().getCentreY() - C(orderLabelHeight)/2, C(orderLabelWidth), C(orderLabelHeight));

    freqKnob.setBounds(orderLabel.getBounds().getRight() + C(spacing), getBounds().getCentreY() - (C(knobHeight) - Constant::Knob::nameLabelHeight)/2, C(knobWidth), C(knobHeight));

    gainKnob.setBounds(freqKnob.getBounds().getRight() + C(spacing), getBounds().getCentreY() - (C(knobHeight) - Constant::Knob::nameLabelHeight) / 2, C(knobWidth), C(knobHeight));

    qualityKnob.setBounds(gainKnob.getBounds().getRight() + C(spacing), getBounds().getCentreY() - (C(knobHeight) - Constant::Knob::nameLabelHeight) / 2, C(knobWidth), C(knobHeight));

    filterModeBox.setBounds(qualityKnob.getBounds().getRight() + C(spacing), getBounds().getCentreY() - C(modeBoxHeight)/2, C(modeBoxWidth), C(modeBoxHeight));

    bypassButton.setBounds(filterModeBox.getBounds().getRight() + C(spacing), getBounds().getCentreY() - C(bypassButtonHeight)/2, C(bypassButtonWidth), C(bypassButtonHeight));

    bypassLabel.setBounds(bypassButton.getBounds().getCentreX() - C(bypassLabelWidth) / 2, bypassButton.getBounds().getY() - static_cast<int>(C(bypassLabelHeight)*1.25), C(bypassLabelWidth), C(bypassLabelHeight));

#undef C
}

void FilterComponent::setThemeColour(const juce::Colour& newColour)
{
    themeColour = newColour;
    updateColour();
}

void FilterComponent::setDefaultFreq(const double normalizedDefaultFreq)
{
    freqKnob.setValue(normalizedDefaultFreq, juce::dontSendNotification);
    freqKnob.setDoubleClickReturnValue(true, normalizedDefaultFreq, juce::ModifierKeys::noModifiers);
}

void FilterComponent::reset()
{
    filter[Convert::toUType(Channel::Left)].reset();
    filter[Convert::toUType(Channel::Right)].reset();
}

void FilterComponent::prepare(const juce::dsp::ProcessSpec& processSpec) noexcept
{
    filter[Convert::toUType(Channel::Left)].prepare(processSpec);
    filter[Convert::toUType(Channel::Right)].prepare(processSpec);
}

void FilterComponent::process(const juce::dsp::ProcessContextReplacing<float> context[]) noexcept
{
    filter[Convert::toUType(Channel::Left)].process(context[Convert::toUType(Channel::Left)]);
    filter[Convert::toUType(Channel::Right)].process(context[Convert::toUType(Channel::Right)]);
}


/*
std::shared_ptr<FilterComponent> FilterComponent::createShared(const int newOrder)
{
    return std::make_shared<FilterComponent>(newOrder);
}

std::unique_ptr<FilterComponent> FilterComponent::createUnique(const int newOrder)
{
    return std::make_unique<FilterComponent>(newOrder);
}


juce::ReferenceCountedObjectPtr<FilterComponent> FilterComponent::createReferenceCounted(const int newOrder)
{
    return { new FilterComponent(newOrder) };
}
*/


void FilterComponent::setOrder(const int newOrder)
{
    this->order = newOrder;
    orderLabel.setText(juce::String(order), juce::dontSendNotification);
    if (!orderLabel.isVisible())
    {
        orderLabel.setVisible(true);
    }
}

void FilterComponent::updateColour()
{
#define NEW_COLOR bypassButton.getToggleState() ? defaultColour : themeColour
    freqKnob.setBarColour(NEW_COLOR);
    gainKnob.setBarColour(NEW_COLOR);
    qualityKnob.setBarColour(NEW_COLOR);
#undef NEW_COLOR
}


std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> FilterComponent::createSliderAttachment(juce::AudioProcessorValueTreeState& stateToUse, const juce::String& parameterID, AttachmentType type)
{
    if (AttachmentType::freqAttachment == type)
    {
        return std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToUse, parameterID, freqKnob);
    }
    else if (AttachmentType::gainAttachment == type)
    {
        return std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToUse, parameterID, gainKnob);
    }
    else if (AttachmentType::qualityAttachment == type)
    {
        return std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToUse, parameterID, qualityKnob);
    }
    else
    {
        return nullptr;
    }
}

std::shared_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> FilterComponent::createComboBoxAttachment(
    juce::AudioProcessorValueTreeState& stateToUse, const juce::String& parameterID)
{
    return std::make_shared<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(stateToUse, parameterID, filterModeBox);
}

void FilterComponent::updateCoefficients(const Settings& settings)
{
    juce::ReferenceCountedObjectPtr<juce::dsp::IIR::Coefficients<float>> coefficients = nullptr;
    if (Convert::toUType(FilterMode::HighPass) == filterModeBox.getSelectedId())
    {
        coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(settings.sampleRate, settings.freq, settings.quality);
    }
    else if (Convert::toUType(FilterMode::LowPass) == filterModeBox.getSelectedId())
    {
        coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(settings.sampleRate, settings.freq, settings.quality);
    }
    else if (Convert::toUType(FilterMode::Peak) == filterModeBox.getSelectedId())
    {
        coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(settings.sampleRate, settings.freq, settings.quality, settings.normalizedGain);
    }
    else if (Convert::toUType(FilterMode::LowShelf) == filterModeBox.getSelectedId())
    {
        coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(settings.sampleRate, settings.freq, settings.quality, settings.normalizedGain);
    }
    else if (Convert::toUType(FilterMode::HighShelf) == filterModeBox.getSelectedId())
    {
        coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(settings.sampleRate, settings.freq, settings.quality, settings.normalizedGain);
    }
    filter[Convert::toUType(Channel::Left)].get<0>().coefficients = *coefficients;
    filter[Convert::toUType(Channel::Right)].get<0>().coefficients = *coefficients;
}

