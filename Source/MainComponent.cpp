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
MainContentComponent::MainContentComponent()
	: gainParam(0.5),
	nfftParam(0),
	qParam(1.0),
	sParam(1.0),
	conv(0, 0),
	playheadAudioLock(),
	playheadState(PlayheadState::stopped),
	playheadAudio(0, 0),
	playheadAudioSamplesCompleted(0),
	soundIdNext(0)
{
	//[Constructor_pre] You can add your own custom stuff here..
	//[/Constructor_pre]

	addAndMakeVisible(waveformGroupBox = new GroupComponent(String(),
		TRANS("Waveform")));

	addAndMakeVisible(waveformComponent = new WaveformComponent("No waveform to display"));

	addAndMakeVisible(inputGroupBox = new GroupComponent(String(),
		TRANS("Input")));

	addAndMakeVisible(convGroupBox = new GroupComponent(String(),
		TRANS("Convolution")));

	addAndMakeVisible(qSlider = new Slider(String()));
	qSlider->setRange(0, 8, 0.01);
	qSlider->setSliderStyle(Slider::LinearHorizontal);
	qSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
	qSlider->addListener(this);
	qSlider->setSkewFactor(0.4);

	addAndMakeVisible(qLabel = new Label(String(),
		TRANS("Q")));
	qLabel->setFont(Font(15.00f, Font::plain));
	qLabel->setJustificationType(Justification::centredLeft);
	qLabel->setEditable(false, false, false);
	qLabel->setColour(TextEditor::textColourId, Colours::black);
	qLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(convButton = new TextButton(String()));
	convButton->setButtonText(TRANS("Convolve"));
	convButton->addListener(this);

	addAndMakeVisible(authorLabel = new Label(String(),
		TRANS("Chris Donahue 2016")));
	authorLabel->setFont(Font(15.00f, Font::plain));
	authorLabel->setJustificationType(Justification::centredLeft);
	authorLabel->setEditable(false, false, false);
	authorLabel->setColour(TextEditor::textColourId, Colours::black);
	authorLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(settingsButton = new TextButton(String()));
	settingsButton->setButtonText(TRANS("Audio Settings"));
	settingsButton->addListener(this);

	addAndMakeVisible(gainSlider = new Slider(String()));
	gainSlider->setRange(0, 1, 0.01);
	gainSlider->setSliderStyle(Slider::LinearHorizontal);
	gainSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
	gainSlider->addListener(this);

	addAndMakeVisible(gainLabel = new Label(String(),
		TRANS("Gain")));
	gainLabel->setFont(Font(15.00f, Font::plain));
	gainLabel->setJustificationType(Justification::centredLeft);
	gainLabel->setEditable(false, false, false);
	gainLabel->setColour(TextEditor::textColourId, Colours::black);
	gainLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(prBehaviorLabel = new Label(String(),
		TRANS("P/R Behavior")));
	prBehaviorLabel->setFont(Font(15.00f, Font::plain));
	prBehaviorLabel->setJustificationType(Justification::centredLeft);
	prBehaviorLabel->setEditable(false, false, false);
	prBehaviorLabel->setColour(TextEditor::textColourId, Colours::black);
	prBehaviorLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(prBehaviorComboBox = new ComboBox(String()));
	prBehaviorComboBox->setEditableText(false);
	prBehaviorComboBox->setJustificationType(Justification::centredLeft);
	prBehaviorComboBox->setTextWhenNothingSelected(String());
	prBehaviorComboBox->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
	prBehaviorComboBox->addItem(TRANS("Independent"), 1);
	prBehaviorComboBox->addItem(TRANS("Linked"), 2);
	prBehaviorComboBox->addItem(TRANS("Inverse"), 3);
	prBehaviorComboBox->addListener(this);

	addAndMakeVisible(playButton = new TextButton(String()));
	playButton->setButtonText(TRANS("Play"));
	playButton->addListener(this);

	addAndMakeVisible(loopButton = new TextButton(String()));
	loopButton->setButtonText(TRANS("Loop"));
	loopButton->addListener(this);

	addAndMakeVisible(stopButton = new TextButton(String()));
	stopButton->setButtonText(TRANS("Stop"));
	stopButton->addListener(this);

	addAndMakeVisible(qDefaultButton = new TextButton(String()));
	qDefaultButton->setButtonText(TRANS("Default"));
	qDefaultButton->addListener(this);

	addAndMakeVisible(sSlider = new Slider(String()));
	sSlider->setRange(0, 15, 0.01);
	sSlider->setSliderStyle(Slider::LinearHorizontal);
	sSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
	sSlider->addListener(this);

	addAndMakeVisible(sDefaultButton = new TextButton(String()));
	sDefaultButton->setButtonText(TRANS("Default"));
	sDefaultButton->addListener(this);

	addAndMakeVisible(nfftSlider = new Slider(String()));
	nfftSlider->setRange(0, 24, 1);
	nfftSlider->setSliderStyle(Slider::LinearHorizontal);
	nfftSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
	nfftSlider->addListener(this);

	addAndMakeVisible(nfftLabel = new Label(String(),
		TRANS("NFFT")));
	nfftLabel->setFont(Font(15.00f, Font::plain));
	nfftLabel->setJustificationType(Justification::centredLeft);
	nfftLabel->setEditable(false, false, false);
	nfftLabel->setColour(TextEditor::textColourId, Colours::black);
	nfftLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(saveButton = new TextButton(String()));
	saveButton->setButtonText(TRANS("Save"));
	saveButton->addListener(this);

	addAndMakeVisible(sLabel = new Label(String(),
		TRANS("S")));
	sLabel->setFont(Font(15.00f, Font::plain));
	sLabel->setJustificationType(Justification::centredLeft);
	sLabel->setEditable(false, false, false);
	sLabel->setColour(TextEditor::textColourId, Colours::black);
	sLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(inputRemoveButton = new TextButton(String()));
	inputRemoveButton->setButtonText(TRANS("Remove"));
	inputRemoveButton->addListener(this);

	addAndMakeVisible(inputAddButton = new TextButton(String()));
	inputAddButton->setButtonText(TRANS("Add"));
	inputAddButton->addListener(this);

	addAndMakeVisible(inputFileListComponent = new InputFileTableListBox(InputFileTableListBox::PrBehavior::independent));


	//[UserPreSize]
	inputFileListComponent->addChangeListener(this);
	waveformComponent->setSound(&playheadAudio);
	setPlayheadAudio(nullptr);

	//timerCallback();
	inputFilesChanged(dontSendNotification);
	setUiFromParams(dontSendNotification);
	//[/UserPreSize]

	setSize(624, 600);


	//[Constructor] You can add your own custom stuff here..
	setAudioChannels(0, JECT_CHANNELS_NUM);
	startTimerHz(JECT_FPS);
	//[/Constructor]
}

MainContentComponent::~MainContentComponent()
{
	//[Destructor_pre]. You can add your own custom destruction code here..
	inputFileListComponent->removeChangeListener(this);
	//[/Destructor_pre]

	waveformGroupBox = nullptr;
	waveformComponent = nullptr;
	inputGroupBox = nullptr;
	convGroupBox = nullptr;
	qSlider = nullptr;
	qLabel = nullptr;
	convButton = nullptr;
	authorLabel = nullptr;
	settingsButton = nullptr;
	gainSlider = nullptr;
	gainLabel = nullptr;
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
	inputRemoveButton = nullptr;
	inputAddButton = nullptr;
	inputFileListComponent = nullptr;


	//[Destructor]. You can add your own custom destruction code here..
	shutdownAudio();
	//[/Destructor]
}

//==============================================================================
void MainContentComponent::paint(Graphics& g)
{
	//[UserPrePaint] Add your own custom painting code here..
	//[/UserPrePaint]

	g.fillAll(Colours::white);

	//[UserPaint] Add your own custom painting code here..
	//[/UserPaint]
}

void MainContentComponent::resized()
{
	//[UserPreResize] Add your own custom resize code here..
	//[/UserPreResize]

	waveformGroupBox->setBounds(8, 242, 608, 214);
	waveformComponent->setBounds(24, 264, 576, 152);
	inputGroupBox->setBounds(8, 8, 608, 224);
	convGroupBox->setBounds(8, 464, 608, 128);
	qSlider->setBounds(120, 520, 248, 24);
	qLabel->setBounds(24, 520, 24, 24);
	convButton->setBounds(384, 488, 216, 56);
	authorLabel->setBounds(424, 552, 136, 24);
	settingsButton->setBounds(480, 424, 120, 24);
	gainSlider->setBounds(120, 424, 344, 24);
	gainLabel->setBounds(24, 424, 88, 24);
	prBehaviorLabel->setBounds(256, 32, 88, 24);
	prBehaviorComboBox->setBounds(352, 32, 248, 24);
	playButton->setBounds(400, 272, 56, 24);
	loopButton->setBounds(528, 272, 56, 24);
	stopButton->setBounds(464, 272, 56, 24);
	qDefaultButton->setBounds(56, 520, 56, 24);
	sSlider->setBounds(120, 552, 248, 24);
	sDefaultButton->setBounds(56, 552, 56, 24);
	nfftSlider->setBounds(120, 488, 248, 24);
	nfftLabel->setBounds(24, 488, 88, 24);
	saveButton->setBounds(528, 376, 56, 24);
	sLabel->setBounds(24, 552, 24, 24);
	inputRemoveButton->setBounds(128, 32, 88, 24);
	inputAddButton->setBounds(24, 32, 88, 24);
	inputFileListComponent->setBounds(24, 64, 576, 152);
	//[UserResized] Add your own custom resize handling here..
	//[/UserResized]
}

void MainContentComponent::sliderValueChanged(Slider* sliderThatWasMoved)
{
	//[UsersliderValueChanged_Pre]
	//[/UsersliderValueChanged_Pre]

	if (sliderThatWasMoved == qSlider)
	{
		//[UserSliderCode_qSlider] -- add your slider handling code here..
		const ScopedLock pl(paramLock);
		qParam = static_cast<float>(qSlider->getValue());
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
		//[/UserSliderCode_sSlider]
	}
	else if (sliderThatWasMoved == nfftSlider)
	{
		//[UserSliderCode_nfftSlider] -- add your slider handling code here..
		const ScopedLock pl(paramLock);
		nfftParam = static_cast<int>(nfftSlider->getValue());
		//[/UserSliderCode_nfftSlider]
	}

	//[UsersliderValueChanged_Post]
	//[/UsersliderValueChanged_Post]
}

void MainContentComponent::buttonClicked(Button* buttonThatWasClicked)
{
	//[UserbuttonClicked_Pre]
	//[/UserbuttonClicked_Pre]

	if (buttonThatWasClicked == convButton)
	{
		//[UserButtonCode_convButton] -- add your button handler code here..
		const ScopedLock fl(soundListLock);

		setPlayheadUiEnabled(false);

		bool convValid = true;

		int pow2 = static_cast<int>(nfftSlider->getValue());
		int fftInputLen = static_cast<int>(pow(2.0, pow2));
		int fftOutputLen = fftInputLen / 2 + 1;
		int numChannels = 1;

		unordered_set<int> includedSounds;
		int maxChannels = 0;
		for (const auto& iter : idToSound) {
			int id = iter.first;
			Sound* sound = iter.second.get();
			int numChannels = sound->getBufferNumChannels();
			if (sound->isIncluded() && numChannels > 0) {
				maxChannels = numChannels > maxChannels ? numChannels : maxChannels;
				includedSounds.emplace(id);
			}
		}

		if (maxChannels == 0) {
			return;
		}

		kiss_fftr_state* fftInverseState = kiss_fftr_alloc(fftInputLen, 1, nullptr, nullptr);
		kiss_fft_cpx* CONV = static_cast<kiss_fft_cpx*>(calloc(fftOutputLen * maxChannels, sizeof(kiss_fft_cpx)));
		conv.setSize(maxChannels, fftInputLen);

		float n = static_cast<float>(includedSounds.size());
		float q;
		float s;
		{
			const ScopedLock pl(paramLock);
			q = qParam;
			s = sParam;
		}

		float max = -1.0f;

		for (int convChannel = 0; convChannel < maxChannels; ++convChannel) {
			kiss_fft_cpx* CONVCHANNEL = CONV + (convChannel * fftOutputLen);

			for (const auto& id : includedSounds) {
				Sound* sound = idToSound[id].get();
				jassert(sound != nullptr);
				float p = static_cast<float>(sound->getPValue());
				float r = static_cast<float>(sound->getRValue());
				int soundNumChannels = sound->getBufferNumChannels();
				int soundChannel = convChannel >= soundNumChannels ? soundNumChannels - 1 : convChannel;
				kiss_fft_cpx* SOUNDCHANNEL = sound->getSpectra(fftInputLen, soundChannel);

				for (int i = 0; i < fftOutputLen; ++i) {
					float xr = SOUNDCHANNEL[i].r;
					float xi = SOUNDCHANNEL[i].i;
					float xMag = sqrtf((xr * xr) + (xi * xi));
					float xPhs = atan2f(xi, xr);
					float convMag = powf(xMag, p);
					float convPhs = r * xPhs;
					float convr = convMag * cosf(convPhs);
					float convi = convMag * sinf(convPhs);

					if (std::isnan(convr) || std::isnan(convi)) {
						convValid = false;
					}

					CONVCHANNEL[i].r += convr;
					CONVCHANNEL[i].i += convi;
				}
			}

			// convolve
			for (int i = 0; i < fftOutputLen; ++i) {
				float cr = CONVCHANNEL[i].r;
				float ci = CONVCHANNEL[i].i;
				float cMag = sqrtf((cr * cr) + (ci * ci));
				float cPhs = atan2f(ci, cr);
				float convMag = powf(cMag, n * q);
				float convPhs = n * s * cPhs;
				float convr = convMag * cosf(convPhs);
				float convi = convMag * sinf(convPhs);

				if (std::isnan(convr) || std::isnan(convi)) {
					convValid = false;
				}

				CONVCHANNEL[i].r = convr;
				CONVCHANNEL[i].i = convi;
			}

			// ifft
			//kiss_fftri(fftInverseState.get(), CONVCHANNEL, conv.getWritePointer(channel));
			kiss_fftri(fftInverseState, CONVCHANNEL, conv.getWritePointer(convChannel));

			// check max
			float channelMax = conv.findMinMax(convChannel, 0, fftInputLen).getEnd();
			max = channelMax > max ? channelMax : max;
		}

		delete fftInverseState;
		delete CONV;

		// normalize
		conv.applyGain(1.0f / max);

		if (!convValid) {
			AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Error", "Parameters produced NaN value.");
			return;
		}

		setPlayheadAudio(&conv);
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
		const ScopedLock fl(soundListLock);
		SparseSet<int> selectedRows = inputFileListComponent->getSelectedRows();
		for (int i = 0; i < selectedRows.size(); ++i) {
			int row = selectedRows[i];
			int id = inputFileListComponent->getIdForRow(row);
			const auto& iter = idToSound.find(id);
			jassert(iter != idToSound.end());
			idToSound.erase(iter);
		}
		if (selectedRows.size() > 0) {
			inputFilesChanged(dontSendNotification);
		}
		//[/UserButtonCode_inputRemoveButton]
	}
	else if (buttonThatWasClicked == inputAddButton)
	{
		//[UserButtonCode_inputAddButton] -- add your button handler code here..
		const ScopedLock fl(soundListLock);
		FileChooser fileChooser("Add sound...", File::nonexistent, "*.wav;*.aif;*.aiff;*.ogg", true);
		if (fileChooser.browseForMultipleFilesToOpen()) {
			Array<File> files = fileChooser.getResults();
			StringArray filePaths;
			for (int i = 0; i < files.size(); ++i) {
				filePaths.add(files[i].getFullPathName());
			}
			filesDropped(filePaths, -1, -1);
		}
		//[/UserButtonCode_inputAddButton]
	}

	//[UserbuttonClicked_Post]
	//[/UserbuttonClicked_Post]
}

void MainContentComponent::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
	//[UsercomboBoxChanged_Pre]
	//[/UsercomboBoxChanged_Pre]

	if (comboBoxThatHasChanged == prBehaviorComboBox)
	{
		//[UserComboBoxCode_prBehaviorComboBox] -- add your combo box handling code here..
		inputFileListComponent->setPrBehavior(static_cast<InputFileTableListBox::PrBehavior>(prBehaviorComboBox->getSelectedId()));
		//[/UserComboBoxCode_prBehaviorComboBox]
	}

	//[UsercomboBoxChanged_Post]
	//[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainContentComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {}

void MainContentComponent::releaseResources() {}

void MainContentComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
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

	int succeeded = 0;
	for (int i = 0; i < filePaths.size(); ++i) {
		String filePath = filePaths[i];
		unique_ptr<Sound> sound(new Sound(filePath));
		if (Sound::readBufferFromAudioFile(filePath, sound->getBufferPtr())) {
			const ScopedLock fl(soundListLock);
			int soundId = soundIdNext++;
			idToSound.emplace(soundId, std::move(sound));
			++succeeded;
		}
	}

	if (succeeded > 0) {
		inputFilesChanged(dontSendNotification);
	}
	if (succeeded < filePaths.size()) {
		AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Invalid file(s)", "One or more files failed to load.");
	}
}

void MainContentComponent::changeListenerCallback(ChangeBroadcaster* source) {
	if (source == inputFileListComponent) {
		const ScopedLock fl(soundListLock);
		updateNfftSlider(dontSendNotification);

		int previewId = inputFileListComponent->getPreviewId();
		if (previewId != -1) {
			const auto& iter = idToSound.find(previewId);
			jassert(iter != idToSound.end());
			setPlayheadAudio(iter->second->getBufferPtr());
		}
	}
}

void MainContentComponent::timerCallback() {
	const ScopedLock pal(playheadAudioLock);

	waveformComponent->setPlayhead(playheadAudioSamplesCompleted);
	waveformComponent->repaint();
}

void MainContentComponent::setPlayheadUiEnabled(bool playheadUiEnabled) {
	playButton->setEnabled(playheadUiEnabled);
	loopButton->setEnabled(playheadUiEnabled);
	stopButton->setEnabled(playheadUiEnabled);
	saveButton->setEnabled(playheadUiEnabled);
}

void MainContentComponent::setPlayheadAudio(AudioBuffer<float>* playheadAudioNew) {
	const ScopedLock pal(playheadAudioLock);

	if (playheadAudioNew != nullptr && (playheadAudioNew->getNumChannels() == 0 || playheadAudioNew->getNumSamples() == 0)) {
		playheadAudioNew == nullptr;
	}

	// update playhead audio
	if (playheadAudioNew == nullptr) {
		playheadAudio.setSize(0, 0);
		setPlayheadUiEnabled(false);
	}
	else {
		if (playheadAudioNew->getNumSamples() != playheadAudio.getNumSamples()) {
			playheadState = PlayheadState::stopped;
			playheadAudioSamplesCompleted = 0;
		}
		playheadAudio.makeCopyOf(*playheadAudioNew);
		setPlayheadUiEnabled(true);
	}

	waveformComponent->repaint();
}

void MainContentComponent::setUiFromParams(NotificationType notificationType) {
	gainSlider->setValue(static_cast<double>(gainParam.get()), notificationType);
	qSlider->setValue(static_cast<double>(qParam), notificationType);
	sSlider->setValue(static_cast<double>(sParam), notificationType);
	prBehaviorComboBox->setSelectedId(static_cast<int>(inputFileListComponent->getPrBehavior()), notificationType);
}

void MainContentComponent::inputFilesChanged(NotificationType notificationType) {
	unordered_map<int, Sound*> idToSoundTable;
	for (const auto& i : idToSound) {
		idToSoundTable.emplace(i.first, i.second.get());
	}

	inputFileListComponent->setIdToSound(idToSoundTable);
	inputFileListComponent->updateContent();

	updateNfftSlider(notificationType);
}


void MainContentComponent::updateNfftSlider(NotificationType notificationType) {
	int maxSamplesNum = 0;
	int totalSamplesNum = 0;
	for (const auto& i : idToSound) {
		if (!i.second->isIncluded()) {
			continue;
		}

		const AudioBuffer<float>* buffer = i.second->getBufferPtr();
		jassert(buffer != nullptr);
		int bufferNumSamples = buffer->getNumSamples();
		maxSamplesNum = bufferNumSamples > maxSamplesNum ? bufferNumSamples : maxSamplesNum;
		totalSamplesNum += bufferNumSamples;
	}

	if (totalSamplesNum > 0) {
		int max2 = static_cast<int>(std::ceil(std::log2(maxSamplesNum)));
		int total2 = static_cast<int>(std::ceil(std::log2(totalSamplesNum - (idToSound.size() - 1))));
		nfftSlider->setRange(static_cast<double>(max2), 28, 1.0);
		nfftSlider->setValue(static_cast<double>(total2), notificationType);
		nfftSlider->setEnabled(true);
		convButton->setEnabled(true);
	}
	else {
		nfftSlider->setEnabled(false);
		convButton->setEnabled(false);
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
				 constructorParams="" variableInitialisers="gainParam(0.5),&#10;nfftParam(0),&#10;qParam(1.0),&#10;sParam(1.0),&#10;conv(0, 0),&#10;playheadAudioLock(),&#10;playheadState(PlayheadState::stopped),&#10;playheadAudio(0, 0),&#10;playheadAudioSamplesCompleted(0),&#10;soundIdNext(0)"
				 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
				 fixedSize="1" initialWidth="624" initialHeight="600">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="" id="7c21d6435b394a3c" memberName="waveformGroupBox" virtualName=""
				  explicitFocusOrder="0" pos="8 242 608 214" title="Waveform"/>
  <GENERICCOMPONENT name="" id="5da17034a15a2c26" memberName="waveformComponent"
					virtualName="" explicitFocusOrder="0" pos="24 264 576 152" class="WaveformComponent"
					params="&quot;No waveform to display&quot;"/>
  <GROUPCOMPONENT name="" id="5b5e49932e4cad01" memberName="inputGroupBox" virtualName=""
				  explicitFocusOrder="0" pos="8 8 608 224" title="Input"/>
  <GROUPCOMPONENT name="" id="251b2a29053ccce1" memberName="convGroupBox" virtualName=""
				  explicitFocusOrder="0" pos="8 464 608 128" title="Convolution"/>
  <SLIDER name="" id="5d8042d5cba6f5af" memberName="qSlider" virtualName=""
		  explicitFocusOrder="0" pos="120 520 248 24" min="0" max="8" int="0.010000000000000000208"
		  style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
		  textBoxWidth="40" textBoxHeight="20" skewFactor="0.4000000000000000222"
		  needsCallback="1"/>
  <LABEL name="" id="8c32c3818b630f5" memberName="qLabel" virtualName=""
		 explicitFocusOrder="0" pos="24 520 24 24" edTextCol="ff000000"
		 edBkgCol="0" labelText="Q" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="15"
		 bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="1b9a996260e602ac" memberName="convButton" virtualName=""
			  explicitFocusOrder="0" pos="384 488 216 56" buttonText="Convolve"
			  connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="45a3ca5fc03eb3c6" memberName="authorLabel" virtualName=""
		 explicitFocusOrder="0" pos="424 552 136 24" edTextCol="ff000000"
		 edBkgCol="0" labelText="Chris Donahue 2016" editableSingleClick="0"
		 editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
		 fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="8a40cfbb6678ded1" memberName="settingsButton" virtualName=""
			  explicitFocusOrder="0" pos="480 424 120 24" buttonText="Audio Settings"
			  connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="4e9f7543cb949220" memberName="gainSlider" virtualName=""
		  explicitFocusOrder="0" pos="120 424 344 24" min="0" max="1" int="0.010000000000000000208"
		  style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
		  textBoxWidth="40" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="" id="617675cab679ff64" memberName="gainLabel" virtualName=""
		 explicitFocusOrder="0" pos="24 424 88 24" edTextCol="ff000000"
		 edBkgCol="0" labelText="Gain" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="15"
		 bold="0" italic="0" justification="33"/>
  <LABEL name="" id="df0c2bbfcc27d23b" memberName="prBehaviorLabel" virtualName=""
		 explicitFocusOrder="0" pos="256 32 88 24" edTextCol="ff000000"
		 edBkgCol="0" labelText="P/R Behavior" editableSingleClick="0"
		 editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
		 fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="" id="e3ce100f165f7ce9" memberName="prBehaviorComboBox"
			virtualName="" explicitFocusOrder="0" pos="352 32 248 24" editable="0"
			layout="33" items="Independent&#10;Linked&#10;Inverse" textWhenNonSelected=""
			textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="" id="ae50f5bf4f928bae" memberName="playButton" virtualName=""
			  explicitFocusOrder="0" pos="400 272 56 24" buttonText="Play"
			  connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="bc50acff95e14f9c" memberName="loopButton" virtualName=""
			  explicitFocusOrder="0" pos="528 272 56 24" buttonText="Loop"
			  connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="ee7f76320bc5ba72" memberName="stopButton" virtualName=""
			  explicitFocusOrder="0" pos="464 272 56 24" buttonText="Stop"
			  connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="458e93826aa283d" memberName="qDefaultButton" virtualName=""
			  explicitFocusOrder="0" pos="56 520 56 24" buttonText="Default"
			  connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="234c4909ac1ef82e" memberName="sSlider" virtualName=""
		  explicitFocusOrder="0" pos="120 552 248 24" min="0" max="15"
		  int="0.010000000000000000208" style="LinearHorizontal" textBoxPos="TextBoxLeft"
		  textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"
		  needsCallback="1"/>
  <TEXTBUTTON name="" id="6b491d9785461117" memberName="sDefaultButton" virtualName=""
			  explicitFocusOrder="0" pos="56 552 56 24" buttonText="Default"
			  connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="2ccccb8c8ed630bf" memberName="nfftSlider" virtualName=""
		  explicitFocusOrder="0" pos="120 488 248 24" min="0" max="24"
		  int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
		  textBoxWidth="40" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="" id="9b09e8ab97220128" memberName="nfftLabel" virtualName=""
		 explicitFocusOrder="0" pos="24 488 88 24" edTextCol="ff000000"
		 edBkgCol="0" labelText="NFFT" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="15"
		 bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="5349946cfc445d79" memberName="saveButton" virtualName=""
			  explicitFocusOrder="0" pos="528 376 56 24" buttonText="Save"
			  connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="676135372bd3b95b" memberName="sLabel" virtualName=""
		 explicitFocusOrder="0" pos="24 552 24 24" edTextCol="ff000000"
		 edBkgCol="0" labelText="S" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="15"
		 bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="ce8360a29a7e1323" memberName="inputRemoveButton"
			  virtualName="" explicitFocusOrder="0" pos="128 32 88 24" buttonText="Remove"
			  connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="dcb4b995c383b4ef" memberName="inputAddButton" virtualName=""
			  explicitFocusOrder="0" pos="24 32 88 24" buttonText="Add" connectedEdges="0"
			  needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="7617b55e4d758efa" memberName="inputFileListComponent"
					virtualName="" explicitFocusOrder="0" pos="24 64 576 152" class="InputFileTableListBox"
					params="InputFileTableListBox::PrBehavior::independent"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
