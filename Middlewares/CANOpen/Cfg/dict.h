
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef _epos_dict_H
#define _epos_dict_H

#include "data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 TestMaster_valueRangeTest (UNS8 typeValue, void * value);
const indextable * TestMaster_scanIndexOD (CO_Data *d, UNS16 wIndex, UNS32 * errorCode);

/* Master node data struct */
extern CO_Data TestMaster_Data;
extern INTEGER32 Pos_Actual_Val;
#endif // TESTMASTER_H
