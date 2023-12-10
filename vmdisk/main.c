/* VMDISK is image file creation of FDD disks for boot into MVM. */

#include <os2.h>
#include <bsedev.h>

#include <stdio.h>
#include <stdlib.h>

typedef
	struct tagIMAGEHEADER
	{
		BYTE	Flags;
		BYTE	Heads;
		WORD	Tracks;
		WORD	Sectors;
		WORD	Bytes;
	} IMAGEHEADER;

typedef struct tagparmList
	{
		UCHAR command;
		UCHAR drive;
	} parmList;

/*
 * error() - Display message, error number and exit program
*/
void error(char *msg, int error)
{
	fprintf(stderr, "Error %d - %s\n", error, msg);
	exit(error);
}

void main(void)
{
	HFILE hfDrive;
	HFILE hfFile;
	ULONG ulActionTaken;
	IMAGEHEADER ihImageHeader;
	BIOSPARAMETERBLOCK bpb;
	ULONG bpbLength = sizeof(bpb);
	parmList parm;
	ULONG parmLength   = sizeof(parm);
	ULONG ulWrote;
	APIRET rc;      /* return code */

	rc=DosOpen("A:",
		&hfDrive,
		&ulActionTaken,
		0,
		0,
		OPEN_ACTION_OPEN_IF_EXISTS,
		OPEN_FLAGS_DASD | OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE,
		0);
	if (rc != NO_ERROR)
		error("DosOpen", rc);

	/*
	 * Lock the drive
	*/
	rc = DosDevIOCtl(
        	hfDrive,
	        IOCTL_DISK,                  /* device catagory          */
	        DSK_LOCKDRIVE,                  /* function code            */
	        0,                      /* parameter packet address */
	        0,                      /* parm list length         */
	        0,                      /* parm list length address */
	        0,                      /* address of extended BPB  */
	        0,                      /* length of extended BPB   */
	        0);                     /* address of ext BPB len   */
	if (rc != NO_ERROR)
		error("DosDevIOCtl lock", rc);

	/*
	 * Get the device parameters
	 * (BPB = BIOS Parameter Block)
	*/
	parm.command = 1;           /* return the BPB for the media
                                   currently in the drive   */
	rc = DosDevIOCtl(
        	hfDrive,
	        IOCTL_DISK,             /* device catagory          */
	        DSK_GETDEVICEPARAMS,    /* function code            */
	        &parm,                  /* parameter packet address */
	        parmLength,             /* parm list length         */
	        &parmLength,
	        &bpb,                /* address of extended BPB  */
	        bpbLength,           /* length of extended BPB   */
	        &bpbLength);

	/*
	 * Unlock the media
	*/      	
	rc = DosDevIOCtl(
		hfDrive,
		IOCTL_DISK,                  /* device catagory          */
		DSK_UNLOCKDRIVE,                  /* function code            */
		0,                      /* parameter packet address */
	        0,                      /* parm list length         */
	        0,                      /* parm list length address */
	        0,                      /* address of extended BPB  */
	        0,                      /* length of extended BPB   */
	        0);                     /* address of ext BPB len   */
	if (rc != NO_ERROR)
		error("DosDevIOCtl unlock", rc);

      	rc=DosClose(hfDrive);
	if (rc != NO_ERROR)
        	error("DosClose", rc);

	ihImageHeader.Flags = 0;
	ihImageHeader.Heads = (BYTE)bpb.cHeads;
	ihImageHeader.Tracks = bpb.cSectors / (bpb.usSectorsPerTrack * bpb.cHeads);
	ihImageHeader.Sectors = bpb.usSectorsPerTrack;
	ihImageHeader.Bytes = bpb.usBytesPerSector;

	/* Open the file.  Use an existing file or create a new */
	/* one if it doesn't exist.                                      */
	rc = DosOpen("test.img",                    /* File path name */
		&hfFile,                  /* File handle */
		&ulActionTaken,                      /* Action taken */
                100L,                           /* File primary allocation */
                FILE_ARCHIVED | FILE_NORMAL,    /* File attribute */
                OPEN_ACTION_CREATE_IF_NEW |
                OPEN_ACTION_OPEN_IF_EXISTS,     /* Open function type */
                OPEN_FLAGS_NOINHERIT |
                OPEN_SHARE_DENYNONE  |
                OPEN_ACCESS_READWRITE,          /* Open mode of the file */
                0L);                            /* No extended attribute */

	if (rc != NO_ERROR)
		error("DosOpen", rc);

	rc = DosWrite(hfFile,                /* File handle */
		(PVOID)&ihImageHeader,         /* String to be written */
		sizeof(ihImageHeader),        /* Size of string to be written */
		&ulWrote);                   /* Bytes actually written */

	if (rc != NO_ERROR)
		error("DosWrite", rc);

	rc = DosClose(hfFile);                /* Close the file */

	if (rc != NO_ERROR)
		error("DosClose", rc);

	// Read track by track and write to image file

}

