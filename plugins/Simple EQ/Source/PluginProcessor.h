#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include <juce_dsp/juce_dsp.h>

//Inhereting from AudioProcessorBase, which is just inhereting from juce::AudioProcessor
//And adding some default implementations

enum Slope
{
    Slope_12,
    Slope_24,
    Slope_36,
    Slope_48
};

struct ChainSettings
{
    float peakFreq {0}, peakGainInDecibels {0}, peakQuality {1.f};
    float lowCutFreq {0}, highCutFreq {0};

    Slope lowCutSlope {Slope::Slope_12}, highCutSlope {Slope::Slope_12};
};

ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts);

class SimpleEQ : public AudioProcessorBase
{
public:
    SimpleEQ();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    void processBlock(juce::AudioBuffer<float>& buffer,
                      juce::MidiBuffer& midiMessages) override;

    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts {
        *this, nullptr, "Parameters", createParameterLayout()};

private:
    using Filter = juce::dsp::IIR::Filter<float>;

    using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;

    using MonoChain = juce::dsp::ProcessorChain<CutFilter, Filter, CutFilter>;

    MonoChain leftChain, rightChain;

    enum ChainPositions
    {
        LowCut,
        Peak,
        HighCut
    };

    void updatePeakFilter(const ChainSettings& chainSettings);

    using Coefficients = Filter::CoefficientsPtr;

    static void updateCoefficients(Coefficients& old, const Coefficients& replacements);

    template <int Index, typename ChainType, typename CoefficientType>
    void update(ChainType& chain, const CoefficientType& coefficients)
    {
        updateCoefficients(chain.template get<Index>().coefficients, coefficients[Index]);
        chain.template setBypassed<Index>(false);
    }

    template <typename ChainType, typename CoefficientType>
    void updateCutFilter(ChainType& leftLowCut,
                         const CoefficientType& cutCoefficients,
                         const Slope& lowCutSlope)
    {
        leftLowCut.template setBypassed<0>(true);
        leftLowCut.template setBypassed<1>(true);
        leftLowCut.template setBypassed<2>(true);
        leftLowCut.template setBypassed<3>(true);

        switch (lowCutSlope)
        {
            case Slope_48:
            {
                update<3>(leftLowCut, cutCoefficients);
            }
            case Slope_36:
            {
                update<2>(leftLowCut, cutCoefficients);
            }
            case Slope_24:
            {
                update<1>(leftLowCut, cutCoefficients);
            }
            case Slope_12:
            {
                update<0>(leftLowCut, cutCoefficients);
            }
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleEQ)
};
