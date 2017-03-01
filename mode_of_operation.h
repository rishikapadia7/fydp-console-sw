#ifndef MODE_OF_OPERATION_H
#define MODE_OF_OPERATION_H

#include "common.h"

/* Set to 1 if using ISR for mode of operation, or 0 if using polling */
#define USING_ISR 0


#if USING_ISR

/*TODO: modify these in an ISR if using ISR*/
volatile static bool calibrationEnabled = 0;
volatile static bool algorithmEnabled = 1;


bool isAlgorithmEnabled()
{
	return calibrationEnabled;
}


bool isCalibrationEnabled()
{
	return calibrationEnabled;
}




#else /* We are using polling */

bool isAlgorithmEnabled()
{
	bool calibrationEnabled = false;
	/* TODO: perform polling for status */
	return calibrationEnabled;
}


bool isCalibrationEnabled()
{
	bool calibrationEnabled = false;
	/* TODO: perform polling for status */
	return calibrationEnabled;
}

#endif /* USING_ISR */




#endif /*MODE_OF_OPERATION_H*/
