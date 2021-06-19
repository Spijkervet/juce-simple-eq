#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include <juce_dsp/juce_dsp.h>

//Inhereting from AudioProcessorBase, which is just inhereting from juce::AudioProcessor
//And adding some default implementations

class MinimalAudioPlugin : public AudioProcessorBase
{
public:
    MinimalAudioPlugin();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    void processBlock(juce::AudioBuffer<float>& buffer,
                      juce::MidiBuffer& midiMessages) override;

    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts {*this, nullptr, "Parameters", createParameterLayout()};

private:
    using Filter = juce::dsp::IIR::Filter<float>;

    using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MinimalAudioPlugin)
};
