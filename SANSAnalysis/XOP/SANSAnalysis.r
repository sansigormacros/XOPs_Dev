/*	CylinderFit.r -- resources for CylinderFit
//now compatible with Project Builder
*/

#include "XOPStandardHeaders.r"

resource 'vers' (1) {						/* XOP version info */
0x01, 0x02, final, 0x00, 0,				/* version bytes and country integer */
"1.1",
"1.1, NIST Center for Neutron Research"
};

resource 'vers' (2) {						/* Igor version info */
0x02, 0x00, release, 0x00, 0,			/* version bytes and country integer */
"6.00",
"(for Igor 6.00 or later)"
};

resource 'STR#' (1100) {					/* custom error messages */
{
	/* [1] */
	"SANS Analysis requires Igor Pro 6.0 or later",
	/* [2] */
	"Wave does not exist.",
	/* [3] */
	"Coefficient wave must be single or double precision floating point.",
}
};

resource 'STR#' (1101) {					// Misc strings for XOP.
{
	"-1",								// -1 means we don't want to add a menu item.
	"No Menu Item",						// Igor ignores item 2 because item 1 is -1.
	"SANS_Model_Docs_v3.01",					// Name of XOP's help file.
}
};

resource 'XOPI' (1100) {
	XOP_VERSION,			/* Tells Igor XOP Toolkit version used to compile XOP */
	DEV_SYS_CODE,			/* Identifies MPW C or THINK C. See XOPTypes.r. */
	0,				/* this XOP requires hierarchichal menus */
	0,				/* this XOP does NOT require a coprocessor */
	XOP_TOOLKIT_VERSION,		/* this XOP does not require an MMU */
};

resource 'XOPF' (1100) {
{
/// Sphere functions		
		"MultiShellSphereX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"PolyMultiShellX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"SphereFormX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"CoreShellSphereX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"PolyCoreFormX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"PolyCoreShellRatioX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"VesicleFormX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"SchulzSpheresX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"PolyRectSpheresX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"PolyHardSpheresX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"BimodalSchulzSpheresX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"GaussSpheresX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"LogNormalSphereX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"BinaryHSX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"BinaryHS_PSF11X",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"BinaryHS_PSF12X",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"BinaryHS_PSF22X",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},
/// Cylinder functions
		"CylinderFormX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"EllipCyl76X",					/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"EllipticalCylinderX",					/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"TriaxialEllipsoidX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"ParallelepipedX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"HollowCylinderX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"EllipsoidFormX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"Cyl_PolyRadiusX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"Cyl_PolyLengthX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"CoreShellCylinderX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"OblateFormX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"ProlateFormX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"FlexExclVolCylX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"FlexCyl_PolyLenX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"FlexCyl_PolyRadX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"FlexCyl_EllipX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"PolyCoShCylinderX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"StackedDiscsX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"LamellarFFX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"LamellarFF_HGX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"LamellarPSX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"LamellarPS_HGX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
/// Two phase models
		"TeubnerStreyModelX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"Power_Law_ModelX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"Peak_Lorentz_ModelX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"Peak_Gauss_ModelX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"Lorentz_ModelX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"FractalX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"DAB_ModelX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"OneLevelX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"TwoLevelX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"ThreeLevelX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},

		"FourLevelX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},
/// Structure Factor Functions		
		"HardSphereStructX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},
		
		"SquareWellStructX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},
		
		"StickyHS_StructX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},
		
		"HayterPenfoldMSAX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == Utility */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			/* double precision wave (coefficient wave) */
			NT_FP64,						/* double precision x */
		},
		
		"DiamCylX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,				/* function category */
		NT_FP64,							/* return value type */			
		{
			NT_FP64,						/* parameter types */
			NT_FP64,
		},
		
		"DiamEllipX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,				/* function category */
		NT_FP64,							/* return value type */			
		{
			NT_FP64,						/* parameter types */
			NT_FP64,
		},
		
/// Resolution smearing functions
		"Smear_Model_20_X",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			HSTRING_TYPE,
			NT_FP64,					/* double precision x */
			NT_FP64,					/* double precision x */
			NT_FP64,					/* double precision x */
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"Smear_Model_76_X",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			HSTRING_TYPE,
			NT_FP64,					/* double precision x */
			NT_FP64,					/* double precision x */
			NT_FP64,					/* double precision x */
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"SmearedCyl_PolyRadiusX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64,					/* double precision x */
			NT_FP64,					/* double precision x */
			NT_FP64,					/* double precision x */
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

// 2D Functions
		"Cylinder_2DX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
			NT_FP64,					/* double precision x */
		},
		
		"Cylinder_2D_Weight2DX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,
		{
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64,
			NT_FP64,
		},

		
		"CoreShellCylinder_2DX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
			NT_FP64,					/* double precision x */
		},
		
		"CoreShellCylinder_2D_Weight2DX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,
		{
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64,
			NT_FP64,
		},

		
		"Ellipsoid_2DX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
			NT_FP64,					/* double precision x */
		},
		
		"Ellipsoid_2D_Weight2DX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,
		{
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64,
			NT_FP64,
		},
		
		"EllipticalCylinder_2DX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
			NT_FP64,					/* double precision x */
		},
		
		"EllipticalCylinder_2D_Weight2DX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,
		{
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64,
			NT_FP64,
		},

		"Sphere_2DX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
			NT_FP64,					/* double precision x */
		},
		
/// new models in 2008 (starts index 68)

		"SpherocylinderX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"ConvexLensX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"DumbbellX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"CappedCylinderX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"BarbellX",
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
// index # 73 is Lamellar_ParaCrystalX		
		"Lamellar_ParaCrystalX",				
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"BCC_ParaCrystalX",				
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"FCC_ParaCrystalX",				
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"SC_ParaCrystalX",				
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"OneShellX",				
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"TwoShellX",				
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"ThreeShellX",				
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"FourShellX",				
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"PolyOneShellX",				
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"PolyTwoShellX",				
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"PolyThreeShellX",				
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"PolyFourShellX",		//case # 84
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
				
		"BroadPeakX",		//case # 85
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"CorrLengthX",		//case # 86
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"TwoLorentzianX",		//case # 87
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"TwoPowerLawX",		//case # 88
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"PolyGaussCoilX",		//case # 89
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		
		"GaussLorentzGelX",		//case # 90
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

		"GaussianShellX",		//case # 91
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		"PolyCoreBicelleX",		//case # 92
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},
		"CSParallelepipedX",		//case # 92
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,						/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,				/* double precision wave (coefficient wave) */
			NT_FP64,					/* double precision x */
		},

	}
};