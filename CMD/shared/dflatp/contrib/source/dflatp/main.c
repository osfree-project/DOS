/* ------------ main .c ------------ */

#include "dfpcomp.h"

SysConfigType SysConfig = {
	  {FALSE,255},             /* Current Color Scheme */
	  {80,25,FALSE,"No set"},  /* Resolution */
	  FALSE,                   /* Snowy? */
	  ':',                     /* Country: Time separator */
	  8,                       /* Editor Tab Size */
	  FALSE                    /* Editor Global Read-only */
};



int main(int argc, char *argv[])
{
	
		int ExitCode=0;

		/* Intro message */
    printf("%s (%i.%i.%i.%i)\n", ProgramModule.Description,ProgramModule.Ver_maj,ProgramModule.Ver_min,ProgramModule.Ver_rel,ProgramModule.Ver_patch);
		printf("(based on FreeDOS DFlat+ %i.%i application framework)\n", DFlatpModule.Ver_maj,DFlatpModule.Ver_min);

	  /* Prepare initial configuration */
   	SelectColorScheme (color);			/* Color Scheme */

    {
#if defined(__TURBOCPP__)
    struct country mycountry;
    static union REGS regs;

    if ( country(0, &mycountry) )
      SysConfig.CountryTimeSeparator = mycountry.co_tmsep[0];
#else
#ifdef __WATCOMC__
    char mycountry[48];	/* probably 34 bytes are enough... */
    union REGS r;
    struct SREGS s;

    r.w.ax = 0x3800;
    s.es = 0;
    s.ds = FP_SEG(&mycountry);
    r.w.dx = FP_OFF(&mycountry);
	  int86x (DOS, &r, &r, &s);

     if (CFlag(r) == 0)
        SysConfig.CountryTimeSeparator = mycountry[13];
#else
    char mycountry[48];	/* probably 34 bytes are enough... */
    union REGS r;
    struct SREGS s;

    r.x.ax = 0x3800;
    s.es = 0;
    s.ds = FP_SEG(&mycountry);
    r.x.dx = FP_OFF(&mycountry);
	  int86x (DOS, &r, &r, &s);

     if (CFlag(r) == 0)
        SysConfig.CountryTimeSeparator = mycountry[13];
#endif
#endif
    }


		/* Start other services */
 		CustomizeDisplayPropBox ();

    
    /* -- All tests of all things required to run the DFLAT+ Application --*/
    if (!init_messages())
    {
    		puts ("DFLAT+: Unable to start the messaging system. Please contact the FreeDOS team");
        return (-1);
    }
  

    /* -- Here runs the main application --*/
    
    ExitCode = DfpMain (argc, argv);
    
    /* -- Finalization routines --*/
    
    return (ExitCode);

}

