#ifndef FFT_WRAP_H
#define FFT_WRAP_H

#include "common.h"
#include "dsplib674x.h"

/*
	This file contains wrapper functions for FFT and iFFT for easily calling DSPLIB functions.
*/

/* These are defines from the sample code */
#define MAXN (FFT_SIZE)
/* M is double FFT_SIZE to account for real-part and imaginary part of complex number */
#define M    (2*MAXN)
/* PAD is used for data alignment reasons */
#define PAD  (16)

/* Contains the twiddle factors used by the FFT radix algorithm. */
float w[M + 2 * PAD];
/* ptr_w will skip beyond the array padding */
float *const ptr_w = w + PAD;

/* brev is used by this specific butterfly radix algorithm for value lookup */
unsigned char brev[64] = {
    0x0, 0x20, 0x10, 0x30, 0x8, 0x28, 0x18, 0x38,
    0x4, 0x24, 0x14, 0x34, 0xc, 0x2c, 0x1c, 0x3c,
    0x2, 0x22, 0x12, 0x32, 0xa, 0x2a, 0x1a, 0x3a,
    0x6, 0x26, 0x16, 0x36, 0xe, 0x2e, 0x1e, 0x3e,
    0x1, 0x21, 0x11, 0x31, 0x9, 0x29, 0x19, 0x39,
    0x5, 0x25, 0x15, 0x35, 0xd, 0x2d, 0x1d, 0x3d,
    0x3, 0x23, 0x13, 0x33, 0xb, 0x2b, 0x1b, 0x3b,
    0x7, 0x27, 0x17, 0x37, 0xf, 0x2f, 0x1f, 0x3f
};

bool_t twiddle_generated = false;
int rad = 2;


/* Function for generating Specialized sequence of twiddle factors */
void tw_gen (float *w, int n)
{
    int i, j, k;
    double x_t, y_t, theta1, theta2, theta3;
    const double PI = 3.141592654;

    for (j = 1, k = 0; j <= n >> 2; j = j << 2)
    {
        for (i = 0; i < n >> 2; i += j)
        {
            theta1 = 2 * PI * i / n;
            x_t = cos (theta1);
            y_t = sin (theta1);
            w[k] = (float) x_t;
            w[k + 1] = (float) y_t;

            theta2 = 4 * PI * i / n;
            x_t = cos (theta2);
            y_t = sin (theta2);
            w[k + 2] = (float) x_t;
            w[k + 3] = (float) y_t;

            theta3 = 6 * PI * i / n;
            x_t = cos (theta3);
            y_t = sin (theta3);
            w[k + 4] = (float) x_t;
            w[k + 5] = (float) y_t;
            k += 6;
        }
    }
}

void generate_twiddle(int N, float * ptr_w)
{
	/* ---------------------------------------------------------------- */
    /* Generate twiddle factors.                                        */
    /* ---------------------------------------------------------------- */
	int i, j;
    j = 0;
    for (i = 0; i <= 31; i++)
        if ((N & (1 << i)) == 0)
            j++;
        else
            break;

    if (j % 2 == 0)
        rad = 4;
    else
        rad = 2;

    tw_gen (ptr_w, N);
}

/*
	Args:
		ptr_x is input array
		ptr_w is array of twiddle factors used by algorithm
			NOTE: this memory address should never be cleared after initialized
			This is done so that twiddle factors are not computed over and over again
		ptr_y is output array

*/
void fft_wrap(float *ptr_x, float *ptr_w, float *ptr_y)
{
	int N = FFT_SIZE;
	if(!twiddle_generated)
	{
		tw_gen(ptr_w, N);
		twiddle_generated = true;
	}
	/* Not sure why they do &ptr_x[0] instead of just ptr_x. */
	DSPF_sp_fftSPxSP (N, &ptr_x[0], &ptr_w[0], ptr_y, brev, rad, 0, N);
}


/*
	Args:
		ptr_x contains frequency domain information.
		ptr_w is array of twiddle factors used by algorithm
		ptr_y is where the inverse will be placed in time domain.
*/

void ifft_wrap(int N, float *ptr_x, float * ptr_w, float *ptr_y)
{
	int N = FFT_SIZE;
	if(!twiddle_generated)
	{
		tw_gen(ptr_w, N);
		twiddle_generated = true;
	}
	
	/* Not sure why they do &ptr_x[0] instead of just ptr_x. */
	DSPF_sp_ifftSPxSP(N, &ptr_x[0], &ptr_w[0], ptr_y, brev, rad, 0, N);
}

#endif /* FFT_WRAP_H */