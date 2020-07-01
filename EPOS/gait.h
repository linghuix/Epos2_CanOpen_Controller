#ifndef __gait_H__
#define __gait_H__
#include "stdint.h"

extern int test_angle[114];


extern float hip_flexion[50], knee_flexion[50];

#define ArrayMaxSize 10
typedef struct {
	int * ArrayName[ArrayMaxSize];
	uint16_t RunNumber;
}trajectory;


#endif
