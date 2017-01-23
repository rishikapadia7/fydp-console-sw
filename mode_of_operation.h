#ifndef MODE_OF_OPERATION_H
#define MODE_OF_OPERATION_H

#include "common.h"

/* Set to 1 if using ISR for mode of operation, or 0 if using polling */
#define USING_ISR 0


#if USING_ISR

/*TODO: modify these in an ISR if using ISR*/
volatile static bool_t calibrationEnabled = 0;
volatile static bool_t algorithmEnabled = 1;


bool_t isAlgorithmEnabled()
{
	return calibrationEnabled;
}


bool_t isCalibrationEnabled()
{
	return calibrationEnabled;
}




#else /* We are using polling */

bool_t isAlgorithmEnabled()
{
	bool_t calibrationEnabled = FALSE;
	/* TODO: perform polling for status */
	return calibrationEnabled;
}


bool_t isCalibrationEnabled()
{
	bool_t calibrationEnabled = FALSE;
	/* TODO: perform polling for status */
	return calibrationEnabled;
}

#endif /* USING_ISR */




#endif /*MODE_OF_OPERATION_H*/
