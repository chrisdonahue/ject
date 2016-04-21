/*
  ==============================================================================

    WaveformComponent.cpp
    Created: 15 Nov 2015 7:34:10pm
    Author:  Chris

  ==============================================================================
*/

#include "WaveformComponent.h"

#include <cmath>
#include <limits>

//==============================================================================
WaveformComponent::WaveformComponent(String message)
	: message(message), sound(nullptr), playhead(-1)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveformComponent::~WaveformComponent()
{
}

void WaveformComponent::paint (Graphics& g)
{
	if (sound == nullptr) {
		g.setColour(Colours::black);
		g.drawFittedText(message, getLocalBounds(),
			Justification::centred, 3, 1.0f);   // draw some placeholder text
	}
	else {
		int channelsNum = sound->getNumChannels();
		int samplesNum = sound->getNumSamples();
		float width = static_cast<float>(getWidth());
		float height = static_cast<float>(getHeight()) / static_cast<float>(channelsNum);
		float heightHalf = height * 0.5f;
		for (int channel = 0; channel < channelsNum; ++channel) {
			float yMid = (static_cast<float>(channel) + 0.5f) * height;
			int samplesPerPixel = static_cast<int>(static_cast<float>(samplesNum) / width);
			if (samplesPerPixel == 0) {
				samplesPerPixel = 1;
			}

			RectangleList<float> waveform;
			waveform.ensureStorageAllocated(getWidth());

			const float* samples = sound->getReadPointer(channel);
			for (int x = 0; x < getWidth(); ++x) {
				// find largest sample in this window
				float xMax = 0.0f;
				for (int sampleNum = 0; sampleNum < samplesPerPixel; ++sampleNum) {
					int sampleIdx = x * samplesPerPixel + sampleNum;
					if (sampleIdx < samplesNum) {
						float sampleAbs = fabsf(samples[sampleIdx]);
						if (sampleAbs > xMax) {
							xMax = sampleAbs;
						}
					}
					else {
						break;
					}
				}
				xMax = fminf(xMax, 1.0f);
			
				float xMaxAbs = xMax * heightHalf;

				waveform.addWithoutMerging(Rectangle<float>(static_cast<float>(x), yMid - xMaxAbs, 1.0f, xMaxAbs + xMaxAbs));
			}

			g.setColour(Colours::lightblue);
			g.fillRectList(waveform);

			g.setColour(Colours::lightsalmon);
			g.drawLine(0.0f, yMid, width, yMid, 1.0f);

			if (playhead > 0) {
				float playheadX = static_cast<float>(playhead / samplesPerPixel);
				g.drawLine(playheadX, yMid - heightHalf, playheadX, yMid + heightHalf);
			}
		}
	}
}

void WaveformComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

const AudioBuffer<float>* WaveformComponent::getSound() const {
	return sound;
}

void WaveformComponent::setSound(const AudioBuffer<float>* soundNew) {
	sound = soundNew;
}

void WaveformComponent::setPlayhead(int sampleNum) {
	playhead = sampleNum;
}