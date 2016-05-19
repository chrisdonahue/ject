/*
  ==============================================================================

    Sound.h
    Created: 11 May 2016 4:03:29pm
    Author:  Chris

  ==============================================================================
*/

#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <memory>

#include "../JuceLibraryCode/JuceHeader.h"
#include "Libraries/kiss_fft130/kiss_fftr.h"

class Sound {
public:
	static bool readBufferFromAudioFile(String filePath, AudioBuffer<float>* samples) {
		AudioFormatManager formatManager;
		formatManager.registerFormat(new WavAudioFormat(), true);
		formatManager.registerFormat(new AiffAudioFormat(), false);
		formatManager.registerFormat(new OggVorbisAudioFormat(), false);
		ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(File(filePath));

		if (reader != nullptr && reader->numChannels > 0 && reader->numChannels <= JECT_CHANNELS_NUM && reader->lengthInSamples > 0) {
			samples->setSize(reader->numChannels, reader->lengthInSamples);
			reader->read(samples, 0, static_cast<int>(reader->lengthInSamples), 0, reader->numChannels == 1, reader->numChannels == 2);
			return true;
		}

		return false;
	};

	Sound(String filePath) :
		buffer(buffer),
		filePath(filePath),
		include(true),
		pValue(1.0),
		rValue(1.0),
		spectra(nullptr) {
		File file(filePath);
		name = file.getFileName();
	};

	Sound() : Sound(String::empty) {};

	AudioBuffer<float>* getBufferPtr() {
		return &buffer;
	};

	String getFilePath() const {
		return filePath;
	};
	
	String getName() const {
		return name;
	};

	bool isIncluded() const {
		return include;
	};

	double getPValue() const {
		return pValue;
	};

	double getRValue() const {
		return rValue;
	};

	kiss_fft_cpx* getSpectra(int nfft) {
		return spectra.get();
	};

private:
	AudioBuffer<float> buffer;
	String filePath;
	String name;
	bool include;
	double pValue;
	double rValue;
	std::unique_ptr<kiss_fft_cpx> spectra;
};

#endif  // SOUND_H_INCLUDED
