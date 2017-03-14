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

#define RAWMIC_UPPER_BOUND (0.8f) /* This is the max value a mic reading can take in float representation.  Note: this reading may be amplified, so it is worthwhile keeping it between 0.7 and 1.0 at most */
#define RAWMIC_SCALE_DOWN (RAWMIC_MAX_VAL / RAWMIC_UPPER_BOUND) /*Gives resulting float range between 0 and RAWMIC_UPPER_BOUND */


float convert_rawmic_to_float(rawmic_t data)
{
	/* scaling required for it to be valid FFT input
		http://stackoverflow.com/questions/15087668/how-to-convert-pcm-samples-in-byte-array-as-floating-point-numbers-in-the-range
		This mentions after the cast, divide by uint32_t MAX , and then when about to create speaker output should multiply back.
		Also verified matlab audioread function uses similar strategy, our MATLAB simulation used floats in the range of -1 to 1 (not integer).
	*/
	float f;
	/*NOTE: in HW we may find that we are over-dividing here and may want to divide by something like RAWMIC_MAX_VAL/2 */
	f = ((float) data) /((float) RAWMIC_SCALE_DOWN); /* yields f in the range of 0 and RAWMIC_UPPER_BOUND * /

	/* We make the signal zero-centered so that there can be negative numbers as well*/
	f = f - RAWMIC_UPPER_BOUND / 2;

	/*f is a value between -RAWMIC_UPPER_BOUND/2 and +RAWMIC_UPPER_BOUND/2 */
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
