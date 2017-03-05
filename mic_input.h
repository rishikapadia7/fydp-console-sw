#ifndef MIC_INPUT_H
#define MIC_INPUT_H

#include "common.h"
#include "mock.h"


/* Obtains raw mic sample as unsigned integer for the mentioned channel */
rawmic_t get_rawmic_data(audio_channel_t ch)
{
	/* MOCK: replace with actual data coming from mic*/
	return	mock_get_mic_input(ch);
}

float convert_rawmic_to_float(rawmic_t data)
{
	/* scaling required for it to be valid FFT input
		http://stackoverflow.com/questions/15087668/how-to-convert-pcm-samples-in-byte-array-as-floating-point-numbers-in-the-range
		This mentions after the cast, divide by uint32_t MAX , and then when about to create speaker output should multiply back.
		Also verified matlab audioread function uses similar strategy, our MATLAB simulation used floats in the range of -1 to 1 (not integer).
	*/
	float f;
	f = ((float) data) /((float) RAWMIC_MAX_VAL); /* yields f in the range of 0 and 1, centered at 0.5 * /

	/* We subtract 0.5 to make it zero-centered as opposed to 0.5-centered */
	f = f - 0.5f;

	return f;
}


void get_mic_data_float(float mic_data_float[AUDIO_CHANNEL_COUNT])
{
	unsigned int i;
	rawmic_t rawdata;
	for(i = 0; i < AUDIO_CHANNEL_COUNT; i++)
	{
		rawdata = get_rawmic_data((audio_channel_t)i);
		mic_data_float[i] = convert_rawmic_to_float(rawdata);
	}
}




#endif /* MIC_INPUT_H */
