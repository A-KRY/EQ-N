/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"

//==============================================================================
EQNAudioProcessorEditor::EQNAudioProcessorEditor (EQNAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    audioProcessor.setEditor(this);

#define C(constant) Constant::PluginEditor::constant

    setSize (C(editorWidth), C(editorHeight));

    for (auto i = 0; i < Constant::FilterBank::filterNumber; ++i)
    {
#define TYPE(type) FilterComponent::AttachmentType::type
        freqKnobAttachment.emplace_back(filterBank.createSliderAttachment(i, audioProcessor.apvts, juce::String(i) + "freq", TYPE(freqAttachment)));
        gainKnobAttachment.emplace_back(filterBank.createSliderAttachment(i, audioProcessor.apvts, juce::String(i) + "gain", TYPE(gainAttachment)));
        qualityKnobAttachment.emplace_back(filterBank.createSliderAttachment(i, audioProcessor.apvts, juce::String(i) + "quality", TYPE(qualityAttachment)));
#undef TYPE
    }

    addAndMakeVisible(filterBank);
#undef C
}

EQNAudioProcessorEditor::~EQNAudioProcessorEditor()
{
}

//==============================================================================
void EQNAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    /*g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);*/

    using namespace Constant::Colours;

    // g.fillAll(Constant::Colours::background);
    // g.setColour(juce::Colours::black);

    enum class Position {Left, Right, Top, Bottom};

    const juce::ColourGradient colors[] = { juce::ColourGradient::horizontal(backgroundOuter, 0, backgroundInner, static_cast<float>(filterBank.getBounds().getX())),
    	juce::ColourGradient::horizontal(backgroundInner, static_cast<float>(filterBank.getBounds().getRight()), backgroundOuter, static_cast<float>(getLocalBounds().getRight())),
        juce::ColourGradient::vertical(backgroundOuter, 0, backgroundInner, static_cast<float>(filterBank.getBounds().getY())),
        juce::ColourGradient::vertical(backgroundInner, static_cast<float>(filterBank.getBounds().getBottom()), backgroundOuter, static_cast<float>(getLocalBounds().getBottom())) };

    juce::Path path[4];
    // fill left
    path[Convert::toUType(Position::Left)].startNewSubPath(getLocalBounds().getTopLeft().toFloat());
    path[Convert::toUType(Position::Left)].lineTo(filterBank.getBounds().getTopLeft().toFloat());
    path[Convert::toUType(Position::Left)].lineTo(filterBank.getBounds().getBottomLeft().toFloat());
    path[Convert::toUType(Position::Left)].lineTo(getLocalBounds().getBottomLeft().toFloat());
    path[Convert::toUType(Position::Left)].closeSubPath();
    g.setGradientFill(colors[Convert::toUType(Position::Left)]);
    g.fillPath(path[Convert::toUType(Position::Left)]);

    path[Convert::toUType(Position::Right)].startNewSubPath(getLocalBounds().getTopRight().toFloat());
    path[Convert::toUType(Position::Right)].lineTo(filterBank.getBounds().getTopRight().toFloat());
    path[Convert::toUType(Position::Right)].lineTo(filterBank.getBounds().getBottomRight().toFloat());
    path[Convert::toUType(Position::Right)].lineTo(getLocalBounds().getBottomRight().toFloat());
    path[Convert::toUType(Position::Right)].closeSubPath();
    g.setGradientFill(colors[Convert::toUType(Position::Right)]);
    g.fillPath(path[Convert::toUType(Position::Right)]);

    path[Convert::toUType(Position::Top)].startNewSubPath(getLocalBounds().getTopLeft().toFloat());
    path[Convert::toUType(Position::Top)].lineTo(filterBank.getBounds().getTopLeft().toFloat());
    path[Convert::toUType(Position::Top)].lineTo(filterBank.getBounds().getTopRight().toFloat());
    path[Convert::toUType(Position::Top)].lineTo(getLocalBounds().getTopRight().toFloat());
    path[Convert::toUType(Position::Top)].closeSubPath();
    g.setGradientFill(colors[Convert::toUType(Position::Top)]);
    g.fillPath(path[Convert::toUType(Position::Top)]);

    path[Convert::toUType(Position::Bottom)].startNewSubPath(getLocalBounds().getBottomLeft().toFloat());
    path[Convert::toUType(Position::Bottom)].lineTo(filterBank.getBounds().getBottomLeft().toFloat());
    path[Convert::toUType(Position::Bottom)].lineTo(filterBank.getBounds().getBottomRight().toFloat());
    path[Convert::toUType(Position::Bottom)].lineTo(getLocalBounds().getBottomRight().toFloat());
    path[Convert::toUType(Position::Bottom)].closeSubPath();
    g.setGradientFill(colors[Convert::toUType(Position::Bottom)]);
    g.fillPath(path[Convert::toUType(Position::Bottom)]);
}

void EQNAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    using namespace Constant::FilterComponent;

    filterBank.setBounds((getWidth() - filterBank.getWidth())/2, (getHeight() - filterBank.getHeight()) / 2, filterBank.getWidth(), filterBank.getHeight());
}

void EQNAudioProcessorEditor::updateFilterCoefficients()
{
    FilterComponent::Settings newSetting;
    newSetting.sampleRate = audioProcessor.getSampleRate();
    for (int i = 0; i < Constant::FilterBank::filterNumber; ++i)
    {
        newSetting.freq = Convert::fromNormalizedFreq(audioProcessor.apvts.getRawParameterValue(juce::String(i) + "freq")->load());
        newSetting.normalizedGain = Convert::toNormalizedGain(Convert::fromNormalizedFilterGain(audioProcessor.apvts.getRawParameterValue(juce::String(i) + "gain")->load()));
        newSetting.quality = Convert::fromNormalizedQuality(audioProcessor.apvts.getRawParameterValue(juce::String(i) + "quality")->load());
        filterBank.updateCoefficients(i, newSetting);
    }
}

void EQNAudioProcessorEditor::filterPrepare(const juce::dsp::ProcessSpec& spec)
{
    filterBank.prepare(spec);
}

void EQNAudioProcessorEditor::filterProcess(const juce::dsp::ProcessContextReplacing<float> context[])
{
    filterBank.process(context);
}
