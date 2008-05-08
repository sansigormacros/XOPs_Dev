/*	CylinderFit.c

A simplified project designed to act as a template for your curve fitting function.
The fitting function is a Cylinder form factor. No resolution effects are included (yet)
*/


#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "SANSAnalysis.h"
#include "libSANSAnalysis.h"
#include "Cylinder.h"


/*	CylinderFormX  :  calculates the form factor of a cylinder at the give x-value p->x

Warning:
The call to WaveData() below returns a pointer to the middle
of an unlocked Macintosh handle. In the unlikely event that your
calculations could cause memory to move, you should copy the coefficient
values to local variables or an array before such operations.
*/
int
CylinderFormX(FitParamsPtr p)
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
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = CylinderForm(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

/*	EllipCyl76X  :  calculates the form factor of a elliptical cylinder at the given x-value p->x

Uses 76 pt Gaussian quadrature for both integrals

Warning:
The call to WaveData() below returns a pointer to the middle
of an unlocked Macintosh handle. In the unlikely event that your
calculations could cause memory to move, you should copy the coefficient
values to local variables or an array before such operations.
*/
int
EllipCyl76X(FitParamsPtr p)
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
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = EllipCyl76(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

/*	EllipCyl20X  :  calculates the form factor of a elliptical cylinder at the given x-value p->x

Uses 76 pt Gaussian quadrature for orientational integral
Uses 20 pt quadrature for the inner integral over the elliptical cross-section

Warning:
The call to WaveData() below returns a pointer to the middle
of an unlocked Macintosh handle. In the unlikely event that your
calculations could cause memory to move, you should copy the coefficient
values to local variables or an array before such operations.
*/
int
EllipticalCylinderX(FitParamsPtr p)
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
			fp= WaveData(p->waveHandle);
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			
			p->result = EllipCyl20(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

/*	TriaxialEllipsoidX  :  calculates the form factor of a Triaxial Ellipsoid at the given x-value p->x

Uses 76 pt Gaussian quadrature for both integrals

Warning:
The call to WaveData() below returns a pointer to the middle
of an unlocked Macintosh handle. In the unlikely event that your
calculations could cause memory to move, you should copy the coefficient
values to local variables or an array before such operations.
*/
int
TriaxialEllipsoidX(FitParamsPtr p)
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
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			
			p->result = TriaxialEllipsoid(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

/*	ParallelepipedX  :  calculates the form factor of a Parallelepiped (a rectangular solid)
at the given x-value p->x

Uses 76 pt Gaussian quadrature for both integrals

Warning:
The call to WaveData() below returns a pointer to the middle
of an unlocked Macintosh handle. In the unlikely event that your
calculations could cause memory to move, you should copy the coefficient
values to local variables or an array before such operations.
*/
int
ParallelepipedX(FitParamsPtr p)
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
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			
			p->result = Parallelepiped(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

/*	HollowCylinderX  :  calculates the form factor of a Hollow Cylinder
at the given x-value p->x

Uses 76 pt Gaussian quadrature for the single integral

Warning:
The call to WaveData() below returns a pointer to the middle
of an unlocked Macintosh handle. In the unlikely event that your
calculations could cause memory to move, you should copy the coefficient
values to local variables or an array before such operations.
*/
int
HollowCylinderX(FitParamsPtr p)
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
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			
			p->result = HollowCylinder(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

/*	EllipsoidFormX  :  calculates the form factor of an ellipsoid of revolution with semiaxes a:a:nua
at the given x-value p->x

Uses 76 pt Gaussian quadrature for the single integral

Warning:
The call to WaveData() below returns a pointer to the middle
of an unlocked Macintosh handle. In the unlikely event that your
calculations could cause memory to move, you should copy the coefficient
values to local variables or an array before such operations.
*/
int
EllipsoidFormX(FitParamsPtr p)
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
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			
			p->result = EllipsoidForm(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}


/*	Cyl_PolyRadiusX  :  calculates the form factor of a cylinder at the given x-value p->x
the cylinder has a polydisperse cross section

*/
int
Cyl_PolyRadiusX(FitParamsPtr p)
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
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			
			p->result = Cyl_PolyRadius(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

/*	Cyl_PolyLengthX  :  calculates the form factor of a cylinder at the given x-value p->x
the cylinder has a polydisperse Length

*/
int
Cyl_PolyLengthX(FitParamsPtr p)
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
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			
			p->result = Cyl_PolyLength(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	
	return 0;
}

/*	CoreShellCylinderX  :  calculates the form factor of a cylinder at the given x-value p->x
the cylinder has a core-shell structure

*/
int
CoreShellCylinderX(FitParamsPtr p)
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
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			
			p->result = CoreShellCylinder(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	
	return 0;
}


/*	PolyCoShCylinderX  :  calculates the form factor of a core-shell cylinder at the given x-value p->x
the cylinder has a polydisperse CORE radius

*/
int
PolyCoShCylinderX(FitParamsPtr p)
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
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			
			p->result = PolyCoShCylinder(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

/*	OblateFormX  :  calculates the form factor of a core-shell Oblate ellipsoid at the given x-value p->x
the ellipsoid has a core-shell structure

*/
int
OblateFormX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			
			p->result = OblateForm(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

/*	ProlateFormX  :  calculates the form factor of a core-shell Prolate ellipsoid at the given x-value p->x
the ellipsoid has a core-shell structure

*/
int
ProlateFormX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			
			p->result = ProlateForm(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


/*	StackedDiscsX  :  calculates the form factor of a stacked "tactoid" of core shell disks
like clay platelets that are not exfoliated

*/
int
StackedDiscsX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = StackedDiscs(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


/*	LamellarFFX  :  calculates the form factor of a lamellar structure - no S(q) effects included

*/
int
LamellarFFX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = LamellarFF(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

/*	LamellarPSX  :  calculates the form factor of a lamellar structure - with S(q) effects included

*/
int
LamellarPSX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = LamellarPS(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}


/*	LamellarPS_HGX  :  calculates the form factor of a lamellar structure - with S(q) effects included

*/
int
LamellarPS_HGX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = LamellarPS_HG(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

/*	LamellarFF_HGX  :  calculates the form factor of a lamellar structure - no S(q) effects included
but extra SLD for head groups is included

*/
int
LamellarFF_HGX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = LamellarFF_HG(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

/*	FlexExclVolCylX  :  calculates the form factor of a flexible cylinder with a circular cross section
-- incorporates Wei-Ren Chen's fixes - 2006

	*/
int
FlexExclVolCylX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = FlexExclVolCyl(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

/*	FlexCyl_EllipX  :  calculates the form factor of a flexible cylinder with an elliptical cross section
-- incorporates Wei-Ren Chen's fixes - 2006

	*/
int
FlexCyl_EllipX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = FlexCyl_Ellip(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

/*	FlexCyl_PolyLenX  :  calculates the form factor of a flecible cylinder at the given x-value p->x
the cylinder has a polydisperse Length

*/
int
FlexCyl_PolyLenX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = FlexCyl_PolyLen(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

/*	FlexCyl_PolyLenX  :  calculates the form factor of a flexible cylinder at the given x-value p->x
the cylinder has a polydisperse cross sectional radius

*/
int
FlexCyl_PolyRadX(FitParamsPtr p)
{
	double *dp;				// Pointer to double precision wave data.
	float *fp;				// Pointer to single precision wave data.
	double q;		//local variables of coefficient wave
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
	
	q= p->x;
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= WaveData(p->waveHandle);
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07  			
		case NT_FP64:
			dp= WaveData(p->waveHandle);
			p->result = FlexCyl_PolyRad(dp,q);
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}	
	return 0;
}

