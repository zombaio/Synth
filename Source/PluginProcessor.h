/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Synth.h"
#include "SynthSound.h"
#include "RingBuffer.h"
#include <string>
#include <math.h>


//==============================================================================
/**
*/
class SynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SynthAudioProcessor();
    ~SynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

	int getNumParameters() override;
	float getParameter(int index) override;
	void setParameter(int index, float newValue) override;

	const String getParameterName(int index) override;
	const String getParameterText(int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//Custom Methods, Params and Public Data
	enum Parameters {
		MasterBypass = 0,
		waveFormParam = 1,
		attackParam = 2,
		delayLengthParam = 3,
		dryMixParam = 4,
		wetMixParam = 5,
		decayParam = 6,
		sustainParam = 7,
		releaseParam = 8,
		totalNumParam
	};

	// Console:
	void log(std::string text);
	bool consoleChanged;
	std::string consoleText;

	// WaveForm:
	int waveForm;

	// Envelope:
	int attackMS;
	int decayMS;
	float sustainLevel;
	int releaseMS;
	float gain;

	// Delay:
	int delayLengthMS;
	float dryMix;
	float wetMix;
	float feedback;
	RingBuffer ringBuffer;

private:
    //==============================================================================
	
	//Private Data, helper methods etc.
	float UserParams[totalNumParam];
	bool UIUpdateFlag;

	// Waveform:
	Synth synth;

	int numberOfVoices;

	// Envelope:
	template <typename FloatType>
	void attack(float& currentGain, AudioBuffer<FloatType>& buffer);
	template <typename FloatType>
	void decay(float& currentGain, AudioBuffer<FloatType>& buffer);
	template <typename FloatType>
	void sustain(float& currentGain, AudioBuffer<FloatType>& buffer);
	template <typename FloatType>
	void release(float& currentGain, AudioBuffer<FloatType>& buffer);

	// Delay:
	AudioSampleBuffer delayBuffer;
	int delayBufferLength;
	int delayReadPosition;
	int delayWritePosition;
	template <typename FloatType>
	void delay(AudioBuffer<FloatType>& buffer);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
