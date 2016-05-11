/*	EventLoadWave.cpp
	
	This XOP is an example for XOP programmers who want to write
	file loader XOPs. Thus, we have kept is as simple as possible.
	
	The file is assumed to be tab- or comma-delimited. It is assumed to contain
	numeric data, optionally preceded by a row of column names. If column names
	are present, they are assumed to be on the first line, with the numeric data
	starting on the second line. If there are no column names, then the numeric
	data is assumed to start on the first line.
	
	See "SimpleLoadWave Help" for an explanation of how to use the SimpleLoadWave XOP.
	
	HR, 10/19/96:
		Changed to make CR, CRLF or LF be acceptable end-of-line markers.
		
		It does not handle LFCR which is a deviant form created by some
		whacko file translators.
	
	HR, 980427:
		Made platform-independent.
		
	HR, 020919:
		Revamped to use Operation Handler so that the SimpleLoadWave operation
		can be called from a user function.
	
	HR, 091021
		Updated for 64-bit compatibility.
*/

#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "EventLoadWave.h"


// from Teabag
union AIMEvent {
	unsigned int raw;
	struct word {
		unsigned short tildax : 8;
		unsigned short y : 8;
		unsigned short time : 13;
		unsigned short ppto : 1;
		unsigned short type : 2;
	} word;
} AimEvent;


// counters for the events
struct counter {
	int XYevents;
	int num0;
	int num1;
	int num2;
	int num3;
	int zeros;
	int t0;
	int minor_rollover;
	int major_rollover;
	int pp;
	int dl;
} counter;


////////


// Global Variables
static char gSeparatorsStr[] = {'\t', ',', 0x00};	// Tab or comma separates one column from the next.


/*	TellFileType(fileMessage, fullFilePath, fileLoaderFlags)

	Shows type of file being loaded in history.
*/
static void
TellFileType(const char* fileMessage, const char* fullFilePath, int fileLoaderFlags)
{
	char temp[MAX_PATH_LEN + 100 + 1];
	
	if ((fileLoaderFlags & FILE_LOADER_QUIET) == 0) {
		sprintf(temp, "%s \"%s\""CR_STR, fileMessage, fullFilePath);
		XOPNotice(temp);
	}
}

/*	FinishWave(ciPtr, fileLoaderFlags)

	Finalizes waves after load.
	
	ciPtr points to the column info for this column.
	
	It returns 0 or an error code.
*/
static int
FinishWave(ColumnInfoPtr ciPtr, int fileLoaderFlags)
{
	waveHndl waveHandle;
	char temp[256];
	CountInt numPoints;
	
	waveHandle = ciPtr->waveHandle;
	WaveHandleModified(waveHandle);
	numPoints = WavePoints(waveHandle);

	if ((fileLoaderFlags & FILE_LOADER_QUIET) == 0) {			// Want message?
		sprintf(temp, "%s loaded, %lld points"CR_STR, ciPtr->waveName, (SInt64)numPoints);
		XOPNotice(temp);
	}
	
	return 0;
}

/*	FindNumberOfRows(fileRef, buffer, bufferLength, rowsInFilePtr)

	Returns via rowsInFilePtr the number of rows in the file, starting
	from the current file position. Restores the file position when done.
	
	A row is considered to consist of 0 or more characters followed by a
	CR or LF or CRLF except that the last row does not need to have any of
	these.
	
	Returns 0 or error code.
*/
static int
FindNumberOfRows(XOP_FILE_REF fileRef, char* buffer, int bufferLength, CountInt* rowsInFilePtr)
{
	SInt64 origFPos;
	int err;
//	UInt32* numBytesReadPtr; // Output: number of bytes read
	
	*rowsInFilePtr = 0;

	if (err = XOPGetFilePosition2(fileRef, &origFPos))
		return err;
	
	while (1) {
		if (err = XOPReadLine(fileRef, buffer, bufferLength, NULL)) {
//		if (err = XOPReadLine(fileRef, buffer, bufferLength, numBytesReadPtr)) {
			if (XOPAtEndOfFile(fileRef))
				err = 0;
			break;
		}
//		if(numBytesReadPtr != NULL){
			*rowsInFilePtr += 1;
//		}
	}
	
	XOPSetFilePosition2(fileRef, origFPos);			// Restore original file position.
	return err;
}

/*	FindNumberOfColumns(fileRef, buffer, bufferLength, numColumnsPtr)

	Returns via numColumnsPtr the number of columns in the file, starting
	from the current file position. Restores the file position when done.
	
	A column is considered to consist of 0 or more characters followed by a
	tab, comma, CR, LF or CRLF.
	
	Returns 0 or error code.
*/
static int
FindNumberOfColumns(XOP_FILE_REF fileRef, char* buffer, int bufferLength, int* numColumnsPtr)
{
	SInt64 origFPos;
	char* bufPtr;
	char ch;
	int err;
	
	*numColumnsPtr = 1;
	
	if (err = XOPGetFilePosition2(fileRef, &origFPos))
		return err;

	if (err = XOPReadLine(fileRef, buffer, bufferLength, NULL))
		return err;
	
	bufPtr = buffer;
	while(1) {
		ch = *bufPtr++;
		if (ch == 0)
			break;
		if (strchr(gSeparatorsStr, ch))				// Tab or comma separates one column from the next.
			*numColumnsPtr += 1;
	}

	XOPSetFilePosition2(fileRef, origFPos);			// Restore original file position.
	
	return 0;
}

/*	ReadASCIINumber(bufPtrPtr, doublePtr)

	Reads an ASCII number from the buffer.
	
	bufPtrPtr is a pointer to a variable that points to the next character
	to be read in the current line. The line is null-terminated but does
	not contain CR or LF.
	
	ReadASCIINumber returns the value via the pointer doublePtr.
	It also advances *bufPtrPtr past the number just read.
	
	It returns the 0 if everything was OK or a non-zero error code.
*/
static int
ReadASCIINumber(char** bufPtrPtr, double *doublePtr)
{
	char *bufPtr;
	double d;
	int hitColumnEnd;
	int ch;
	
	bufPtr = *bufPtrPtr;					// Points to next character to read.
	
	// See if we have the end of the column before number.
	hitColumnEnd = 0;
	while (1) {
		ch = *bufPtr;
		if (ch == ' ') {					// Skip leading spaces.
			bufPtr += 1;
			continue;
		}
		if (ch==0 || strchr(gSeparatorsStr, ch))
			hitColumnEnd = 1;
		break;								// We've found the first non-space character.
	}

	if (hitColumnEnd || sscanf(bufPtr, " %lf", &d) <= 0)
		*doublePtr = DOUBLE_NAN;
	else
		*doublePtr = d;

	// Now figure out how many characters were really needed for number.
	while (1) {								// Search for tab or comma or null-terminator.
		ch = *bufPtr;
		if (ch == 0)
			break;
		bufPtr += 1;
		if (strchr(gSeparatorsStr, ch))
			break;
	}
	
	*bufPtrPtr = bufPtr;					// Points to next character to be read.
	return 0;		
}

/// simply scans through the whole file and counts the events as specified
int ScanEvents(unsigned int lword) 
{	
	AimEvent.raw = lword;
	
	if(lword == 0) counter.zeros++;
	
	switch (AimEvent.word.type) {
		case AIMTYPE_XY:		// 0
			if (AimEvent.word.ppto) counter.pp++;
			counter.num0++;
			counter.XYevents++;
			break;
		case AIMTYPE_XYM:	// 2
			if (AimEvent.word.ppto) counter.pp++;
			counter.num2++;
			counter.XYevents++;
			break;
		case AIMTYPE_MIR:	//1
			if (AimEvent.word.ppto) counter.t0++;
			counter.num1++;
			break;
		case AIMTYPE_MAR:
			if (AimEvent.word.ppto) counter.t0++;
			counter.num3++;
	}
	return 1;
}


/*	LoadEventData(fileRef, buffer, bufferLength, fileLoaderFlags, caPtr, numRows, numColumns)

	Loads simple tab or comma delimited data into waves.
	caPtr points to locked array of column info (see EventLoadWave.h).
	numColumns is number of columns in file.
	
	File mark is assumed pointing to start of first row of data.
*/
static int
LoadEventData(
	XOP_FILE_REF fileRef,
	char* buffer, int bufferLength,
	int fileLoaderFlags, ColumnInfoPtr caPtr,
	CountInt numRows, CountInt numColumns)
{
//	ColumnInfoPtr ciPtr;
	ColumnInfoPtr xLocPtr;
	ColumnInfoPtr yLocPtr;
	ColumnInfoPtr timePtr;
//	int column;
	IndexInt row;			//IndexInt = long
//	double doubleValue;
	int isDouble,removeBadEvents;
//	char* bufPtr;				// Points to the next character in the current line of text.
	int err;
	//
	char buf[128];		//TB
	unsigned int lword;
	long time_msw, time_lsw, x, y;
	long nRoll, rolloverHappened;
	double rollTime;		// declaring this as double forces a correct type conversion when calculating the time
	double t,t_longest;		// these need to be double to hold the longest time values, unsigned long is not large enough
	int numBad;
	int numRemoved;
	char bufStr[256];
	
	isDouble = fileLoaderFlags & FILE_LOADER_DOUBLE_PRECISION;
	removeBadEvents = fileLoaderFlags & EVENT_REMOVE_BAD_EVENTS;		// this is == 256 if the flag is set
	// -- so ((1) && 256) returns 1!

//	sprintf(bufStr,"XOP removeBadEvents flag = %d\r",removeBadEvents);
//	XOPNotice(bufStr);
	
	err = 0;

	numBad = 0;
	numRemoved = 0;
	nRoll = 0;
	rolloverHappened = 0;
	rollTime = 67108864;		// == 2^26, units of 0.1 microseconds
	

	xLocPtr = caPtr + 0;
	yLocPtr = caPtr + 1;
	timePtr = caPtr + 2;	
	
	time_msw=0;
	time_lsw=0;
	t_longest = 0;
	row = 0;
	
	if(removeBadEvents) {
		// remove events at the beginning up to a type==2 so that the msw and lsw times are reset properly
		while(fgets(buf,sizeof(buf),fileRef)) {
			if (sscanf(buf,"%x",&lword)) {
				AimEvent.raw = lword;
				if(AimEvent.word.type == 2) {
					// this is the first event with a proper time value, so process the XY-time event as ususal
					// and then break to drop to the main loop, where the next event == type 1
					x = ~AimEvent.word.tildax & 127;
					y = AimEvent.word.y & 127;
					time_lsw = AimEvent.word.time;
					
					// this is the first point, be sure that row = 0
					row = 0;
					((float*)xLocPtr->waveData)[row] = (float)x;
					((float*)yLocPtr->waveData)[row] = (float)y;
					break;		//get out, and read the rest of the file as normal
				} else {
					numBad++;
					numRemoved++;
				}

			}
		}
	}
	
	sprintf(bufStr,"XOP numRemoved at beginning = %d\r",numRemoved);
	XOPNotice(bufStr);
	
// now read in the main portion of the file...	
	while(fgets(buf,sizeof(buf),fileRef)) {
		if (sscanf(buf,"%x",&lword)) {
			
			AimEvent.raw = lword;
			
			switch (AimEvent.word.type) {
				case AIMTYPE_XY:
					// if the datavalue is == 0, just skip it now (it can only be interpreted as type 0, obviously)
					// **** I may need to decrement row here if I'm not breaking out far enough
					if((lword == 0) && removeBadEvents) {
						numRemoved += 1;
						//sprintf(bufStr,"XOP zero at row = %d\r",row);
						//XOPNotice(bufStr);
						break;
					}
					// if it's a pileup, skip it now.
					if ((AimEvent.word.ppto) && removeBadEvents) {
						numRemoved += 1;
						break;
					}
					
					x = ~AimEvent.word.tildax & 127;
					y = AimEvent.word.y & 127;
					time_lsw = AimEvent.word.time;
					
					t = (double) (nRoll*rollTime + ((time_msw << 13) + time_lsw));

					// catch the "bad" events:
					// if an XY event follows a rollover, time_msw is 0 by definition, but does not immediately get 
					// re-evalulated here. Throw out only the immediately following points where msw is still 8191
					if((rolloverHappened) && removeBadEvents) {
						// maybe a bad event
						if(time_msw == 8191) {
							numBad +=1;
							numRemoved += 1;
						} else {
							// time_msw has been reset, points are good now, so keep this one
							((float*)xLocPtr->waveData)[row] = (float)x;
							((float*)yLocPtr->waveData)[row] = (float)y;
							((double*)timePtr->waveData)[row] = (double)t;
							
							row += 1;
							rolloverHappened = 0;
						}
					} else {
						// normal processing of good point, keep it
						((float*)xLocPtr->waveData)[row] = (float)x;
						((float*)yLocPtr->waveData)[row] = (float)y;
						((double*)timePtr->waveData)[row] = (double)t;
						
						row += 1;
					}
					
					break;
				case AIMTYPE_XYM:		
					//XY-time - save the x and y, we'll get time with the next event, a minor rollover
					x = ~AimEvent.word.tildax & 127;
					y = AimEvent.word.y & 127;
					((float*)xLocPtr->waveData)[row] = (float)x;
					((float*)yLocPtr->waveData)[row] = (float)y;
					
					time_lsw = AimEvent.word.time;
					
					break;
				case AIMTYPE_MIR:
										
					time_msw = AimEvent.word.time;
					t = (double) (nRoll*rollTime + ((time_msw << 13) + time_lsw));

					((double*)timePtr->waveData)[row] = (double)t;

					if (t > t_longest) t_longest = t;
					
					// was there a t0 signal?
					if (AimEvent.word.ppto) {
						// reset nRoll = 0 for calcluating the time
						nRoll = 0;
					}
					
					row += 1;
					
					break;
				case AIMTYPE_MAR:
					
					nRoll += 1;
					rolloverHappened = 1;
					
					// was this major rollover also a t0 signal?
					if (AimEvent.word.ppto) {
						// reset nRoll = 0 for calcluating the time
						nRoll = 0;
					}
					
			}		//end of the switch statement

		}		//if (good data value)
		
	}	// while (reading lines)
	

	//
	sprintf(bufStr,"XOP Done reading in all of the file\r");
	XOPNotice(bufStr);
	
	SetOperationNumVar("V_numBad", (double)numBad);
	SetOperationNumVar("V_numRemoved", (double)numRemoved);

//	err = 0;
//	for (row = 1; row < numRows; row++) {
//		//if (err = XOPReadLine(fileRef, buffer, bufferLength, NULL)) {
//		//	if (XOPAtEndOfFile(fileRef))
//		//		err = 0;
//		//	break;
//		//}
//		//bufPtr = buffer;
//		for (column = 0; column < numColumns; column++) {
//			ciPtr = caPtr + column;
//			if(row == 1) {
//				sprintf(bufStr,"assigning column=%d, row = %d\r",column,row);
//				XOPNotice(bufStr);
//			}
//			// Store the data.
//			if (isDouble)
//				((double*)ciPtr->waveData)[row] = 1.1;	
//			else {
//				((float*)xLocPtr->waveData)[row] = (float)1.1;
//				((float*)yLocPtr->waveData)[row] = (float)2.2;
//				((float*)timePtr->waveData)[row] = (float)3.3;
//				//((float*)ciPtr->waveData)[row] = (float)2.2;
//			}
//		}
//		if (err)
//			break;
//		SpinCursor();
//	}
	
//	sprintf(bufStr,"after assignment, err = %d\r",err);
//	XOPNotice(bufStr);
	
	
	return err;
}

/*	GetWaveNames(...)

	Stores a wave name for each column in the corresponding record of the
	array pointed to by caPtr.
	
	If the file appears to have a row of wave names and if the user has
	specified reading names from the file, then the names are read from
	the file. Otherwise, the names are generated from the base name.

	The file names are assumed to be on the first line, if they are present at all.
	
	This routine reads the names row, if there is one, leaving the file marker at
	the start of the numeric data. If there is no names row, it does not read
	anything from the file, so that the file marker will still be at the start
	of the numeric data.
	
	Returns 0 if OK or a non-zero error code.
*/
static int
GetWaveNames(
	XOP_FILE_REF fileRef,
	ColumnInfoPtr caPtr,
	char* buffer, int bufferLength,
	int numColumns,
	int fileLoaderFlags,
	int fileHasNamesRow,
	const char* baseName)
{
	ColumnInfoPtr ciPtr;
	int getNamesFromNamesRow;
	char* bufPtr;
	char ch;
	int nameSuffix;
	int column;
	int i;
	int err=0;


	getNamesFromNamesRow = fileHasNamesRow && (fileLoaderFlags & EVENT_COUNTS_ONLY);
	nameSuffix = -1;
	
	err = 0;
	if (fileHasNamesRow) {
		if (err = XOPReadLine(fileRef, buffer, bufferLength, NULL))
			return err;
	}
	else {
		*buffer = 0;
	}
	bufPtr = buffer;

	for (column = 0; column < numColumns; column++) {
		ciPtr = caPtr + column;
		if (getNamesFromNamesRow) {
			for (i = 0; i < 256; i++) {					// Column name assumed never longer than 256.
				ch = *bufPtr++;
				if (ch == 0)
					break;
				if (strchr(gSeparatorsStr, ch))			// Tab or comma separates one column from the next.
					break;
				if (i < MAX_OBJ_NAME)
					ciPtr->waveName[i] = ch;
			}
			if (err)
				break;									// File manager error.
		}
		else {		// Use default names.
			if (fileLoaderFlags & FILE_LOADER_OVERWRITE) {
				sprintf(ciPtr->waveName, "%s%lld", baseName, (SInt64)column);
			}
			else {
				nameSuffix += 1;
				if (err = UniqueName2(MAIN_NAME_SPACE, baseName, ciPtr->waveName, &nameSuffix))
					return err;
			}
		}
	
		SanitizeWaveName(ciPtr->waveName, column);		// Make sure it is a proper wave name.
	}
	
	return err;
}

/*	GetWaveNameList(caPtr, numColumns, waveNamesHandle)

	Stores semicolon-separated list of wave names in waveNamesHandle with
	a null terminating character at the end. This is used to set the
	Igor variable S_waveNames via SetFileLoaderOperationOutputVariables.
*/
static int
GetWaveNameList(ColumnInfoPtr caPtr, CountInt numColumns, Handle waveNamesHandle)
{
	ColumnInfoPtr ciPtr;
	char* p;
	int waveNamesLen;
	int column;
	
	waveNamesLen = 0;
	for (column = 0; column < numColumns; column++) {
		ciPtr = caPtr + column;
		if (ciPtr->waveHandle != NULL)						// We made a wave for this column ?
			waveNamesLen += (int)strlen(ciPtr->waveName)+1;	// +1 for semicolon.
	}
	SetHandleSize(waveNamesHandle, waveNamesLen+1);			// +1 for null char at end.
	if (MemError())
		return NOMEM;

	p = *waveNamesHandle;		// DEREFERENCE -- we must not scramble heap.
	for (column = 0; column < numColumns; column++) {
		ciPtr = caPtr + column;
		if (ciPtr->waveHandle != NULL) {					// We made a wave for this column ?
			strcpy(p, ciPtr->waveName);
			p += strlen(ciPtr->waveName);
			*p++ = ';';
		}
	}
	*p = 0;						// Add null char.

	return 0;
}

/*	LoadEvent(fileRef, baseName, fileLoaderFlags, wavesLoadedPtr, waveNamesHandle)
	
	Loads a simple tab-delimited TEXT file and returns error code.
	fileRef is the file reference for the file to be loaded.
	baseName is base name for new waves.
	fileLoaderFlags contains bit flags corresonding to flags the user
	supplied to the XOP.
	
	Sets *wavesLoadedPtr to the number of waves succesfully loaded.
	Stores in waveNamesHandle a semicolon-separated list of wave names
	with a null character at the end.
	*wavesLoadedPtr is initially a handle with 0 bytes in it.
*/
static int
LoadEvent(
	XOP_FILE_REF fileRef,
	const char* baseName,
	int fileLoaderFlags,
	int* wavesLoadedPtr,
	Handle waveNamesHandle)
{
	CountInt numRows;			//this is a not a normal value -- see FindNumberOfRows
	int numColumns;
	int column;									// Current column.
	int fileHasNamesRow;						// Truth file has column names.
	ColumnInfoPtr caPtr;						// Pointer to an array of records, one for each column. See EventLoadWave.h.
	ColumnInfoPtr ciPtr;						// Pointer to the record for a specific column.
	char* buffer;
	int bufferLength;
	int err;
	char bufStr[500];		//to print
	// for the file scan
	char buf[128];		//TB
	unsigned int lword;
	int scanOnly;
	
	caPtr = NULL;
	bufferLength = 20000;			// This is an arbitrary choice of maximum line length.
	buffer = (char*)NewPtr(bufferLength);
	if (buffer == NULL)
		return NOMEM;
	
	*wavesLoadedPtr = 0;

	// Find number of columns of data.
//	if (err = FindNumberOfColumns(fileRef, buffer, bufferLength, &numColumns))
//		goto done;

	numColumns = 3;		//force this to three (only because I want 3 output waves of my naming scheme
	
	
//	// Determine if file has column names.
//	if (err = XOPReadLine(fileRef, buffer, bufferLength, NULL))
//		goto done;
//	// File assumed to have column names if first char is alphabetic - a very simple-minded test.
//	fileHasNamesRow = isalpha(*buffer);
	fileHasNamesRow = 0;		//force this to false

	XOPSetFilePosition2(fileRef, 0);						// Go back to start of first row.
		
	// Make data structure used to input columns.
	caPtr = (ColumnInfoPtr)NewPtr(numColumns*sizeof(ColumnInfo));
	if (caPtr == NULL) {
		err = NOMEM;
		goto done;
	}
	MemClear((char *)caPtr, numColumns*sizeof(ColumnInfo));	
	
	err = GetWaveNames(fileRef, caPtr, buffer, bufferLength, numColumns, fileLoaderFlags, fileHasNamesRow, baseName);
	if (err)												// Error reading names ?
		goto done;
	
	// GetWaveNames leaves the file marker pointing to the numeric data.

	scanOnly = fileLoaderFlags & EVENT_COUNTS_ONLY;
// do a scan of the file to get the counts 
	// zero the counter
	counter.XYevents = 0;
	counter.num0 = 0;
	counter.num1 = 0;
	counter.num2 = 0;
	counter.num3 = 0;
	counter.zeros = 0;
	counter.t0 = 0;
	counter.major_rollover = 0;
	counter.minor_rollover = 0;
	counter.pp = 0;
	counter.dl = 0;		
	
	//process all of the events, one-by one, here I'm just getting the counts
	while(fgets(buf,sizeof(buf),fileRef)) {
		if (sscanf(buf,"%x",&lword)) {
			ScanEvents(lword);
		}
	}
	
	SetOperationNumVar("V_nXYevents", (double)counter.XYevents);
	SetOperationNumVar("V_num0", (double)counter.num0);
	SetOperationNumVar("V_num1", (double)counter.num1);
	SetOperationNumVar("V_num2", (double)counter.num2);
	SetOperationNumVar("V_num3", (double)counter.num3);
	SetOperationNumVar("V_numT0", (double)counter.t0);
	SetOperationNumVar("V_numPP", (double)counter.pp);
	SetOperationNumVar("V_numZero", (double)counter.zeros);
	
	sprintf(bufStr,"V_nXYevents = %d\r",counter.XYevents);
	XOPNotice(bufStr);

	if(scanOnly) {
		//close the file before leaving? - nope, LoadWave() wll do this on exit from here
		sprintf(bufStr,"Scan only...No event processing\r");
		XOPNotice(bufStr);
		return(0);			//get out before any waves are generated
	}
	
	
	/// not just a scan, now I have the counts, etc.
	XOPSetFilePosition2(fileRef, 0);						// Go back to start of first row.
	
	// Find number of rows in the file.
//	if (err = FindNumberOfRows(fileRef, buffer, bufferLength, &numRows))
//		goto done;
//	if (numRows < 1) {
//		err = NO_DATA_FOUND;
//		goto done;
//	}

	numRows = (CountInt)counter.XYevents;
	
//	sprintf(bufStr,"numCol = %d, numRows = %lld\r",numColumns,(SInt64)numRows);
//	XOPNotice(bufStr);
	
// from the manual for the MakeWave utility - integer types are only recommended for storage when there
	// is a great need to save space (there is here) - but that integers are internally translated into FP values
	// for any display or analysis. So just leave them as-is here, as FileLoaderMakeWave generates
	// Make wave for each column.
	for (column = 0; column < numColumns; column++) {
		ciPtr = caPtr + column;
		ciPtr->waveAlreadyExisted = FetchWave(ciPtr->waveName) != NULL;
		if (column==0 || column == 1) {
			// columns 0 and 1 are 
			err = FileLoaderMakeWave(column, ciPtr->waveName, numRows, fileLoaderFlags, &ciPtr->waveHandle);
		} else {
			// column 2 is the time, and needs to be DP
			err = FileLoaderMakeWave(column, ciPtr->waveName, numRows, (fileLoaderFlags | FILE_LOADER_DOUBLE_PRECISION), &ciPtr->waveHandle);
		}

//		sprintf(bufStr,"make wave = %d\r",column);
//		XOPNotice(bufStr);
		if (err) {
			sprintf(bufStr,"FileLoaderMakeWave returned an error  numCol = %d, numRows = %lld\r",numColumns,(SInt64)numRows);
			XOPNotice(bufStr);
			break;		// NOTE: In this case, not all fields in caPtr are set.
		}
	}
	
	if (err == 0) {
		// Lock wave handles and get pointers to wave data.
		for (column = 0; column < numColumns; column++) {
			ciPtr = caPtr + column;
			ciPtr->waveData = WaveData(ciPtr->waveHandle);		// ciPtr->waveData is now valid because the wave is locked.
		}
	
//		sprintf(bufStr,"Waves locked, ready to load\r");
//		XOPNotice(bufStr);
		
		// Load data. This is where the work is done
		err = LoadEventData(fileRef, buffer, bufferLength, fileLoaderFlags, caPtr, numRows, numColumns);
	}
	
	if (err==0) {
		// Clean up waves.
		for (column = 0; column < numColumns; column++)
			FinishWave(caPtr + column, fileLoaderFlags);
		*wavesLoadedPtr = numColumns;
	}
	else {
		// Error occurred - kill any waves that we created.
		for (column = 0; column < numColumns; column++) {
			ciPtr = caPtr + column;
			if (ciPtr->waveHandle && !ciPtr->waveAlreadyExisted) {	// We made a wave for this column ?
				KillWave(ciPtr->waveHandle);
				ciPtr->waveHandle = NULL;
			}
		}
	}
			
	// Get semicolon-separated list of wave names used below for SetFileLoaderOperationOutputVariables.
	if (err == 0)
		err = GetWaveNameList(caPtr, numColumns, waveNamesHandle);

done:
	if (buffer != NULL)
		DisposePtr(buffer);
	if (caPtr != NULL)
		DisposePtr((Ptr)caPtr);
	
	return err;
}

/*	GetLoadFile(initialDir, fullFilePath)

	GetLoadFile puts up a standard open dialog to get the name of the file
	that the user wants to open.
	
	initialDir is a full path to the directory to initially display in the
	dialog or "" if you don't care.
	
	It returns -1 if the user cancels or 0 if the user clicks Open.
	If the user clicks Open, returns the full path via fullFilePath.
*/
static int
GetLoadFile(const char* initialDir, char* fullFilePath)
{
	#ifdef MACIGOR
		const char* filterStr = "Data Files:TEXT:.dat;All Files:****:;";
	#endif
	#ifdef WINIGOR
		const char* filterStr = "Data Files (*.dat)\0*.dat\0All Files (*.*)\0*.*\0\0";	
	#endif
	char prompt[80];
	int result;
	
	static int fileIndex = 2;		// This preserves the setting across invocations of the dialog. A more sophisticated XOP would save this as a preference.

	*fullFilePath = 0;				// Must be preset to zero because on Windows XOPOpenFileDialog passes this to GetOpenFileName which requires that it be preset.
	
	strcpy(prompt, "Looking for a tab or comma-delimited file");
	result = XOPOpenFileDialog(prompt, filterStr, &fileIndex, initialDir, fullFilePath);

	return result;
}

/*	LoadWave(calledFromFunction, flags, baseName, symbolicPathName, fileParam)

	LoadWave loads data from the tab-delimited file specified by symbolicPathName and fileParam.
	
	calledFromFunction is 1 if we were called from a user function, zero otherwise.
	
	flags contains bits set based on the command line flags that were
	used when the command was invoked from the Igor command line or from a macro.
	
	baseName is the base name to use for new waves if autonaming is enabled by fileLoaderFlags.
	
	It returns 0 if everything goes OK or an error code if not.
*/
int
LoadWave(int calledFromFunction, int fileLoaderFlags, const char* baseName, const char* symbolicPathName, const char* fileParam)
{
	char symbolicPathPath[MAX_PATH_LEN+1];		// Full path to the folder that the symbolic path refers to. This is a native path with trailing colon (Mac) or backslash (Win).
	char nativeFilePath[MAX_PATH_LEN+1];		// Full path to the file to load. Native path.
	Handle waveNamesHandle;
	int wavesLoaded;
	XOP_FILE_REF fileRef;
	int err;

	*symbolicPathPath = 0;
	if (*symbolicPathName != 0) {
		if (err = GetPathInfo2(symbolicPathName, symbolicPathPath))
			return err;
	}
	
	if (GetFullPathFromSymbolicPathAndFilePath(symbolicPathName, fileParam, nativeFilePath) != 0)
		fileLoaderFlags |= FILE_LOADER_INTERACTIVE;		// Need dialog to get file name.
		
	if (!FullPathPointsToFile(nativeFilePath))			// File does not exist or path is bad?
		fileLoaderFlags |= FILE_LOADER_INTERACTIVE;		// Need dialog to get file name.

	if (fileLoaderFlags & FILE_LOADER_INTERACTIVE) {
		if (GetLoadFile(symbolicPathPath, nativeFilePath))
			return -1;							// User cancelled.
	}
	
	TellFileType("Event file load from", nativeFilePath, fileLoaderFlags);
	
	if (err = SetFileLoaderOperationOutputVariables(calledFromFunction, nativeFilePath, 0, ""))	// Initialize Igor output variables.
		return err;
	
	// Open file.
	if (err = XOPOpenFile(nativeFilePath, 0, &fileRef))
		return err;
	
	waveNamesHandle = NewHandle(0L);	// Will contain semicolon-separated list of wave names.
	WatchCursor();
	err = LoadEvent(fileRef, baseName, fileLoaderFlags, &wavesLoaded, waveNamesHandle);
	XOPCloseFile(fileRef);
	ArrowCursor();
	
	// Store standard file loader output globals.
	if (err == 0)
		err = SetFileLoaderOperationOutputVariables(calledFromFunction, nativeFilePath, wavesLoaded, *waveNamesHandle);

	DisposeHandle(waveNamesHandle);
	
	return err;
}

/*	XOPMenuItem()

	XOPMenuItem is called when the XOP's menu item is selected.
*/
static int
XOPMenuItem(void)
{
	char filePath[MAX_PATH_LEN+1];				// Room for full file specification.
	int fileLoaderFlags;
	int err;

	if (GetLoadFile("", filePath))
		return 0;								// User cancelled.
	
	fileLoaderFlags = EVENT_COUNTS_ONLY | FILE_LOADER_DOUBLE_PRECISION;
	err = LoadWave(0, fileLoaderFlags, "wave", "", filePath);
	return err;
}

/*	XOPEntry()

	This is the entry point from the host application to the XOP when the message specified by the
	host is other than INIT.
*/
extern "C" void
XOPEntry(void)
{	
	XOPIORecResult result = 0;
	
	switch (GetXOPMessage()) {
		case CLEANUP:								// XOP about to be disposed of.
			break;

		case MENUITEM:								// XOPs menu item selected.
			result = XOPMenuItem();
			SetXOPType(TRANSIENT);					// XOP is done now.
			break;
	}
	
	SetXOPResult(result);
}

/*	main()

	This is the initial entry point at which the host application calls XOP.
	The message sent by the host must be INIT.
	
	main does any necessary initialization and then sets the XOPEntry field of the
	XOPRecHandle to the address to be called for future messages.
*/
HOST_IMPORT int
XOPMain(IORecHandle ioRecHandle)
{
	int err;
	
	XOPInit(ioRecHandle);				// Do standard XOP initialization.
	SetXOPEntry(XOPEntry);				// Set entry point for future calls.

	if (igorVersion < 620) {			// Requires Igor Pro 6.20 or later.
		SetXOPResult(OLD_IGOR);			// OLD_IGOR is defined in EventLoadWave.h and there are corresponding error strings in EventLoadWave.r and EventLoadWaveWinCustom.rc.
		return EXIT_FAILURE;
	}
	
	if (err = RegisterEventLoadWave()) {
		SetXOPResult(err);
		return EXIT_FAILURE;
	}

	SetXOPResult(0);
	return EXIT_SUCCESS;
}
