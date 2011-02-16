#include "XOPStandardHeaders.r"

resource 'vers' (1) {						/* XOP version info */
	0x01, 0x00, final, 0x00, 0,				/* version bytes and country integer */
	"1.00",
	"1.00, © 1993 WaveMetrics, Inc., all rights reserved."
};

resource 'vers' (2) {						/* Igor version info */
	0x05, 0x00, release, 0x00, 0,			/* version bytes and country integer */
	"5.00",
	"(for Igor 5.00 or later)"
};

resource 'STR#' (1100) {					/* custom error messages */
	{
		/* [1] */
		"SANSMonteCarlo requires Igor Pro 6.1 or later.",
		/* [2] */
		"Wave does not exist.",
		/* [3] */
		"This function requires a 3D wave.",
	}
};

/* no menu item */

resource 'XOPI' (1100) {
	XOP_VERSION,							// XOP protocol version.
	DEV_SYS_CODE,							// Development system information.
	0,										// Obsolete - set to zero.
	0,										// Obsolete - set to zero.
	XOP_TOOLKIT_VERSION,					// XOP Toolkit version.
};

resource 'XOPF' (1100) {
	{
		"Monte_SANSX",		/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
		},
		"Monte_SANSX2",		/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
		},
		
		"DebyeSpheresX",						/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,				/* function category == Utility */
		NT_FP64,							/* return value type */	
		{
						NT_FP64,			/* single precision wave (q-wave) */
			NT_FP64 + WAVE_TYPE,				/* single precision wave (x coordinates) */
			NT_FP64 + WAVE_TYPE,				/* single precision wave (y coordinates) */
			NT_FP64 + WAVE_TYPE,				/* single precision wave (z coordinates) */
			NT_FP64 + WAVE_TYPE,				/* single precision wave (rho at xyz) */
                        NT_FP64,				// Rprimary, the primary sphere radius
                        NT_FP64,				// grid, should be passed as 0.62*Rprimary
		},
		
		"Monte_SANSX3",		/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
		},
		
		"Monte_SANSX4",		/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
		},
		
		"maxDistanceX",		/* function name */
		F_UTIL | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
		},
		
		"binDistanceX",		/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			// XYZ waves
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,			// distance Bin wave (this is returned)
			NT_FP64,						// grid
			NT_FP64,						// bin width
			NT_FP64,						// start index
			NT_FP64,						// stop index
		},
		
		"SobolX",		/* function name */
		F_UTIL | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,							/* return value type */			
		{
			NT_FP64,						// requested dimension (this is really an integer)
			NT_FP64 + WAVE_TYPE,			// result wave
		},
		
		"binSLDDistanceX",		/* function name */
		F_UTIL | F_THREADSAFE | F_EXTERNAL,					/* function category == UTILITY */
		NT_FP64,							/* return value type */			
		{
			NT_FP64 + WAVE_TYPE,			// XYZ waves
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,
			NT_FP64 + WAVE_TYPE,			// rho wave
			NT_FP64 + WAVE_TYPE,			// distance Bin wave, 2D (this is returned)
			NT_FP64 + WAVE_TYPE,			// SLD lookup
			NT_FP64 + WAVE_TYPE,			// PSF id matrix
			NT_FP64,						// grid
			NT_FP64,						// bin width
			NT_FP64,						// start index
			NT_FP64,						// stop index
		},
		
	}
};
