
#include "gait.h"

/*int test_angle[24] = {	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
							500,0,
							(0.0),0.0,0.0,0.0,0.0,
							(0.0),0.0,0.0,0.0,0.0,
							0,500};
*/
int test_angle[114] = {500, 
1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
500,0, -500,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-500, 0};


float hip_flexion[50] = {28.237,27.53,26.662,25.546,24.135,22.423,20.469,18.409,16.358,14.332,12.297,10.229,8.136,6.069,4.064,2.153,0.341,-1.363,-2.986,-4.531,-6.007,-7.399,-8.683,-9.837,-10.814,-11.531,-11.848,-11.586,-10.581,-8.744,-6.111,-2.832,0.895,4.868,8.909,12.829,16.48,19.735,22.537,24.883,26.794,28.29,29.369,30.06,30.427,30.561,30.551,30.452,30.282,29.988};

float knee_flexion[50] = {7.102,8.449,10.158,11.772,12.992,13.599,13.527,12.995,12.22,11.283,10.256,9.193,8.152,7.174,6.271,5.442,4.702,4.079,3.597,3.299,3.222,3.418,3.947,4.855,6.2,8.084,10.621,13.945,18.181,23.361,29.341,35.748,42.002,47.489,51.734,54.476,55.651,55.3,53.502,50.384,46.118,40.922,35.037,28.801,22.629,16.957,12.215,8.741,6.708,6.017};

#define trajectory_N 5

/*curve queue*/
OS_EVENT * Trajectory_Q_1;
void * trajectoryPointer_1[trajectory_N];
trajectory trajectoryBuffer_1[trajectory_N];
uint16_t CurrentTrajectoryIndex = 0;

// init a trajectory queue
void gait_init(void)
{
	Trajectory_Q_1 = OSQCreate(&trajectoryPointer_1[0],5);
}

// addCuve(knee_flexion,hip_flexion, knee_flexion, hip_flexion, {50,50,50,50}, 5)
void addCuve(int *LK,int *LH, int *RK, int *RH, int len[],uint8_t times)
{
	uint8_t err;
	trajectoryBuffer_1[CurrentTrajectoryIndex].LHArrayName = LH;
	trajectoryBuffer_1[CurrentTrajectoryIndex].LKArrayName = LK;
	trajectoryBuffer_1[CurrentTrajectoryIndex].RHArrayName = RH;
	trajectoryBuffer_1[CurrentTrajectoryIndex].RKArrayName = RK;
	trajectoryBuffer_1[CurrentTrajectoryIndex].RunNumber = times;
	for(uint8_t i=0;i<4;i++){
		trajectoryBuffer_1[CurrentTrajectoryIndex].len[i] = len[i];
	}
	
	if((err = OSQPost(Trajectory_Q_1, &trajectoryBuffer_1[CurrentTrajectoryIndex])) != OS_ERR_NONE){
		if(err == OS_ERR_Q_FULL){																	// queue is full
			ERROR(5,"Trajectory_Q_1 is full  Size>%d", ((OS_Q *)Trajectory_Q_1->OSEventPtr)->OSQSize);
		}
	}
	else{
		CurrentTrajectoryIndex++;																	// index move on
		if(CurrentTrajectoryIndex == trajectory_N){													// loop
			CurrentTrajectoryIndex=0;
		}
	}
}

//get trajectory struct, if empty return with zero tra.RunNumber.
trajectory getCurve(void)
{
	trajectory * ptra;
	trajectory tra = {0};
	uint8_t error;
	if((ptra = (trajectory *)OSQAccept(Trajectory_Q_1, &error)) != (void *)0)						//no suspending just like QSQPost
	{
		tra.LHArrayName = ptra->LHArrayName;
		tra.LKArrayName = ptra->LKArrayName;
		tra.RHArrayName = ptra->RHArrayName;
		tra.RKArrayName = ptra->RKArrayName;
		tra.RunNumber = ptra->RunNumber;
		for(int8_t i = 0; i < 4;i++){
			tra.len[i] = ptra->len[i];
		}
		return tra;
	}
	else
	{
		return tra;
	}
}
