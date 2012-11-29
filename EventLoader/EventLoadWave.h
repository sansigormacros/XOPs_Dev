// EventLoadWave.h -- quates for SimpleLoadWave XOP

// Custom error codes.
enum {
	IMPROPER_FILE_TYPE= 1 + FIRST_XOP_ERR,	/* "Not the type of file this XOP loads." */
	NO_DATA_FOUND,							/* "Could not find at least one row of wave data in the file." */
	EXPECTED_TD_FILE,						/* "Expected name of loadable file." */
	EXPECTED_BASENAME,						/* "Expected base name for new waves." */
	OLD_IGOR								/* "SimpleLoadWave requires Igor Pro 5.00 or later." */
};
#define XOP_FIRST_ERR IMPROPER_FILE_TYPE
#define XOP_LAST_ERR EXPECTED_BASENAME


/// Event-mode specific definitons

#define AIMTYPE_XY  0 // XY Event
#define AIMTYPE_XYM 2 // XY Minor event
#define AIMTYPE_MIR 1 // Minor rollover event
#define AIMTYPE_MAR 3 // Major rollover event

#define USECSPERTICK 0.1 // microseconds
#define TICKSPERUSEC 10
#define MAXBINS 2000
#define XBINS   128
#define YBINS   128




// Structure used in loading file.
typedef struct ColumnInfo {
	char waveName[MAX_OBJ_NAME+1];			/* name of wave for this column */
	int waveAlreadyExisted;					/* truth that wave existed before XOP executed */
	waveHndl waveHandle;					/* handle to this wave */
	void* waveData;							/* pointer to wave data once it has been locked */
	/* put other column information here */
}ColumnInfo, *ColumnInfoPtr;


///////////


// Misc Equates
#define EVENT_COUNTS_ONLY (FILE_LOADER_LAST_FLAG<<1)	/* flag bit for /W command line option */
#define EVENT_REMOVE_BAD_EVENTS (FILE_LOADER_LAST_FLAG<<2)	//flag bit for /R command line option

// Prototypes

// In EventLoadWave.c
int LoadWave(int calledFromFunction, int flags, const char* baseName, const char* symbolicPathName, const char* fileParam);
HOST_IMPORT int main(IORecHandle ioRecHandle);

// In EventLoadWaveOperation.c
int RegisterEventLoadWave(void);
