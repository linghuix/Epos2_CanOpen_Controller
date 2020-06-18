#ifndef __HW_EPOS_H
#define __HW_EPOS_H

#include <conf_epos.h>
#include "epos_bsp.h"

#include <dict.h>

#include "canfestival.h"
#include "sdo_control.h"
#include "nmt_control.h"

extern Epos *Controller[];

void Epos_NodeEnable(void);
void Epos_ReceiveDate(void);
void Epos_Conroller_TIMBack(void);
void EPOS_Start(void);
void EPOS_Reset(void);
void Epos_PosSet(Epos* epos, Uint32 pos);

void Epos_ControlTask(void);

void Node_Initial_Postion(void);


#define Node_To_Home_Postion(e) Epos_PosSet(e,0)
#endif

