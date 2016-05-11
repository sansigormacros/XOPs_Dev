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

static XOPIORecResult
RegisterFunction()
{
	int funcIndex;
	
	funcIndex = (int)GetXOPItem(0);			// Which function invoked ?
	switch (funcIndex) {
		//
		// Sphere Model Functions
		//
		case 0:							// y = MultiShellX(w,x) (curve fitting function).
			return((XOPIORecResult)MultiShellSphereX);	// This function is called using the direct method.
			break;
		case 1:							// y = PolyMultiShellX(w,x) (curve fitting function).
			return((XOPIORecResult)PolyMultiShellX);	// This function is called using the direct method.
			break;
		case 2:							// y = SphereFormX(w,x) (curve fitting function).
			return((XOPIORecResult)SphereFormX);	// This function is called using the direct method.
			break;
		case 3:							// y = CoreShellX(w,x) (curve fitting function).
			return((XOPIORecResult)CoreShellSphereX);	// This function is called using the direct method.
			break;
		case 4:							// y = PolyCoreX(w,x) (curve fitting function).
			return((XOPIORecResult)PolyCoreFormX);	// This function is called using the direct method.
			break;
		case 5:							// y = PolyCoreShellRatioX(w,x) (curve fitting function).
			return((XOPIORecResult)PolyCoreShellRatioX);	// This function is called using the direct method.
			break;
		case 6:							// y = Vesicle_ULX(w,x) (curve fitting function).
			return((XOPIORecResult)VesicleFormX);	// This function is called using the direct method.
			break;
		case 7:							// y = SchulzSpheresX(w,x) (curve fitting function).
			return((XOPIORecResult)SchulzSpheresX);	// This function is called using the direct method.
			break;
		case 8:							// y = PolyRectSpheresX(w,x) (curve fitting function).
			return((XOPIORecResult)PolyRectSpheresX);	// This function is called using the direct method.
			break;
		case 9:							// y = PolyHardSphereIntensityX(w,x) (curve fitting function).
			return((XOPIORecResult)PolyHardSpheresX);	// This function is called using the direct method.
			break;
		case 10:							// y = BimodalSchulzSpheresX(w,x) (curve fitting function).
			return((XOPIORecResult)BimodalSchulzSpheresX);	// This function is called using the direct method.
			break;
		case 11:							// y = GaussPolySphereX(w,x) (curve fitting function).
			return((XOPIORecResult)GaussSpheresX);	// This function is called using the direct method.
			break;
		case 12:							// y = LogNormalPolySphereX(w,x) (curve fitting function).
			return((XOPIORecResult)LogNormalSphereX);	// This function is called using the direct method.
			break;
		case 13:							// y = BinaryHSX(w,x) (curve fitting function).
			return((XOPIORecResult)BinaryHSX);	// This function is called using the direct method.
			break;
		case 14:							// y = BinaryHS_PSF11X(w,x) (curve fitting function).
			return((XOPIORecResult)BinaryHS_PSF11X);	// This function is called using the direct method.
			break;
        case 15:							// y = BinaryHS_PSF12X(w,x) (curve fitting function).
			return((XOPIORecResult)BinaryHS_PSF12X);	// This function is called using the direct method.
			break;
		case 16:							// y = BinaryHS_PSF22X(w,x) (curve fitting function).
			return((XOPIORecResult)BinaryHS_PSF22X);	// This function is called using the direct method.
			break;
			// 
			// Cylinder Model Functions
			//
		case 17:							// y = CylinderFormX(w,x) (curve fitting function).
			return((XOPIORecResult)CylinderFormX);	// This function is called using the direct method.
			break;
		case 18:							// y = EllipCylFit76X(w,x) (curve fitting function).
			return((XOPIORecResult)EllipCyl76X);	// This function is called using the direct method.
			break;
		case 19:							// y = EllipCylFit20X(w,x) (curve fitting function).
			return((XOPIORecResult)EllipticalCylinderX);	// This function is called using the direct method.
			break;
		case 20:							// y = TriaxialEllipsoidX(w,x) (curve fitting function).
			return((XOPIORecResult)TriaxialEllipsoidX);	// This function is called using the direct method.
			break;
		case 21:							// y = ParallelepipedX(w,x) (curve fitting function).
			return((XOPIORecResult)ParallelepipedX);	// This function is called using the direct method.
			break;
		case 22:							// y = HollowCylinderX(w,x) (curve fitting function).
			return((XOPIORecResult)HollowCylinderX);	// This function is called using the direct method.
			break;
		case 23:							// y = EllipsoidFormX(w,x) (curve fitting function).
			return((XOPIORecResult)EllipsoidFormX);	// This function is called using the direct method.
			break;        
		case 24:							// y = Cyl_PolyRadiusX(w,x) (curve fitting function).
			return((XOPIORecResult)Cyl_PolyRadiusX);	// This function is called using the direct method.
			break;  
		case 25:							// y = Cyl_PolyLengthX(w,x) (curve fitting function).
			return((XOPIORecResult)Cyl_PolyLengthX);	// This function is called using the direct method.
			break; 
		case 26:							// y = CoreShellCylinderX(w,x) (curve fitting function).
			return((XOPIORecResult)CoreShellCylinderX);	// This function is called using the direct method.
			break;
		case 27:					// y = OblateFormX(w,x) (curve fitting function).
			return((XOPIORecResult)OblateFormX);	// This function is called using the direct method.
			break;
		case 28:					// y = ProlateFormX(w,x) (curve fitting function).
			return((XOPIORecResult)ProlateFormX);	// This function is called using the direct method.
			break;
		case 29:					// y = FlexExclVolCylX(w,x) (curve fitting function).
			return((XOPIORecResult)FlexExclVolCylX);	// This function is called using the direct method.
			break;                        
		case 30:					// y = FlexCyl_PolyLenX(w,x) (curve fitting function).
			return((XOPIORecResult)FlexCyl_PolyLenX);	// This function is called using the direct method.
			break;
		case 31:					// y = FlexCyl_PolyRadX(w,x) (curve fitting function).
			return((XOPIORecResult)FlexCyl_PolyRadX);	// This function is called using the direct method.
			break;
		case 32:					// y = FlexCyl_EllipX(w,x) (curve fitting function).
			return((XOPIORecResult)FlexCyl_EllipX);	// This function is called using the direct method.
			break;
		case 33:					// y = PolyCoShCylinderX(w,x) (curve fitting function).
			return((XOPIORecResult)PolyCoShCylinderX);	// This function is called using the direct method.
			break;
		case 34:					// y = StackedDisksX(w,x) (curve fitting function).
			return((XOPIORecResult)StackedDiscsX);	// This function is called using the direct method.
			break;
		case 35:					// y = LamellarFFX(w,x) (curve fitting function).
			return((XOPIORecResult)LamellarFFX);	// This function is called using the direct method.
			break;
		case 36:					// y = LamellarFF_HGX(w,x) (curve fitting function).
			return((XOPIORecResult)LamellarFF_HGX);	// This function is called using the direct method.
			break;
		case 37:					// y = LamellarPSX(w,x) (curve fitting function).
			return((XOPIORecResult)LamellarPSX);	// This function is called using the direct method.
			break;
		case 38:					// y = LamellarPS_HGX(w,x) (curve fitting function).
			return((XOPIORecResult)LamellarPS_HGX);	// This function is called using the direct method.
			break;
			//
			// Two Phase Model Functions
			//
		case 39:							// y = TeubnerStreyModelX(w,x) (curve fitting function).
			return((XOPIORecResult)TeubnerStreyModelX);	// This function is called using the direct method.
			break;
		case 40:							// y = Power_Law_ModelX(w,x) (curve fitting function).
			return((XOPIORecResult)Power_Law_ModelX);	// This function is called using the direct method.
			break;
		case 41:							// y = Peak_Lorentz_ModelX(w,x) (curve fitting function).
			return((XOPIORecResult)Peak_Lorentz_ModelX);	// This function is called using the direct method.
			break;
		case 42:							// y = Peak_Gauss_ModelX(w,x) (curve fitting function).
			return((XOPIORecResult)Peak_Gauss_ModelX);	// This function is called using the direct method.
			break;
		case 43:							// y = Lorentz_ModelX(w,x) (curve fitting function).
			return((XOPIORecResult)Lorentz_ModelX);	// This function is called using the direct method.
			break;
		case 44:							// y = FractalX(w,x) (curve fitting function).
			return((XOPIORecResult)FractalX);	// This function is called using the direct method.
			break;
		case 45:							// y = DAB_ModelX(w,x) (curve fitting function).
			return((XOPIORecResult)DAB_ModelX);	// This function is called using the direct method.
			break;
		case 46:							// y = OneLevelX(w,x) (curve fitting function).
			return((XOPIORecResult)OneLevelX);	// This function is called using the direct method.
			break;
		case 47:							// y = TwoLevelX(w,x) (curve fitting function).
			return((XOPIORecResult)TwoLevelX);	// This function is called using the direct method.
			break;
		case 48:							// y = ThreeLevelX(w,x) (curve fitting function).
			return((XOPIORecResult)ThreeLevelX);	// This function is called using the direct method.
			break;
		case 49:							// y = FourLevelX(w,x) (curve fitting function).
			return((XOPIORecResult)FourLevelX);	// This function is called using the direct method.
			break;
			//
			// Structure Factor Functions
			//
		case 50:							// y = HardSphereStructX(w,x) (curve fitting function).
			return((XOPIORecResult)HardSphereStructX);	// This function is called using the direct method.
			break;
		case 51:							// y = SquareWellStructX(w,x) (curve fitting function).
			return((XOPIORecResult)SquareWellStructX);	// This function is called using the direct method.
			break;
		case 52:							// y = StickyHS_StructX(w,x) (curve fitting function).
			return((XOPIORecResult)StickyHS_StructX);	// This function is called using the direct method.
			break;
		case 53:							// y = HayterPenfoldMSAX(w,x) (curve fitting function).
			return((XOPIORecResult)HayterPenfoldMSAX);	// This function is called using the direct method.
			break;
		case 54:							// y = DiamCylX(a,b) (utility).
			return((XOPIORecResult)DiamCylX);			// This function is called using the direct method.
			break;
		case 55:							// y = DiamEllipX(a,b) (utility).
			return((XOPIORecResult)DiamEllipX);			// This function is called using the direct method.
			break;
			//
			// Resolution Smearing Functions
		case 56:							// y = Smear_Model_20_X (utility).
			return((XOPIORecResult)Smear_Model_20_X);			// This function is called using the direct method.
			break;
		case 57:							// y =Smear_Model_76_X (utility).
			return((XOPIORecResult)Smear_Model_76_X);			// This function is called using the direct method.
			break;	
		case 58:							// y =Smear_Model_76_X (utility).
			return((XOPIORecResult)SmearedCyl_PolyRadiusX);			// This function is called using the direct method.
			break;
// 2D Functions from DANSE
		case 59:							// y = f(c,y,x)
			return((XOPIORecResult)Cylinder_2D);			// This function is called using the direct method.
			break;
		case 60:							// y = f(c,y,x)
			return((XOPIORecResult)Cylinder_2D_Weight2D);			// This function is called using the direct method.
			break;
		case 61:							// y = f(c,y,x)
			return((XOPIORecResult)CoreShellCylinder_2D);			// This function is called using the direct method.
			break;
		case 62:							// y = f(c,y,x)
			return((XOPIORecResult)CoreShellCylinder_2D_Weight2D);			// This function is called using the direct method.
			break;
		case 63:							// y = f(c,y,x)
			return((XOPIORecResult)Ellipsoid_2D);			// This function is called using the direct method.
			break;
		case 64:							// y = f(c,y,x)
			return((XOPIORecResult)Ellipsoid_2D_Weight2D);			// This function is called using the direct method.
			break;
		case 65:							// y = f(c,y,x)
			return((XOPIORecResult)EllipticalCylinder_2D);			// This function is called using the direct method.
			break;
		case 66:							// y = f(c,y,x)
			return((XOPIORecResult)EllipticalCylinder_2D_Weight2D);			// This function is called using the direct method.
			break;
		case 67:							// y = f(c,y,x)
			return((XOPIORecResult)Sphere_2D);			// This function is called using the direct method.
			break;
/// new models added in 2008
		case 68:							// y = f(c,y,x)
			return((XOPIORecResult)SpherocylinderX);			// This function is called using the direct method.
			break;
		case 69:							// y = f(c,y,x)
			return((XOPIORecResult)ConvexLensX);			// This function is called using the direct method.
			break;
		case 70:							// y = f(c,y,x)
			return((XOPIORecResult)DumbbellX);			// This function is called using the direct method.
			break;
		case 71:							// y = f(c,y,x)
			return((XOPIORecResult)CappedCylinderX);			// This function is called using the direct method.
			break;
		case 72:							// y = f(c,y,x)
			return((XOPIORecResult)BarbellX);			// This function is called using the direct method.
			break;
		case 73:							// y = f(c,y,x)
			return((XOPIORecResult)Lamellar_ParaCrystalX);			// This function is called using the direct method.
			break;
			//
		case 74:							// y = f(c,y,x)
			return((XOPIORecResult)BCC_ParaCrystalX);			// This function is called using the direct method.
			break;
		case 75:							// y = f(c,y,x)
			return((XOPIORecResult)FCC_ParaCrystalX);			// This function is called using the direct method.
			break;
		case 76:							// y = f(c,y,x)
			return((XOPIORecResult)SC_ParaCrystalX);			// This function is called using the direct method.
			break;
		case 77:							// y = f(c,y,x)
			return((XOPIORecResult)OneShellX);			// This function is called using the direct method.
			break;
		case 78:							// y = f(c,y,x)
			return((XOPIORecResult)TwoShellX);			// This function is called using the direct method.
			break;
		case 79:							// y = f(c,y,x)
			return((XOPIORecResult)ThreeShellX);			// This function is called using the direct method.
			break;
		case 80:							// y = f(c,y,x)
			return((XOPIORecResult)FourShellX);			// This function is called using the direct method.
			break;
		case 81:							// y = f(c,y,x)
			return((XOPIORecResult)PolyOneShellX);			// This function is called using the direct method.
			break;
		case 82:							// y = f(c,y,x)
			return((XOPIORecResult)PolyTwoShellX);			// This function is called using the direct method.
			break;
		case 83:							// y = f(c,y,x)
			return((XOPIORecResult)PolyThreeShellX);			// This function is called using the direct method.
			break;
		case 84:							// y = f(c,y,x)
			return((XOPIORecResult)PolyFourShellX);			// This function is called using the direct method.
			break;
			//
		case 85:							// y = f(c,y,x)
			return((XOPIORecResult)BroadPeakX);			// This function is called using the direct method.
			break;
		case 86:							// y = f(c,y,x)
			return((XOPIORecResult)CorrLengthX);			// This function is called using the direct method.
			break;
		case 87:							// y = f(c,y,x)
			return((XOPIORecResult)TwoLorentzianX);			// This function is called using the direct method.
			break;
		case 88:							// y = f(c,y,x)
			return((XOPIORecResult)TwoPowerLawX);			// This function is called using the direct method.
			break;
		case 89:							// y = f(c,y,x)
			return((XOPIORecResult)PolyGaussCoilX);			// This function is called using the direct method.
			break;
		case 90:							// y = f(c,y,x)
			return((XOPIORecResult)GaussLorentzGelX);			// This function is called using the direct method.
			break;
		case 91:							// y = f(c,y,x)
			return((XOPIORecResult)GaussianShellX);			// This function is called using the direct method.
			break;
		case 92:							// y = f(c,y,x)
			return((XOPIORecResult)FuzzySpheresX);			// This function is called using the direct method.
			break;
		case 93:							// y = f(c,y,x)
			return((XOPIORecResult)PolyCoreBicelleX);			// This function is called using the direct method.
			break;
		case 94:							// y = f(c,y,x)
			return((XOPIORecResult)CSParallelepipedX);			// This function is called using the direct method.
			break;
		case 95:							//One Yukawa
			return((XOPIORecResult)OneYukawaX);	// This function is called using the direct method.
			break;
		case 96:							// Two Yukawa
			return((XOPIORecResult)TwoYukawaX);	// This function is called using the direct method.
			break;
	}
	return 0;
}

/*	XOPEntry()

This is the entry point from the host application to the XOP for all
messages after the INIT message.
*/
static void
XOPEntry(void)
{	
	XOPIORecResult result = 0;
	
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
 
 updated for TK6 30JAN2012 SRK
*/
HOST_IMPORT int						// was void
XOPMain(IORecHandle ioRecHandle)
{	
	XOPInit(ioRecHandle);							// Do standard XOP initialization.
	SetXOPEntry(XOPEntry);							// Set entry point for future calls.
	
	if (igorVersion < 620) {						// checks required for ThreadSafe declarations
		SetXOPResult(OLD_IGOR);
		return EXIT_FAILURE;					// added for TK6
	}
	
	SetXOPResult(0);
	return EXIT_SUCCESS;					// added for TK6
	
//	else {
//		if (igorVersion >= 700)
//			SetXOPResult(IGOR_OBSOLETE);
//		else
//			SetXOPResult(0L);
//	}
	
}


