/*
	ResolutionSmearing.h -- 
*/

#pragma pack(2)

/* Prototypes */
typedef struct SmearParams {
	double x;				//Independent Variable
	waveHndl waveHandle;	// Coefficient wave
	double i_shad;
	double i_qbar;
	double i_sigq;
	double result;
}SmearParams, *SmearParamsPtr;

typedef struct GenSmearParams {
	double x;				//Independent Variable
	waveHndl waveHandle;	// Coefficient wave
	double i_shad;
	double i_qbar;
	double i_sigq;
	Handle funcname;
	double result;
}GenSmearParams, *GenSmearParamsPtr;

typedef struct PassParams {
	waveHndl waveHandle;
	double x;
}PassParams, *PassParamsPtr;

#pragma pack()

/* IGOR Fit Functions */
int Smear_Model_20_X(GenSmearParamsPtr p);
int Smear_Model_76_X(GenSmearParamsPtr p);
int SmearedCyl_PolyRadiusX(SmearParamsPtr p);


static double qtrap_USANS(FunctionInfo fi, PassParams p, double aa, double bb, double eps, int maxit);
static double trapzd_USANS(FunctionInfo fi, PassParams p, double aa, double bb, int nn);