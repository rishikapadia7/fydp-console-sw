#ifndef MIC_INPUT_H
#define MIC_INPUT_H

#include "common.h"

typedef uint16_t rawmic_t;

/* Obtains raw mic sample as unsigned integer for the mentioned channel */
rawmic_t get_rawmic_data(audio_channel_t ch)
{
	if(ch == LEFT)
	{
		return 0; /* TODO: replace with actual data */
	}
	else
	{
		return 1; /* TODO: replace with actual data */
	}
}

float convert_rawmic_to_float(rawmic_t data)
{
	/* TODO (maybe): there may be some scaling required for it to be valid FFT input
		http://stackoverflow.com/questions/15087668/how-to-convert-pcm-samples-in-byte-array-as-floating-point-numbers-in-the-range
		This mentions after the cast, divide by uint32_t MAX , and then when about to create speaker output should multiply back.
		However, this may not be necessary as the type-casting could be sufficient for our purposes.
			http://stackoverflow.com/questions/6281206/type-coercion-in-c-unsigned-int-to-float
	*/
	return (float) data;
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
