
#include <conf_epos.h>
#include "HW_epos.h"
#include "nmt_control.h"



UNS8 masterNMT(CO_Data*d, Epos* epos,UNS8 cs)
{
	return masterSendNMTstateChange (d, epos->node_ID, cs);
}
