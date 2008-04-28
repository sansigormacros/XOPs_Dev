/*	SimpleFit.c

A simplified project designed to act as a template for your curve fitting function.
The fitting function is a simple polynomial. It works but is of no practical use.
*/


#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "SANSAnalysis.h"
#include "libSANSAnalysis.h"
#include "StructureFactor.h"


//Hard Sphere Structure Factor
//
int
HardSphereStructX(FitParamsPtr p)
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
			p->result = HardSphereStruct(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	return 0;
}

//Sticky Hard Sphere Structure Factor
//
int
StickyHS_StructX(FitParamsPtr p)
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
			p->result = StickyHS_Struct(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	return 0;
}



//     SUBROUTINE SQWELL: CALCULATES THE STRUCTURE FACTOR FOR A
//                        DISPERSION OF MONODISPERSE HARD SPHERES
//     IN THE Mean Spherical APPROXIMATION ASSUMING THE SPHERES
//     INTERACT THROUGH A SQUARE WELL POTENTIAL.
//** not the best choice of closure ** see note below
//     REFS:  SHARMA,SHARMA, PHYSICA 89A,(1977),212
int
SquareWellStructX(FitParamsPtr p)
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
			XOPNotice("I think it's single precision\r");
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = SquareWellStruct(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			XOPNotice("I don't know what it is\r");
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

// Hayter-Penfold (rescaled) MSA structure factor for screened Coulomb interactions 
//
int
HayterPenfoldMSAX(FitParamsPtr p)
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
			p->result = HayterPenfoldMSA(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}


// called as DiamCylX(hcyl,rcyl)
int
DiamCylX(DiamParamsPtr p)
{
	double hcyl,rcyl;
	
	hcyl = p->p1;
	rcyl = p->p2;
    
	p->result = DiamCyl(hcyl,rcyl);
	
	return(0);
}

//prolate OR oblate ellipsoids
//aa is the axis of rotation
//if aa>bb, then PROLATE
//if aa<bb, then OBLATE
// A. Isihara, J. Chem. Phys. 18, 1446 (1950)
//returns DIAMETER
// called as DiamEllipX(aa,bb)
int
DiamEllipX(DiamParamsPtr p)
{
	
	double aa,bb;
	
	aa = p->p1;
	bb = p->p2;
	
	p->result = DiamEllip(aa,bb);
	
	return(0);
}


///////////end of XOP


