#include <stdio.h>
#include <string.h>

#define INCL_VDM
#include <os2vdm.h> /* system header */

APIRET syntax(void)
{
//   cmd_ShowSystemMessage(cmd_MSG_DISKCOPY_HELP,0L);
   return 0;
}

//**************************************************************************
// Start of program
//**************************************************************************
int main (int argc, char* argv[], char* envp[])
{
  int argi;
  int iteration;
  char drive[3] = {0};
  char path[256] = {0};

    if (argc == 1)
    {
        return syntax();
    }

    for (argi = 1; argi < argc; argi++)
    {
        if ((argv[argi][0] == '-') || (argv[argi][0] == '/'))
        {
            switch (argv[argi][1])
            {
                case 'h':
                case 'H':
                case '?':
                case '-':
                    return syntax();


                default:
                    fprintf(stderr, "Unknown options '%s'.\n", argv[argi]);
                    return 0;//NO_ERROR;
            }
        } else {
			iteration++;
			if (iteration==1)
			{
				strcpy(drive, argv[argi]);
			} else if (iteration==2)
			{
				strcpy(path, argv[argi]);
				VdmSubstSet(drive[0], path);
				return 0;
			}
		}
	}
	return syntax();
}
