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

/*
	Applies bandpass filter to input signal S.
		S is in the fourier domain and is of size M (when considering both real and imaginary parts.
		S is partitioned in the frequency domain appropriately.
	Anything outside of this pass-band is zeroed out for both positive and negative frequencies.
	
	@pass_start and @pass_stop are non-negative frequencies in Hertz.
*/
void fourier_bpf(float * S, float pass_start, float pass_stop)
{
	/* TODO: implement when we have determined how sp_FFT function partitions the signal S, so that we know where particular 
	frequencies are located in this fourier domain signal. Consider both negative and positive frequencies, and imaginary parts.
	Should use windowing such as a raised cosine, otherwise will get ringing in the time domain.
	*/
}

void fourier_lpf(float *S, float cutoff)
{
	fourier_bpf(S, 0, cutoff);
}

void apply_hpf(float *S, float cutoff)
{
	fourier_bpf(S,cutoff,FFT_FREQ_MAX);
}



#endif /* SIGNAL_PROCESSING_H */

