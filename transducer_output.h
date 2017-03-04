#ifndef TRANSDUCER_OUTPUT_H
#define TRANSDUCER_OUTPUT_H

#include "common.h"


/* Scaling required as per:
		http://stackoverflow.com/questions/15087668/how-to-convert-pcm-samples-in-byte-array-as-floating-point-numbers-in-the-range
		Input f is expected to be between -1 and 1.
	*/
transducerout_t convert_float_to_transducerout(float f)
{
	/* We add back the 1 since it's unsigned number we are converting to and the number can be purely positive*/
	f = (f + 1) * TRANSDUCEROUT_MAX_VAL;
	if( f > TRANSDUCEROUT_MAX_VAL ) f = TRANSDUCEROUT_MAX_VAL;
	return (transducerout_t) f;
}


#endif /* TRANSDUCER_OUTPUT_H */
