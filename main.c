/* 
    fydp-console-sw 
    ANSI C89 / ISO C90 programming standard.
	// style comments are not allowed!
*/

#include "common.h"
#include "dsplib674x.h"
#include "mode_of_operation.h"
#include "mic_input.h"
#include "speaker_output.h"
#include "fft_wrap.h"
#include "signal_processing.h"

#ifndef _TMS320C6X
#include "matlab_helper.h"
#endif

#define MATLAB_DEBUG_ENABLED 0

unsigned int iteration_count = 0;
#define NUM_SIMULATION_CYCLES 400


void run_calibration()
{
    /*TODO: populate calibration data structures.
	NOTE: if using hardcoded data, then this function returns immediately.
	*/
}

void run_main_algorithm()
{
	float mic_data_float[AUDIO_CHANNEL_COUNT]; /* gets populated with newest mic samples as float */
	unsigned int ch;

	/*Get mic input */
    /*	returns an array of floats, 1 float per mic
		this is assuming that reading McBSP buffered input takes minimal clock cycles, otherwise we may need to process mic one by one
	*/
	get_mic_data_float(mic_data_float);

	/*NORMAL_PRINT("run_main_algorithm audio_data[01].x[0] = %f, %f \n", audio_data[0].x[0], audio_data[1].x[0]);*/
	/* append to working signal to operate on (signal is allocated in common.h) */
	add_new_mic_data(mic_data_float);
	/*NORMAL_PRINT("run_main_algorithm mic_data_float = %f, %f \n", mic_data_float[0], mic_data_float[1]);*/
	
	/* TODO: perform hilbert transform to make analytical signal */

	
	for(ch = 0; ch < AUDIO_CHANNEL_COUNT; ch++)
	{
		fft_wrap(audio_data[ch].x,audio_data[ch].X);
		/* TODO: perform some signal processing here */

		DSPF_sp_blk_move(audio_data[ch].X, audio_data[ch].Y, M);
		ifft_wrap(audio_data[ch].Y,audio_data[ch].y);

		/*Write to speakers*/
		send_speaker_output(audio_data[ch].y);
	}

#if MATLAB_DEBUG_ENABLED
	if(iteration_count == 300)
	{
		printf("x signal:\n");
		matlab_float_print_complex(audio_data[0].x, M);
		printf("\n\n\n\n X signal: \n");
		matlab_float_print_complex(audio_data[0].X, M);
		printf("\n\n\n\n Y signal: \n");
		matlab_float_print_complex(audio_data[0].Y, M);
		printf("\n\n\n\n y signal: \n");
		matlab_float_print_complex(audio_data[0].y, M);

		

	}
#endif /* MATLAB_DEBUG_ENABLED */
	
	
    /*Perform signal processing
	- input signal windowing
	
	- magnitude adjustment
	- phase adjustment
		- feedback elimination (this will be part of magnitude and phase adjustment and may involve subtraction and not just multiplication)
		- voice obfuscation (same, but may involve addition and subtraction as well)
	- ifft (may or may not be able to use previous signal data to reduce computation - research)
	- inverse windowing (to counteract initial input windowing)
	*/
	


}

int main()
{

    /*Calibration switch must be enabled at power-on to calibrate
    switch does not have effect during normal mode of operation (likely accidental if switched)*/
    if(is_calibration_enabled()) 
    {
        run_calibration();
        /*TODO: perhaps have a pause here? */
    }

	fft_wrap_init();
	NORMAL_PRINT("Completed FFT init.\n");
    
	while(iteration_count < NUM_SIMULATION_CYCLES)
    {
        /*wait for algorithm to be enabled (controlled by board switch)
        user controls whether regular headphones listening mode, or antivoice mode */
        if(is_algorithm_enabled())
        {
            run_main_algorithm(); 
        }
        else
        {
            /*sleep to save power if possible / easy? */
        }
		/*NOTE: we may split up is_algorithm_enabled into voiceObfuscationEnabled and ancEnabled as they are 2 different modes of operation*/

		iteration_count++;
    }
    
    return 0;
}
