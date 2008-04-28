/*
 * SphereForm.c
 * Return Q,I for the formfactor of a sphere as
 * a test of libSANSAnalysis
 *
 * A Jackson, April 2007
 */

#include "../lib/libSANSAnalysis.h"
#include <math.h>
#include <stdio.h>

int main(){
	double q[128],i[128];
	// Default model parameters from IGOR macros
	double params[4] = {1,60,1e-6,0.01};
	int ii;

	for (ii = 0; ii < 128; ii++){
		q[ii] = 0.001 + (0.5-0.001)*ii/128;
		//Call the form factor calculation
		i[ii] = SphereForm(params,q[ii]);
	}

	for (ii = 0; ii < 128; ii++){
		printf("%g,%g\n", q[ii], i[ii]);
	}
	
	return 0;
}
