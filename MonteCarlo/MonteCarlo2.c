/*
 *  MonteCarlo.c
 *  SANSAnalysis
 *
 *  Created by Steve Kline on 10/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "MonteCarlo.h"

static int gCallSpinProcess = 1;		// Set to 1 to all user abort (cmd dot) and background processing.

//////////
//    PROGRAM Monte_SANS
//    PROGRAM simulates multiple SANS.
//       revised 2/12/99  JGB
//	      added calculation of random deviate, and 2D 10/2008 SRK

//    N1 = NUMBER OF INCIDENT NEUTRONS.
//    N2 = NUMBER INTERACTED IN THE SAMPLE.
//    N3 = NUMBER ABSORBED.
//    THETA = SCATTERING ANGLE.

// works fine in the single-threaded case.
//
/// currently crashes if threaded. apparently something here is either doing an unknown callback, or is accessing
// a bad place in memory. 
//
// the operations SpinProcess() and WaveHandleModified() are callbacks and MUST be commented out before threading.
// - some locks are non-existent
// - supposedly safe wave access routines are used
//
// random number generators are not thread-safe, and can give less than random results, but is this enough to crash?
// -- a possible workaround is to define multiple versions (poor man's threading)
//
//
//

// version X uses ran3
// version X2 uses ran1

int
Monte_SANSX2(MC_ParamsPtr p) {
	double *inputWave;				/* pointer to double precision wave data */
	double *ran_dev;				/* pointer to double precision wave data */
	double *nt;				/* pointer to double precision wave data */
	double *j1;				/* pointer to double precision wave data */
	double *j2;				/* pointer to double precision wave data */
	double *nn;				/* pointer to double precision wave data */
//	double *MC_linear_data;				/* pointer to double precision wave data */
	double *results;				/* pointer to double precision wave data */
	double result;				//return value

	long imon;
	double r1,r2,xCtr,yCtr,sdd,pixSize,thick,wavelength,sig_incoh,sig_sas;
	long ind,index,n_index;
	double qmax,theta_max,q0,zpow;
	long n1,n2,n3;
	double dth,zz,xx,yy,phi;
	double theta,ran,ll,rr,ttot;
	long done,find_theta,err;		//used as logicals
	long xPixel,yPixel;
	double vx,vy,vz,theta_z;
	double sig_abs,ratio,sig_total;
	double testQ,testPhi,left,delta,dummy,pi;
	double sigabs_0,num_bins;
	long NSingleIncoherent,NSingleCoherent,NScatterEvents,incoherentEvent,coherentEvent;
	long NDoubleCoherent,NMultipleScatter,isOn,xCtr_long,yCtr_long;
	long NMultipleCoherent,NCoherentEvents;


	// for accessing the 2D wave data, direct method (see the WaveAccess example XOP)
	waveHndl wavH;
	int waveType,hState;
	long numDimensions;
	long dimensionSizes[MAX_DIMENSIONS+1];
	char* dataStartPtr;
	long dataOffset;
	long numRows, numColumns,numRows_ran_dev;
	double *dp0, *dp, value[2];				// Pointers used for double data.
	long seed;
	long indices[MAX_DIMENSIONS];
	
	char buf[256];
		
	/* check that wave handles are all valid */
	if (p->inputWaveH == NIL) {
		SetNaN64(&p->result);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->ran_devH == NIL) {
		SetNaN64(&p->result);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}	
	if (p->ntH == NIL) {
		SetNaN64(&p->result);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->j1H == NIL) {
		SetNaN64(&p->result);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->j2H == NIL) {
		SetNaN64(&p->result);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->nnH == NIL) {
		SetNaN64(&p->result);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->MC_linear_dataH == NIL) {
		SetNaN64(&p->result);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->resultsH == NIL) {
		SetNaN64(&p->result);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	
	p->result = 0;
	
// trusting that all inputs are DOUBLE PRECISION WAVES!!!
	inputWave = WaveData(p->inputWaveH);
	ran_dev = WaveData(p->ran_devH);
	nt = WaveData(p->ntH);
	j1 = WaveData(p->j1H);
	j2 = WaveData(p->j2H);
	nn = WaveData(p->nnH);
//	MC_linear_data = WaveData(p->MC_linear_dataH);
	results = WaveData(p->resultsH);
	
	seed = (long)results[0];
	
//	sprintf(buf, "input seed = %ld\r", seed);
//	XOPNotice(buf);
	
	if(seed >= 0) {
		seed = -1234509876;
	}

	dummy = ran1(&seed);		//initialize the random sequence by passing in a negative value
	seed = 12348765;		//non-negative after that does nothing

	imon = (int)inputWave[0];
	r1 = inputWave[1];
	r2 = inputWave[2];
	xCtr = inputWave[3];
	yCtr = inputWave[4];
	sdd = inputWave[5];
	pixSize = inputWave[6];
	thick = inputWave[7];
	wavelength = inputWave[8];
	sig_incoh = inputWave[9];
	sig_sas = inputWave[10];
	xCtr_long = round(xCtr);
	yCtr_long = round(yCtr);
	
	dummy = MDGetWaveScaling(p->ran_devH, 0, &delta, &left);		//0 is the rows
	if (result = MDGetWaveDimensions(p->ran_devH, &numDimensions, dimensionSizes))
		return result;
	numRows_ran_dev = dimensionSizes[0];
	
	pi = 4.0*atan(1.0);	
	
	// access the 2D wave data for writing using the direct method
	wavH = p->MC_linear_dataH;
	if (wavH == NIL)
		return NOWAV;

//	waveType = WaveType(wavH);
//	if (waveType & NT_CMPLX)
//		return NO_COMPLEX_WAVE;
//	if (waveType==TEXT_WAVE_TYPE)
//		return NUMERIC_ACCESS_ON_TEXT_WAVE;
//	if (result = MDGetWaveDimensions(wavH, &numDimensions, dimensionSizes))
//		return result;
//	numRows = dimensionSizes[0];
//	numColumns = dimensionSizes[1];
	
//	if (result = MDAccessNumericWaveData(wavH, kMDWaveAccessMode0, &dataOffset))
//		return result;
		
//	hState = MoveLockHandle(wavH);		// So wave data can't move. Remember to call HSetState when done.
//	dataStartPtr = (char*)(*wavH) + dataOffset;
//	dp0 = (double*)dataStartPtr;			// Pointer to the start of the 2D wave data.
	
//scattering power and maximum qvalue to bin
//	zpow = .1		//scattering power, calculated below
	qmax = 4.0*pi/wavelength;	//maximum Q to bin 1D data. (A-1) (not really used)
	sigabs_0 = 0.0;		// ignore absorption cross section/wavelength [1/(cm A)]
	n_index = 50;	// maximum number of scattering events per neutron
	num_bins = 200;		//number of 1-D bins (not really used)
	
//c       total SAS cross-section
//
	zpow = sig_sas*thick;			//since I now calculate the sig_sas from the model
	sig_abs = sigabs_0 * wavelength;
	sig_total = sig_abs + sig_sas + sig_incoh;
//	Print "The TOTAL XSECTION. (CM-1) is ",sig_total
//	Print "The TOTAL SAS XSECTION. (CM-1) is ",sig_sas
//	results[0] = sig_total;
//	results[1] = sig_sas;
//	RATIO = SIG_ABS / SIG_TOTAL
	ratio = sig_incoh / sig_total;
	
	theta_max = wavelength*qmax/(2*pi);
//C     SET Theta-STEP SIZE.
	dth = theta_max/num_bins;
//	Print "theta bin size = dth = ",dth

//C     INITIALIZE COUNTERS.
	n1 = 0;
	n2 = 0;
	n3 = 0;
	NSingleIncoherent = 0;
	NSingleCoherent = 0;
	NDoubleCoherent = 0;
	NMultipleScatter = 0;
	NScatterEvents = 0;
	NMultipleCoherent = 0;
	NCoherentEvents = 0;
	
	isOn = 0;
	
//C     MONITOR LOOP - looping over the number of incedent neutrons
//note that zz, is the z-position in the sample - NOT the scattering power
// NOW, start the loop, throwing neutrons at the sample.
	do {
		////SpinProcess() IS A CALLBACK, and not good for Threading!
//		if ((n1 % 1000 == 0) && gCallSpinProcess && SpinProcess()) {		// Spins cursor and allows background processing.
//				result = -1;								// User aborted.
//				break;
//		}
	
		vx = 0.0;			// Initialize direction vector.
		vy = 0.0;
		vz = 1.0;
		
		theta = 0.0;		//	Initialize scattering angle.
		phi = 0.0;			//	Intialize azimuthal angle.
		n1 += 1;			//	Increment total number neutrons counter.
		done = 0;			//	True when neutron is absorbed or when  scattered out of the sample.
		index = 0;			//	Set counter for number of scattering events.
		zz = 0.0;			//	Set entering dimension of sample.
		incoherentEvent = 0;
		coherentEvent = 0;
		
		do	{				//	Makes sure position is within circle.
			ran = ran1(&seed);		//[0,1]
			xx = 2.0*r1*(ran-0.5);		//X beam position of neutron entering sample.
			ran = ran1(&seed);		//[0,1]
			yy = 2.0*r1*(ran-0.5);		//Y beam position ...
			rr = sqrt(xx*xx+yy*yy);		//Radial position of neutron in incident beam.
		} while(rr>r1);

		do {   //Scattering Loop, will exit when "done" == 1
				// keep scattering multiple times until the neutron exits the sample
			ran = ran1(&seed);		//[0,1]  RANDOM NUMBER FOR DETERMINING PATH LENGTH
			ll = path_len(ran,sig_total);
			//Determine new scattering direction vector.
			err = NewDirection(&vx,&vy,&vz,theta,phi);		//vx,vy,vz updated, theta, phi unchanged by function
									
			//X,Y,Z-POSITION OF SCATTERING EVENT.
			xx += ll*vx;
			yy += ll*vy;
			zz += ll*vz;
			rr = sqrt(xx*xx+yy*yy);		//radial position of scattering event.

			//sprintf(buf, "xx,yy,zz,vx,vy,vz,ll = %g %g %g %g %g %g %g\r",xx,yy,zz,vx,vy,vz,ll);
			//XOPNotice(buf);
						
			//Check whether interaction occurred within sample volume.
			if (((zz > 0.0) && (zz < thick)) && (rr < r2)) {
				//NEUTRON INTERACTED.
				//sprintf(buf,"neutron interacted\r");
				//XOPNotice(buf);
				
				index += 1;			//Increment counter of scattering events.
				if (index == 1) {
					n2 += 1; 		//Increment # of scat. neutrons
				}
				ran = ran1(&seed);		//[0,1]
				//Split neutron interactions into scattering and absorption events
				if (ran > ratio ) {		//C             NEUTRON SCATTERED coherently
					//sprintf(buf,"neutron scatters coherently\r");
					//XOPNotice(buf);
					coherentEvent += 1;
					find_theta = 0;			//false
					do {
						// pick a q-value from the deviate function
						// pnt2x truncates the point to an integer before returning the x
						// so get it from the wave scaling instead
//						q0 =left + binarysearchinterp(ran_dev,ran1(seed))*delta;
						
						q0 =left + locate_interp(ran_dev,numRows_ran_dev,ran1(&seed))*delta;
						theta = q0/2/pi*wavelength;		//SAS approximation
						
						find_theta = 1;		//always accept

						//sprintf(buf, "after locate_interp call q0 = %g, theta = %g,left = %g,delta = %g\r",q0,theta,left,delta);
						//XOPNotice(buf);

					} while(!find_theta);
					
					ran = ran1(&seed);		//[0,1]
					phi = 2.0*pi*ran;			//Chooses azimuthal scattering angle.
				} else {
					//NEUTRON scattered incoherently
					//sprintf(buf,"neutron scatters incoherent\r");
					//XOPNotice(buf);
					incoherentEvent += 1;
				  // phi and theta are random over the entire sphere of scattering
					// !can't just choose random theta and phi, won't be random over sphere solid angle

					ran = ran1(&seed);		//[0,1]
					theta = acos(2.0*ran-1);
           	  	
					ran = ran1(&seed);		//[0,1]
					phi = 2.0*pi*ran;			//Chooses azimuthal scattering angle.
				}		//(ran > ratio)
			} else {
				//NEUTRON ESCAPES FROM SAMPLE -- bin it somewhere								
				done = 1;		//done = true, will exit from loop
				//Increment #scattering events array
				MemClear(indices, sizeof(indices)); // Must be 0 for unused dimensions.
				indices[0] =index;			//this sets access to nn[index]
				if (index <= n_index) {
					if (result = MDGetNumericWavePointValue(p->nnH, indices, value))
						return result;
					value[0] += 1; // add one to the value
					if (result = MDSetNumericWavePointValue(p->nnH, indices, value))
						return result;
				//	nn[index] += 1;
				}
												
				if( index != 0) {		//neutron was scattered, figure out where it went
					theta_z = acos(vz);		// Angle (= 2theta) WITH respect to z axis.
					testQ = 2*pi*sin(theta_z)/wavelength;
					
					// pick a random phi angle, and see if it lands on the detector
					// since the scattering is isotropic, I can safely pick a new, random value
					// this would not be true if simulating anisotropic scattering.
					testPhi = ran1(&seed)*2*pi;
					
					// is it on the detector?	
					FindPixel(testQ,testPhi,wavelength,sdd,pixSize,xCtr,yCtr,&xPixel,&yPixel);
													
					if(xPixel != -1 && yPixel != -1) {
						isOn += 1;
						MemClear(indices, sizeof(indices)); // Must be 0 for unused dimensions.
						indices[0] = xPixel;
						indices[1] = yPixel;
						if (result = MDGetNumericWavePointValue(wavH, indices, value))
							return result;
						value[0] += 1; // Real part
						if (result = MDSetNumericWavePointValue(wavH, indices, value))
							return result;
						//if(index==1)  // only the single scattering events
							//dp = dp0 + xPixel + yPixel*numColumns;		//offset the pointer to the exact memory location
							//*dp += 1;		//increment the value there
						//endif
					}
					

	/*		is this causing me a problem since I'm not locking these? Probably not, since it crashes even if I comment these out... */
					if(theta_z < theta_max) {
						//Choose index for scattering angle array.
						//IND = NINT(THETA_z/DTH + 0.4999999)
						ind = round(theta_z/dth + 0.4999999);		//round is eqivalent to nint()
						nt[ind] += 1; 			//Increment bin for angle.
						//Increment angle array for single scattering events.
						if (index == 1) {
							j1[ind] += 1;
						}
						//Increment angle array for double scattering events.
						if (index == 2) {
							j2[ind] += 1;
						}
					}
	/**/
					
					// increment all of the counters now since done==1 here and I'm sure to exit and get another neutron
					NScatterEvents += index;		//total number of scattering events
					if(index == 1 && incoherentEvent == 1) {
						NSingleIncoherent += 1;
					}
					if(index == 1 && coherentEvent == 1) {
						NSingleCoherent += 1;
					}
					if(index == 2 && coherentEvent == 1 && incoherentEvent == 0) {
						NDoubleCoherent += 1;
					}
					if(index > 1) {
						NMultipleScatter += 1;
					}
					if(coherentEvent >= 1 && incoherentEvent == 0) {
						NCoherentEvents += 1;
					}
					if(coherentEvent > 1 && incoherentEvent == 0) {
						NMultipleCoherent += 1;
					}

				} else {	// index was zero, neutron must be transmitted, so just increment the proper counters and data
						isOn += 1;
						nt[0] += 1;
						MemClear(indices, sizeof(indices)); // Must be 0 for unused dimensions.
						//indices[0] = xCtr_long;		//don't put everything in one pixel
						//indices[1] = yCtr_long;
						indices[0] = (long)round(xCtr+xx/pixSize);
						indices[1] = (long)round(yCtr+yy/pixSize);
						// check for valid indices - got an XOP error, probably from here
						if(indices[0] > 127) indices[0] = 127;
						if(indices[0] < 0) indices[0] = 0;
						if(indices[1] > 127) indices[1] = 127;
						if(indices[1] < 0) indices[1] = 0;
						
						if (result = MDGetNumericWavePointValue(wavH, indices, value))
							return result;
						value[0] += 1; // Real part
						if (result = MDSetNumericWavePointValue(wavH, indices, value))
							return result;
					}	
			}
		 } while (!done);
	} while(n1 < imon);
	
// assign the results to the wave

	MemClear(indices, sizeof(indices)); // Must be 0 for unused dimensions.
	value[0] = (double)n1;
	indices[0] = 0;
	if (result = MDSetNumericWavePointValue(p->resultsH, indices, value))
		return result;
	value[0] = (double)n2;
	indices[0] = 1;
	if (result = MDSetNumericWavePointValue(p->resultsH, indices, value))
		return result;
	value[0] = (double)isOn;
	indices[0] = 2;
	if (result = MDSetNumericWavePointValue(p->resultsH, indices, value))
		return result;
	value[0] = (double)NScatterEvents;
	indices[0] = 3;
	if (result = MDSetNumericWavePointValue(p->resultsH, indices, value))
		return result;
	value[0] = (double)NSingleCoherent;
	indices[0] = 4;
	if (result = MDSetNumericWavePointValue(p->resultsH, indices, value))
		return result;
	value[0] = (double)NMultipleCoherent;
	indices[0] = 5;
	if (result = MDSetNumericWavePointValue(p->resultsH, indices, value))
		return result;
	value[0] = (double)NMultipleScatter;
	indices[0] = 6;
	if (result = MDSetNumericWavePointValue(p->resultsH, indices, value))
		return result;	
	value[0] = (double)NCoherentEvents;
	indices[0] = 7;
	if (result = MDSetNumericWavePointValue(p->resultsH, indices, value))
		return result;

//	HSetState((Handle)wavH, hState);		//release the handle of the 2D data wave
//	WaveHandleModified(wavH);			// Inform Igor that we have changed the wave. (CALLBACK! needed, but not allowed in Threading)
	
	return(0);
}
////////	end of main function for calculating multiple scattering

