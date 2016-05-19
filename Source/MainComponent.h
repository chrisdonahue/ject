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
#include <unordered_set>
#include <unordered_map>
#include <utility>

#include "JuceHeader.h"

#include "InputFileTableListBox.h"
#include "Sound.h"
#include "WaveformComponent.h"

using std::unique_ptr;
using std::shared_ptr;
using std::vector;
using std::pair;
using std::tuple;
using std::unordered_map;
using std::unordered_set;

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
		id=0,
		name,
		path,
		pValue,
		rValue,
		numAttrs
	};
	CriticalSection fileListLock;
	unordered_map<int, unique_ptr<Sound>> idToSound;
	unordered_set<int> includedSounds;
	int fileIdNext;

	void loadFileList(XmlElement* fileListNew);

	void setPlayheadUiEnabled(bool playheadUiEnabled);
	void setPlayheadAudio(AudioBuffer<float>* playheadAudio);
	void setUiFromParams(NotificationType notificationType);
	void inputFilesChanged(NotificationType notificationType);
	void updateNfftSlider(NotificationType notificationType);
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> waveformGroupBox;
    ScopedPointer<WaveformComponent> waveformComponent;
    ScopedPointer<GroupComponent> inputGroupBox;
    ScopedPointer<GroupComponent> convGroupBox;
    ScopedPointer<Slider> qSlider;
    ScopedPointer<Label> qLabel;
    ScopedPointer<TextButton> convButton;
    ScopedPointer<Label> authorLabel;
    ScopedPointer<TextButton> settingsButton;
    ScopedPointer<Slider> gainSlider;
    ScopedPointer<Label> gainLabel;
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
    ScopedPointer<TextButton> inputRemoveButton;
    ScopedPointer<TextButton> inputAddButton;
    ScopedPointer<InputFileTableListBox> inputFileListComponent;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CB87035FA43504BB__
