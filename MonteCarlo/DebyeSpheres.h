/*
 *
 *  Created by Steve Kline on Tue Dec 15 2009.
 *  Copyright (c) 2009 NCNR. All rights reserved.
 *
 */

//#include <Carbon/Carbon.h>
#include <stdio.h>

// Parameters passed from Igor to the function, in reverse order of the parameter list
// result is the last parameter, always.
typedef struct AltiParams {
    double 	 grid;		// effective c-to-c distance between spheres = 0.62*Rprimary
    double   Rprimary;	//primary sphere radius
	waveHndl rhowavH;	// rho at xyz!!!
	waveHndl zwavH;	// z coordinate. ALL are expected to be SP waves
	waveHndl ywavH;	// y coordinate.
	waveHndl xwavH;	// x coordinate.
    double qval;	// q-value.
	void* tp;			//unused void for threadsafe functions
	double result;
}AltiParams, *AltiParamsPtr;   
 
 
double PhiQR(double qval, double rval);
double XYZDistance(double x1, double x2,double y1, double y2,double z1, double z2);
int DebyeSpheresX(AltiParamsPtr p);