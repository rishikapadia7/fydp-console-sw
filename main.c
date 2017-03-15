/* 
    fydp-console-sw 
    ANSI C89 / ISO C90 programming standard.
	// style comments are not allowed!
*/

#include "antivoice/antivoice.h"

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
	signal_processing_init();
    
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
	NORMAL_PRINT("Completed %u simulation iterations (samples).\n", NUM_SIMULATION_CYCLES);


    return 0;
}
