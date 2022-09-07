/* ------------- menu.c ------------- */

#include "dfpcomp.h"

/* DFLat+ 1.0: Find command at the level of menu, not menubar */
static struct PopDown *FindCmd2(MENU *mn, int cmd)
{
    MENU *mnu = mn;
    while (mnu->Title != (void *)-1)    {
        struct PopDown *pd = mnu->Selections;
				if (pd == NULL) continue;
        while (pd->SelectionTitle != NULL)    {
            if (pd->ActionId == cmd)
                return pd;
            pd++;
        }
        mnu++;
    }
    return NULL;
}

static struct PopDown *FindCmd(MBAR *mn, int cmd)
{
		return FindCmd2 (mn->PullDown, cmd);
}


char *GetCommandText(MBAR *mn, int cmd)
{
    struct PopDown *pd = FindCmd(mn, cmd);
    if (pd != NULL)
        return pd->SelectionTitle;
    return NULL;
}

BOOL isCascadedCommand(MBAR *mn, int cmd)
{
    struct PopDown *pd = FindCmd(mn, cmd);
    if (pd != NULL)
        return pd->Attrib & CASCADED;
    return FALSE;
}

/* DFlat+ 1.0: isCascadedCommand2 based on MENU, not MENUBAR */
BOOL isCascadedCommand2(MENU *mn, int cmd)
{
    struct PopDown *pd = FindCmd2(mn, cmd);

    if (pd != NULL)
        return !!(pd->Attrib & CASCADED);
      
    return FALSE;
}

void ActivateCommand(MBAR *mn, int cmd)
{
    struct PopDown *pd = FindCmd(mn, cmd);
    if (pd != NULL)
        pd->Attrib &= ~INACTIVE;
}

void DeactivateCommand(MBAR *mn, int cmd)
{
    struct PopDown *pd = FindCmd(mn, cmd);
    if (pd != NULL)
        pd->Attrib |= INACTIVE;
}

BOOL isActive(MBAR *mn, int cmd)
{
    struct PopDown *pd = FindCmd(mn, cmd);
    if (pd != NULL)
        return !(pd->Attrib & INACTIVE);
    return FALSE;
}

BOOL GetCommandToggle(MBAR *mn, int cmd)
{
    struct PopDown *pd = FindCmd(mn, cmd);
    if (pd != NULL)
        return (pd->Attrib & CHECKED) != 0;
    return FALSE;
}

void SetCommandToggle(MBAR *mn, int cmd)
{
    struct PopDown *pd = FindCmd(mn, cmd);
    if (pd != NULL)
        pd->Attrib |= CHECKED;
}

void ClearCommandToggle(MBAR *mn, int cmd)
{
    struct PopDown *pd = FindCmd(mn, cmd);
    if (pd != NULL)
        pd->Attrib &= ~CHECKED;
}

void InvertCommandToggle(MBAR *mn, int cmd)
{
    struct PopDown *pd = FindCmd(mn, cmd);
    if (pd != NULL)
        pd->Attrib ^= CHECKED;
}
