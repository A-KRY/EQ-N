/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQNAudioProcessor::EQNAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    apvts(*this, nullptr, "ValueTreeState", createParameters()),
    editorPtr(nullptr)
#endif
{
}

EQNAudioProcessor::~EQNAudioProcessor()
{
}

// Create parameters to use
#define STANDARD_NORMALIZABLE_RANGE juce::NormalisableRange<float>(0.0f, 1.0f)
#define DEFAULT_CATEGORY juce::AudioProcessorParameter::genericParameter
#define DEFAULT(constant) Constant::DefaultVal::Filter::constant
#define DEFAULT_FREQ_BY_INDEX(index) \
	(((index) == 0) ? (DEFAULT(highPass)) : (((index) == Constant::FilterBank::filterNumber-1) ? (DEFAULT(lowPass)) : (DEFAULT(peak))))
juce::AudioProcessorValueTreeState::ParameterLayout EQNAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    for (int i = 0; i < Constant::FilterBank::filterNumber; ++i)
    {
        // freq
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::String(i) + "freq", "Freq",
            STANDARD_NORMALIZABLE_RANGE, DEFAULT_FREQ_BY_INDEX(i), juce::String(), DEFAULT_CATEGORY,
            [](float value, int)
            {
                juce::String str(static_cast<int>(Convert::fromNormalizedFreq(value)));
				return str;
            },
            [](const juce::String& text)
            {
	            return Convert::toNormalizedFreq(text.getFloatValue());
            }
            ));

        // gain
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::String(i) + "gain", "Gain",
            STANDARD_NORMALIZABLE_RANGE, DEFAULT(gain), juce::String(), DEFAULT_CATEGORY,
            [](float value, int)
            {
                juce::String str(Convert::fromNormalizedFilterGain(value));
				const int dotIndex = str.lastIndexOf(".");
				return dotIndex == -1 ? str : str.dropLastCharacters(str.length() - dotIndex - 2);
            },
            [](const juce::String& text)
            {
                return Convert::toNormalizedFilterGain(text.getFloatValue());
            }
            ));

        // quality
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::String(i) + "quality", "Q",
            STANDARD_NORMALIZABLE_RANGE, DEFAULT(quality), juce::String(), DEFAULT_CATEGORY,
            [](float value, int)
            {
                juce::String str(Convert::fromNormalizedQuality(value));
				const int dotIndex = str.lastIndexOf(".");
				return dotIndex == -1 ? str : str.dropLastCharacters(str.length() - dotIndex - 2);
            },
            [](const juce::String& text)
            {
                return Convert::toNormalizedQuality(text.getFloatValue());
            }
            ));
    }
    return layout;
}
#undef DEFAULT_FREQ_BY_INDEX
#undef DEFAULT
#undef DEFAULT_CATEGORY
#undef STANDARD_NORMALIZABLE_RANGE


//==============================================================================
const juce::String EQNAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EQNAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EQNAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EQNAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EQNAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EQNAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EQNAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EQNAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EQNAudioProcessor::getProgramName (int index)
{
    return {};
}

void EQNAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EQNAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    if (nullptr !=editorPtr)
    {
        editorPtr->updateFilterCoefficients();

        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32>(samplesPerBlock), 1 };

        editorPtr->filterPrepare(spec);
    }
}

void EQNAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EQNAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EQNAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    if (nullptr != editorPtr)
    {
        editorPtr->updateFilterCoefficients();
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context[2]{block.getSingleChannelBlock(LeftChannel), block.getSingleChannelBlock(RightChannel)};
        editorPtr->filterProcess(context);
    }

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool EQNAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EQNAudioProcessor::createEditor()
{
    return new EQNAudioProcessorEditor (*this);
}

//==============================================================================
void EQNAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EQNAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EQNAudioProcessor();
}
