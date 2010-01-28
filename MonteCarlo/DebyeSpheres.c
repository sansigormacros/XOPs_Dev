/*	DebyeSpheres.c


*/

#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "DebyeSpheres.h"

#pragma XOP_SET_STRUCT_PACKING			// All structures are 2-byte-aligned.

// Prototypes
HOST_IMPORT void main(IORecHandle ioRecHandle);

// Custom error codes
#define REQUIRES_IGOR_200 1 + FIRST_XOP_ERR
#define NON_EXISTENT_WAVE 2 + FIRST_XOP_ERR
#define REQUIRES_SP_OR_DP_WAVE 3 + FIRST_XOP_ERR



/*	Calculates the scattered intensity from a collection of spheres
    using Debye's method. 

	Warning:
		The call to WaveData() below returns a pointer to the middle
		of an unlocked Macintosh handle. In the unlikely event that your
		calculations could cause memory to move, you should copy the coefficient
		values to local variables or an array before such operations.
*/
int
DebyeSpheresX(AltiParamsPtr p)
{
	float qv;				// input q-value
	float ival;				//output intensity value
	float *xv,*yv,*zv,*rv;		//pointers to input xyz-rho coordinates
	int i,j;
    int npt;
	float rval,grid,vol,fQR,dum,dij;

	

	// check for all of the required waves
	if (p->rhowavH == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	if (p->zwavH == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	if (p->ywavH == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	if (p->xwavH == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}


    //check to see that all are float, not double
	if(WaveType(p->rhowavH) != NT_FP32 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP32;
    }
    if(WaveType(p->zwavH) != NT_FP32 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP32;
    }
    if(WaveType(p->ywavH) != NT_FP32 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP32;
    }
    if(WaveType(p->xwavH) != NT_FP32 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP32;
    }

	
	// convert the input to float. Do all calculations as float.

    rval = (float) p->Rprimary;		// primary sphere radius
    grid = (float) p->grid;			// calling program should set this to 0.62*Rprimary
	qv = (float) p->qval;

//
    npt = (int) WavePoints(p->xwavH);	//wavePoints returns long, number of XYZ points
	xv = WaveData(p->xwavH);		//xyz locations
	yv = WaveData(p->ywavH);
	zv = WaveData(p->zwavH);
	rv = WaveData(p->rhowavH);
    
	
	vol = 4.0*3.1415927/3.0*rval*rval*rval;
	ival = 0.0;
	fQR = PhiQR(qv,rval);
	//do the i=j sum
	for(i=0;i<npt;i+=1) {
		dum = rv[i]*vol*fQR;
		ival += dum*dum;
	}
	//do the i!=j double sum
	dum = vol*vol*fQR*fQR;
	for(i=0;i<npt;i+=1) {
		for(j=(i+1);j<npt;j+=1) {
			dij=XYZDistance(xv[i],xv[j],yv[i],yv[j],zv[i],zv[j]) * grid;
			ival += 2.0*rv[i]*rv[j]*dum*sin(dij*qv)/dij/qv;
		}
	}

    p->result= (DOUBLE) ival;
	
    return 0;

}


float PhiQR(float qval, float rval)
{
	float retval,qr;
	
	qr = qval*rval;
	retval = (float) ( 3*(sin(qr) - qr*cos(qr))/qr/qr/qr );
	return(retval);
}

float XYZDistance(float x1, float x2,float y1, float y2,float z1, float z2)
{
	float retval,dx,dy,dz;
	
	dx = (x1-x2);
	dy = (y1-y2);
	dz = (z1-z2);
	retval = (float) sqrt( dx*dx + dy*dy + dz*dz );
	return(retval);
}


#pragma XOP_RESET_STRUCT_PACKING			// All structures are 2-byte-aligned.
// All structures are 2-byte-aligned.
