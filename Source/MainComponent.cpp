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

//[Headers] You can add your own extra header files here...
#include <algorithm>

#include "Libraries/kiss_fft130/kiss_fftr.h"
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainContentComponent::MainContentComponent ()
    : gainParam(0.5),
      nfftParam(0),
      pParam(0.5),
      qParam(1.0),
      rParam(0.5),
      sParam(1.0),
      prBehavior(PrBehavior::independent),
      waveformDisplayLock(),
      conv(0, 0),
      convDirty(true),
      playheadAudioLock(),
      playheadState(PlayheadState::stopped),
      playheadAudio(0, 0),
      playheadAudioSamplesCompleted(0),
      fileIdNext(0)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (inputGroupBox = new GroupComponent (String(),
                                                           TRANS("Input")));

    addAndMakeVisible (convGroupBox = new GroupComponent (String(),
                                                          TRANS("Convolution")));

    addAndMakeVisible (phaseComboBox = new GroupComponent (String(),
                                                           TRANS("Phase")));

    addAndMakeVisible (magniComboBox = new GroupComponent (String(),
                                                           TRANS("Magnitude")));

    addAndMakeVisible (waveformGroupBox = new GroupComponent (String(),
                                                              TRANS("Waveform")));

    addAndMakeVisible (qSlider = new Slider (String()));
    qSlider->setRange (0, 8, 0.01);
    qSlider->setSliderStyle (Slider::LinearHorizontal);
    qSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    qSlider->addListener (this);
    qSlider->setSkewFactor (0.4);

    addAndMakeVisible (qLabel = new Label (String(),
                                           TRANS("Q")));
    qLabel->setFont (Font (15.00f, Font::plain));
    qLabel->setJustificationType (Justification::centredLeft);
    qLabel->setEditable (false, false, false);
    qLabel->setColour (TextEditor::textColourId, Colours::black);
    qLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (convButton = new TextButton (String()));
    convButton->setButtonText (TRANS("Convolve"));
    convButton->addListener (this);

    addAndMakeVisible (authorLabel = new Label (String(),
                                                TRANS("Chris Donahue 2016")));
    authorLabel->setFont (Font (15.00f, Font::plain));
    authorLabel->setJustificationType (Justification::centredLeft);
    authorLabel->setEditable (false, false, false);
    authorLabel->setColour (TextEditor::textColourId, Colours::black);
    authorLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (settingsButton = new TextButton (String()));
    settingsButton->setButtonText (TRANS("Audio Settings"));
    settingsButton->addListener (this);

    addAndMakeVisible (gainSlider = new Slider (String()));
    gainSlider->setRange (0, 1, 0.01);
    gainSlider->setSliderStyle (Slider::LinearHorizontal);
    gainSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    gainSlider->addListener (this);

    addAndMakeVisible (gainLabel = new Label (String(),
                                              TRANS("Gain")));
    gainLabel->setFont (Font (15.00f, Font::plain));
    gainLabel->setJustificationType (Justification::centredLeft);
    gainLabel->setEditable (false, false, false);
    gainLabel->setColour (TextEditor::textColourId, Colours::black);
    gainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (waveformComponent = new WaveformComponent ("No waveform to display"));

    addAndMakeVisible (prBehaviorLabel = new Label (String(),
                                                    TRANS("P/R Behavior")));
    prBehaviorLabel->setFont (Font (15.00f, Font::plain));
    prBehaviorLabel->setJustificationType (Justification::centredLeft);
    prBehaviorLabel->setEditable (false, false, false);
    prBehaviorLabel->setColour (TextEditor::textColourId, Colours::black);
    prBehaviorLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (prBehaviorComboBox = new ComboBox (String()));
    prBehaviorComboBox->setEditableText (false);
    prBehaviorComboBox->setJustificationType (Justification::centredLeft);
    prBehaviorComboBox->setTextWhenNothingSelected (String());
    prBehaviorComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    prBehaviorComboBox->addItem (TRANS("Independent"), 1);
    prBehaviorComboBox->addItem (TRANS("Linked"), 2);
    prBehaviorComboBox->addItem (TRANS("Inverse"), 3);
    prBehaviorComboBox->addListener (this);

    addAndMakeVisible (playButton = new TextButton (String()));
    playButton->setButtonText (TRANS("Play"));
    playButton->addListener (this);

    addAndMakeVisible (loopButton = new TextButton (String()));
    loopButton->setButtonText (TRANS("Loop"));
    loopButton->addListener (this);

    addAndMakeVisible (stopButton = new TextButton (String()));
    stopButton->setButtonText (TRANS("Stop"));
    stopButton->addListener (this);

    addAndMakeVisible (qDefaultButton = new TextButton (String()));
    qDefaultButton->setButtonText (TRANS("Default"));
    qDefaultButton->addListener (this);

    addAndMakeVisible (sSlider = new Slider (String()));
    sSlider->setRange (0, 15, 0.01);
    sSlider->setSliderStyle (Slider::LinearHorizontal);
    sSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    sSlider->addListener (this);

    addAndMakeVisible (sDefaultButton = new TextButton (String()));
    sDefaultButton->setButtonText (TRANS("Default"));
    sDefaultButton->addListener (this);

    addAndMakeVisible (nfftSlider = new Slider (String()));
    nfftSlider->setRange (0, 24, 1);
    nfftSlider->setSliderStyle (Slider::LinearHorizontal);
    nfftSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    nfftSlider->addListener (this);

    addAndMakeVisible (nfftLabel = new Label (String(),
                                              TRANS("NFFT")));
    nfftLabel->setFont (Font (15.00f, Font::plain));
    nfftLabel->setJustificationType (Justification::centredLeft);
    nfftLabel->setEditable (false, false, false);
    nfftLabel->setColour (TextEditor::textColourId, Colours::black);
    nfftLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (saveButton = new TextButton (String()));
    saveButton->setButtonText (TRANS("Save"));
    saveButton->addListener (this);

    addAndMakeVisible (sLabel = new Label (String(),
                                           TRANS("S")));
    sLabel->setFont (Font (15.00f, Font::plain));
    sLabel->setJustificationType (Justification::centredLeft);
    sLabel->setEditable (false, false, false);
    sLabel->setColour (TextEditor::textColourId, Colours::black);
    sLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rComponent = new ParameterSliderTableListBox ("R"));

    addAndMakeVisible (pComponent = new ParameterSliderTableListBox ("P"));

    addAndMakeVisible (inputRemoveButton = new TextButton (String()));
    inputRemoveButton->setButtonText (TRANS("Remove"));
    inputRemoveButton->addListener (this);

    addAndMakeVisible (inputAddButton = new TextButton (String()));
    inputAddButton->setButtonText (TRANS("Add"));
    inputAddButton->addListener (this);

    addAndMakeVisible (inputFileListComponent = new InputFileTableListBox());


    //[UserPreSize]
	inputFileListComponent->addChangeListener(this);
	pComponent->addChangeListener(this);
	rComponent->addChangeListener(this);

	//timerCallback();
	inputFilesChanged(dontSendNotification);
	setUiFromParams(dontSendNotification);
	setPlayheadUiEnabled(false);
	convButton->setEnabled(false);
    //[/UserPreSize]

    setSize (832, 584);


    //[Constructor] You can add your own custom stuff here..
	setAudioChannels(0, JECT_CHANNELS_NUM);
	startTimerHz(JECT_FPS);
    //[/Constructor]
}

MainContentComponent::~MainContentComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	{
		const ScopedLock fl(fileListLock);
		for (auto i : fileIdToAttrs) {
			delete std::get<FileAttr::fileBuffer>(i.second);
		}
	}
	fftFree();
	inputFileListComponent->removeChangeListener(this);
	pComponent->removeChangeListener(this);
	rComponent->removeChangeListener(this);
    //[/Destructor_pre]

    inputGroupBox = nullptr;
    convGroupBox = nullptr;
    phaseComboBox = nullptr;
    magniComboBox = nullptr;
    waveformGroupBox = nullptr;
    qSlider = nullptr;
    qLabel = nullptr;
    convButton = nullptr;
    authorLabel = nullptr;
    settingsButton = nullptr;
    gainSlider = nullptr;
    gainLabel = nullptr;
    waveformComponent = nullptr;
    prBehaviorLabel = nullptr;
    prBehaviorComboBox = nullptr;
    playButton = nullptr;
    loopButton = nullptr;
    stopButton = nullptr;
    qDefaultButton = nullptr;
    sSlider = nullptr;
    sDefaultButton = nullptr;
    nfftSlider = nullptr;
    nfftLabel = nullptr;
    saveButton = nullptr;
    sLabel = nullptr;
    rComponent = nullptr;
    pComponent = nullptr;
    inputRemoveButton = nullptr;
    inputAddButton = nullptr;
    inputFileListComponent = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
	shutdownAudio();
    //[/Destructor]
}

//==============================================================================
void MainContentComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainContentComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    inputGroupBox->setBounds (8, 0, 224, 512);
    convGroupBox->setBounds (240, 224, 584, 96);
    phaseComboBox->setBounds (536, 328, 288, 248);
    magniComboBox->setBounds (240, 328, 288, 248);
    waveformGroupBox->setBounds (240, 2, 584, 214);
    qSlider->setBounds (344, 352, 168, 24);
    qLabel->setBounds (256, 352, 24, 24);
    convButton->setBounds (600, 248, 208, 56);
    authorLabel->setBounds (48, 552, 136, 24);
    settingsButton->setBounds (8, 520, 224, 24);
    gainSlider->setBounds (352, 184, 456, 24);
    gainLabel->setBounds (256, 184, 88, 24);
    waveformComponent->setBounds (256, 24, 552, 152);
    prBehaviorLabel->setBounds (256, 280, 88, 24);
    prBehaviorComboBox->setBounds (352, 280, 232, 24);
    playButton->setBounds (616, 32, 56, 24);
    loopButton->setBounds (744, 32, 56, 24);
    stopButton->setBounds (680, 32, 56, 24);
    qDefaultButton->setBounds (280, 352, 56, 24);
    sSlider->setBounds (640, 352, 168, 24);
    sDefaultButton->setBounds (576, 352, 56, 24);
    nfftSlider->setBounds (352, 248, 240, 24);
    nfftLabel->setBounds (256, 248, 88, 24);
    saveButton->setBounds (744, 136, 56, 24);
    sLabel->setBounds (552, 352, 24, 24);
    rComponent->setBounds (552, 384, 256, 176);
    pComponent->setBounds (256, 384, 256, 176);
    inputRemoveButton->setBounds (128, 24, 88, 24);
    inputAddButton->setBounds (24, 24, 88, 24);
    inputFileListComponent->setBounds (24, 56, 192, 440);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainContentComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == qSlider)
    {
        //[UserSliderCode_qSlider] -- add your slider handling code here..
		const ScopedLock pl(paramLock);
		qParam = static_cast<float>(qSlider->getValue());
		convDirty = true;
        //[/UserSliderCode_qSlider]
    }
    else if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
		gainParam.set(static_cast<float>(gainSlider->getValue()));
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == sSlider)
    {
        //[UserSliderCode_sSlider] -- add your slider handling code here..
		const ScopedLock pl(paramLock);
		sParam = static_cast<float>(sSlider->getValue());
		convDirty = true;
        //[/UserSliderCode_sSlider]
    }
    else if (sliderThatWasMoved == nfftSlider)
    {
        //[UserSliderCode_nfftSlider] -- add your slider handling code here..
		const ScopedLock pl(paramLock);
		nfftParam = static_cast<int>(nfftSlider->getValue());
		convDirty = true;
        //[/UserSliderCode_nfftSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MainContentComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == convButton)
    {
        //[UserButtonCode_convButton] -- add your button handler code here..
		/*
		const ScopedLock cl(convLock);
		if (convDirty) {
			if (s0.getNumSamples() == 0 && s1.getNumSamples() == 0) {
				AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Error", "You must assign at least one sound before convolving.");
				return;
			}

			setPlayheadUiEnabled(false);

			// retrieve params
			bool convValid = true;
			float p = (1.0f - pParam.get());
			float q = qParam.get();
			float r = (1.0f - rParam.get());
			float s = sParam.get();
			float max = 1.0f;

			// calculate czt coeffs
			int s0Channels = s0.getNumChannels();
			int s1Channels = s1.getNumChannels();
			int s0Samples = s0.getNumSamples();
			int s1Samples = s1.getNumSamples();
			int convChannelsNum = s0Channels > s1Channels ? s0Channels : s1Channels;
			int n = static_cast<int>(nfftSlider->getValue());
			int nfft = static_cast<int>(pow(2.0, n));
			int nffto = nfft / 2 + 1;
			conv.setSize(convChannelsNum, nfft);

			// alloc fft state
			kiss_fftr_state* fftForwardState = kiss_fftr_alloc(nfft, 0, nullptr, nullptr);
			kiss_fftr_state* fftInverseState = kiss_fftr_alloc(nfft, 1, nullptr, nullptr);
			float* fftForwardBuffer = static_cast<float*>(malloc(sizeof(float) * nfft));
			kiss_fft_cpx* S0 = static_cast<kiss_fft_cpx*>(malloc(sizeof(kiss_fft_cpx) * (nffto)));
			kiss_fft_cpx* S1 = static_cast<kiss_fft_cpx*>(malloc(sizeof(kiss_fft_cpx) * (nffto)));
			kiss_fft_cpx* CONV = S0;

			for (int channel = 0; channel < convChannelsNum; ++channel) {
				// retrieve channel buffers
				const float* s0buf = nullptr;
				if (s0Channels > 0) {
					s0buf = s0.getReadPointer(channel >= s0Channels ? s0Channels - 1 : channel);
				}
				const float* s1buf = nullptr;
				if (s1Channels > 0) {
					 s1buf = s1.getReadPointer(channel >= s1Channels ? s1Channels - 1 : channel);
				}

				// fft s0
				int i = 0;
				if (s0Samples > 1) {
					for (i = 0; i < s0Samples; ++i) {
						fftForwardBuffer[i] = s0buf[i];
					}
				}
				else {
					fftForwardBuffer[i] = 1.0;
					++i;
				}
				for (; i < nfft; ++i) {
					fftForwardBuffer[i] = 0.0f;
				}
				kiss_fftr(fftForwardState, fftForwardBuffer, S0);

				// fft s1
				i = 0;
				if (s1Samples > 1) {
					for (i = 0; i < s1Samples; ++i) {
						fftForwardBuffer[i] = s1buf[i];
					}
				}
				else {
					fftForwardBuffer[i] = 1.0;
					++i;
				}
				for (; i < nfft; ++i) {
					fftForwardBuffer[i] = 0.0f;
				}
				kiss_fftr(fftForwardState, fftForwardBuffer, S1);

				// convolve
				for (i = 0; i < nffto; ++i) {
					float xr = S0[i].r;
					float xi = S0[i].i;
					float yr = S1[i].r;
					float yi = S1[i].i;
					float xMag = sqrtf((xr * xr) + (xi * xi));
					float yMag = sqrtf((yr * yr) + (yi * yi));
					float xPhs = atan2f(xi, xr);
					float yPhs = atan2f(yi, yr);
					float convMag = powf(powf(xMag, p) * powf(yMag, (1.0f - p)), 2.0f * q);
					float convPhs = 2.0f * s * ((r * xPhs) + ((1.0f - r) * yPhs));
					float convr = convMag * cosf(convPhs);
					float convi = convMag * sinf(convPhs);
					if (std::isnan(convr) || std::isnan(convi)) {
						convValid = false;
					}
					CONV[i].r = convr;
					CONV[i].i = convi;
				}

				// inverse czt
				kiss_fftri(fftInverseState, CONV, conv.getWritePointer(channel));

				// check max
				float channelMax = conv.findMinMax(channel, 0, nfft).getEnd();
				max = channelMax > max ? channelMax : max;

				// fill buffer
				float* convbuf = conv.getWritePointer(channel);
			}

			// free fft state
			free(S1);
			free(S0);
			free(fftForwardBuffer);
			free(fftForwardState);
			free(fftInverseState);

			// normalize
			conv.applyGain(1.0f / max);

			if (!convValid) {
				AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Error", "Parameters produced NaN value.");
				return;
			}

			// copy to playhead buffer
			{
				const ScopedLock pal(playheadAudioLock);
				if (playheadAudio.getNumSamples() != conv.getNumSamples()) {
					playheadState = PlayheadState::stopped;
					playheadAudioSamplesCompleted = 0;
				}
				playheadAudio.makeCopyOf(conv);
			}

			// copy to UI
			{
				const ScopedLock wdl(waveformDisplayLock);
				waveformComponent->setSound(&conv);
				waveformComponent->repaint();
			}

			setPlayheadUiEnabled(true);

			convDirty = false;
		}
		*/
        //[/UserButtonCode_convButton]
    }
    else if (buttonThatWasClicked == settingsButton)
    {
        //[UserButtonCode_settingsButton] -- add your button handler code here..
		AudioDeviceSelectorComponent audioSettingsComp(deviceManager,
			0, 256,
			0, 256,
			true, true, true, false);

		audioSettingsComp.setSize(500, 450);

		DialogWindow::LaunchOptions o;
		o.content.setNonOwned(&audioSettingsComp);
		o.dialogTitle = "Audio Settings";
		o.componentToCentreAround = this;
		o.dialogBackgroundColour = Colours::azure;
		o.escapeKeyTriggersCloseButton = true;
		o.useNativeTitleBar = false;
		o.resizable = false;

		o.runModal();

		ScopedPointer<XmlElement> audioState(deviceManager.createStateXml());

		getAppProperties().getUserSettings()->setValue("audioDeviceState", audioState);
		getAppProperties().getUserSettings()->saveIfNeeded();
        //[/UserButtonCode_settingsButton]
    }
    else if (buttonThatWasClicked == playButton)
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
		const ScopedLock pal(playheadAudioLock);
		playheadState = PlayheadState::playing;
		playheadAudioSamplesCompleted = 0;
        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == loopButton)
    {
        //[UserButtonCode_loopButton] -- add your button handler code here..
		const ScopedLock pal(playheadAudioLock);
		playheadState = PlayheadState::looping;
        //[/UserButtonCode_loopButton]
    }
    else if (buttonThatWasClicked == stopButton)
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
		const ScopedLock pal(playheadAudioLock);
		playheadState = PlayheadState::stopped;
		playheadAudioSamplesCompleted = 0;
        //[/UserButtonCode_stopButton]
    }
    else if (buttonThatWasClicked == qDefaultButton)
    {
        //[UserButtonCode_qDefaultButton] -- add your button handler code here..
		qSlider->setValue(1.0);
        //[/UserButtonCode_qDefaultButton]
    }
    else if (buttonThatWasClicked == sDefaultButton)
    {
        //[UserButtonCode_sDefaultButton] -- add your button handler code here..
		sSlider->setValue(1.0);
        //[/UserButtonCode_sDefaultButton]
    }
    else if (buttonThatWasClicked == saveButton)
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
		const ScopedLock pal(playheadAudioLock);

		if (playheadAudio.getNumChannels() > 0 && playheadAudio.getNumSamples() > 0) {
			FileChooser fileChooser("Save as...", File::nonexistent, "*.wav", true);
			if (fileChooser.browseForFileToSave(true)) {
				File outputFile = fileChooser.getResult();
				outputFile.deleteFile();
				WavAudioFormat wavFormat;
				ScopedPointer<FileOutputStream> outputFileStream = outputFile.createOutputStream();
				ScopedPointer<AudioFormatWriter> writer = wavFormat.createWriterFor(outputFileStream, 44100.0, playheadAudio.getNumChannels(), 16, StringPairArray(), 0);
				writer->writeFromAudioSampleBuffer(playheadAudio, 0, playheadAudio.getNumSamples());
				outputFileStream.release();
			}
		}
        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == inputRemoveButton)
    {
        //[UserButtonCode_inputRemoveButton] -- add your button handler code here..
		//jassert(fileIdToAttrs.size() == inputFileList.getNumRows());
		const ScopedLock fl(fileListLock);
        //[/UserButtonCode_inputRemoveButton]
    }
    else if (buttonThatWasClicked == inputAddButton)
    {
        //[UserButtonCode_inputAddButton] -- add your button handler code here..
		//jassert(fileIdToAttrs.size() == inputFileList.getNumRows());
		const ScopedLock fl(fileListLock);
        //[/UserButtonCode_inputAddButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainContentComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == prBehaviorComboBox)
    {
        //[UserComboBoxCode_prBehaviorComboBox] -- add your combo box handling code here..
		prBehavior = PrBehavior(prBehaviorComboBox->getSelectedId());
        //[/UserComboBoxCode_prBehaviorComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {}

void MainContentComponent::releaseResources() {}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) {
	const ScopedLock cl(playheadAudioLock);

	AudioSampleBuffer& block = *(bufferToFill.buffer);

	int blockLen = block.getNumSamples();
	int blockChannelsNum = block.getNumChannels();
	int blockSamplesRemaining = blockLen;
	int blockSamplesCompleted = 0;

	switch (playheadState) {
	case PlayheadState::stopped: {
		block.clear();
	}
		break;

	case PlayheadState::playing: {
		int playheadAudioChannelsNum = playheadAudio.getNumChannels();
		int playheadAudioSamplesLen = playheadAudio.getNumSamples();
		int playheadAudioSamplesRemaining = playheadAudioSamplesLen - playheadAudioSamplesCompleted;
		int playheadAudioSamplesCopy = std::min(playheadAudioSamplesRemaining, blockLen);

		for (int blockChannel = 0; blockChannel < blockChannelsNum; ++blockChannel) {
			int playheadAudioChannel = blockChannel < playheadAudioChannelsNum ? blockChannel : playheadAudioChannelsNum - 1;
			block.copyFrom(blockChannel, 0, playheadAudio, playheadAudioChannel, playheadAudioSamplesCompleted, playheadAudioSamplesCopy);
		}

		playheadAudioSamplesCompleted += playheadAudioSamplesCopy;
		playheadAudioSamplesRemaining -= playheadAudioSamplesCopy;
		blockSamplesCompleted += playheadAudioSamplesCopy;
		blockSamplesRemaining -= playheadAudioSamplesCopy;

		if (playheadAudioSamplesRemaining == 0) {
			playheadState = PlayheadState::stopped;
			playheadAudioSamplesCompleted = 0;
		}

		for (int blockChannel = 0; blockChannel < blockChannelsNum; ++blockChannel) {
			block.clear(blockChannel, blockSamplesCompleted, blockSamplesRemaining);
		}

		blockSamplesCompleted += blockSamplesRemaining;
		blockSamplesRemaining -= blockSamplesRemaining;
	}
		break;

	case PlayheadState::looping: {
		while (blockSamplesRemaining > 0) {
			int playheadAudioChannelsNum = playheadAudio.getNumChannels();
			int playheadAudioSamplesLen = playheadAudio.getNumSamples();
			int playheadAudioSamplesRemaining = playheadAudioSamplesLen - playheadAudioSamplesCompleted;
			int playheadAudioSamplesCopy = std::min(playheadAudioSamplesRemaining, blockSamplesRemaining);

			for (int blockChannel = 0; blockChannel < blockChannelsNum; ++blockChannel) {
				int playheadAudioChannel = blockChannel < playheadAudioChannelsNum ? blockChannel : playheadAudioChannelsNum - 1;
				block.copyFrom(blockChannel, blockSamplesCompleted, playheadAudio, playheadAudioChannel, playheadAudioSamplesCompleted, playheadAudioSamplesCopy);
			}

			playheadAudioSamplesCompleted += playheadAudioSamplesCopy;
			playheadAudioSamplesRemaining -= playheadAudioSamplesCopy;
			blockSamplesCompleted += playheadAudioSamplesCopy;
			blockSamplesRemaining -= playheadAudioSamplesCopy;
			if (playheadAudioSamplesRemaining == 0) {
				playheadAudioSamplesCompleted = 0;
			}
		}
	}

		break;

	default:
		jassertfalse;
		break;
	}

	float gain = gainParam.get();
	gain = gain * gain * gain * gain;
	block.applyGain(gain);
}

bool MainContentComponent::isInterestedInFileDrag(const StringArray& files) {
	return true;
}

void MainContentComponent::filesDropped(const StringArray& filePaths, int x, int y) {
	x; y;

	auto loadFile = [](const File& droppedFile) {
		AudioFormatManager formatManager;
		formatManager.registerFormat(new WavAudioFormat(), true);
		formatManager.registerFormat(new AiffAudioFormat(), false);
		formatManager.registerFormat(new OggVorbisAudioFormat(), false);
		ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(droppedFile);

		AudioBuffer<float>* samples = nullptr;
		if (reader != nullptr && reader->numChannels > 0 && reader->numChannels <= JECT_CHANNELS_NUM && reader->lengthInSamples > 0) {
			samples = new AudioBuffer<float>(reader->numChannels, static_cast<int>(reader->lengthInSamples));
			reader->read(samples, 0, static_cast<int>(reader->lengthInSamples), 0, reader->numChannels == 1, reader->numChannels == 2);
		}
		return samples;
	};
	auto nameFile = [](const String& filePath) {
		File droppedFile(filePath);
		return droppedFile.getFileName();
	};

	const ScopedLock fl(fileListLock);
	int succeeded = 0;
	for (int i = 0; i < filePaths.size(); ++i) {
		String filePath = filePaths[i];
		File file(filePath);
		String fileName = file.getFileName();
		AudioBuffer<float>* fileBuffer = loadFile(file);
		if (fileBuffer != nullptr) {
			int fileId = fileIdNext++;
			fileIdToAttrs[fileId] = std::make_tuple(filePath, fileName, fileBuffer);
			succeeded++;
		}
	}

	if (succeeded > 0) {
		convDirty = true;
		inputFilesChanged(dontSendNotification);
	}
	if (succeeded < filePaths.size()) {
		AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Invalid file(s)", "One or more files failed to load.");
	}
}

void MainContentComponent::changeListenerCallback(ChangeBroadcaster* source) {
	if (source == inputFileListComponent) {
		const ScopedLock fl(fileListLock);
		const int lastSelected = inputFileListComponent->getLastRowSelected();
		if (lastSelected >= 0) {
			AudioBuffer<float>* selectedBuffer = std::get<FileAttr::fileBuffer>(fileIdToAttrs[rowToFileId[lastSelected]]);
			setPlayheadAudio(selectedBuffer);
		}
		else {
			const ScopedLock cl(convLock);
			setPlayheadAudio(&conv);
		}
		updatePRComponentLists();
	}
	else if (source == pComponent) {
		const ScopedLock pl(paramLock);
		//jassert(fileIdToAttrs.size() == pParam.size());
	}
	else if (source == rComponent) {
		const ScopedLock pl(paramLock);
		//jassert(fileIdToAttrs.size() == rParam.size());
	}
}

void MainContentComponent::timerCallback() {
	const ScopedLock wdl(waveformDisplayLock);

	waveformComponent->setPlayhead(playheadAudioSamplesCompleted);
	waveformComponent->repaint();

	//setUiFromParams(dontSendNotification);
}

void MainContentComponent::setPlayheadUiEnabled(bool playheadUiEnabled) {
	playButton->setEnabled(playheadUiEnabled);
	loopButton->setEnabled(playheadUiEnabled);
	stopButton->setEnabled(playheadUiEnabled);
	saveButton->setEnabled(playheadUiEnabled);
}

void MainContentComponent::setPlayheadAudio(AudioBuffer<float>* playheadAudioNew) {
	if (playheadAudioNew != nullptr && (playheadAudioNew->getNumChannels() == 0 || playheadAudioNew->getNumSamples() == 0)) {
		playheadAudioNew == nullptr;
	}

	// update display
	{
		const ScopedLock wdl(waveformDisplayLock);
		waveformComponent->setSound(playheadAudioNew);
		waveformComponent->repaint();
	}

	// update playhead audio
	if (playheadAudioNew != nullptr) {
		const ScopedLock pal(playheadAudioLock);
		if (playheadAudioNew->getNumSamples() != playheadAudio.getNumSamples()) {
			playheadState = PlayheadState::stopped;
			playheadAudioSamplesCompleted = 0;
		}
		playheadAudio.makeCopyOf(*playheadAudioNew);
	}

	// update playhead UI
	setPlayheadUiEnabled(playheadAudioNew != nullptr);
}

void MainContentComponent::setUiFromParams(NotificationType notificationType) {
	gainSlider->setValue(static_cast<double>(gainParam.get()), notificationType);
	//pSlider->setValue(static_cast<double>(pParam.get()), notificationType);
	qSlider->setValue(static_cast<double>(qParam), notificationType);
	//rSlider->setValue(static_cast<double>(rParam.get()), notificationType);
	sSlider->setValue(static_cast<double>(sParam), notificationType);
	prBehaviorComboBox->setSelectedId(prBehavior, notificationType);
}

void MainContentComponent::inputFilesChanged(NotificationType notificationType) {
	int filesNum = fileIdToAttrs.size();
	int samplesNum = 0;
	for (auto i : fileIdToAttrs) {
		AudioBuffer<float>* fileBuffer = std::get<FileAttr::fileBuffer>(i.second);
		samplesNum += fileBuffer->getNumSamples();
	}

	if (samplesNum > 0) {
		int n2 = static_cast<int>(std::ceil(std::log2(samplesNum - (filesNum - 1))));
		nfftSlider->setRange(static_cast<double>(n2), 28, 1.0);
		nfftSlider->setValue(static_cast<double>(n2));
		nfftSlider->setEnabled(true);
		convButton->setEnabled(true);
	}
	else {
		nfftSlider->setEnabled(false);
		convButton->setEnabled(false);
	}

	StringArray fileNames;
	int row = 0;
	rowToFileId.clear();
	for (auto i : fileIdToAttrs) {
		int fileId = i.first;
		String fileName = std::get<FileAttr::fileName>(i.second);
		rowToFileId[row++] = fileId;
		fileNames.add(fileName);
	}
	inputFileListComponent->getModel().updateFileNames(fileNames);
	inputFileListComponent->updateContent();
	updatePRComponentLists();
}

void MainContentComponent::updatePRComponentLists() {
	Array<int> includedRows;
	Array<int> includedFileIds;
	inputFileListComponent->getIncludedRows(includedRows);
	for (auto i : includedRows) {
		int fileId = rowToFileId[i];
		includedFileIds.add(fileId);
	}

	StringArray fileNames;
	for (auto i : includedFileIds) {
		String fileName = std::get<FileAttr::fileName>(fileIdToAttrs[i]);
		fileNames.add(fileName);
	}
	pComponent->getModel().updateFileNames(fileNames);
	pComponent->updateContent();
	rComponent->getModel().updateFileNames(fileNames);
	rComponent->updateContent();
}

void MainContentComponent::fftFree() {
	for (int channel = 0; channel < JECT_CHANNELS_NUM; ++channel) {
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainContentComponent" componentName=""
                 parentClasses="public AudioAppComponent, public FileDragAndDropTarget, public Timer, public ChangeListener"
                 constructorParams="" variableInitialisers="gainParam(0.5),&#10;nfftParam(0),&#10;pParam(0.5),&#10;qParam(1.0),&#10;rParam(0.5),&#10;sParam(1.0),&#10;prBehavior(PrBehavior::independent),&#10;waveformDisplayLock(),&#10;conv(0, 0),&#10;convDirty(true),&#10;playheadAudioLock(),&#10;playheadState(PlayheadState::stopped),&#10;playheadAudio(0, 0),&#10;playheadAudioSamplesCompleted(0),&#10;fileIdNext(0)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="832" initialHeight="584">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="" id="5b5e49932e4cad01" memberName="inputGroupBox" virtualName=""
                  explicitFocusOrder="0" pos="8 0 224 512" title="Input"/>
  <GROUPCOMPONENT name="" id="251b2a29053ccce1" memberName="convGroupBox" virtualName=""
                  explicitFocusOrder="0" pos="240 224 584 96" title="Convolution"/>
  <GROUPCOMPONENT name="" id="575ce3c3d9a50031" memberName="phaseComboBox" virtualName=""
                  explicitFocusOrder="0" pos="536 328 288 248" title="Phase"/>
  <GROUPCOMPONENT name="" id="21c1f2698d79584b" memberName="magniComboBox" virtualName=""
                  explicitFocusOrder="0" pos="240 328 288 248" title="Magnitude"/>
  <GROUPCOMPONENT name="" id="7c21d6435b394a3c" memberName="waveformGroupBox" virtualName=""
                  explicitFocusOrder="0" pos="240 2 584 214" title="Waveform"/>
  <SLIDER name="" id="5d8042d5cba6f5af" memberName="qSlider" virtualName=""
          explicitFocusOrder="0" pos="344 352 168 24" min="0" max="8" int="0.010000000000000000208"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="40" textBoxHeight="20" skewFactor="0.4000000000000000222"
          needsCallback="1"/>
  <LABEL name="" id="8c32c3818b630f5" memberName="qLabel" virtualName=""
         explicitFocusOrder="0" pos="256 352 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Q" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="1b9a996260e602ac" memberName="convButton" virtualName=""
              explicitFocusOrder="0" pos="600 248 208 56" buttonText="Convolve"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="45a3ca5fc03eb3c6" memberName="authorLabel" virtualName=""
         explicitFocusOrder="0" pos="48 552 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Chris Donahue 2016" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="8a40cfbb6678ded1" memberName="settingsButton" virtualName=""
              explicitFocusOrder="0" pos="8 520 224 24" buttonText="Audio Settings"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="4e9f7543cb949220" memberName="gainSlider" virtualName=""
          explicitFocusOrder="0" pos="352 184 456 24" min="0" max="1" int="0.010000000000000000208"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="" id="617675cab679ff64" memberName="gainLabel" virtualName=""
         explicitFocusOrder="0" pos="256 184 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="" id="5da17034a15a2c26" memberName="waveformComponent"
                    virtualName="" explicitFocusOrder="0" pos="256 24 552 152" class="WaveformComponent"
                    params="&quot;No waveform to display&quot;"/>
  <LABEL name="" id="df0c2bbfcc27d23b" memberName="prBehaviorLabel" virtualName=""
         explicitFocusOrder="0" pos="256 280 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="P/R Behavior" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="" id="e3ce100f165f7ce9" memberName="prBehaviorComboBox"
            virtualName="" explicitFocusOrder="0" pos="352 280 232 24" editable="0"
            layout="33" items="Independent&#10;Linked&#10;Inverse" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="" id="ae50f5bf4f928bae" memberName="playButton" virtualName=""
              explicitFocusOrder="0" pos="616 32 56 24" buttonText="Play" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="bc50acff95e14f9c" memberName="loopButton" virtualName=""
              explicitFocusOrder="0" pos="744 32 56 24" buttonText="Loop" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="ee7f76320bc5ba72" memberName="stopButton" virtualName=""
              explicitFocusOrder="0" pos="680 32 56 24" buttonText="Stop" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="458e93826aa283d" memberName="qDefaultButton" virtualName=""
              explicitFocusOrder="0" pos="280 352 56 24" buttonText="Default"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="234c4909ac1ef82e" memberName="sSlider" virtualName=""
          explicitFocusOrder="0" pos="640 352 168 24" min="0" max="15"
          int="0.010000000000000000208" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TEXTBUTTON name="" id="6b491d9785461117" memberName="sDefaultButton" virtualName=""
              explicitFocusOrder="0" pos="576 352 56 24" buttonText="Default"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="2ccccb8c8ed630bf" memberName="nfftSlider" virtualName=""
          explicitFocusOrder="0" pos="352 248 240 24" min="0" max="24"
          int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="" id="9b09e8ab97220128" memberName="nfftLabel" virtualName=""
         explicitFocusOrder="0" pos="256 248 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="NFFT" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="5349946cfc445d79" memberName="saveButton" virtualName=""
              explicitFocusOrder="0" pos="744 136 56 24" buttonText="Save"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="676135372bd3b95b" memberName="sLabel" virtualName=""
         explicitFocusOrder="0" pos="552 352 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="S" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="" id="c5b31d19af3a5454" memberName="rComponent" virtualName=""
                    explicitFocusOrder="0" pos="552 384 256 176" class="ParameterSliderTableListBox"
                    params="&quot;R&quot;"/>
  <GENERICCOMPONENT name="" id="6b2b891fb1909c36" memberName="pComponent" virtualName=""
                    explicitFocusOrder="0" pos="256 384 256 176" class="ParameterSliderTableListBox"
                    params="&quot;P&quot;"/>
  <TEXTBUTTON name="" id="ce8360a29a7e1323" memberName="inputRemoveButton"
              virtualName="" explicitFocusOrder="0" pos="128 24 88 24" buttonText="Remove"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="dcb4b995c383b4ef" memberName="inputAddButton" virtualName=""
              explicitFocusOrder="0" pos="24 24 88 24" buttonText="Add" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="7617b55e4d758efa" memberName="inputFileListComponent"
                    virtualName="" explicitFocusOrder="0" pos="24 56 192 440" class="InputFileTableListBox"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
