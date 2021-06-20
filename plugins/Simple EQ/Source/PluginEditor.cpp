#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleEQEditor::SimpleEQEditor(SimpleEQ& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , peakFreqSliderAttachment(audioProcessor.apvts, "Peak Freq", peakFreqSlider)
    , peakGainSliderAttachment(audioProcessor.apvts, "Peak Gain", peakGainSlider)
    , peakQualitySliderAttachment(audioProcessor.apvts, "Peak Quality", peakQualitySlider)
    , lowCutFreqSliderAttachment(audioProcessor.apvts, "LowCut Freq", lowCutFreqSlider)
    , highCutFreqSliderAttachment(audioProcessor.apvts, "HighCut Freq", highCutFreqSlider)
    , lowCutSlopeSliderAttachment(audioProcessor.apvts, "LowCut Slope", lowCutSlopeSlider)
    , highCutSlopeSliderAttachment(
          audioProcessor.apvts, "HighCut Slope", highCutSlopeSlider)
{
    for (auto* comp: getComps())
    {
        addAndMakeVisible(comp);
    }
    setSize(600, 400);
}

SimpleEQEditor::~SimpleEQEditor()
{
}

void SimpleEQEditor::resized()
{
    // Layout the positions of subcomponents in the editor
    auto bounds = getLocalBounds();
    auto responseArea = bounds.removeFromTop(bounds.getHeight() * 0.33);

    auto lowCutArea = bounds.removeFromLeft(bounds.getWidth() * 0.33);
    auto highCutArea = bounds.removeFromRight(bounds.getWidth() * 0.5);

    lowCutFreqSlider.setBounds(lowCutArea.removeFromTop(lowCutArea.getHeight() * 0.5));
    lowCutSlopeSlider.setBounds(lowCutArea);

    highCutFreqSlider.setBounds(highCutArea.removeFromTop(highCutArea.getHeight() * 0.5));
    highCutSlopeSlider.setBounds(highCutArea);

    peakFreqSlider.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.33));
    peakGainSlider.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.5));
    peakQualitySlider.setBounds(bounds);
}

std::vector<juce::Component*> SimpleEQEditor::getComps()
{
    return {&peakFreqSlider,
            &peakGainSlider,
            &peakQualitySlider,
            &lowCutFreqSlider,
            &highCutFreqSlider,
            &lowCutSlopeSlider,
            &highCutSlopeSlider};
}