#pragma once

#include "PluginProcessor.h"

struct CustomRotarySlider : juce::Slider
{
    CustomRotarySlider()
        : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                       juce::Slider::TextEntryBoxPosition::NoTextBox)
    {
    }
};

class SimpleEQEditor : public juce::AudioProcessorEditor
{
public:
    SimpleEQEditor(SimpleEQ&);
    ~SimpleEQEditor() override;
    void resized() override;

private:
    SimpleEQ& audioProcessor;
    CustomRotarySlider peakFreqSlider, peakGainSlider, peakQualitySlider,
        lowCutFreqSlider, highCutFreqSlider, lowCutSlopeSlider, highCutSlopeSlider;

    std::vector<juce::Component*> getComps();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleEQEditor)
};
