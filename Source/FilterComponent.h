/*
  ==============================================================================

    FilterComponent.h
    Created: 22 Mar 2023 10:53:50pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


#include "Knob.h"

#include "Constant.h"

#include "BypassButtonLookAndFeel.h"
#include "Convert.h"

//==============================================================================
class FilterComponent  : public juce::Component,
    public juce::ReferenceCountedObject
{
public:
    // Constructor
    FilterComponent(const int newOrder = 0);

    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /*
    // Factory Method
    
    static std::shared_ptr<FilterComponent> createShared(const int newOrder = 0);

    static std::unique_ptr<FilterComponent> createUnique(const int newOrder = 0);

    static juce::ReferenceCountedObjectPtr<FilterComponent> createReferenceCounted(const int newOrder = 0);
    */

    

    enum class FilterMode
    {
	    HighPass = 1,
        LowPass,
        Peak,
        LowShelf,
        HighShelf,
    };

    enum class AttachmentType
    {
        freqAttachment,
        gainAttachment,
        qualityAttachment,
    };

    enum class Channel
    {
        Left,
        Right,
    };

    struct Settings
    {
        double sampleRate{0.0};
        float freq{0.5}, normalizedGain{0.5}, quality{0.5};
    };

    void setThemeColour(const juce::Colour& newColour);

    // 设置滤波器默认频率
    void setDefaultFreq(const double normalizedDefaultFreq);

    // Filter
    void reset();

    void prepare(const juce::dsp::ProcessSpec&) noexcept;

    void process(const juce::dsp::ProcessContextReplacing<float> context[]) noexcept;

    // 设置滤波器类型
    void setFilterMode(FilterMode newMode)
    {
        filterModeBox.setSelectedId(Convert::toUType(newMode), false);
    }

    // 序号
    JUCE_NODISCARD int getOrder() const
    {
	    return order;
    }

    void setOrder(const int newOrder);

    // 创建 AudioProcessorValueTreeState 的 Attachment
    std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> createSliderAttachment(juce::AudioProcessorValueTreeState& stateToUse, const juce::String& parameterID, AttachmentType type);

    std::shared_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> createComboBoxAttachment(juce::AudioProcessorValueTreeState& stateToUse, const juce::String& parameterID);

    // 更新滤波器系数
    void updateCoefficients(const Settings& settings);

    // 获得滤波器系数
    decltype(auto) getCoefficients()
    {
        return std::move(filter[Convert::toUType(Channel::Left)].get<0>().coefficients);
    }

private:

    // 序号
    int order;

    // 色彩主题
    juce::Colour themeColour;
    juce::Colour defaultColour;

    // 序号标签
    juce::Label orderLabel, bypassLabel;

    // 旋钮
    // Knob is inherited from juce::Slider
    Knob freqKnob, gainKnob, qualityKnob;

    // 下拉框
    juce::ComboBox filterModeBox;

    // 旁通按钮
    juce::ToggleButton bypassButton;

    BypassButtonLookAndFeel bypassLookAndFeel;

    // 更新色彩主题
    void updateColour();

    // 滤波器
    juce::dsp::ProcessorChain<juce::dsp::IIR::Filter<float>> filter[2];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
