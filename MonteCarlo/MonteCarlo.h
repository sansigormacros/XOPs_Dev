/*
 *  MonteCarlo.h
 *  SANSAnalysis
 *
 *  Created by Steve Kline on 10/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <math.h>
#include <ctype.h>

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <float.h>
#include "winFuncs.h"
#endif
 
/* Prototypes */
HOST_IMPORT void main(IORecHandle ioRecHandle);

 
#define OLD_IGOR 1 + FIRST_XOP_ERR
#define NON_EXISTENT_WAVE 2 + FIRST_XOP_ERR
#define NEEDS_2D_WAVE 3 + FIRST_XOP_ERR


// All structures passed to Igor are two-byte aligned.
#include "XOPStructureAlignmentTwoByte.h"

struct MC_Params {     // This structure must be 2-byte-aligned because it receives parameters from Igor.
	waveHndl resultsH;	// results of MC
	waveHndl MC_linear_dataH;		//this is a 2D WAVE
	waveHndl nnH;
	waveHndl j2H;
	waveHndl j1H;
	waveHndl ntH;
	waveHndl ran_devH;
	waveHndl inputWaveH;
	void* tp;				//unused void for ThreadSafe functions
	double result;		// return value is unused, save for error if needed
};
typedef struct MC_Params MC_Params;
typedef struct MC_Params *MC_ParamsPtr;

#include "XOPStructureAlignmentReset.h"


// function prototypes
int Monte_SANSX(MC_ParamsPtr p);
int FindPixel(double testQ, double testPhi, double lam, double sdd, double pixSize, double xCtr, double yCtr, long *xPixel, long *yPixel);
int NewDirection(double *vx, double *vy, double *vz, double theta, double phi);
double path_len(double aval, double sig_tot);
float ran1(long *idum);
float ran3(long *idum);
double locate_interp(double xx[], long n, double x);
