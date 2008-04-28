/*	TwoPhaseFit.c

*/


#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "SANSAnalysis.h"
#include "libSANSAnalysis.h"
#include "TwoPhase.h"

// scattering from the Teubner-Strey model for microemulsions - hardly needs to be an XOP...
int
TeubnerStreyModelX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
    
	q = p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
            SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07            
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = TeubnerStreyModel(dp,q);																
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
Power_Law_ModelX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;
	
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
			p->result = Power_Law_Model(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}


int
Peak_Lorentz_ModelX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;
	
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
			p->result = Peak_Lorentz_Model(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
Peak_Gauss_ModelX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;
	
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
			p->result = Peak_Gauss_Model(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
Lorentz_ModelX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;
	
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
			p->result=Lorentz_Model(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
FractalX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;
	
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
            p->result = Fractal(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
DAB_ModelX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;
	
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
			p->result = DAB_Model(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

// G. Beaucage's Unified Model (1-4 levels)
//
int
OneLevelX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;
	
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
			p-> result = OneLevel(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

// G. Beaucage's Unified Model (1-4 levels)
//
int
TwoLevelX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;
	
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
			p->result = TwoLevel(dp, q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

// G. Beaucage's Unified Model (1-4 levels)
//
int
ThreeLevelX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;
	
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
			p->result = ThreeLevel(dp, q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

// G. Beaucage's Unified Model (1-4 levels)
//
int
FourLevelX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;
	
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
			p->result = FourLevel(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}


///////////end of XOP


