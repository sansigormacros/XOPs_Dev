/*	DebyeSpheres.c


*/

#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "DebyeSpheres.h"

//#pragma XOP_SET_STRUCT_PACKING			// All structures are 2-byte-aligned.

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


/*	
 
 given the distances XYZ as a triplet (on a unit grid)
 return the maximum distance. The calling program must multiply by
 the grid dimension to get real distance
 
 */
int
maxDistanceX(DistParamPtr p)
{
	double dmax,dij;				//output dmax value, dij
	double *xv,*yv,*zv;		//pointers to input xyz coordinates
	int i,j;
    int npt;
	
	
	
	// check for all of the required waves
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

    //check to see that all are double
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
	
	//
    npt = (int) WavePoints(p->xwavH);	//wavePoints returns long, number of XYZ points
	xv = WaveData(p->xwavH);		//xyz locations
	yv = WaveData(p->ywavH);
	zv = WaveData(p->zwavH);
	
	dmax = 0;
	//do the i!=j double loop, keeping the maximum distance

	for(i=0;i<npt;i+=1) {
		for(j=(i+1);j<npt;j+=1) {
//			dij=XYZDistance(xv[i],xv[j],yv[i],yv[j],zv[i],zv[j]);
			dij = (xv[i]-xv[j])*(xv[i]-xv[j]) + (yv[i]-yv[j])*(yv[i]-yv[j]) + (zv[i]-zv[j])*(zv[i]-zv[j]);
			if(dij > dmax) {
				dmax = dij;
			}
		}
	}
	
    p->result = dmax;
	
    return 0;
	
}

/*	
 
 given the distances XYZ as a triplet (on a unit grid)
 return the binned histogram of distances
 
 */
int
binDistanceX(BinParamPtr p)
{
	double *xv,*yv,*zv,*bv;		//pointers to input xyz coordinates
	int i,j;
    int npt,numBins,binIndex;
	double grid,binWidth,val;
	int p1,p2;
	
	
	
	// check for all of the required waves
	if (p->bwavH == NIL) {
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
	
    //check to see that all are double
	if(WaveType(p->bwavH) != NT_FP64 ) {
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
	
	//
    npt = (int) WavePoints(p->xwavH);	//wavePoints returns long, number of XYZ points
    numBins = (int) WavePoints(p->bwavH);	//wavePoints returns long, number of points in bin wave
	p1 = (int) p->p1;
	p2 = (int) p->p2;
	
	
	xv = WaveData(p->xwavH);		//xyz locations
	yv = WaveData(p->ywavH);
	zv = WaveData(p->zwavH);
	bv = WaveData(p->bwavH);
	
	grid = p->grid;
	binWidth = p->binWidth;
	
	//do the i!=j double loop, 	
	for(i=p1;i<p2;i+=1) {
		for(j=(i+1);j<npt;j+=1) {
			val = XYZDistance(xv[i],xv[j],yv[i],yv[j],zv[i],zv[j])*grid;
			binIndex = (int)(val/binWidth-0.5);
			if(binIndex > numBins -1 ) {
				//Print "bad index"
			} else {
				bv[binIndex] += 1;
			}
			
		}
	}
	
    p->result = 0;
	
    return 0;
	
}


/*	
 
 given the distances XYZ as a triplet (on a unit grid) and the SLD at each point,
 return the binned histogram of distances for each of the parwise interactions

 The returned binning is a matrix, and has to be assigned as such
 
 */
int
binSLDDistanceX(BinSLDParamPtr p)
{
	double *xv,*yv,*zv;		//pointers to input xyz coordinates
	double *rho,*SLDLook,*PSFid;	// rho and the SLD lookup vector
	int i,j;
    int npt,numBins,binIndex;
	double grid,binWidth,val,retVal;
	int p1,p2;

	
// for accessing the 2D wave data to write the results	
	waveHndl wavH,PSFwavH;
//	long numDimensions;
//	long dimensionSizes[MAX_DIMENSIONS+1];
	double value[2];				// Pointers used for double data.
	long indices[MAX_DIMENSIONS];
//	
	long rhoi,rhoj,rii,rji,PSFIndex;
	
	
	// check for all of the required waves
	if (p->PSFidH == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	if (p->SLDLookH == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	if (p->bwavH == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
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
	
    //check to see that all are double
	if(WaveType(p->PSFidH) != NT_FP64 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP64;
    }
	if(WaveType(p->SLDLookH) != NT_FP64 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP64;
    }
	if(WaveType(p->bwavH) != NT_FP64 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP64;
    }
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
	
	
	// access the 2D wave data for writing using the direct method
	wavH = p->bwavH;
	if (wavH == NIL)
		return NOWAV;
	//
	PSFwavH = p->PSFidH;
	
    npt = (int) WavePoints(p->xwavH);	//wavePoints returns long, number of XYZ points
    numBins = (int) WavePoints(p->bwavH);	//wavePoints returns long, number of points in bin wave
	
	xv = WaveData(p->xwavH);		//xyz locations
	yv = WaveData(p->ywavH);
	zv = WaveData(p->zwavH);
	rho = WaveData(p->rhowavH);
	SLDLook = WaveData(p->SLDLookH);
	PSFid = WaveData(p->PSFidH);			//this one is 2D
	
	p1 = (int) p->p1;
	p2 = (int) p->p2;
	
	grid = p->grid;
	binWidth = p->binWidth;
	
	//do the i!=j double loop, 	
	for(i=p1;i<p2;i+=1) {
		for(j=(i+1);j<npt;j+=1) {
			val = XYZDistance(xv[i],xv[j],yv[i],yv[j],zv[i],zv[j])*grid;
			binIndex = (int)(val/binWidth-0.5);
			if(binIndex > numBins -1 ) {
				//Print "bad index"
			} else {
				rhoi = (long) rho[i];				//get the rho value at i and j
				rhoj = (long) rho[j];
				rii = (long) SLDLook[rhoi];			//rho i index
				rji = (long) SLDLook[rhoj];			//rho j index
				MemClear(indices, sizeof(indices)); // Must be 0 for unused dimensions.
				indices[0] = rii;
				indices[1] = rji;
				if (retVal = MDGetNumericWavePointValue(PSFwavH, indices, value))
					return retVal;
				//PSFIndex = (long) PSFid[rii][rji];		//doesn't work
				PSFIndex = (long) value[0];
				
				//now do the assignment to the 2D
				// equivalent to binMatrix[binIndex][PSFIndex]
				
				MemClear(indices, sizeof(indices)); // Must be 0 for unused dimensions.
				indices[0] = binIndex;
				indices[1] = PSFIndex;
				if (retVal = MDGetNumericWavePointValue(wavH, indices, value))
					return retVal;
				value[0] += 1; // Real part
				if (retVal = MDSetNumericWavePointValue(wavH, indices, value))
					return retVal;
				
			}
			
		}
	}
	
    p->result = 0;
	
    return 0;
	
}


///// this is directly from Numerical Recipes
// -- I did change the float to double, since Igor treats all as double
// and n is an int, not a pointer (seemed unnecessary)
//
#define MAXBIT 30
#define MAXDIM 6
static int iminarg1,iminarg2;
#define IMIN(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ? (iminarg1) : (iminarg2))

int
SobolX(SobolParamPtr p)
{
	int j,k,l;
	unsigned long i,im,ipp;
	static double fac;
	static unsigned long in,ix[MAXDIM+1],*iu[MAXBIT+1];
	static unsigned long mdeg[MAXDIM+1]={0,1,2,3,3,4,4};
	static unsigned long ip[MAXDIM+1]={0,0,1,1,2,1,4};
	static unsigned long iv[MAXDIM*MAXBIT+1]={
		0,1,1,1,1,1,1,3,1,3,3,1,1,5,7,7,3,3,5,15,11,5,15,13,9};
	
	static int initDone=0;
	char buf[256];

	int n=0;
	double *x;		//output x vector
	
	// check for all of the required waves
	if (p->bwavH == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
    //check to see that all are double
	if(WaveType(p->bwavH) != NT_FP64 ) {
        SetNaN64(&p->result);
        return kExpectedNT_FP64;
    }
 	x = WaveData(p->bwavH);
	n = (int)(p->nIn);			// not sure that the negative input will be properly cast to int
	
//	sprintf(buf, "input, recast n = %g  %d\r",p->nIn, n);
//	XOPNotice(buf);
	
	if (n < 0) {
		
		if(initDone) {
			sprintf(buf, "Don't re-initialize\r");
			XOPNotice(buf);
			return 0;
		}
		
		for (j=1,k=0;j<=MAXBIT;j++,k+=MAXDIM) iu[j] = &iv[k];
		for (k=1;k<=MAXDIM;k++) {
			for (j=1;j<=mdeg[k];j++) iu[j][k] <<= (MAXBIT-j);
			for (j=mdeg[k]+1;j<=MAXBIT;j++) {
				ipp=ip[k];
				i=iu[j-mdeg[k]][k];
				i ^= (i >> mdeg[k]);
				for (l=mdeg[k]-1;l>=1;l--) {
					if (ipp & 1) i ^= iu[j-l][k];
					ipp >>= 1;
				}
				iu[j][k]=i;
			}
		}
		fac=1.0/(1L << MAXBIT);
		in=0;
		
		initDone=1;
		
		sprintf(buf, "Initialization loop done\r");
		XOPNotice(buf);
		
	} else {
		im=in;
		for (j=1;j<=MAXBIT;j++) {
			if (!(im & 1)) break;
			im >>= 1;
		}
		if (j > MAXBIT) {
			sprintf(buf, "MAXBIT too small in sobseq\r");
			XOPNotice(buf);
		}
		im=(j-1)*MAXDIM;
		for (k=1;k<=IMIN(n,MAXDIM);k++) {
			ix[k] ^= iv[im+k];
			x[k-1]=ix[k]*fac;			/// this is a real array to send back, count this one from zero
			//sprintf(buf, "calculate x[%d] = %g\r",k,ix[k]*fac);
			//XOPNotice(buf);
		}
		in++;
	}
	
//	sprintf(buf, "x[0],x[1] = %g  %g\r",x[0],x[1]);
//	XOPNotice(buf);

	
	p->result = 0;
	
    return 0;
}

#undef MAXBIT
#undef MAXDIM


//#pragma XOP_RESET_STRUCT_PACKING			// All structures are 2-byte-aligned.
