// header for SphereFit.c

#include "XOPStructureAlignmentTwoByte.h"

/* structs */
typedef struct DiamParams{
	double p2;
	double p1;
	double result;
}DiamParams, *DiamParamsPtr;

#include "XOPStructureAlignmentReset.h"

/* IGOR Fit Functions */
int HardSphereStructX(FitParamsPtr p);
int SquareWellStructX(FitParamsPtr p);
int StickyHS_StructX(FitParamsPtr p);
int HayterPenfoldMSAX(FitParamsPtr p);
int DiamCylX(DiamParamsPtr p);
int DiamEllipX(DiamParamsPtr p);