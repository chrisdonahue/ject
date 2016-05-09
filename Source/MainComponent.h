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

#include <tuple>
#include <vector>
#include <unordered_map>
#include <utility>

#include "JuceHeader.h"

#include "InputFileTableListBox.h"
#include "ParameterSliderTableListBox.h"
#include "WaveformComponent.h"

using std::vector;
using std::pair;
using std::tuple;
using std::unordered_map;

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
                              public ChangeListener,
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
	void changeListenerCallback(ChangeBroadcaster* source) override;

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
	CriticalSection paramLock;
	int nfftParam;
	HashMap<int, float> pParam;
	float qParam;
	HashMap<int, float> rParam;
	float sParam;

	// ui state
	PrBehavior prBehavior;
	CriticalSection waveformDisplayLock;

	// conv state
	CriticalSection convLock;
	AudioBuffer<float> conv;
	bool convDirty;

	// audio playback state
	Atomic<float> gainParam;
	CriticalSection playheadAudioLock;
	PlayheadState playheadState;
	AudioBuffer<float> playheadAudio;
	int playheadAudioSamplesCompleted;

	// file list state
	enum FileAttr {
		filePath=0,
		fileName,
		fileBuffer
	};
	CriticalSection fileListLock;
	int fileIdNext;
	unordered_map<int, tuple<String, String, AudioBuffer<float>*>> fileIdToAttrs;
	unordered_map<int, int> rowToFileId;

	void setPlayheadUiEnabled(bool playheadUiEnabled);
	void setPlayheadAudio(AudioBuffer<float>* playheadAudio);
	void setUiFromParams(NotificationType notificationType);
	void inputFilesChanged(NotificationType notificationType);
	void updatePRComponentLists();
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
    ScopedPointer<WaveformComponent> waveformComponent;
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
    ScopedPointer<Label> sLabel;
    ScopedPointer<ParameterSliderTableListBox> rComponent;
    ScopedPointer<ParameterSliderTableListBox> pComponent;
    ScopedPointer<TextButton> inputRemoveButton;
    ScopedPointer<TextButton> inputAddButton;
    ScopedPointer<InputFileTableListBox> inputFileListComponent;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CB87035FA43504BB__
