/* 
    fydp-console-sw 
    ANSI C89 / ISO C90 programming standard.
	// style comments are not allowed!
*/

#include "common.h"
#include "dsplib674x.h"
#include "mode_of_operation.h"
#include "mic_input.h"
#include "transducer_output.h"


void runCalibration()
{
    /*TODO: populate calibration data structures.
	NOTE: if using hardcoded data, then this function returns immediately.
	*/
}

void runMainAlgorithm()
{
    /*Get mic input */
    /*TODO: call to mic_data.h 
		returns an array of floats, 1 float per mic
		this is assuming that reading McBSP buffered input takes minimal clock cycles, otherwise we may need to process mic one by one
	*/

    /*Perform signal processing
	- input signal windowing
	- sliding fft
	- memcpy to a signal to operate on
	- magnitude adjustment
	- phase adjustment
		- feedback elimination (this will be part of magnitude and phase adjustment and may involve subtraction and not just multiplication)
		- voice obfuscation (same, but may involve addition and subtraction as well)
	- ifft (may or may not be able to use previous signal data to reduce computation - research)
	- inverse windowing (to counteract initial input windowing)
	*/
	
    /*Write to transducers*/
		/* call to transducer_output.h, takes floats as input */

}

int main()
{
    /*Calibration switch must be enabled at power-on to calibrate
    switch does not have effect during normal mode of operation (likely accidental if switched)*/
    if(isCalibrationEnabled()) 
    {
        runCalibration();
        /*TODO: perhaps have a pause here? */
    }
    
    while(1)
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
		/*NOTE: we may split up isAlgorithmEnabled into voiceObfuscationEnabled and ancEnabled as they are 2 different modes of operatoin*/
    }
    
    return 0;
}
