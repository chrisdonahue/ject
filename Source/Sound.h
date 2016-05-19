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
	static AudioBuffer<float>* readBufferFromAudioFile(String filePath) {
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

	Sound(AudioBuffer<float>* buffer, String filePath) :
		buffer(buffer),
		filePath(filePath),
		include(true),
		pValue(1.0),
		rValue(1.0),
		spectra(nullptr) {
		File file(filePath);
		name = file.getFileName();
	};

	Sound(AudioBuffer<float>* buffer) : Sound(buffer, String::empty) {};

	AudioBuffer<float>* getBuffer() const {
		return buffer.get();
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
	std::unique_ptr<AudioBuffer<float>> buffer;
	String filePath;
	String name;
	bool include;
	double pValue;
	double rValue;
	std::unique_ptr<kiss_fft_cpx> spectra;
};

#endif  // SOUND_H_INCLUDED
