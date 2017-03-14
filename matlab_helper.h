#ifndef MATLAB_HELPER_H
#define MATLAB_HELPER_H

void matlab_float_print_real_only(float * in, unsigned int in_count)
{
	unsigned int i;
	for(i = 0; i < in_count; i+=2)
	{
		printf("%f, ", in[i]);
	}
}

void matlab_float_print_complex(float * in, unsigned int in_count)
{
	unsigned int i;
	for(i = 0; i < in_count; i+=2)
	{
		printf("%f + 1i*(%f), ", in[i], in[i+1]);
	}
}

void matlab_float_print_array(float * in, unsigned int in_count)
{
	unsigned int i;
	for(i = 0; i < in_count; i++)
	{
		printf("%f, ", in[i]);
	}
}

#endif /* MATLAB_HELPER_H */
