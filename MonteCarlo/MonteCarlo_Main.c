/*
 *  MonteCarlo_Main.c
 *  SANSMonteCarlo
 *
 *  Created by Steve Kline on 7/1/10.
 *  Copyright 2010 NIST. All rights reserved.
 *
 */

// Contains all of the XOP entry points
// contains all of the RNG definitions
// contains all of the utility functions required by Monte Carlo instances

#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "MonteCarlo.h"
#include "DebyeSpheres.h"

int
FindPixel(double testQ, double testPhi, double lam, double sdd,
		  double pixSize, double xCtr, double yCtr, long *xPixel, long *yPixel) {
	
	double theta,dy,dx,qx,qy,pi;
	pi = 4.0*atan(1.0);	
	//decompose to qx,qy
	qx = testQ*cos(testPhi);
	qy = testQ*sin(testPhi);
	
	//convert qx,qy to pixel locations relative to # of pixels x, y from center
	theta = 2.0*asin(qy*lam/4.0/pi);
	dy = sdd*tan(theta);
	*yPixel = lround(yCtr + dy/pixSize);		//corrected 7/2010 to round away from zero, to avoid 2x counts in row 0 and column 0
	
	theta = 2.0*asin(qx*lam/4.0/pi);
	dx = sdd*tan(theta);
	*xPixel = lround(xCtr + dx/pixSize);
	
	//if on detector, return xPix and yPix values, otherwise -1
	if(*yPixel > 127 || *yPixel < 0) {
		*yPixel = -1;
	}
	if(*xPixel > 127 || *xPixel < 0) {
		*xPixel = -1;
	}
	
	return(0);
}


//calculates new direction (xyz) from an old direction
//theta and phi don't change
int
NewDirection(double *vx, double *vy, double *vz, double theta, double phi) {
	
	int err=0;
	double vx0,vy0,vz0;
	double nx,ny,mag_xy,tx,ty,tz;
	
	//store old direction vector
	vx0 = *vx;
	vy0 = *vy;
	vz0 = *vz;
	
	mag_xy = sqrt(vx0*vx0 + vy0*vy0);
	if(mag_xy < 1e-12) {
		//old vector lies along beam direction
		nx = 0;
		ny = 1;
		tx = 1;
		ty = 0;
		tz = 0;
	} else {
		nx = -vy0 / mag_xy;
		ny = vx0 / mag_xy;
		tx = -vz0*vx0 / mag_xy;
		ty = -vz0*vy0 / mag_xy;
		tz = mag_xy ;
	}
	
	//new scattered direction vector
	*vx = cos(phi)*sin(theta)*tx + sin(phi)*sin(theta)*nx + cos(theta)*vx0;
	*vy = cos(phi)*sin(theta)*ty + sin(phi)*sin(theta)*ny + cos(theta)*vy0;
	*vz = cos(phi)*sin(theta)*tz + cos(theta)*vz0;
	
	return(err);
}

double
path_len(double aval, double sig_tot) {
	
	double retval;
	
	retval = -1.0*log(1.0-aval)/sig_tot;
	
	return(retval);
}


#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

float ran1(long *idum)
{
	int j;
	long k;
	static long iy=0;
	static long iv[NTAB];
	float temp;
	
	if (*idum <= 0 || !iy) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(*idum)/IQ;
			*idum=IA*(*idum-k*IQ)-IR*k;
			if (*idum < 0) *idum += IM;
			if (j < NTAB) iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ;
	*idum=IA*(*idum-k*IQ)-IR*k;
	if (*idum < 0) *idum += IM;
	j=iy/NDIV;
	iy=iv[j];
	iv[j] = *idum;
	if ((temp=AM*iy) > RNMX) return RNMX;
	else return temp;
}
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX


//////////a complete copy of ran1(), simply renamed ran1a()
#define IA2 16807
#define IM2 2147483647
#define AM2 (1.0/IM2)
#define IQ2 127773
#define IR2 2836
#define NTAB2 32
#define NDIV2 (1+(IM2-1)/NTAB2)
#define EPS2 1.2e-7
#define RNMX2 (1.0-EPS2)

float ran1a(long *idum)
{
	int j;
	long k;
	static long iy=0;
	static long iv[NTAB2];
	float temp;
	
	if (*idum <= 0 || !iy) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		for (j=NTAB2+7;j>=0;j--) {
			k=(*idum)/IQ2;
			*idum=IA2*(*idum-k*IQ2)-IR2*k;
			if (*idum < 0) *idum += IM2;
			if (j < NTAB2) iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ2;
	*idum=IA2*(*idum-k*IQ2)-IR2*k;
	if (*idum < 0) *idum += IM2;
	j=iy/NDIV2;
	iy=iv[j];
	iv[j] = *idum;
	if ((temp=AM2*iy) > RNMX2) return RNMX2;
	else return temp;
}
#undef IA2
#undef IM2
#undef AM2
#undef IQ2
#undef IR2
#undef NTAB2
#undef NDIV2
#undef EPS2
#undef RNMX2
///////////////


////////////////////////
#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)

float ran3(long *idum)
{
	static int inext,inextp;
	static long ma[56];
	static int iff=0;
	long mj,mk;
	int i,ii,k;
	
	if (*idum < 0 || iff == 0) {
		iff=1;
		mj=MSEED-(*idum < 0 ? -*idum : *idum);
		mj %= MBIG;
		ma[55]=mj;
		mk=1;
		for (i=1;i<=54;i++) {
			ii=(21*i) % 55;
			ma[ii]=mk;
			mk=mj-mk;
			if (mk < MZ) mk += MBIG;
			mj=ma[ii];
		}
		for (k=1;k<=4;k++)
			for (i=1;i<=55;i++) {
				ma[i] -= ma[1+(i+30) % 55];
				if (ma[i] < MZ) ma[i] += MBIG;
			}
		inext=0;
		inextp=31;
		*idum=1;
	}
	if (++inext == 56) inext=1;
	if (++inextp == 56) inextp=1;
	mj=ma[inext]-ma[inextp];
	if (mj < MZ) mj += MBIG;
	ma[inext]=mj;
	return mj*FAC;
}
#undef MBIG
#undef MSEED
#undef MZ
#undef FAC

//////////////////////// a complete copy of ran3() renamed ran3a()
#define MBIG2 1000000000
#define MSEED2 161803398
#define MZ2 0
#define FAC2 (1.0/MBIG2)

float ran3a(long *idum)
{
	static int inext,inextp;
	static long ma[56];
	static int iff=0;
	long mj,mk;
	int i,ii,k;
	
	if (*idum < 0 || iff == 0) {
		iff=1;
		mj=MSEED2-(*idum < 0 ? -*idum : *idum);
		mj %= MBIG2;
		ma[55]=mj;
		mk=1;
		for (i=1;i<=54;i++) {
			ii=(21*i) % 55;
			ma[ii]=mk;
			mk=mj-mk;
			if (mk < MZ2) mk += MBIG2;
			mj=ma[ii];
		}
		for (k=1;k<=4;k++)
			for (i=1;i<=55;i++) {
				ma[i] -= ma[1+(i+30) % 55];
				if (ma[i] < MZ2) ma[i] += MBIG2;
			}
		inext=0;
		inextp=31;
		*idum=1;
	}
	if (++inext == 56) inext=1;
	if (++inextp == 56) inextp=1;
	mj=ma[inext]-ma[inextp];
	if (mj < MZ2) mj += MBIG2;
	ma[inext]=mj;
	return mj*FAC2;
}
#undef MBIG2
#undef MSEED2
#undef MZ2
#undef FAC2


// returns the interpolated point value in xx[0,n-1] that has the value x
double locate_interp(double xx[], long n, double x)
{
	unsigned long ju,jm,jl,j;
	int ascnd;
	double pt;
	
	//	char buf[256];
	
	jl=0;
	ju=n-1;
	ascnd=(xx[n-1] > xx[0]);
	while (ju-jl > 1) {
		jm=(ju+jl) >> 1;
		if (x > xx[jm] == ascnd)
			jl=jm;
		else
			ju=jm;
	}
	j=jl;		// the point I want is between xx[j] and xx[j+1]
	pt = (x- xx[j])/(xx[j+1] - xx[j]);		//fractional distance, using linear interpolation
	
	//	sprintf(buf, "x = %g, j= %ld, pt = %g\r",x,j,pt);
	//	XOPNotice(buf);
	
	return(pt+(double)j);
}




/////////////////////////////
/*	RegisterFunction()
 
 Igor calls this at startup time to find the address of the
 XFUNCs added by this XOP. See XOP manual regarding "Direct XFUNCs".
 */
static long
RegisterFunction()
{
	int funcIndex;
	
	funcIndex = GetXOPItem(0);		// Which function is Igor asking about?
	switch (funcIndex) {
		case 0:						// 
			return((long)Monte_SANSX);
			break;
		case 1:						// 
			return((long)Monte_SANSX2);
			break;
		case 2:						// 
			return((long)DebyeSpheresX);
			break;
		case 3:						// 
			return((long)Monte_SANSX3);
			break;
		case 4:						// 
			return((long)Monte_SANSX4);
			break;
	}
	return(NIL);
}

/*	XOPEntry()
 
 This is the entry point from the host application to the XOP for all messages after the
 INIT message.
 */
static void
XOPEntry(void)
{	
	long result = 0;
	
	switch (GetXOPMessage()) {
		case FUNCADDRS:
			result = RegisterFunction();
			break;
	}
	SetXOPResult(result);
}

/*	main(ioRecHandle)
 
 This is the initial entry point at which the host application calls XOP.
 The message sent by the host must be INIT.
 main() does any necessary initialization and then sets the XOPEntry field of the
 ioRecHandle to the address to be called for future messages.
 */
HOST_IMPORT void
main(IORecHandle ioRecHandle)
{	
	XOPInit(ioRecHandle);							// Do standard XOP initialization.
	SetXOPEntry(XOPEntry);							// Set entry point for future calls.
	
	if (igorVersion < 600)				// Requires Igor Pro 6.00 or later.
		SetXOPResult(OLD_IGOR);			// OLD_IGOR is defined in WaveAccess.h and there are corresponding error strings in WaveAccess.r and WaveAccessWinCustom.rc.
	else
		SetXOPResult(0L);
}
