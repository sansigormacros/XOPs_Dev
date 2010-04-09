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
    DOUBLE 	 grid;		// effective c-to-c distance between spheres = 0.62*Rprimary
    DOUBLE   Rprimary;	//primary sphere radius
	waveHndl rhowavH;	// rho at xyz!!!
	waveHndl zwavH;	// z coordinate. ALL are expected to be SP waves
	waveHndl ywavH;	// y coordinate.
	waveHndl xwavH;	// x coordinate.
    DOUBLE qval;	// q-value.
	void* tp;			//unused void for threadsafe functions
	DOUBLE result;
}AltiParams, *AltiParamsPtr;   
 
 
float PhiQR(float qval, float rval);
float XYZDistance(float x1, float x2,float y1, float y2,float z1, float z2);
int DebyeSpheresX(AltiParamsPtr p);