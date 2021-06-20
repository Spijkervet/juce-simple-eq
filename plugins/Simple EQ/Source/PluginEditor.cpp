#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleEQEditor::SimpleEQEditor(SimpleEQ& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
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