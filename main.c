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

#define NUM_SIMULATION_CYCLES 400

void runCalibration()
{
    /*TODO: populate calibration data structures.
	NOTE: if using hardcoded data, then this function returns immediately.
	*/
}

void runMainAlgorithm()
{
	float mic_data_float[AUDIO_CHANNEL_COUNT]; /* gets populated with newest mic samples as float */
	unsigned int ch;

	/*Get mic input */
    /*	returns an array of floats, 1 float per mic
		this is assuming that reading McBSP buffered input takes minimal clock cycles, otherwise we may need to process mic one by one
	*/
	get_mic_data_float(mic_data_float);

	NORMAL_PRINT("runMainAlgorithm audio_data[01].x[0] = %f, %f \n", audio_data[0].x[0], audio_data[1].x[0]);
	/* append to working signal to operate on (signal is allocated in common.h) */
	add_new_mic_data(mic_data_float);
	NORMAL_PRINT("runMainAlgorithm mic_data_float = %f, %f \n", mic_data_float[0], mic_data_float[1]);
	

	
	for(ch = 0; ch < AUDIO_CHANNEL_COUNT; ch++)
	{
		fft_wrap(audio_data[ch].x,audio_data[ch].X);
		/* TODO: perform some signal processing here */

		/* TODO: add benchmarking */

		DSPF_sp_blk_move(audio_data[ch].X, audio_data[ch].Y, M);
		ifft_wrap(audio_data[ch].Y,audio_data[ch].y);

	}
	
	/*NORMAL_PRINT("x value is %f and y value is %f\n", audio_data[0].x[0], audio_data[0].y[0]); */
	
	/* TODO: show that mic input and speaker out are roughly the same, and what is the error as a result of float - integer scaling */
	


    /*Perform signal processing
	- input signal windowing
	
	- magnitude adjustment
	- phase adjustment
		- feedback elimination (this will be part of magnitude and phase adjustment and may involve subtraction and not just multiplication)
		- voice obfuscation (same, but may involve addition and subtraction as well)
	- ifft (may or may not be able to use previous signal data to reduce computation - research)
	- inverse windowing (to counteract initial input windowing)
	*/
	
    /*Write to speakers*/
		/* call to speaker_output.h, takes floats as input */

}

int main()
{
	unsigned int iteration_count = 0;
    /*Calibration switch must be enabled at power-on to calibrate
    switch does not have effect during normal mode of operation (likely accidental if switched)*/
    if(isCalibrationEnabled()) 
    {
        runCalibration();
        /*TODO: perhaps have a pause here? */
    }

	fft_wrap_init();
	NORMAL_PRINT("Completed FFT init.\n");
    
	while(iteration_count < NUM_SIMULATION_CYCLES)
    {
        /*wait for algorithm to be enabled (controlled by board switch)
        user controls whether regular headphones listening mode, or antivoice mode */
        if(isAlgorithmEnabled())
        {
            runMainAlgorithm(); 
        }
        else
        {
            /*sleep to save power if possible / easy? */
        }
		/*NOTE: we may split up isAlgorithmEnabled into voiceObfuscationEnabled and ancEnabled as they are 2 different modes of operation*/

		iteration_count++;
    }
    
    return 0;
}
