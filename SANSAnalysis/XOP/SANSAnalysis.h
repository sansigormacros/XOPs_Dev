/*
	SANSAnalysis.h -- definitions general to all code.
*/


/* Prototypes */
HOST_IMPORT void main(IORecHandle ioRecHandle);

// Custom error codes
#define REQUIRES_IGOR_200 1 + FIRST_XOP_ERR
#define NON_EXISTENT_WAVE 2 + FIRST_XOP_ERR
#define REQUIRES_SP_OR_DP_WAVE 3 + FIRST_XOP_ERR


#include "XOPStructureAlignmentTwoByte.h"

// Fit function parameter structure
typedef struct FitParams {
	double x;				// Independent variable.
	waveHndl waveHandle;	// Coefficient wave.
	void* tp;				//unused void for ThreadSafe functions
	double result;
}FitParams, *FitParamsPtr;

// Fit function parameter structure
typedef struct FitParams2D {
	double qy;				// Independent variable.
	double qx;				// Independent variable.
	waveHndl waveHandle;	// Coefficient wave.
	void* tp;				//unused void for ThreadSafe functions
	double result;
}FitParams2D, *FitParams2DPtr;

// for 2D functions with arbitrary weights in phi and theta
typedef struct FitParams2DWeight {
	double qy;				// Independent variable.
	double qx;				// Independent variable.
	waveHndl weight_values;
	waveHndl par_values;
	waveHndl waveHandle;	// Coefficient wave.
	void* tp;				//unused void for ThreadSafe functions
	double result;
}FitParams2DWeight, *FitParams2DWeightPtr;

#include "XOPStructureAlignmentReset.h"