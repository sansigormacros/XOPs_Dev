// header for SphereFit.c

#pragma pack(2)

/* structs */
typedef struct DiamParams{
	double p2;
	double p1;
	double result;
}DiamParams, *DiamParamsPtr;

typedef struct FitParams_Yuk {
	waveHndl SQHandle;				// Sq returned as a wave.
	waveHndl QHandle;				//independent variable, Q
	waveHndl CoefHandle;	// Coefficient wave.
	double retVal;
} FitParams_Yuk, *FitParamsPtr_Yuk;


#pragma pack()

/* IGOR Fit Functions */
int HardSphereStructX(FitParamsPtr p);
int SquareWellStructX(FitParamsPtr p);
int StickyHS_StructX(FitParamsPtr p);
int HayterPenfoldMSAX(FitParamsPtr p);
int DiamCylX(DiamParamsPtr p);
int DiamEllipX(DiamParamsPtr p);

// two-Yukawa SQ
int	OneYukawaX(FitParamsPtr_Yuk p);
int	TwoYukawaX(FitParamsPtr_Yuk p);