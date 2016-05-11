/*	SimpleFit.c

A simplified project designed to act as a template for your curve fitting function.
The fitting function is a simple polynomial. It works but is of no practical use.
*/


#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "SANSAnalysis.h"
#include "libSANSAnalysis.h"
#include "StructureFactor.h"
#include "2Y_OneYukawa.h"
#include "2Y_TwoYukawa.h"


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
			fp= (float*)WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
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
			fp= (float*)WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
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
			fp= (float*)WaveData(p->waveHandle);
			SetNaN64(&p->result);
			XOPNotice("I think it's single precision\r");
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
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
			fp= (float*)WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
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


//
//
int
OneYukawaX(FitParamsPtr_Yuk p)
{
	double *sq;			//pointer to sq wave
	double *qw;			//pointer to q wave
	double *cw;			//pointer to coef wave
	CountInt npnts,i;			//number of points in waves
	
	
	double a, b, c, d;	
	int debug = 0,check,ok;			//always keep this to zero...
	//default parameters
	double Z,K,phi,radius;
	char buf[256];
	
	/* check that wave handles are all valid */
	if (p->SQHandle == NIL) {
		SetNaN64(&p->retVal);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->QHandle == NIL) {
		SetNaN64(&p->retVal);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->CoefHandle == NIL) {
		SetNaN64(&p->retVal);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}	
	
	//get the wave data
	sq = (double*)WaveData(p->SQHandle);
	qw = (double*)WaveData(p->QHandle);					
	cw = (double*)WaveData(p->CoefHandle);					
	npnts = (CountInt)WavePoints(p->QHandle);						// Number of points in q wave.
	
	phi = cw[0];
	radius = cw[1];
	K = cw[2];
	Z = cw[3];
	
	if(fabs(Z) < 0.1) Z = 0.1;			// values near zero are very bad for the calculation
	
	//	sprintf(buf, "Input OK, phi,radius,K,Z = %g %g %g %g\r",phi,radius,K,Z);
	//	XOPNotice(buf);
	
	debug = 0;
	ok = Y_SolveEquations( Z, K, phi, &a, &b, &c, &d, debug );
	
	if( ok )
	{
		//		sprintf(buf, "Y_SolveEquations OK\r");
		//		XOPNotice(buf);
		
		check = Y_CheckSolution( Z, K, phi, a, b, c, d );
		if(debug) {
			sprintf(buf, "solution = (%g, %g, %g, %g) check = %d\r", a, b, c, d, check );
			XOPNotice(buf);
		}
	}
	
	//	sprintf(buf, "Y_CheckSolution OK\r");
	//	XOPNotice(buf);
	
	// loop through and calculate the S(q), or return 1 if the solution failed
	//	if(check) {		//from the converted c-code
	
	if(ok) {		//less restrictive, if a solution found, return it, even if the equations aren't quite satisfied
		
		for (i = 0; i < npnts; i++) {
			sq[i] = SqOneYukawa(qw[i]*radius*2.0, Z, K, phi, a, b, c, d);
		}	
	} else {
		for (i = 0; i < npnts; i++) {
			sq[i] = 1000;		// return a really bogus value, as Yun suggests
		}
	}
	
	// mark the returned wave as updated so that the graph etc. automatically updates	
	WaveHandleModified(p->SQHandle);
	
	p->retVal = 0;
	
	return 0;
}


int
TwoYukawaX(FitParamsPtr_Yuk p)
{
	double *sq;			//pointer to sq wave
	double *qw;			//pointer to q wave
	double *cw;			//pointer to coef wave
	CountInt npnts,i;			//number of points in waves
	
	
	double a, b, c1, c2, d1, d2;	
	int debug = 0,check,ok;			//always keep this to zero...
	//default parameters
	double Z1,K1,Z2,K2,phi,radius;
	char buf[256];
	
	/* check that wave handles are all valid */
	if (p->SQHandle == NIL) {
		SetNaN64(&p->retVal);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->QHandle == NIL) {
		SetNaN64(&p->retVal);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->CoefHandle == NIL) {
		SetNaN64(&p->retVal);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}	
	
	//get the wave data
	sq = (double*)WaveData(p->SQHandle);
	qw = (double*)WaveData(p->QHandle);					
	cw = (double*)WaveData(p->CoefHandle);					
	npnts = (CountInt)WavePoints(p->QHandle);						// Number of points in q wave.
	
	phi = cw[0];
	radius = cw[1];
	K1 = cw[2];
	Z1 = cw[3];
	K2 = cw[4];
	Z2 = cw[5];
	
	if(fabs(Z1) < 0.001) Z1 = 0.001;			// values near zero are very bad for the calculation
	if(fabs(Z2) < 0.001) Z2 = 0.001;			// values near zero are very bad for the calculation
	if(fabs(K1) < 0.001) K1 = 0.001;			// values near zero are very bad for the calculation
	if(fabs(K2) < 0.001) K2 = 0.001;			// values near zero are very bad for the calculation
	
	
	//	sprintf(buf, "Input OK, phi,radius,K1,Z1,K2,Z2 = %g %g %g %g %g %g\r",phi,radius,K1,Z1,K2,Z2);
	//	XOPNotice(buf);
	
	debug = 0;
	
	ok = TY_SolveEquations( Z1, Z2, K1, K2, phi, &a, &b, &c1, &c2, &d1, &d2, debug );
	if( ok )
	{
		//		sprintf(buf, "TY_SolveEquations OK \r");
		//		XOPNotice(buf);
		
		
		check = TY_CheckSolution( Z1, Z2, K1, K2, phi, a, b, c1, c2, d1, d2 );
		if(debug) {
			sprintf(buf, "solution = (%g, %g, %g, %g, %g, %g) check = %d\r", a, b, c1, c2, d1, d2, check );
			XOPNotice(buf);
		}
	}
	//	sprintf(buf, "TY_CheckSolution OK \r");
	//	XOPNotice(buf);
	
	// loop through and calculate the S(q), or return 1 if the solution failed
	//	if(check) {		//from the converted c-code
	
	if(ok) {		//less restrictive, if a solution found, return it, even if the equations aren't quite satisfied
		
		
		for (i = 0; i < npnts; i++) {
			sq[i] = SqTwoYukawa(qw[i]*radius*2.0, Z1, Z2, K1, K2, phi, a, b, c1, c2, d1, d2);
		}	
	} else {
		for (i = 0; i < npnts; i++) {
			sq[i] = 1000;		// return a really bogus value, as Yun suggests
		}
	}
	
	// mark the returned wave as updated so that the graph etc. automatically updates	
	WaveHandleModified(p->SQHandle);
	
	p->retVal = 0;
	
	return 0;
}





///////////end of XOP


