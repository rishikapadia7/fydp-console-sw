#ifndef SIGNAL_PROCESSING_H
#define SIGNAL_PROCESSING_H

#include "common.h"
#include "dsplib674x.h"

/* Prepend newest data and discards oldest data from the end of the array */
void add_new_mic_data(float mic_data_float[AUDIO_CHANNEL_COUNT])
{
	unsigned int ch;
	for(ch = 0; ch < AUDIO_CHANNEL_COUNT; ch++)
	{
		/* We shift by 2 since both real and imag. */
		DSPF_sp_blk_move(audio_data[ch].x,audio_data[ch].x + 2, M - 2);
		/* Place new data at front of array */
		audio_data[ch].x[0] = mic_data_float[ch];
	}
}


#endif /* SIGNAL_PROCESSING_H */

