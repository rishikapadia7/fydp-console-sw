#ifndef TRANSDUCER_OUTPUT_H
#define TRANSDUCER_OUTPUT_H

#include "common.h"


/* Scaling required as per:
		http://stackoverflow.com/questions/15087668/how-to-convert-pcm-samples-in-byte-array-as-floating-point-numbers-in-the-range
		Input f is expected to be between -1 and 1.
	*/
transducerout_t convert_float_to_transducerout(float f)
{
	/* We add 1 since it's unsigned number we are converting to and the number can be purely positive*/
	f = (f + 1);
	/* We now have f between 0 and 2.  Scale up to be between 0 and MAX_VAL. */
	f = f * (TRANSDUCEROUT_MAX_VAL / 2);
	if( f > TRANSDUCEROUT_MAX_VAL )
	{
		ERROR_PRINT("convert_float_to_transducerout resulted in value > TRANSDUCEROUT_MAX_VAL of %f\n", f);
		f = TRANSDUCEROUT_MAX_VAL;
	}

	return (transducerout_t) f;
}


#endif /* TRANSDUCER_OUTPUT_H */

