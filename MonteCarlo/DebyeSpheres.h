/*
 *
 *  Created by Steve Kline on Tue Dec 15 2009.
 *  Copyright (c) 2009 NCNR. All rights reserved.
 *
 */

//#include <Carbon/Carbon.h>
#include <stdio.h>

// All structures passed to Igor are two-byte aligned.
#pragma pack(2)

// Parameters passed from Igor to the function, in reverse order of the parameter list
// result is the last parameter, always.
typedef struct AltiParams {
    double 	 grid;		// effective c-to-c distance between spheres = 0.62*Rprimary
    double   Rprimary;	//primary sphere radius
	waveHndl rhowavH;	// rho at xyz!!!
	waveHndl zwavH;	// z coordinate. ALL are expected to be DP waves
	waveHndl ywavH;	// y coordinate.
	waveHndl xwavH;	// x coordinate.
    double qval;	// q-value.
	void* tp;			//unused void for threadsafe functions
	double result;
}AltiParams, *AltiParamsPtr;   


// Parameters passed from Igor to the function, in reverse order of the parameter list
// result is the last parameter, always.
typedef struct DistParam {
	double p2;
	double p1;		// start and stop of the outer index
	waveHndl zwavH;	// z coordinate. ALL are expected to be DP waves
	waveHndl ywavH;	// y coordinate.
	waveHndl xwavH;	// x coordinate.
	void* tp;			//unused void for threadsafe functions
	double result;
}DistParam, *DistParamPtr;   

// Parameters passed from Igor to the function, in reverse order of the parameter list
// result is the last parameter, always.
typedef struct BinParam {
	double p2;
	double p1;		// start and stop of the outer index
	double binWidth;
	double grid;
	waveHndl bwavH;	// bin wave
	waveHndl zwavH;	// z coordinate. ALL are expected to be DP waves
	waveHndl ywavH;	// y coordinate.
	waveHndl xwavH;	// x coordinate.
	void* tp;			//unused void for threadsafe functions
	double result;
}BinParam, *BinParamPtr;   

// Parameters passed from Igor to the function, in reverse order of the parameter list
// result is the last parameter, always.
typedef struct BinSLDParam {
	double p2;
	double p1;		// start and stop of the outer index
	double binWidth;
	double grid;
	double minSLD;
	waveHndl PSFidH;	// psf id matrix, this is 2D
	waveHndl SLDLookH;	// SLD lookup wave, this is 1D
	waveHndl bwavH;	// bin wave, this is 2D
	waveHndl rhowavH;		//rho @ XYZ
	waveHndl zwavH;	// z coordinate. ALL are expected to be DP waves
	waveHndl ywavH;	// y coordinate.
	waveHndl xwavH;	// x coordinate.
	void* tp;			//unused void for threadsafe functions
	double result;
}BinSLDParam, *BinSLDParamPtr;   


// Parameters passed from Igor to the function, in reverse order of the parameter list
// result is the last parameter, always.
typedef struct SobolParam {
	waveHndl bwavH;	// result wave
	double nIn;		// initialization, or dimension - this is really an int
	//	void* tp;			//unused void for threadsafe functions
	double result;
}SobolParam, *SobolParamPtr;   



#pragma pack()		// return to default structure packing


double PhiQR(double qval, double rval);
double XYZDistance(double x1, double x2,double y1, double y2,double z1, double z2);
int DebyeSpheresX(AltiParamsPtr p);
int maxDistanceX(DistParamPtr p);
int binDistanceX(BinParamPtr p);
int binSLDDistanceX(BinSLDParamPtr p);
int SobolX(SobolParamPtr p);

