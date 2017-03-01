#ifndef COMMON_H
#define COMMON_H

/* This file contains all general includes and type declarations, as well as global configuraiton data */
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdbool.h"
#include "stdint.h"

/* Global Constants */
#define FFT_SIZE 128 /* this is positive and neg freq combined, number of bins */

typedef enum audio_channel {
	LEFT = 0,
	RIGHT,
	AUDIO_CHANNEL_COUNT
} audio_channel_t;





/*** Data structures that are used by FFT and iFFT ***/

#define MAXN (FFT_SIZE)
/* M is double FFT_SIZE to account for real-part and imaginary part of complex number */
#define M    (2*MAXN)
/* PAD is used for data alignment reasons - as data alignment is 8 (which is double word alignment), 
so we want give 16 32-bit floats for the compiler to play around with */
#define PAD  (16)


#ifdef _TMS320C6X
#pragma DATA_ALIGN(audio_data[LEFT].x_padded, 8);
#pragma DATA_ALIGN(audio_data[LEFT].X_padded, 8);
#pragma DATA_ALIGN(audio_data[LEFT].Y_padded, 8);
#pragma DATA_ALIGN(audio_data[LEFT].y_padded, 8);
#pragma DATA_ALIGN(audio_data[RIGHT].x_padded, 8);
#pragma DATA_ALIGN(audio_data[RIGHT].X_padded, 8);
#pragma DATA_ALIGN(audio_data[RIGHT].Y_padded, 8);
#pragma DATA_ALIGN(audio_data[RIGHT].y_padded, 8);
#endif /* _TMS320C6X */

typedef struct audio_data_structures
{
	/* Do not access _padded structures directly from application code.
		Use the convenience ptrs below them.
	*/
	float x_padded[M + 2 * PAD]; /* input to fft */
	float X_padded[M + 2 * PAD]; /* The fft of x */
	float Y_padded[M + 2 * PAD]; /* Input into ifft */
	float y_padded[M + 2 * PAD]; /* Output of ifft */
	
	/* Below fields are initialized on the first fft call. */
	float * x; /* = x_padded + PAD */
	float * X; /* = X_padded + PAD */
	float * Y; /* = Y_padded + PAD */
	float * y; /* = y_padded + PAD */
} audio_data_t;

audio_data_t audio_data[AUDIO_CHANNEL_COUNT];


#endif /*COMMON_H*/
