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
		nfft(-1),
		spectra(nullptr) {
		File file(filePath);
		name = file.getFileName();
	};

	Sound() : Sound(String::empty) {};

	AudioBuffer<float>* getBufferPtr() {
		return &buffer;
	};

	int getBufferNumChannels() const {
		return buffer.getNumChannels();
	};

	int getBufferNumSamples() const {
		return buffer.getNumSamples();
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

	void setInclude(bool includeNew) {
		include = includeNew;
	};

	double getPValue() const {
		return pValue;
	};

	void setPValue(double pValueNew) {
		pValue = pValueNew;
	};

	double getRValue() const {
		return rValue;
	};

	void setRValue(double rValueNew) {
		rValue = rValueNew;
	};

	kiss_fft_cpx* getSpectra(int nfftNew, int channel) {
		int numSamples = buffer.getNumSamples();

		if (nfftNew != nfft) {
			jassert(nfftNew > buffer.getNumSamples());

			int fftInputLen = nfftNew;
			int fftOutputLen = fftInputLen / 2 + 1;
			int numChannels = buffer.getNumChannels();

			std::unique_ptr<kiss_fftr_state> fftState(kiss_fftr_alloc(nfftNew, 0, nullptr, nullptr));
			std::unique_ptr<float> fftInput(static_cast<float*>(malloc(sizeof(float) * fftInputLen)));
			spectra.reset(static_cast<kiss_fft_cpx*>(malloc(sizeof(kiss_fft_cpx) * fftOutputLen * numChannels)));

			for (int c = 0; c < numChannels; ++c) {
				float* bufferRaw = buffer.getWritePointer(c);
				memcpy(fftInput.get(), bufferRaw, sizeof(float) * numSamples);
				kiss_fftr(fftState.get(), fftInput.get(), spectra.get() + (c * numSamples));
			}

			nfft = nfftNew;
		}

		return spectra.get() + (channel * numSamples);
	};

private:
	AudioBuffer<float> buffer;
	String filePath;
	String name;
	bool include;
	double pValue;
	double rValue;
	int nfft;
	std::unique_ptr<kiss_fft_cpx> spectra;
};

#endif  // SOUND_H_INCLUDED
