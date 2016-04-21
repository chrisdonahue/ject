/*
  ==============================================================================

    WaveformComponent.h
    Created: 15 Nov 2015 7:34:10pm
    Author:  Chris

  ==============================================================================
*/

#ifndef WAVEFORMCOMPONENT_H_INCLUDED
#define WAVEFORMCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformComponent    : public Component
{
public:
    WaveformComponent(String message);
    ~WaveformComponent();

    void paint (Graphics&);
    void resized();

	const AudioBuffer<float>* getSound() const;
	void setSound(const AudioBuffer<float>* soundNew);
	void setPlayhead(int sampleNum);

private:
	String message;
	const AudioBuffer<float>* sound;
	int playhead;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformComponent)
};


#endif  // WAVEFORMCOMPONENT_H_INCLUDED
