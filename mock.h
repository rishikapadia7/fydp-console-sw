#ifndef MOCK_DATA_H
#define MOCK_DATA_H

/* NOTE: this file is for simulation use only.  Not used on the board. */


#include "common.h"




/* Returns the raw mic data type (usually unsigned) at arbitrary.
	Future: can use this function to read a .wav file if desired or a .txt file instead.
*/
rawmic_t mock_get_mic_input(audio_channel_t ch)
{
	double val;
	static unsigned int i = 0;

	if(ch){
		val = sin (2 * 3.1415 *  50 * i / (double) FFT_SIZE) + 1;
	}
	else
	{
		val = cos (2 * 3.1415 *  50 * i / (double) FFT_SIZE) + 1;
	}
	i++;

	return (rawmic_t)(val * RAWMIC_MAX_VAL);
}



#endif /* MOCK_DATA_H */
