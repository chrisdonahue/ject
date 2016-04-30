/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_CB87035FA43504BB__
#define __JUCE_HEADER_CB87035FA43504BB__

//[Headers]     -- You can add your own extra header files here --
#define JECT_CHANNELS_NUM 2
#define JECT_FPS 30

#include <vector>
#include <utility>

#include "JuceHeader.h"

#include "WaveformComponent.h"

using std::vector;
using std::pair;

ApplicationProperties& getAppProperties();
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainContentComponent  : public AudioAppComponent,
                              public FileDragAndDropTarget,
                              public Timer,
                              public SliderListener,
                              public ButtonListener,
                              public ComboBoxListener
{
public:
    //==============================================================================
    MainContentComponent ();
    ~MainContentComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void prepareToPlay(int samplesPerBlockExpeted, double sampleRate) override;
	void releaseResources() override;
	void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;

	bool isInterestedInFileDrag(const StringArray& files) override;
	void filesDropped(const StringArray& files, int x, int y) override;

	void timerCallback() override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	enum PrBehavior {
		independent=1,
		linked,
		inverse
	};

	enum PlayheadState {
		stopped=0,
		playing,
		looping
	};

	// audio parameters
	Atomic<float> gainParam;
	Atomic<int> nfftParam;
	Atomic<float> pParam;
	Atomic<float> qParam;
	Atomic<float> rParam;
	Atomic<float> sParam;

	// ui state
	PrBehavior prBehavior;
	CriticalSection waveformDisplayLock;

	// loaded sounds state
	AudioBuffer<float> s0;
	AudioBuffer<float> s1;

	// conv state
	CriticalSection convLock;
	AudioBuffer<float> conv;
	bool convDirty;

	// audio playback state
	CriticalSection playheadAudioLock;
	PlayheadState playheadState;
	AudioBuffer<float> playheadAudio;
	int playheadAudioSamplesCompleted;

	void setPlayheadUiEnabled(bool playheadUiEnabled);
	void setUiFromParams(NotificationType notificationType);
	void soundChanged(NotificationType notificationType);
	void fftFree();
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> inputGroupBox;
    ScopedPointer<GroupComponent> convGroupBox;
    ScopedPointer<GroupComponent> phaseComboBox;
    ScopedPointer<GroupComponent> magniComboBox;
    ScopedPointer<GroupComponent> waveformGroupBox;
    ScopedPointer<Slider> qSlider;
    ScopedPointer<Label> qLabel;
    ScopedPointer<TextButton> convButton;
    ScopedPointer<Label> authorLabel;
    ScopedPointer<TextButton> settingsButton;
    ScopedPointer<Slider> gainSlider;
    ScopedPointer<Label> gainLabel;
    ScopedPointer<WaveformComponent> convComponent;
    ScopedPointer<Label> prBehaviorLabel;
    ScopedPointer<ComboBox> prBehaviorComboBox;
    ScopedPointer<TextButton> playButton;
    ScopedPointer<TextButton> loopButton;
    ScopedPointer<TextButton> stopButton;
    ScopedPointer<TextButton> qDefaultButton;
    ScopedPointer<Slider> sSlider;
    ScopedPointer<TextButton> sDefaultButton;
    ScopedPointer<Slider> nfftSlider;
    ScopedPointer<Label> nfftLabel;
    ScopedPointer<TextButton> saveButton;
    ScopedPointer<Label> sLabel2;
    ScopedPointer<PolygonSliderComponent> rComponent;
    ScopedPointer<PolygonSliderComponent> component2;
    ScopedPointer<ListBox> inputListComponent;
    ScopedPointer<TextButton> inputRemoveButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CB87035FA43504BB__
