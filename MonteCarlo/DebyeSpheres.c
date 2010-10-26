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

 everything was previously declared as float, some inputs were as double.
 
 -- to avoid confusion, calculate everything in double, pass everything in as double
  -- this is more precision than is necessary, but avoids strange results from type casting
     behind the scenes
*/
int
DebyeSpheresX(AltiParamsPtr p)
{
	double qv;				// input q-value
	double ival;				//output intensity value
	double *xv,*yv,*zv,*rv;		//pointers to input xyz-rho coordinates
	int i,j;
    int npt;
	double rval,grid,vol,fQR,dum,dij;

	

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
	/*
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
	*/
	
    //check to see that all are double
	if(WaveType(p->rhowavH) != NT_FP64 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP64;
    }
    if(WaveType(p->zwavH) != NT_FP64 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP64;
    }
    if(WaveType(p->ywavH) != NT_FP64 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP64;
    }
    if(WaveType(p->xwavH) != NT_FP64 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP64;
    }
	
	
	// (NO) -- convert the input to float. Do all calculations as float.
	// do everything in double. no reason to do in float, except for the previous Altivec incarnation
	
    rval = p->Rprimary;		// primary sphere radius
    grid = p->grid;			// calling program should set this to 0.62*Rprimary
	qv = p->qval;

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

    p->result = ival;
	
    return 0;

}


double PhiQR(double qval, double rval)
{
	double retval,qr;
	
	qr = qval*rval;
	retval = ( 3*(sin(qr) - qr*cos(qr))/qr/qr/qr );
	return(retval);
}

double XYZDistance(double x1, double x2,double y1, double y2,double z1, double z2)
{
	double retval,dx,dy,dz;
	
	dx = (x1-x2);
	dy = (y1-y2);
	dz = (z1-z2);
	retval = sqrt( dx*dx + dy*dy + dz*dz );
	return(retval);
}


#pragma XOP_RESET_STRUCT_PACKING			// All structures are 2-byte-aligned.
// All structures are 2-byte-aligned.
