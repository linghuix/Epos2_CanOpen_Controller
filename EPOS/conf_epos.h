#ifndef EPOS_H
#define EPOS_H

#define SDO

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include "epos_bsp.h"


#include "canfestival.h"
#include <dict.h>
//demand value 只是表示输入控制器的数值，只是经过规划器规划而已，并不是实际的数值


//------------------------------------------------------------------------
//define variables  定义变量类型
//------------------------------------------------------------------------

//typedef char                    int8;
//typedef int                     int16;
//typedef long                    int32;
typedef uint8_t                 Uint8;
typedef uint16_t                Uint16;
typedef uint32_t                Uint32;
typedef uint8_t                 BOOL;
typedef uint16_t                stcCAN;

#define NOT_USED 0

extern  Uint32  epos_err_LK;
extern  Uint32  epos_err_LH;
extern  Uint32  epos_err_RK;
extern  Uint32  epos_err_RH;

extern Uint32   buffer_size_LK;    
extern Uint32   buffer_size_LH;
extern Uint32   buffer_size_RK;
extern Uint32   buffer_size_RH;

extern Uint32   status_LK;          //0为未使能，1为PPM

extern Uint32 pos_value_LK;
extern Uint32 pos_value_LH;
extern Uint32 pos_value_RK;
extern Uint32 pos_value_RH;

#define NODE_LK (1) /* epos 24/5的节点ID */
#define NODE_LH (2) /* epos 70/10的节点ID */
#define NODE_RK (3) /* epos 24/5的节点ID */
#define NODE_RH (4) /* epos 70/10的节点ID */

/************常数*************/

#define PPMODE 0x01
#define MAX_ACC 50000
#define MAX_DEC 50000
#define MODE_NONE 0x00
#define MAX_F_ERR 2000
#define MAX_P_V 5000//4000
#define QDEC MAX_ACC
#define ALL 0



enum Profile_Position_Mode
{
    Profile_Position_Mode = (uint8_t)(1),//目标位置为零

	/*CONFIGURE*/
	Position_window = 0x60670020,			//到达目标点的识别范围
	Position_window_time = 0x60680010,
    Soft_P_Limit_Min = 0x607D0120,  //软件限制
	Soft_P_Limit_Max = 0x607D0220,  //软件限制
	Max_Profile_Velocity = 0x607F,
	Q_deceleration = 0x607F,
	Max_Acceleration = 0x60C5,

	/*COMMAND*/
	Controlword = 0x6040,         //绝对相对设定等功能
	Target_pos = 0x607A0020,
	Profile_Velocity = 0x60810020,      //规划路径的最大速度
	Profile_Acceleration = 0x60830020,  //规划路径max Acceleration
	Profile_Deceleration = 0x60840020,  //min Deceleration
	Motion_Profile_Type = 0x60860010,

	/*OUT*/
	//Pos_Demand_Value = 0x6062,
	Statusword = 0x60410010,
};

enum Position_Mode
{
	Position_Mode  = 0xFF,		// -1

	/*CONFIGURE*/
	Max_allowed_speed =0x64100420,
	Position_Setpoint_Scaling = 0x23030110,
	Position_Setpoint_Offset = 0x23030220,
	Position_Setpoint_Notation_Index = 0x23030308,
	Position_Setpoint = 0x23010420,
	/*Max_Profile_Velocity = 0x607F,
	Max_Acceleration = 0x60C5,
	Soft_P_Limit_Min = 0x607D0120,  //软件限制
	Soft_P_Limit_Max = 0x607D0220,  //软件限制*/

	/*COMMAND*/
	Pos_SET_VALUE = 0x20620020,

	/*OUT*/
	Pos_Demand_Value = 0x60620020,	 	//轨迹生成的点
	Pos_Actual_Value = 0x60640020,
	//Position_Setpoint = 0x23030420,
};

enum Current_Mode
{
    Current_Mode  = 0xFD,

	/*CONFIGURE*/
	//Max_allowed_speed =0x641004,
	Current_Setpoint_Scaling = 0x23010110,
	Current_Setpoint_Offset = 0x23010210,
	Current_Setpoint_Notation_Index = 0x23010308,
	Current_Setpoint = 0x23010410,

	/*COMMAND*/
	CM_SET_VALUE = 0x2030,

	/*OUT*/
	Current_Demand_Value = 0x2031,
	Current_Actual_Value = 0x60780010,
	//Current_Setpoint = 0x23010410,
};

enum Velocity_Mode
{
    Velocity_Mode = 0xFE,
    
    /*CONFIGURE*/
    
    /*COMMAND*/
    VM_SET_VALUE = 0x206B0020,
    
    /*OUT*/
    Velocity_Demand_Value = 0x606B0020,
	Velocity_Actual_Value = 0x606C0020,
	Velocity_Actual_Value_Filtered = 0x20280020,

};

enum Homing_Mode
{

    Homing_Mode = (uint8_t)6,
    /*CONFIGURE*/
    
    /*COMMAND*/
    //Controlword = 0x6040,
    Homing_Method = 0x6098,
    Homing_Speeds = 0x6099,
    Homing_Acceleration = 0x609A,
    Home_Offset = 0x607C,
    Current_Threshold = 0x2080,
    Home_Pos = 0x2081,

    /*OUT*/
    //Statusword = 0x6041,          //是否复位
};

enum Interpolated_Position_Mode
{
    Interpolated_Position_Mode = (uint8_t)7,
        /*COMMAND*/
        //Controlword = 0x6040,
        Interpolation_Data_Record = 0x20C1, //a FIFO 启动前必须包含至少两个数据点，否则无法规划轨迹。最好使用PDO进行数据传输

        /*OUT*/
        //Statusword = 0x6041, //是否复位
        Interpolation_Buffer = 0x20C4,  //FIFO 缓冲区 的状态
        //Pos_Demand_Value = 0x6062,
};

enum Profile_Velocity_Mode
{
    Profile_Velocity_Mode = (uint8_t)3,//目标位置有速度
    /*COMMAND*/
    
    //Controlword = 0x6040,
    Target_Velocity = 0x60FF0020,          //目标位置的速度
    //Profile_Acceleration = 0x6083,  //max Acceleration
    //Profile_Deceleration = 0x6084,  //min Deceleration
    //Motion_Profile_Type = 0x6086,
    
    /*OUT*/
    //Velocity_Demand_Value = 0x606B,
    //Statusword = 0x6041,
};

//模式  index+interger
enum E_OBJ_MODE
{
    OP_MODE = 0x60600008,           //Modes of operation, Sub-index 0x00, INTEGER8
	OP_MODE_Read = 0x60610008,      //Modes of operation display, Subindex 0x00 ,INTEGER8  RO

    Diagnostic_Mode = 0xFC,
    Master_Encoder_Mode = 0xFB,
    Step_Direction_Mode = 0xFA,

};


// E_OBJ_DICTIONARY 类型的枚举，类似于define. 参考手册见 EPOS2 Firmware Specification.pdf P110
enum E_OBJ_DICTIONARY
{
    Fault_Reset = 0x80,   //重置错误
    
    OD_ERR_REG = 0x1001,    //error register, Index 0x1001, Sub-index 0x00, UNSIGNED8

    OD_ERR_HIS = 0x1003,    //error history, Index 0x1003,  number of entries 0x05
        SI_ERR_CNT = 0x00,  //number of errors
        SI_ERR_HIS1 = 0x01, //error history [1],Index 0x1003,Sub-index 0x01, UNSIGNED32
        SI_ERR_HIS2 = 0x02, //error history [2],Index 0x1003,Sub-index 0x02, UNSIGNED32
        SI_ERR_HIS3 = 0x03, //error history [3],Index 0x1003,Sub-index 0x03, UNSIGNED32
        SI_ERR_HIS4 = 0x04, //error history [4],Index 0x1003,Sub-index 0x04, UNSIGNED32
        SI_ERR_HIS5 = 0x05, //error history [5],Index 0x1003,Sub-index 0x05, UNSIGNED32

    OD_STORE = 0x1010,      //Save all Parameters, Subindex 0x01, Type UNSIGNED32
        SAVE_Code = 0x73617665,

    OD_CAN_BITRATE = 0x20010010, //Subindex 0x00, Type UNSIGNED16

    OD_CURRENT_AVG = 0x2027, //Current Actual Value Averaged, Subindex 0x00,Type INTEGER16

    //OD_CM_SET = 0x2030, //Setting value of current regulator in current mode [mA], Sub-index 0x00, INTEGER16

    OD_ANALOG_IN = 0x207C,//analog inputs, number of entries 2
        SI_ANALOG1 = 0x01,  //analog input 1, Index 0x207C, Sub-index 0x01,Type INTEGER16, analog input 1 [mV].
        SI_ANALOG2 = 0x02,  //analog input 2, Index 0x207C, Sub-index 0x02,Type INTEGER16,The voltage measured at analog input 2 [mV].

    Max_gear_input_speed = 0x30030020,//Subindex 0x03, UNSIGNED32
		
		OD_CTRL_WORD = 0x60400010,      /*controlword, UNSIGNED16,
                                  bit6 Operation mode specific: 0: Abs;  1: rel
                                 */
    //OD_STATUS_WORD = 0x60410010, //Statusword, Sub-index 0x00, UNSIGNED16

    OD_ACTUAL_POS = 0x60640020,     //actual position, Sub-index 0x00, INTEGER32,

    OD_Following_ERR_window = 0x60650020,   //Following error window, Sub-index 0x00, UNSIGNED32
		
    OD_Position_Window = 0x6067,//实际意义参考 firmware pdf
    Pos_Window_Time = 0x6068,   //进入Position_Window的时间，单位ms
    
    
    OD_CURRENT_VAL = 0x60780020,    //Current Actual Value, Index 0x6078, Subindex 0x00,Type INTEGER16
    OD_TARGET_POS = 0x607A0020,     /*target position, Sub-index 0x00, INTEGER32,
                                  units steps (quadcounts = 4*Encoder Counts / Revolution)*/
                                  
    
    OD_MAX_P_VELOCITY = 0x607F0020, //UNSIGNED32, [1, 25000]

		OD_MAX_MOTOR_SPEED = 0x60800020, //0x00, UNSIGNED32,

    OD_P_VELOCITY = 0x6081,     //Profile velocity, Sub-index 0x00, UNSIGNED32, Unit:rpm
    OD_P_ACCELERATION = 0x60830020, //profile acceleration, Sub-index 0x00,UNSIGNED32
    OD_P_DECELERATION = 0x60840020, //profile deceleration, Sub-index 0x00,UNSIGNED32
    OD_QS_DECELERATION =  0x60850020, //quick stop deceleration, Sub-index 0x00, UINT32
    
    OD_Motion_Profile_Type = 0x60860010,
    
    OD_Interpolation_Sub_Mode = 0x60C0,
    Interpolation_Time_Period_1 = 0x60C20108,//time between two PDOs
		Interpolation_Time_Period_2 = 0x60C20208,//unit   -3对应ms
	
    Interpolation_Data_Configuration = 0x60C4,
    
    OD_Max_Acceleration = 0x60C50020,

    OD_TARGET_VELOCITY = 0x60FF0020,  //target velocity, Sub-index 0x00, INTEGER32
    OD_MOTOR_DATA = 0x6410,  //motor data, number of entries 0x06,具体含义参照firmware
		OD_MOTOR_DATA_MAX_V = 0x64100420,  //motor data, number of entries 0x06,具体含义参照firmware
		OD_MOTOR_DATA_continue_I = 0x64100120,
		OD_MOTOR_DATA_MAX_I = 0x64100220,
		OD_MOTOR_DATA_MAX_MPP = 0x64100320,
		OD_MOTOR_DATA_TH_CONT = 0x64100520
};


#define EPOS_DELAY1  5          //5ms
#define EPOS_DELAY2  50
#define EPOS_DELAY3  62.5


// CAN 类型
struct  CANMSGID_BITS {        // bits  description
   Uint16      EXTMSGID_L:16;  // 0:15
   Uint16      EXTMSGID_H:2;   // 16:17
   Uint16      STDMSGID:11;    // 18:28
   Uint16      AAM:1;          // 29, The auto answer mode bit
   Uint16      AME:1;          // 30, The acceptance mask enable bit
   Uint16      IDE:1;          // 31, The identifier extension bit

};

/* Allow access to the bit fields or entire register */
union CANMSGID_REG {
   Uint32                all;
   struct CANMSGID_BITS  bit;
};


typedef struct CANFrame_t
{
    union CANMSGID_REG  msg_id;
    Uint32  low_4byte;
    Uint32  high_4byte;
    Uint8   DataLen;
    BOOL    IsExtend;
    BOOL    IsRemote;
}stcCANFrame;


//EPOS控制器对象
typedef struct __Epos
{
    stcCAN* CAN_Handles;//EPOS
    
    stcCANFrame buf;        //EPOS一帧数据的缓冲区
    
    BOOL b_init;                //Epos是否初始化的标志
    
    Uint8 node_ID;          //CANOPEN网络所在EPOS控制器的ID
    Uint8 cur_mode;         //EPOS的工作模式
    
    Uint32 opt;              //EPOS用于保存PPMODE下的opt参数
    Uint32 acc;                  //EPOS的加速度
    Uint32 dec;                  //EPOS的负加速度
    
    BOOL b_need_shutdown;   //是否需要关断EPOS对的标志
    
}Epos;



//------------------------------------------------------------------------
//define functions
//------------------------------------------------------------------------



//CANOpen
void EposMaster_Init(void);
void EposMaster_Start(void);
void EposMaster_Stop(void);

extern void Node_PDOConfig(Epos* A);
extern void NMT_Start(Epos* epos, Uint32 ID);
void NMT_Pre(Epos* epos, Uint32 ID);

void Print(CanRxMsg RxMessage);//打印接收到的CAN帧
        
//EPOS

//extern BOOL Epos_start_Read(Epos* epos,Uint16 Index,Uint8 SubIndex, int fd1);

//extern BOOL Epos_end_Read(Epos* epos, Uint32 *p_param, int fd1);

extern void Node_StructInit(Epos* epos1, Uint8 CAN_ID, Uint8 NODE_ID);

extern void Node_ParamConfig(Epos* epos);

extern void Epos_Delay(Uint32 time);

//extern Uint32 changeIntOrder(Uint32 param);

void Node_setMode(Epos* epos, Uint16 mode);        //设定控制器的工作模式

void Node_OperEn(Epos* epos);                   //从 Switch On Disable 到 Operation Enable


//Control Funtional
void PM_SetAngle(Epos* epos, Uint32 angle);//Postion Mode
//extern void Epos_Write_PVT(Epos* epos, Uint16 Index, Uint8 SubIndex, Uint32 param1, Uint32 param2, Uint8 param3);
//------------------------------------------------------------------------
#endif // EPOS_H
