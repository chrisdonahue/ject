/*
  ==============================================================================

    Sound.h
    Created: 11 May 2016 4:03:29pm
    Author:  Chris

  ==============================================================================
*/

#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#define JECT_CHANNELS_NUM 2

#include <memory>

#include "../JuceLibraryCode/JuceHeader.h"
#include "Libraries/kiss_fft130/kiss_fftr.h"

class Sound {
public:
	static bool readBufferFromAudioFile(AudioFormatManager* formatManager, String filePath, AudioBuffer<float>* samples) {
		ScopedPointer<AudioFormatReader> reader = formatManager->createReaderFor(File(filePath));

		if (reader != nullptr && reader->numChannels > 0 && reader->numChannels <= JECT_CHANNELS_NUM && reader->lengthInSamples > 0) {
			samples->setSize(reader->numChannels, reader->lengthInSamples);
			reader->read(samples, 0, static_cast<int>(reader->lengthInSamples), 0, reader->numChannels == 1, reader->numChannels == 2);
			return true;
		}

		return false;
	};

	Sound(String filePath) :
		buffer(0, 0),
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

	~Sound() {
		if (spectra != nullptr) {
			delete spectra;
		}
	}

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

	const kiss_fft_cpx* getSpectra(int nfftNew, int channel) {
		int fftInputLen = nfftNew;
		int fftOutputLen = fftInputLen / 2 + 1;

		if (nfftNew != nfft) {
			int numChannels = buffer.getNumChannels();
			int numSamples = buffer.getNumSamples();

			jassert(channel < numChannels);
			jassert(nfftNew >= numSamples);

			kiss_fftr_state* fftState = kiss_fftr_alloc(nfftNew, 0, nullptr, nullptr);
			float* fftInput = static_cast<float*>(malloc(sizeof(float) * fftInputLen));

			if (spectra != nullptr) {
				delete spectra;
			}
			spectra = static_cast<kiss_fft_cpx*>(malloc(sizeof(kiss_fft_cpx) * fftOutputLen * numChannels));

			for (int c = 0; c < numChannels; ++c) {
				const float* bufferRaw = buffer.getReadPointer(c);
				memcpy(fftInput, bufferRaw, sizeof(float) * numSamples);
				for (int s = numSamples; s < fftInputLen; ++s) {
					fftInput[s] = 0.0f;
				}
				kiss_fftr(fftState, fftInput, spectra + (c * fftOutputLen));
			}

			delete fftState;
			delete fftInput;

			nfft = nfftNew;
		}

		return spectra + (channel * fftOutputLen);
	};

private:
	AudioBuffer<float> buffer;
	String filePath;
	String name;
	bool include;
	double pValue;
	double rValue;
	int nfft;
	kiss_fft_cpx* spectra;
};

#endif  // SOUND_H_INCLUDED
