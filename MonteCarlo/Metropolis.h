/*
 *  Metropolis.h
 *  SANSAnalysis
 *
 *  Created by Steve Kline on 7/15/14.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


// All structures passed to Igor are two-byte aligned.
#pragma pack(2)

struct Metropolis_Params {     // This structure must be 2-byte-aligned because it receives parameters from Igor.
	double gCount;
	double nIter;
	double nVox;
	double tVox;
	double radius;
	waveHndl energyH;
	waveHndl zzH;
	waveHndl yyH;
	waveHndl xxH;
	waveHndl UofRH;
	void* tp;				//unused void for ThreadSafe functions
	double retVal;		// return value is unused, save for error if needed
};
typedef struct Metropolis_Params Metropolis_Params;
typedef struct Metropolis_Params *Metropolis_ParamsPtr;

/*
struct MetroEnergy_Params {   
	double index;
	double rz;
	double ry;
	double rx;
	double nVox;
	double tVox;
	double radius;
	waveHndl zzH;
	waveHndl yyH;
	waveHndl xxH;
	waveHndl UofRH;
	void* tp;				
	double retVal;
};
typedef struct MetroEnergy_Params MetroEnergy_Params;
typedef struct MetroEnergy_Params *MetroEnergy_ParamsPtr;
*/

#pragma pack()		// return to default structure packing

// function prototypes - communicates w/Igor
int MetropolisX(Metropolis_ParamsPtr p);


// internal to the XOP
double M_energy(double ur[], double xx[], double yy[], double zz[], double tVox, CountInt nVox, double dx, double dy, double dz, CountInt jj, CountInt num);
double M_TotalEnergy(double ur[], double xx[], double yy[], double zz[], double tVox, CountInt nVox, CountInt num);
