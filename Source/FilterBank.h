/*
  ==============================================================================

    FilterBank.h
    Created: 27 Mar 2023 3:49:08pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constant.h"
#include "FilterComponent.h"

//==============================================================================
/*
*/
class FilterBank  : public juce::Component
{
public:
    FilterBank();
    ~FilterBank() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // 获得滤波器数目
    JUCE_NODISCARD int getFilterNumber() const noexcept
    {
        return static_cast<int>(filters.size());
    }

    // 创建 AudioProcessorValueTreeState 的 Attachment
    std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> createSliderAttachment(const int filterIndex, juce::AudioProcessorValueTreeState& stateToUse, const juce::String& parameterID, FilterComponent::AttachmentType type);

    std::shared_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> createComboBoxAttachment(const int filterIndex, juce::AudioProcessorValueTreeState& stateToUse, const juce::String& parameterID);

    // 准备
    void prepare(const juce::dsp::ProcessSpec& spec);

    // 处理
    void process(const juce::dsp::ProcessContextReplacing<float> context[]);

    // 重置
    void reset();

    // 更新滤波器系数
    void updateCoefficients(const int filterIndex, const FilterComponent::Settings& settings);

private:

    std::vector<FilterComponent> filters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterBank)
};

