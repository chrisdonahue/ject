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
      s0(0, 0),
      s1(0, 0),
      conv(0, 0),
      convDirty(true),
      playheadAudioLock(),
      playheadState(PlayheadState::stopped),
      playheadAudio(0, 0),
      playheadAudioSamplesCompleted(0)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (convGroupBox = new GroupComponent (String(),
                                                          TRANS("Convolution")));

    addAndMakeVisible (controlGroupBox = new GroupComponent (String(),
                                                             TRANS("Controls")));

    addAndMakeVisible (s1GroupBox = new GroupComponent (String(),
                                                        TRANS("Sound 2")));

    addAndMakeVisible (s0GroupBox = new GroupComponent (String(),
                                                        TRANS("Sound 1")));

    addAndMakeVisible (pSlider = new Slider (String()));
    pSlider->setRange (0, 1, 0.01);
    pSlider->setSliderStyle (Slider::LinearHorizontal);
    pSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    pSlider->addListener (this);

    addAndMakeVisible (qSlider = new Slider (String()));
    qSlider->setRange (0, 8, 0.01);
    qSlider->setSliderStyle (Slider::LinearHorizontal);
    qSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    qSlider->addListener (this);
    qSlider->setSkewFactor (0.4);

    addAndMakeVisible (pLabel = new Label (String(),
                                           TRANS("P")));
    pLabel->setFont (Font (15.00f, Font::plain));
    pLabel->setJustificationType (Justification::centredLeft);
    pLabel->setEditable (false, false, false);
    pLabel->setColour (TextEditor::textColourId, Colours::black);
    pLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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

    addAndMakeVisible (titleLabel = new Label (String(),
                                               TRANS("JUCE Extended Convolution Techniques (JECT)")));
    titleLabel->setFont (Font (15.00f, Font::plain));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (s0Component = new WaveformComponent ("Drag and drop a sound file"));

    addAndMakeVisible (s1Component = new WaveformComponent ("Drag and drop a sound file"));

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

    addAndMakeVisible (convComponent = new WaveformComponent ("Press convolve"));

    addAndMakeVisible (rLabel = new Label (String(),
                                           TRANS("R")));
    rLabel->setFont (Font (15.00f, Font::plain));
    rLabel->setJustificationType (Justification::centredLeft);
    rLabel->setEditable (false, false, false);
    rLabel->setColour (TextEditor::textColourId, Colours::black);
    rLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rSlider = new Slider (String()));
    rSlider->setRange (0, 1, 0.01);
    rSlider->setSliderStyle (Slider::LinearHorizontal);
    rSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    rSlider->addListener (this);

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

    addAndMakeVisible (pDefaultButton = new TextButton (String()));
    pDefaultButton->setButtonText (TRANS("Default"));
    pDefaultButton->addListener (this);

    addAndMakeVisible (rDefaultButton = new TextButton (String()));
    rDefaultButton->setButtonText (TRANS("Default"));
    rDefaultButton->addListener (this);

    addAndMakeVisible (qDefaultButton = new TextButton (String()));
    qDefaultButton->setButtonText (TRANS("Default"));
    qDefaultButton->addListener (this);

    addAndMakeVisible (sSlider = new Slider (String()));
    sSlider->setRange (0, 15, 0.01);
    sSlider->setSliderStyle (Slider::LinearHorizontal);
    sSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sSlider->addListener (this);

    addAndMakeVisible (sLabel = new Label (String(),
                                           TRANS("S")));
    sLabel->setFont (Font (15.00f, Font::plain));
    sLabel->setJustificationType (Justification::centredLeft);
    sLabel->setEditable (false, false, false);
    sLabel->setColour (TextEditor::textColourId, Colours::black);
    sLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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

    addAndMakeVisible (clear1Button = new TextButton (String()));
    clear1Button->setButtonText (TRANS("Clear"));
    clear1Button->addListener (this);

    addAndMakeVisible (clear0Button = new TextButton (String()));
    clear0Button->setButtonText (TRANS("Clear"));
    clear0Button->addListener (this);

    addAndMakeVisible (saveButton = new TextButton (String()));
    saveButton->setButtonText (TRANS("Save"));
    saveButton->addListener (this);


    //[UserPreSize]
	//timerCallback();
	soundChanged(dontSendNotification);
	setUiFromParams(dontSendNotification);
	setPlayheadUiEnabled(false);
	convButton->setEnabled(false);
    //[/UserPreSize]

    setSize (600, 700);


    //[Constructor] You can add your own custom stuff here..
	setAudioChannels(0, JECT_CHANNELS_NUM);
	startTimerHz(JECT_FPS);
    //[/Constructor]
}

MainContentComponent::~MainContentComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	fftFree();
    //[/Destructor_pre]

    convGroupBox = nullptr;
    controlGroupBox = nullptr;
    s1GroupBox = nullptr;
    s0GroupBox = nullptr;
    pSlider = nullptr;
    qSlider = nullptr;
    pLabel = nullptr;
    qLabel = nullptr;
    convButton = nullptr;
    authorLabel = nullptr;
    titleLabel = nullptr;
    s0Component = nullptr;
    s1Component = nullptr;
    settingsButton = nullptr;
    gainSlider = nullptr;
    gainLabel = nullptr;
    convComponent = nullptr;
    rLabel = nullptr;
    rSlider = nullptr;
    prBehaviorLabel = nullptr;
    prBehaviorComboBox = nullptr;
    playButton = nullptr;
    loopButton = nullptr;
    stopButton = nullptr;
    pDefaultButton = nullptr;
    rDefaultButton = nullptr;
    qDefaultButton = nullptr;
    sSlider = nullptr;
    sLabel = nullptr;
    sDefaultButton = nullptr;
    nfftSlider = nullptr;
    nfftLabel = nullptr;
    clear1Button = nullptr;
    clear0Button = nullptr;
    saveButton = nullptr;


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

    convGroupBox->setBounds (8, 186, 584, 184);
    controlGroupBox->setBounds (8, 376, 584, 320);
    s1GroupBox->setBounds (304, 0, 288, 184);
    s0GroupBox->setBounds (8, 0, 288, 184);
    pSlider->setBounds (208, 496, 368, 24);
    qSlider->setBounds (208, 560, 368, 24);
    pLabel->setBounds (24, 496, 112, 24);
    qLabel->setBounds (24, 560, 112, 24);
    convButton->setBounds (424, 656, 150, 24);
    authorLabel->setBounds (24, 656, 160, 24);
    titleLabel->setBounds (24, 624, 272, 24);
    s0Component->setBounds (16, 16, 272, 160);
    s1Component->setBounds (312, 16, 272, 160);
    settingsButton->setBounds (264, 656, 150, 24);
    gainSlider->setBounds (120, 400, 456, 24);
    gainLabel->setBounds (24, 400, 88, 24);
    convComponent->setBounds (16, 200, 568, 160);
    rLabel->setBounds (24, 528, 112, 24);
    rSlider->setBounds (208, 528, 368, 24);
    prBehaviorLabel->setBounds (24, 464, 96, 24);
    prBehaviorComboBox->setBounds (120, 464, 450, 24);
    playButton->setBounds (392, 208, 56, 24);
    loopButton->setBounds (520, 208, 56, 24);
    stopButton->setBounds (456, 208, 56, 24);
    pDefaultButton->setBounds (144, 496, 56, 24);
    rDefaultButton->setBounds (144, 528, 56, 24);
    qDefaultButton->setBounds (144, 560, 56, 24);
    sSlider->setBounds (208, 592, 368, 24);
    sLabel->setBounds (24, 592, 112, 24);
    sDefaultButton->setBounds (144, 592, 56, 24);
    nfftSlider->setBounds (120, 432, 456, 24);
    nfftLabel->setBounds (24, 432, 88, 24);
    clear1Button->setBounds (520, 24, 56, 24);
    clear0Button->setBounds (224, 24, 56, 24);
    saveButton->setBounds (520, 328, 56, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainContentComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == pSlider)
    {
        //[UserSliderCode_pSlider] -- add your slider handling code here..
		float p = static_cast<float>(pSlider->getValue());
		pParam.set(p);

		switch (prBehavior) {
		case PrBehavior::independent:
			break;
		case PrBehavior::linked:
			rSlider->setValue(p, dontSendNotification);
			rParam.set(p);
			break;
		case PrBehavior::inverse:
			rSlider->setValue((1.0f - p), dontSendNotification);
			rParam.set((1.0f - p));
			break;
		default:
			jassertfalse;
		}

		convDirty = true;
        //[/UserSliderCode_pSlider]
    }
    else if (sliderThatWasMoved == qSlider)
    {
        //[UserSliderCode_qSlider] -- add your slider handling code here..
		qParam.set(static_cast<float>(qSlider->getValue()));
		convDirty = true;
        //[/UserSliderCode_qSlider]
    }
    else if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
		gainParam.set(static_cast<float>(gainSlider->getValue()));
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == rSlider)
    {
        //[UserSliderCode_rSlider] -- add your slider handling code here..
		float r = static_cast<float>(rSlider->getValue());
		rParam.set(r);

		switch (prBehavior) {
		case PrBehavior::independent:
			break;
		case PrBehavior::linked:
			pSlider->setValue(r, dontSendNotification);
			pParam.set(r);
			break;
		case PrBehavior::inverse:
			pSlider->setValue((1.0f - r), dontSendNotification);
			pParam.set((1.0f - r));
			break;
		default:
			jassertfalse;
		}

		convDirty = true;
        //[/UserSliderCode_rSlider]
    }
    else if (sliderThatWasMoved == sSlider)
    {
        //[UserSliderCode_sSlider] -- add your slider handling code here..
		sParam.set(static_cast<float>(sSlider->getValue()));
		convDirty = true;
        //[/UserSliderCode_sSlider]
    }
    else if (sliderThatWasMoved == nfftSlider)
    {
        //[UserSliderCode_nfftSlider] -- add your slider handling code here..
		nfftParam.set(static_cast<int>(nfftSlider->getValue()));
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
				convComponent->setSound(&conv);
				convComponent->repaint();
			}

			setPlayheadUiEnabled(true);

			convDirty = false;
		}
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
		const ScopedLock cl(convLock);
		const ScopedLock pal(playheadAudioLock);
		playheadState = PlayheadState::playing;
		playheadAudioSamplesCompleted = 0;
        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == loopButton)
    {
        //[UserButtonCode_loopButton] -- add your button handler code here..
		const ScopedLock cl(convLock);
		const ScopedLock pal(playheadAudioLock);
		playheadState = PlayheadState::looping;
        //[/UserButtonCode_loopButton]
    }
    else if (buttonThatWasClicked == stopButton)
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
		const ScopedLock cl(convLock);
		const ScopedLock pal(playheadAudioLock);
		playheadState = PlayheadState::stopped;
		playheadAudioSamplesCompleted = 0;
        //[/UserButtonCode_stopButton]
    }
    else if (buttonThatWasClicked == pDefaultButton)
    {
        //[UserButtonCode_pDefaultButton] -- add your button handler code here..
		pSlider->setValue(0.5);
        //[/UserButtonCode_pDefaultButton]
    }
    else if (buttonThatWasClicked == rDefaultButton)
    {
        //[UserButtonCode_rDefaultButton] -- add your button handler code here..
		rSlider->setValue(0.5);
        //[/UserButtonCode_rDefaultButton]
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
    else if (buttonThatWasClicked == clear1Button)
    {
        //[UserButtonCode_clear1Button] -- add your button handler code here..
		s1.setSize(0, 0);

		const ScopedLock wdl(waveformDisplayLock);
		s1Component->setSound(nullptr);
		s1Component->repaint();

		soundChanged(dontSendNotification);
        //[/UserButtonCode_clear1Button]
    }
    else if (buttonThatWasClicked == clear0Button)
    {
        //[UserButtonCode_clear0Button] -- add your button handler code here..
		s0.setSize(0, 0);

		const ScopedLock wdl(waveformDisplayLock);
		s0Component->setSound(nullptr);
		s0Component->repaint();

		soundChanged(dontSendNotification);
        //[/UserButtonCode_clear0Button]
    }
    else if (buttonThatWasClicked == saveButton)
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
		const ScopedLock cl(convLock);

		if (conv.getNumChannels() > 0 && conv.getNumSamples() > 0) {
			FileChooser fileChooser("Save as...", File::nonexistent, "*.wav", true);
			if (fileChooser.browseForFileToSave(true)) {
				File outputFile = fileChooser.getResult();
				outputFile.deleteFile();
				WavAudioFormat wavFormat;
				ScopedPointer<FileOutputStream> outputFileStream = outputFile.createOutputStream();
				ScopedPointer<AudioFormatWriter> writer = wavFormat.createWriterFor(outputFileStream, 44100.0, conv.getNumChannels(), 16, StringPairArray(), 0);
				writer->writeFromAudioSampleBuffer(conv, 0, conv.getNumSamples());
				outputFileStream.release();
			}
		}
        //[/UserButtonCode_saveButton]
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
	return files.size() <= 2;
}

void MainContentComponent::filesDropped(const StringArray& files, int x, int y) {
	y;

	auto loadFile = [](const String& filePath) {
		File droppedFile(filePath);

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

	bool loadSucceeded = false;
	if (files.size() == 1) {
		AudioBuffer<float>* sf = loadFile(files[0]);
		if (sf != nullptr) {
			AudioBuffer<float>& s = x < getWidth() / 2 ? s0 : s1;
			s.makeCopyOf(*sf);

			const ScopedLock wdl(waveformDisplayLock);
			WaveformComponent* sComponent = x < getWidth() / 2 ? s0Component : s1Component;
			sComponent->setSound(&s);
			sComponent->repaint();
			loadSucceeded = true;
		}
		delete sf;
	}
	else if (files.size() == 2) {
		AudioBuffer<float>* sf0 = loadFile(files[0]);
		AudioBuffer<float>* sf1 = loadFile(files[1]);
		if (sf0 != nullptr && sf1 != nullptr) {
			s0.makeCopyOf(*sf0);
			s1.makeCopyOf(*sf1);

			const ScopedLock wdl(waveformDisplayLock);
			s0Component->setSound(&s0);
			s0Component->repaint();
			s1Component->setSound(&s1);
			s1Component->repaint();
			loadSucceeded = true;
		}
		delete sf0;
		delete sf1;
	}

	if (loadSucceeded) {
		soundChanged(dontSendNotification);
		convDirty = true;
	}
	else {
		AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Invalid file(s)", "Must be a valid WAV or AIFF file(s).");
	}
}

void MainContentComponent::timerCallback() {
	const ScopedLock wdl(waveformDisplayLock);

	convComponent->setPlayhead(playheadAudioSamplesCompleted);
	convComponent->repaint();

	//setUiFromParams(dontSendNotification);
}

void MainContentComponent::setPlayheadUiEnabled(bool playheadUiEnabled) {
	playButton->setEnabled(playheadUiEnabled);
	loopButton->setEnabled(playheadUiEnabled);
	stopButton->setEnabled(playheadUiEnabled);
	saveButton->setEnabled(playheadUiEnabled);
}

void MainContentComponent::setUiFromParams(NotificationType notificationType) {
	gainSlider->setValue(static_cast<double>(gainParam.get()), notificationType);
	pSlider->setValue(static_cast<double>(pParam.get()), notificationType);
	qSlider->setValue(static_cast<double>(qParam.get()), notificationType);
	rSlider->setValue(static_cast<double>(rParam.get()), notificationType);
	sSlider->setValue(static_cast<double>(sParam.get()), notificationType);
	prBehaviorComboBox->setSelectedId(prBehavior, notificationType);
}

void MainContentComponent::soundChanged(NotificationType notificationType) {
	int n = s0.getNumSamples();
	int m = s1.getNumSamples();
	clear0Button->setEnabled(n > 0);
	clear1Button->setEnabled(m > 0);
	if (n > 0 || m > 0) {
		int n2 = static_cast<int>(std::ceil(std::log2(m + n - 1)));
		nfftSlider->setRange(static_cast<double>(n2), 24, 1.0);
		nfftSlider->setValue(static_cast<double>(n2));
		nfftSlider->setEnabled(true);
		convButton->setEnabled(true);
	}
	else {
		nfftSlider->setEnabled(false);
		convButton->setEnabled(false);
	}
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
                 parentClasses="public AudioAppComponent, public FileDragAndDropTarget, public Timer"
                 constructorParams="" variableInitialisers="gainParam(0.5),&#10;nfftParam(0),&#10;pParam(0.5),&#10;qParam(1.0),&#10;rParam(0.5),&#10;sParam(1.0),&#10;prBehavior(PrBehavior::independent),&#10;waveformDisplayLock(),&#10;s0(0, 0),&#10;s1(0, 0),&#10;conv(0, 0),&#10;convDirty(true),&#10;playheadAudioLock(),&#10;playheadState(PlayheadState::stopped),&#10;playheadAudio(0, 0),&#10;playheadAudioSamplesCompleted(0)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="700">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="" id="7c21d6435b394a3c" memberName="convGroupBox" virtualName=""
                  explicitFocusOrder="0" pos="8 186 584 184" title="Convolution"/>
  <GROUPCOMPONENT name="" id="d29ea4e3198c885f" memberName="controlGroupBox" virtualName=""
                  explicitFocusOrder="0" pos="8 376 584 320" title="Controls"/>
  <GROUPCOMPONENT name="" id="7f4de84a2a2d0de8" memberName="s1GroupBox" virtualName=""
                  explicitFocusOrder="0" pos="304 0 288 184" title="Sound 2"/>
  <GROUPCOMPONENT name="" id="936ab3959f78b732" memberName="s0GroupBox" virtualName=""
                  explicitFocusOrder="0" pos="8 0 288 184" title="Sound 1"/>
  <SLIDER name="" id="b734202570349ef7" memberName="pSlider" virtualName=""
          explicitFocusOrder="0" pos="208 496 368 24" min="0" max="1" int="0.010000000000000000208"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="" id="5d8042d5cba6f5af" memberName="qSlider" virtualName=""
          explicitFocusOrder="0" pos="208 560 368 24" min="0" max="8" int="0.010000000000000000208"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.4000000000000000222"
          needsCallback="1"/>
  <LABEL name="" id="5a92a1c0c61b5c41" memberName="pLabel" virtualName=""
         explicitFocusOrder="0" pos="24 496 112 24" edTextCol="ff000000"
         edBkgCol="0" labelText="P" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="" id="8c32c3818b630f5" memberName="qLabel" virtualName=""
         explicitFocusOrder="0" pos="24 560 112 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Q" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="1b9a996260e602ac" memberName="convButton" virtualName=""
              explicitFocusOrder="0" pos="424 656 150 24" buttonText="Convolve"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="45a3ca5fc03eb3c6" memberName="authorLabel" virtualName=""
         explicitFocusOrder="0" pos="24 656 160 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Chris Donahue 2016" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="45188882c1412d7c" memberName="titleLabel" virtualName=""
         explicitFocusOrder="0" pos="24 624 272 24" edTextCol="ff000000"
         edBkgCol="0" labelText="JUCE Extended Convolution Techniques (JECT)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="" id="377e700af803a7e6" memberName="s0Component" virtualName=""
                    explicitFocusOrder="0" pos="16 16 272 160" class="WaveformComponent"
                    params="&quot;Drag and drop a sound file&quot;"/>
  <GENERICCOMPONENT name="" id="5b0b3104156858db" memberName="s1Component" virtualName=""
                    explicitFocusOrder="0" pos="312 16 272 160" class="WaveformComponent"
                    params="&quot;Drag and drop a sound file&quot;"/>
  <TEXTBUTTON name="" id="8a40cfbb6678ded1" memberName="settingsButton" virtualName=""
              explicitFocusOrder="0" pos="264 656 150 24" buttonText="Audio Settings"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="4e9f7543cb949220" memberName="gainSlider" virtualName=""
          explicitFocusOrder="0" pos="120 400 456 24" min="0" max="1" int="0.010000000000000000208"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="" id="617675cab679ff64" memberName="gainLabel" virtualName=""
         explicitFocusOrder="0" pos="24 400 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="" id="5da17034a15a2c26" memberName="convComponent" virtualName=""
                    explicitFocusOrder="0" pos="16 200 568 160" class="WaveformComponent"
                    params="&quot;Press convolve&quot;"/>
  <LABEL name="" id="445a0c5c9d3f6ec3" memberName="rLabel" virtualName=""
         explicitFocusOrder="0" pos="24 528 112 24" edTextCol="ff000000"
         edBkgCol="0" labelText="R" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="" id="a14a93f161aeeefb" memberName="rSlider" virtualName=""
          explicitFocusOrder="0" pos="208 528 368 24" min="0" max="1" int="0.010000000000000000208"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="" id="df0c2bbfcc27d23b" memberName="prBehaviorLabel" virtualName=""
         explicitFocusOrder="0" pos="24 464 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="P/R Behavior" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="" id="e3ce100f165f7ce9" memberName="prBehaviorComboBox"
            virtualName="" explicitFocusOrder="0" pos="120 464 450 24" editable="0"
            layout="33" items="Independent&#10;Linked&#10;Inverse" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="" id="ae50f5bf4f928bae" memberName="playButton" virtualName=""
              explicitFocusOrder="0" pos="392 208 56 24" buttonText="Play"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="bc50acff95e14f9c" memberName="loopButton" virtualName=""
              explicitFocusOrder="0" pos="520 208 56 24" buttonText="Loop"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="ee7f76320bc5ba72" memberName="stopButton" virtualName=""
              explicitFocusOrder="0" pos="456 208 56 24" buttonText="Stop"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="a6a8906cf722d7da" memberName="pDefaultButton" virtualName=""
              explicitFocusOrder="0" pos="144 496 56 24" buttonText="Default"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="c2e4b33c06a7012" memberName="rDefaultButton" virtualName=""
              explicitFocusOrder="0" pos="144 528 56 24" buttonText="Default"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="458e93826aa283d" memberName="qDefaultButton" virtualName=""
              explicitFocusOrder="0" pos="144 560 56 24" buttonText="Default"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="234c4909ac1ef82e" memberName="sSlider" virtualName=""
          explicitFocusOrder="0" pos="208 592 368 24" min="0" max="15"
          int="0.010000000000000000208" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="" id="6cc43f6f86e31c23" memberName="sLabel" virtualName=""
         explicitFocusOrder="0" pos="24 592 112 24" edTextCol="ff000000"
         edBkgCol="0" labelText="S" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="6b491d9785461117" memberName="sDefaultButton" virtualName=""
              explicitFocusOrder="0" pos="144 592 56 24" buttonText="Default"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="2ccccb8c8ed630bf" memberName="nfftSlider" virtualName=""
          explicitFocusOrder="0" pos="120 432 456 24" min="0" max="24"
          int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="" id="9b09e8ab97220128" memberName="nfftLabel" virtualName=""
         explicitFocusOrder="0" pos="24 432 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="NFFT" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="b854313eefa4be50" memberName="clear1Button" virtualName=""
              explicitFocusOrder="0" pos="520 24 56 24" buttonText="Clear"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="d7e64cf27208ed92" memberName="clear0Button" virtualName=""
              explicitFocusOrder="0" pos="224 24 56 24" buttonText="Clear"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="5349946cfc445d79" memberName="saveButton" virtualName=""
              explicitFocusOrder="0" pos="520 328 56 24" buttonText="Save"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
