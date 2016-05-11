/*
 *  Metropolis.c
 *  SANSAnalysis
 *
 *  Created by Steve Kline on 10/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "Metropolis.h"
#include "MonteCarlo.h"


int
MetropolisX(Metropolis_ParamsPtr p) {
	double *UofR;				/* pointer to double precision wave data */
	double *xx;				/* pointer to double precision wave data */
	double *yy;				/* pointer to double precision wave data */
	double *zz;				/* pointer to double precision wave data */
	double *energy;				/* pointer to double precision wave data */
//	double radius;				
	double tVox;				
	CountInt nVox;                  // these are declared double in the struct definition!
	CountInt numIter;
	CountInt gCount;
//	double retVal;				//return value
	
	// for accessing the wave data, direct method (see the WaveAccess example XOP)
//	waveHndl wavH;
	
	CountInt jj,kk,num,good;
	double Uold,Unew;
	double step,delta,bolt;
	double ratio,finalEnergy;
    CountInt xnew,ynew,znew;
	float ran;
	SInt32 seed;
	
	char buf[256];
		

	/* check that wave handles are all valid */
	if (p->UofRH == NIL) {
		SetNaN64(&p->retVal);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->xxH == NIL) {
		SetNaN64(&p->retVal);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}	
	if (p->yyH == NIL) {
		SetNaN64(&p->retVal);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->zzH == NIL) {
		SetNaN64(&p->retVal);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	if (p->energyH == NIL) {
		SetNaN64(&p->retVal);					/* return NaN if wave is not valid */
		return(NON_EXISTENT_WAVE);
	}
	
	p->retVal = 0.0;
	
// trusting that all inputs are double PRECISION WAVES!!!
	UofR = (double*)WaveData(p->UofRH);
	xx = (double*)WaveData(p->xxH);
	yy = (double*)WaveData(p->yyH);
	zz = (double*)WaveData(p->zzH);
	energy = (double*)WaveData(p->energyH);
	
	//input variables
	tVox = (double)p->tVox;
	nVox = (CountInt)(p->nVox);
	numIter = (CountInt)(p->nIter);
	gCount = (CountInt)(p->gCount);
	
	num = WavePoints(p->xxH);		//number of points in x,y,z
	
	seed = (SInt32)energy[0];			// pick up a seed from somewhere
	
//		sprintf(buf, "XOP number of points = %lld\r", (SInt64)num);
//		XOPNotice(buf);
	
	if(seed >= 0) {
		seed = -1234509876;
	}
	
	ran = ran3(&seed);		//initialize the random sequence by passing in a negative value
	seed = 12348765;		//non-negative after that does nothing
	
	good = 0;		// # of accepted moves
	
	step = tVox;		//default step?? should this be in terms of radius?
	
	// do some number of iterations (kk)
	for(kk=0;kk<numIter;kk+=1) {
	//at each iteration, loop over all of the particles
		if( (kk*10 % numIter) == 0) {
			sprintf(buf, "Iteration %lld of %lld\r", (SInt64)kk,(SInt64)numIter);
			XOPNotice(buf);
		}
			
		good = 0;		//re-initialize the number of good moves
			
		for(jj=0;jj<num;jj+=1) {
				
			//if(mod(jj, num/100 ) == 0)
			//	Print "sphere = ",jj," of ",num
			//endif
				
			// 2- calculate the initial energy
			Uold = M_energy(UofR,xx,yy,zz,tVox,nVox,xx[jj],yy[jj],zz[jj],jj,num);
				
			// 3- move a sphere randomly (allow fractional positions at this point)
			//displacement d=(ran - 0.5)*dmax in each xyz. this gives forward or backward steps. 
			// ran is from 0,1
			ran = ran3(&seed);
			xnew = (CountInt)MC_round(xx[jj] + ((double)ran-0.5)*step); // double new x coordinate for j-particle
			ran = ran3(&seed);	
			ynew = (CountInt)MC_round(yy[jj] + ((double)ran-0.5)*step); // new y coordinate for j-particle
			ran = ran3(&seed);
			znew = (CountInt)MC_round(zz[jj] + ((double)ran-0.5)*step); // new z coordinate for j-particle
				
			// nix the fractional positions -- gives misleading energy calculations, esp. with hard spheres			
			// test point converted to round above
				
			// enforce in-bounds (periodic)
			if( (xnew>=nVox) || (xnew<0) ) {
				xnew = labs(nVox - labs(xnew));
				}
			if( (ynew>=nVox) || (ynew<0) ) {
				ynew = labs(nVox - labs(ynew));
			}
			if( (znew>=nVox) || (znew<0) ) {
				znew = labs(nVox - labs(znew));
			}
							
			// 4- calculate the new energy
			Unew = M_energy(UofR,xx,yy,zz,tVox,nVox,xnew,ynew,znew,jj,num);
			
			// 5- decide whether to accept the move:
			//		if dU <(=?) 0, accept the move
			//		if dU > 0, calculate W=exp(-dU)
			//		then if random num > W, accept new configuration	
			// 6- update the current energy, go back to step 3 and repeat
			
			delta = Unew-Uold;
			/*
			if( (kk*10 % numIter) == 0 && jj==0) {
				sprintf(buf, "XOP delta = %lf\r", delta);
				XOPNotice(buf);
			}
			 */
			if(delta <= 0) {
				//move is good
				Uold = Unew;
				xx[jj] = (double)xnew;
				yy[jj] = (double)ynew;
				zz[jj] = (double)znew;
				good += 1;
			} else {
				bolt = exp(-delta);
				ran = ran3(&seed);
				if ((double)ran < bolt)	 {	// accept anyways
					xx[jj] = (double)xnew; 
					yy[jj] = (double)ynew; 
					zz[jj] = (double)znew;
					good += 1;
					Uold = Unew;
				}
			}
										
		}		//jj loop over particles
										
		// calculate the final total energy after each pass, and save it
		if( (kk*10 % numIter) == 0) {
			finalEnergy=M_TotalEnergy(UofR,xx,yy,zz,tVox,nVox,num);
			energy[gCount+kk+1] = finalEnergy;
		}
											
		// calculate the fraction of accepted moves
		ratio = (double)good/(double)num*100;
											
		if (ratio > 50.0) { //! adjust the step for randomization
			step = step*1.05;
			if (step > 2*tVox) {
				step = 2*tVox;
			}
		} else {
			step = step*0.95;
			if (step < 0.1*tVox) {
				step = 0.1*tVox;
			}
		} //! end adjust the step for randomization

		/*
		if( (kk*10 % numIter) == 0) {
			sprintf(buf, "XOP percent of accepted moves = %lf\r", ratio);
			XOPNotice(buf);
			sprintf(buf, "XOP step = %lf\r", step);
			XOPNotice(buf);
		}
		 */

							
	}		//kk total iterations
	
	finalEnergy=M_TotalEnergy(UofR,xx,yy,zz,tVox,nVox,num);
	sprintf(buf, "XOP final energy = %lf\r", finalEnergy);
	XOPNotice(buf);
	return(0);
}



// total energy of the system - without double counting
double
M_TotalEnergy(double ur[], double xx[], double yy[], double zz[], double tVox, CountInt nVox, CountInt num) {

	IndexInt ii,jj;
	double energy,dx,dy,dz,dist;

	energy=0;

	for(ii=0;ii<num;ii+=1) {
		for(jj=ii+1;jj<num;jj+=1) {
			dx = xx[jj] - xx[ii]; //! calculates distance
			if(fabs(dx) > nVox/2) {
				dx = (nVox-1) - fabs(dx);		//enforce periodic conditions
			}

			dy = yy[jj] - yy[ii]; //! calculates distance 
			if(fabs(dx) > nVox/2) {
				dy = (nVox-1) - fabs(dy);		//enforce periodic conditions
			}

			dz = zz[jj] - zz[ii]; //! calculates distance 
			if(fabs(dz) > nVox/2) {
				dz = (nVox-1) - fabs(dz);		//enforce periodic conditions
			}

			dist = sqrt(dx*dx+dy*dy+dz*dz);// ! distance (in box units)
			dist *= tVox;		//real units

	//			energy += UofR[round(dist/tVox)] 		 //! calc. the energy		
			energy += ur[MC_round(dist)]; 		 //! calc. the energy		

		}
	}

	return(energy);
}




double
M_energy(double ur[], double xx[], double yy[], double zz[], double tVox, CountInt nVox, double rx, double ry, double rz, CountInt jj,CountInt num)
{
	IndexInt ii;
	double dx,dy,dz,dist,energy;

	energy = 0.0; //! initial energy of 0.0

	for(ii=0;ii<num;ii+=1) {
		if (ii != jj)  {		//! if i and j are the same point then skip
			
			dx = rx - xx[ii]; //! calculates distance
			if(fabs(dx) > nVox/2) {
				dx = (nVox-1) - fabs(dx);		//enforce periodic conditions
			}

			dy = ry - yy[ii]; //! calculates distance 
			if(fabs(dy) > nVox/2) {
				dy = (nVox-1) - fabs(dy);	//enforce periodic conditions
			}

			dz = rz - zz[ii]; //! calculates distance 
			if(fabs(dz) > nVox/2) {
				dz = (nVox-1) - fabs(dz);		//enforce periodic conditions
			}

			dist = sqrt(dx*dx+dy*dy+dz*dz);// ! distance (in box units)
			dist *= tVox;		//real units

			//			energy += UofR[round(dist/tVox)] 		 //! calc. the energy
			energy += ur[MC_round(dist)]; 		 //! calc. the energy
		}
	}

	return(energy);
} 
