/*
 * canopen_interface.h
 *
 *  Created on: Mar 5, 2020
 *      Author: test
 */

#ifndef CANOPEN_INTERFACE_H_
#define CANOPEN_INTERFACE_H_


#include "canfestival.h"
#include "nmt_control.h"
#include "HW_epos.h"
#include "debug.h"

#define State_Hook_Enable
#define Lifgrd_Hook_Enable
#define SYN_Hook_Enable
#define EMCY_Hook_Enable




UNS32 Edit_Dict(CO_Data* d, Uint32 Index_Type,Uint8 SubIndex, void* pdata);

#endif /* CANOPEN_INTERFACE_H_ */
