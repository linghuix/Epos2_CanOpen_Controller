#ifndef __gait_H__
#define __gait_H__
#include "stdint.h"
#include "app.h"


extern int test_angle[114];


extern float hip_flexion[50], knee_flexion[50];

//#define ArrayMaxSize 10
typedef struct {
	int * LKArrayName;
	int * LHArrayName;
	int * RKArrayName;
	int * RHArrayName;
	int len[4];								// length of curve len[0] for LK, len[1] for LH and so on.
	uint16_t RunNumber;
}trajectory;

void gait_init(void);
void addCuve(int *LK,int *LH, int *RK, int *RH, int len[],uint8_t times);
trajectory getCurve(void);


#endif
