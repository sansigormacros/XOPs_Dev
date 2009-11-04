/*	SimpleFit.c

A simplified project designed to act as a template for your curve fitting function.
The fitting function is a simple polynomial. It works but is of no practical use.
*/


#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "SANSAnalysis.h"
#include "libSANSAnalysis.h"
#include "Sphere.h"

// scattering from a sphere - hardly needs to be an XOP...
int
SphereFormX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
//	int hState;
//	char buf[256];
		
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;

	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = SphereForm(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


// scattering from a monodisperse core-shell sphere - hardly needs to be an XOP...
int
CoreShellSphereX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = CoreShellForm(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

// scattering from a unilamellar vesicle - hardly needs to be an XOP...
// same functional form as the core-shell sphere, but more intuitive for a vesicle
int
VesicleFormX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = VesicleForm(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


// scattering from a core shell sphere with a (Schulz) polydisperse core and constant shell thickness
//
int
PolyCoreFormX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = PolyCoreForm(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


// scattering from a uniform sphere with a (Schulz) size distribution
// structure factor effects are explicitly and correctly included.
//
int
PolyHardSpheresX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = PolyHardSphereIntensity(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

// scattering from a uniform sphere with a (Schulz) size distribution, bimodal population
// NO CROSS TERM IS ACCOUNTED FOR == DILUTE SOLUTION!!
//
int
BimodalSchulzSpheresX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = BimodalSchulzSpheres(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


// scattering from a uniform sphere with a (Schulz) size distribution
//
int
SchulzSpheresX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = SchulzSpheres(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}



// scattering from a uniform sphere with a rectangular size distribution
//
int
PolyRectSpheresX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = PolyRectSpheres(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


// scattering from a uniform sphere with a Gaussian size distribution
//
int
GaussSpheresX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = GaussPolySphere(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


// scattering from a uniform sphere with a LogNormal size distribution
//
int
LogNormalSphereX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = LogNormalPolySphere(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


// scattering from a core shell sphere with a (Schulz) polydisperse core and constant ratio (shell thickness)/(core radius)
// - the polydispersity is of the WHOLE sphere
//
int
PolyCoreShellRatioX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = PolyCoreShellRatio(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


// scattering from a a binary population of hard spheres, 3 partial structure factors
// are properly accounted for...
//	 Input (fitting) variables are:
//	larger sphere radius(angstroms) = guess[0]
// 	smaller sphere radius (A) = w[1]
//	number fraction of larger spheres = guess[2]
//	total volume fraction of spheres = guess[3]
//	size ratio, alpha(0<a<1) = derived
//	SLD(A-2) of larger particle = guess[4]
//	SLD(A-2) of smaller particle = guess[5]
//	SLD(A-2) of the solvent = guess[6]
//	background = guess[7]
int
BinaryHSX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = BinaryHS(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

int
BinaryHS_PSF11X(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = BinaryHS_PSF11(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

int
BinaryHS_PSF12X(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = BinaryHS_PSF12(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


int
BinaryHS_PSF22X(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = BinaryHS_PSF22(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}



/*
 // calculates the scattering from a spherical particle made up of a core (aqueous) surrounded
 // by N spherical layers, each of which is a PAIR of shells, solvent + surfactant since there
 //must always be a surfactant layer on the outside
 //
 // bragg peaks arise naturally from the periodicity of the sample
 // resolution smeared version gives he most appropriate view of the model
 
	Warning:
 The call to WaveData() below returns a pointer to the middle
 of an unlocked Macintosh handle. In the unlikely event that your
 calculations could cause memory to move, you should copy the coefficient
 values to local variables or an array before such operations.
 */
int
MultiShellSphereX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = MultiShell(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

/*
 // calculates the scattering from a POLYDISPERSE spherical particle made up of a core (aqueous) surrounded
 // by N spherical layers, each of which is a PAIR of shells, solvent + surfactant since there
 //must always be a surfactant layer on the outside
 //
 // bragg peaks arise naturally from the periodicity of the sample
 // resolution smeared version gives he most appropriate view of the model
 //
 // Polydispersity is of the total (outer) radius. This is converted into a distribution of MLV's
 // with integer numbers of layers, with a minimum of one layer... a vesicle... depending
 // on the parameters, the "distribution" of MLV's that is used may be truncated
 //
	Warning:
 The call to WaveData() below returns a pointer to the middle
 of an unlocked Macintosh handle. In the unlikely event that your
 calculations could cause memory to move, you should copy the coefficient
 values to local variables or an array before such operations.
 */
int
PolyMultiShellX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = PolyMultiShell(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

// new models, 2008....

int
OneShellX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = OneShell(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

int
TwoShellX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = TwoShell(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

int
ThreeShellX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = ThreeShell(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

int
FourShellX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = FourShell(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

//

int
PolyOneShellX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = PolyOneShell(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

int
PolyTwoShellX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = PolyTwoShell(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

int
PolyThreeShellX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = PolyThreeShell(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

int
PolyFourShellX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = PolyFourShell(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

// paracrystal models, 2008
int
BCC_ParaCrystalX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = BCC_ParaCrystal(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


int
FCC_ParaCrystalX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = FCC_ParaCrystal(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


int
SC_ParaCrystalX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = SC_ParaCrystal(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

int
FuzzySpheresX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = FuzzySpheres(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

