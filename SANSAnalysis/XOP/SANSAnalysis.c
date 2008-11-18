/*
 *  SANSAnalysis.c
 *  SANSAnalysis
 *
 *  Created by Andrew Jackson on 4/23/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */


#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "SANSAnalysis.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "TwoPhase.h"
#include "StructureFactor.h"
#include "ResolutionSmearing.h"
#include "Func2D.h"

static long
RegisterFunction()
{
	int funcIndex;
	
	funcIndex = GetXOPItem(0);			// Which function invoked ?
	switch (funcIndex) {
		//
		// Sphere Model Functions
		//
		case 0:							// y = MultiShellX(w,x) (curve fitting function).
			return((long)MultiShellSphereX);	// This function is called using the direct method.
			break;
		case 1:							// y = PolyMultiShellX(w,x) (curve fitting function).
			return((long)PolyMultiShellX);	// This function is called using the direct method.
			break;
		case 2:							// y = SphereFormX(w,x) (curve fitting function).
			return((long)SphereFormX);	// This function is called using the direct method.
			break;
		case 3:							// y = CoreShellX(w,x) (curve fitting function).
			return((long)CoreShellSphereX);	// This function is called using the direct method.
			break;
		case 4:							// y = PolyCoreX(w,x) (curve fitting function).
			return((long)PolyCoreFormX);	// This function is called using the direct method.
			break;
		case 5:							// y = PolyCoreShellRatioX(w,x) (curve fitting function).
			return((long)PolyCoreShellRatioX);	// This function is called using the direct method.
			break;
		case 6:							// y = Vesicle_ULX(w,x) (curve fitting function).
			return((long)VesicleFormX);	// This function is called using the direct method.
			break;
		case 7:							// y = SchulzSpheresX(w,x) (curve fitting function).
			return((long)SchulzSpheresX);	// This function is called using the direct method.
			break;
		case 8:							// y = PolyRectSpheresX(w,x) (curve fitting function).
			return((long)PolyRectSpheresX);	// This function is called using the direct method.
			break;
		case 9:							// y = PolyHardSphereIntensityX(w,x) (curve fitting function).
			return((long)PolyHardSpheresX);	// This function is called using the direct method.
			break;
		case 10:							// y = BimodalSchulzSpheresX(w,x) (curve fitting function).
			return((long)BimodalSchulzSpheresX);	// This function is called using the direct method.
			break;
		case 11:							// y = GaussPolySphereX(w,x) (curve fitting function).
			return((long)GaussSpheresX);	// This function is called using the direct method.
			break;
		case 12:							// y = LogNormalPolySphereX(w,x) (curve fitting function).
			return((long)LogNormalSphereX);	// This function is called using the direct method.
			break;
		case 13:							// y = BinaryHSX(w,x) (curve fitting function).
			return((long)BinaryHSX);	// This function is called using the direct method.
			break;
		case 14:							// y = BinaryHS_PSF11X(w,x) (curve fitting function).
			return((long)BinaryHS_PSF11X);	// This function is called using the direct method.
			break;
        case 15:							// y = BinaryHS_PSF12X(w,x) (curve fitting function).
			return((long)BinaryHS_PSF12X);	// This function is called using the direct method.
			break;
		case 16:							// y = BinaryHS_PSF22X(w,x) (curve fitting function).
			return((long)BinaryHS_PSF22X);	// This function is called using the direct method.
			break;
			// 
			// Cylinder Model Functions
			//
		case 17:							// y = CylinderFormX(w,x) (curve fitting function).
			return((long)CylinderFormX);	// This function is called using the direct method.
			break;
		case 18:							// y = EllipCylFit76X(w,x) (curve fitting function).
			return((long)EllipCyl76X);	// This function is called using the direct method.
			break;
		case 19:							// y = EllipCylFit20X(w,x) (curve fitting function).
			return((long)EllipticalCylinderX);	// This function is called using the direct method.
			break;
		case 20:							// y = TriaxialEllipsoidX(w,x) (curve fitting function).
			return((long)TriaxialEllipsoidX);	// This function is called using the direct method.
			break;
		case 21:							// y = ParallelepipedX(w,x) (curve fitting function).
			return((long)ParallelepipedX);	// This function is called using the direct method.
			break;
		case 22:							// y = HollowCylinderX(w,x) (curve fitting function).
			return((long)HollowCylinderX);	// This function is called using the direct method.
			break;
		case 23:							// y = EllipsoidFormX(w,x) (curve fitting function).
			return((long)EllipsoidFormX);	// This function is called using the direct method.
			break;        
		case 24:							// y = Cyl_PolyRadiusX(w,x) (curve fitting function).
			return((long)Cyl_PolyRadiusX);	// This function is called using the direct method.
			break;  
		case 25:							// y = Cyl_PolyLengthX(w,x) (curve fitting function).
			return((long)Cyl_PolyLengthX);	// This function is called using the direct method.
			break; 
		case 26:							// y = CoreShellCylinderX(w,x) (curve fitting function).
			return((long)CoreShellCylinderX);	// This function is called using the direct method.
			break;
		case 27:					// y = OblateFormX(w,x) (curve fitting function).
			return((long)OblateFormX);	// This function is called using the direct method.
			break;
		case 28:					// y = ProlateFormX(w,x) (curve fitting function).
			return((long)ProlateFormX);	// This function is called using the direct method.
			break;
		case 29:					// y = FlexExclVolCylX(w,x) (curve fitting function).
			return((long)FlexExclVolCylX);	// This function is called using the direct method.
			break;                        
		case 30:					// y = FlexCyl_PolyLenX(w,x) (curve fitting function).
			return((long)FlexCyl_PolyLenX);	// This function is called using the direct method.
			break;
		case 31:					// y = FlexCyl_PolyRadX(w,x) (curve fitting function).
			return((long)FlexCyl_PolyRadX);	// This function is called using the direct method.
			break;
		case 32:					// y = FlexCyl_EllipX(w,x) (curve fitting function).
			return((long)FlexCyl_EllipX);	// This function is called using the direct method.
			break;
		case 33:					// y = PolyCoShCylinderX(w,x) (curve fitting function).
			return((long)PolyCoShCylinderX);	// This function is called using the direct method.
			break;
		case 34:					// y = StackedDisksX(w,x) (curve fitting function).
			return((long)StackedDiscsX);	// This function is called using the direct method.
			break;
		case 35:					// y = LamellarFFX(w,x) (curve fitting function).
			return((long)LamellarFFX);	// This function is called using the direct method.
			break;
		case 36:					// y = LamellarFF_HGX(w,x) (curve fitting function).
			return((long)LamellarFF_HGX);	// This function is called using the direct method.
			break;
		case 37:					// y = LamellarPSX(w,x) (curve fitting function).
			return((long)LamellarPSX);	// This function is called using the direct method.
			break;
		case 38:					// y = LamellarPS_HGX(w,x) (curve fitting function).
			return((long)LamellarPS_HGX);	// This function is called using the direct method.
			break;
			//
			// Two Phase Model Functions
			//
		case 39:							// y = TeubnerStreyModelX(w,x) (curve fitting function).
			return((long)TeubnerStreyModelX);	// This function is called using the direct method.
			break;
		case 40:							// y = Power_Law_ModelX(w,x) (curve fitting function).
			return((long)Power_Law_ModelX);	// This function is called using the direct method.
			break;
		case 41:							// y = Peak_Lorentz_ModelX(w,x) (curve fitting function).
			return((long)Peak_Lorentz_ModelX);	// This function is called using the direct method.
			break;
		case 42:							// y = Peak_Gauss_ModelX(w,x) (curve fitting function).
			return((long)Peak_Gauss_ModelX);	// This function is called using the direct method.
			break;
		case 43:							// y = Lorentz_ModelX(w,x) (curve fitting function).
			return((long)Lorentz_ModelX);	// This function is called using the direct method.
			break;
		case 44:							// y = FractalX(w,x) (curve fitting function).
			return((long)FractalX);	// This function is called using the direct method.
			break;
		case 45:							// y = DAB_ModelX(w,x) (curve fitting function).
			return((long)DAB_ModelX);	// This function is called using the direct method.
			break;
		case 46:							// y = OneLevelX(w,x) (curve fitting function).
			return((long)OneLevelX);	// This function is called using the direct method.
			break;
		case 47:							// y = TwoLevelX(w,x) (curve fitting function).
			return((long)TwoLevelX);	// This function is called using the direct method.
			break;
		case 48:							// y = ThreeLevelX(w,x) (curve fitting function).
			return((long)ThreeLevelX);	// This function is called using the direct method.
			break;
		case 49:							// y = FourLevelX(w,x) (curve fitting function).
			return((long)FourLevelX);	// This function is called using the direct method.
			break;
			//
			// Structure Factor Functions
			//
		case 50:							// y = HardSphereStructX(w,x) (curve fitting function).
			return((long)HardSphereStructX);	// This function is called using the direct method.
			break;
		case 51:							// y = SquareWellStructX(w,x) (curve fitting function).
			return((long)SquareWellStructX);	// This function is called using the direct method.
			break;
		case 52:							// y = StickyHS_StructX(w,x) (curve fitting function).
			return((long)StickyHS_StructX);	// This function is called using the direct method.
			break;
		case 53:							// y = HayterPenfoldMSAX(w,x) (curve fitting function).
			return((long)HayterPenfoldMSAX);	// This function is called using the direct method.
			break;
		case 54:							// y = DiamCylX(a,b) (utility).
			return((long)DiamCylX);			// This function is called using the direct method.
			break;
		case 55:							// y = DiamEllipX(a,b) (utility).
			return((long)DiamEllipX);			// This function is called using the direct method.
			break;
			//
			// Resolution Smearing Functions
		case 56:							// y = Smear_Model_20_X (utility).
			return((long)Smear_Model_20_X);			// This function is called using the direct method.
			break;
		case 57:							// y =Smear_Model_76_X (utility).
			return((long)Smear_Model_76_X);			// This function is called using the direct method.
			break;	
		case 58:							// y =Smear_Model_76_X (utility).
			return((long)SmearedCyl_PolyRadiusX);			// This function is called using the direct method.
			break;
// 2D Functions from DANSE
		case 59:							// y = f(c,y,x)
			return((long)Cylinder_2D);			// This function is called using the direct method.
			break;
		case 60:							// y = f(c,y,x)
			return((long)Cylinder_2D_Weight2D);			// This function is called using the direct method.
			break;
		case 61:							// y = f(c,y,x)
			return((long)CoreShellCylinder_2D);			// This function is called using the direct method.
			break;
		case 62:							// y = f(c,y,x)
			return((long)CoreShellCylinder_2D_Weight2D);			// This function is called using the direct method.
			break;
		case 63:							// y = f(c,y,x)
			return((long)Ellipsoid_2D);			// This function is called using the direct method.
			break;
		case 64:							// y = f(c,y,x)
			return((long)Ellipsoid_2D_Weight2D);			// This function is called using the direct method.
			break;
		case 65:							// y = f(c,y,x)
			return((long)EllipticalCylinder_2D);			// This function is called using the direct method.
			break;
		case 66:							// y = f(c,y,x)
			return((long)EllipticalCylinder_2D_Weight2D);			// This function is called using the direct method.
			break;
		case 67:							// y = f(c,y,x)
			return((long)Sphere_2D);			// This function is called using the direct method.
			break;
/// new models added in 2008
		case 68:							// y = f(c,y,x)
			return((long)SpherocylinderX);			// This function is called using the direct method.
			break;
		case 69:							// y = f(c,y,x)
			return((long)ConvexLensX);			// This function is called using the direct method.
			break;
		case 70:							// y = f(c,y,x)
			return((long)DumbbellX);			// This function is called using the direct method.
			break;
		case 71:							// y = f(c,y,x)
			return((long)CappedCylinderX);			// This function is called using the direct method.
			break;
		case 72:							// y = f(c,y,x)
			return((long)BarbellX);			// This function is called using the direct method.
			break;
		case 73:							// y = f(c,y,x)
			return((long)Lamellar_ParaCrystalX);			// This function is called using the direct method.
			break;
			//
		case 74:							// y = f(c,y,x)
			return((long)BCC_ParaCrystalX);			// This function is called using the direct method.
			break;
		case 75:							// y = f(c,y,x)
			return((long)FCC_ParaCrystalX);			// This function is called using the direct method.
			break;
		case 76:							// y = f(c,y,x)
			return((long)SC_ParaCrystalX);			// This function is called using the direct method.
			break;
		case 77:							// y = f(c,y,x)
			return((long)OneShellX);			// This function is called using the direct method.
			break;
		case 78:							// y = f(c,y,x)
			return((long)TwoShellX);			// This function is called using the direct method.
			break;
		case 79:							// y = f(c,y,x)
			return((long)ThreeShellX);			// This function is called using the direct method.
			break;
		case 80:							// y = f(c,y,x)
			return((long)FourShellX);			// This function is called using the direct method.
			break;
		case 81:							// y = f(c,y,x)
			return((long)PolyOneShellX);			// This function is called using the direct method.
			break;
		case 82:							// y = f(c,y,x)
			return((long)PolyTwoShellX);			// This function is called using the direct method.
			break;
		case 83:							// y = f(c,y,x)
			return((long)PolyThreeShellX);			// This function is called using the direct method.
			break;
		case 84:							// y = f(c,y,x)
			return((long)PolyFourShellX);			// This function is called using the direct method.
			break;
			//
		case 85:							// y = f(c,y,x)
			return((long)BroadPeakX);			// This function is called using the direct method.
			break;
		case 86:							// y = f(c,y,x)
			return((long)CorrLengthX);			// This function is called using the direct method.
			break;
		case 87:							// y = f(c,y,x)
			return((long)TwoLorentzianX);			// This function is called using the direct method.
			break;
		case 88:							// y = f(c,y,x)
			return((long)TwoPowerLawX);			// This function is called using the direct method.
			break;
		case 89:							// y = f(c,y,x)
			return((long)PolyGaussCoilX);			// This function is called using the direct method.
			break;
		case 90:							// y = f(c,y,x)
			return((long)GaussLorentzGelX);			// This function is called using the direct method.
			break;
		case 91:							// y = f(c,y,x)
			return((long)GaussianShellX);			// This function is called using the direct method.
			break;
	}
	return NIL;
}

/*	XOPEntry()

This is the entry point from the host application to the XOP for all
messages after the INIT message.
*/
static void
XOPEntry(void)
{	
	long result = 0;
	
	switch (GetXOPMessage()) {
		case FUNCADDRS:
			result = RegisterFunction();	// This tells Igor the address of our function.
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
	
	if (igorVersion < 600) {						// checks required for ThreadSafe declarations
		SetXOPResult(IGOR_OBSOLETE);
	}
	else {
		if (igorVersion >= 700)
			SetXOPResult(IGOR_OBSOLETE);
		else
			SetXOPResult(0L);
	}
}


