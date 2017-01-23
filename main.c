/* 
    fydp-console-sw 
    ANSI C89 / ISO C90 programming standard.
	// style comments are not allowed!
*/

/*TODO: modify these in an ISR*/
volatile unsigned short calibrationEnabled = 0;
volatile unsigned short algorithmEnabled = 1;

void runCalibration()
{
    /*TODO: populate calibration data structures */
}

void runMainAlgorithm()
{
    /*Get mic data */
    /*TODO: (call to separate file which handles conversion)*/

    /*Perform signal processing in frequency domain*/

    /*Write to transducers*/
}

int main()
{
    /*Calibration switch must be enabled at power-on to calibrate
    switch does not have effect during normal mode of operation (likely accidental if switched)*/
    if(calibrationEnabled) 
    {
        runCalibration();
        /*TODO: perhaps have a pause here? */
    }
    
    while(1)
    {
        /*wait for algorithm to be enabled (controlled by board switch)
        user controls whether regular headphones listening mode, or antivoice mode */
        if(algorithmEnabled)
        {
            runMainAlgorithm(); 
        }
        else
        {
            /*sleep to save power if possible / easy? */
        }
    }
    
    return 0;
}
