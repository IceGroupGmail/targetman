#if !defined(AFX_POWER_MODBUS__C9BEE721_A8E7_44C8_9802_107CA28C518F__INCLUDED_)
#define AFX_POWER_MODBUS__C9BEE721_A8E7_44C8_9802_107CA28C518F__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "power_crc.h"
#include <set>
#include <map>
#include <vector>
#include <list>
using namespace std;

#ifdef WIN32
#pragma warning(disable:4786)
#endif
enum LOCATION
{
	LOCATION_ON = 0x70,//�Ƿ�λ
	LOCATION_LONGITUDE = 0x01,//����
	LOCATION_LATITUDE = 0x02,//ά��
};
enum FAULT_INFORMATION
{
	FAULT_TARGET_BOARD_D0 = 1,//����а����
	FAULT_OPTIMAL_SENSOR_D1 = 2,//��紫��������
	FAULT_CURRENT_SAMPLE_D2 = 4,//����������·����
	FAULT_POWER_CICUIT_D3 = 8,//������·����
	FAULT_MOTOR_BLOCK_D4 = 16,//�����ת
	FAULT_MOTORS_ENSOR_D5 = 32//�������������
};
enum  MOVE_STATUS
{
	MOVE_STOP_D15 = 0xF000, //��ֹOR�˶�
	MOVE_STAND_UP = 0x0001, //	0 δ֪	1 �� 	2 ��
	MOVE_LAYDOWN =  0x0002, //D0~D3:��D0~D3��ʾ��״̬

};
enum REGISTER_TARGET
{
	TARGET_LOCATION = 0x0001,

	TARGET_LONGITUDE_DEGREE = 0x0002,
	TARGET_LONGITUDE_MINUTE = 0x0003,
	TARGET_LONGITUDE_MINUTE_DECIMAL = 0x0004,

	TARGET_ALTITUDE_DEGREE = 0x0005,
	TARGET_ALTITUDE_MINUTE = 0x0006,
	TARGET_ALTITUDE_MINUTE_DECIMAL = 0x0007,
	TARGET_FAULT_INFORMATION = 0x0008,

	TARGET_MOVE_STATUS = 0x0009, //�˶�״̬
	TARGET_BATTERY = 0x000A,//��ص���
	TARGET_HIT_BULLETS = 0x000B,//���е���
	TARGET_HIT_POINTS = 0x000C,//���л���

	TARGET_DEVICETYPE = 0x0101,//	�豸����
	TARGET_DEVICENO   = 0x0102,//	�豸���
	TARGET_DEVICEMODE = 0x0103,//	ͨ��ģʽ
	TARGET_DEVICENO1 = 0x0104,//	�豸��1
	TARGET_DEVICENO2 = 0x0105,//	�豸��2
	TARGET_PARAMETER = 0x0106,//	����
	TARGET_PARA      = 0x0107,//	������

	TARGET_RESET = 0x0201,//��λ
	TARGET_POSTURE_CONTROL = 0x0202,//��	�𡢵����ٶȣ�5����
	TARGET_LIGHT_CONTROL   = 0x0203,//�ƹ����	���������ȣ�5����
	TARGET_HIT_SETTING     = 0x0204 //���е�������	���������ָ������
};

enum REGISTER_CAR
{
	CAR_SPEED = 0x0001,//�ٶ�2���ֽ�
	CAR_POSITION = 0x0002,//λ��2���ֽ�
	CAR_MODE = 0x0003,//ģʽ2���ֽ�
	CAR_ERROR_CODE = 0x0004,//����2���ֽ�
	CAR_INITILIZE = 0x0101,//��ʼ��	2���ֽ�
	CAR_BREAKER  = 0x0102,//ɲ��	2���ֽ�
	CAR_CURVE_ANGLE = 0x0103,//������ʻ - �Ƕ�	2���ֽ�
	CAR_CURVE_RADIUS = 0x0104,//������ʻ - ת��뾶	2���ֽ�
	CAR_LINE_DISTANCE = 0x0105,//ֱ����ʻ - ��ʻ����	2���ֽ�
	CAR_LINE_TAP = 0x0106,//ֱ����ʻ - �ٶȵ�λ	2���ֽ�
	CAR_RELEASE = 0x0107,//�ͷ�	2���ֽ�
	CAR_PARK = 0x0108,//פ��	2���ֽ�
	CAR_SPEED_LEFTWHEEL = 0x0109,//������ʻ - �����ٶ�	2���ֽ�
	CAR_SPEED_RIGHTWHEEL = 0x010A,//������ʻ - �����ٶ�	2���ֽ�
	CAR_TURNTAIL_ALTITUDE = 0x010B,//��ͷ - ����	2���ֽ�
	CAR_TURNTAIL_TAP      = 0x010C//��ͷ - �ٶȵ�λ	2���ֽ�
};
//��Ҫ��ֵ�Ĵ�����ʼ��ַ�� 
//1.������ֵ��ȡ
#define REGISTER_PARA_BAUD     0x0060   //������
#define REGISTER_PARA_DATABITS 0x0064   //����λ
#define REGISTER_PARA_STOPBITS 0x0068   //ֹͣλ
#define REGISTER_PARA_PARITY   0X006C   //У�鷽ʽ
#define REGISTER_PARA_Ua       0X0070   //Ua���
#define REGISTER_PARA_Ub       0X0074   //Ub���
#define REGISTER_PARA_Uc       0X0078   //Uc���
#define REGISTER_PARA_Ia       0X007C   //Ia���
#define REGISTER_PARA_Ib       0X0080   //Ib���
#define REGISTER_PARA_Ic       0X0084   //Ic���
#define REGISTER_PARA_I0       0X0088   //I0���
#define REGISTER_PARA_Pa       0X008C   //Pa���
#define REGISTER_PARA_Pb       0X0090   //Pb���
#define REGISTER_PARA_Pc       0X0094   //Pc���
#define REGISTER_PARA_NETWORK  0x0098   //����ѡ��
#define REGISTER_PARA_PT       0x009C   //���ѹ[PT���1 220]
#define REGISTER_PARA_CT       0x00A0   //���ѹ[CT���100:5=20 200:5=40 300:5=60 600:5=120]
#define REGISTER_PARA_TIME     0x00A4   //ʱ��
#define REGISTER_PARA_PWD      0x00A8   //����
#define REGISTER_PARA_ADDR     0x00AC   //��ַ
#define REGISTER_PARA_EXIT     0x00B0   //�˳�
#define REGISTER_PARA_CONTROL  0x00B4   //ң��
#define REGISTER_PARAS_FLOAT   0x00B6   //���ø�����������������
#define REGISTER_PARA_PROCTIME 0x00B8   //�������ʱ��
#define REGISTER_PARA_PROCVER  0x00BA   //��������汾
#define REGISTER_AMP_ADJUST    0x0051   //��ֵ�Զ�У׼
#define REGISTER_ANG_ADJUST    0x0052   //��λ�Զ�У׼
#define REGISTER_PARAS_ALL     0x0053   //�������в���

//10.������
#define FC_READ_PARA    0x80 //��ȡ����
#define FC_SET_PARA     0x81 //���ò���
#define FC_READ_TIME    0X90 //��ȡװ��ʱ��
#define FC_SET_TIME     0x91 //����װ��ʱ��
#define FC_READ_SETTING 0x04 //��ȡ��ֵ
#define FC_SET_SETTING  0x10 //д��ֵ
#define FC_READ_COIL    0x01 //��ȡ��Ȧ״̬
#define FC_READ_STATUS  0x02 //��ȡң��
#define FC_READ_ANALOG  0x03 //��ȡң��
#define FC_TELE_CONTROL 0x05 //ң��
#define FC_READ_EVENT   0x16 //��ȡ�¼�
#define FC_EXIT_SET     0x82 //�˳�����
#define FC_ERROR_RAISE  0x83 //������� 
#define FC_ADJUST_PARA  0x93 //װ��У׼
#define FC_SET_PARAS    0x94 //�������в���      


#define  ERROR_BASE 40
#define  ERROR_READ_PARA   (ERROR_BASE + 1)
#define  ERROR_READ_TIME   (ERROR_BASE + 2)
#define  ERROR_READ_ANALOG (ERROR_BASE + 3)
#define  ERROR_WRITE_PARA  (ERROR_BASE + 4)
#define  ERROR_WRITE_TIME  (ERROR_BASE + 5)

#define STATUS_BASE      10
#define STATUS_INDEX_DI1 1
#define STATUS_INDEX_DI2 2
#define STATUS_INDEX_DI3 3

//������λ��
#define  POS_DEV_ID   0
#define  POS_FC       1
#define  POS_BYTES    2
#define  POS_REGISTER 2
#define  POS_REGISTER_NUM   4
#define  POS_SET_PARA_BYTES 6
#define  POS_TIME_SET 5

#define  MAX_ANALOG_PER_DEV 64
#define  MAX_STATUS_PER_DEV 32
#define  MAX_PARA_PER_DEV   16
#define  MAX_CONTROL_PER_DEV 8
#define  MAX_DEV_NUM         10

#define  CLOSE_DEV 0X00FF
#define  OPEN_DEV  0x00DD

const UBYTE1 ACT_DEV       = 0X01;
const UBYTE1 START_ADDRESS = 0x02;
const UBYTE1 FUNCTION_CODE = FC_READ_PARA;
const UBYTE2 REGISTER_NUM  = 0X0004;
const FBYTE4 trip_val      = 0.05f;
const FBYTE4 trip_time     = 0.02f;

const UBYTE1 STR_LEN       = 32;
const UBYTE1 CONFIG_NUM    = 32;
const UBYTE1 MEASURE_NUM   = 64;
class config_item
{
	UBYTE4 itemNo;          //��ʾ���
	UBYTE4 itemCode;        //���ݱ���
	UBYTE4 itemSub;         //����ȥ�±�
	BYTE1  itemChn[STR_LEN];//���ı�ʶ
	BYTE1  itemEng[STR_LEN];//Ӣ�ı�ʶ
	BYTE4  oldValue;        //��ֵ
	BYTE4  curValue;        //��ǰֵ
	BYTE4  maxVal;          //���ֵ
	BYTE4  minVal;          //��Сֵ
	UBYTE1 changed;         //���ݱ仯
	UBYTE1 readOnly;        //ֻ������
};

class meas_item
{
	UBYTE4 itemNo;          //��ʾ���
	UBYTE4 itemCode;        //���ݱ���
	UBYTE4 itemSub;         //����ȥ�±�
	BYTE1  itemChn[STR_LEN];//���ı�ʶ
	BYTE1  itemEng[STR_LEN];//Ӣ�ı�ʶ
	BYTE4  oldValue;        //��ֵ
	BYTE4  curValue;        //��ǰֵ
	BYTE4  maxVal;          //���ֵ
	BYTE4  minVal;          //��Сֵ
	BYTE4  lastUpdate;      //���һ�θ���ʱ��
	BYTE4  regAddr;         //�Ĵ�����ַ
	BYTE4  regBytes;        //�ֽ���
	UBYTE1  devDataType;    //�ɼ�������
	UBYTE1  stnDataType;    //��վ������
	UBYTE1  modbusType;     //modbus��������
	UBYTE1  convertType;    //ת������
	UBYTE1 readWrite;       //��д����
};

class scanblock
{
	BYTE1 modbusStation[STR_LEN];            //modbus�˿�����
	config_item configs[CONFIG_NUM];         //������Ŀ
	meas_item   measures[MEASURE_NUM];       //�ɼ���Ŀ
};

struct modbus_item
{
	UBYTE2 id;
	char   desc[16];
	FBYTE4 value;
	UBYTE1 type;
	UBYTE1 bitidx;
	bool   bVal;
};

//����4�ֽڶ���
typedef struct 
{
	unsigned char startCode;			//offset=4

	unsigned int posEPT;//��ֵ��Ҫÿ��1s�浽eeprom��ȥ���ϵ����ؽ��� ��λkwh*100
	unsigned int negEPT;//��ֵ��Ҫÿ��1s�浽eeprom��ȥ���ϵ����ؽ��� ��λkwh*100
	unsigned short pt;
	unsigned short ct;
	unsigned int rsvd[4];		     //offset = 32

	unsigned char  datbit;
	unsigned char  stopbit;
	unsigned char  parity;			 //offset = 32

	unsigned short band;			 
	unsigned short devAddr;			 //36

	unsigned short ua;				 //40
	unsigned short ub;

	unsigned short uc;
	unsigned short ia;			     //44

	unsigned short ib;
	unsigned short ic;				//48

	unsigned short i0;
	unsigned short pha;			   //52

	unsigned short phb;
	unsigned short phc;			  //56

	unsigned short dc;			 
	unsigned char  flt;          //��������ʽ,1:������ 2��������
	unsigned char  sum;			 //60
}tDEVPARAM;

class modbus_functions
{
 public:
	  static int modbus_init();

	  static int toReadPara(UBYTE1 *pAsk,UBYTE2 devID, UBYTE2 register_addr);
      static int onReadPara(UBYTE1 *pAsk,UBYTE1* pAnswer);
	  static int onReadPara(UBYTE1 *pAsk,UBYTE1* pAnswer,FBYTE4 val1,FBYTE4 val2);

	  static int toSetPara(UBYTE1 *pAsk,UBYTE2 devID, UBYTE2 paraId, BYTE4 paraValue);
	  static int toSetPara(UBYTE1 *pAsk,UBYTE2 devID, UBYTE2 register_addr, FBYTE4 trip_val, FBYTE4 trip_time);
      static int onSetPara(UBYTE1 *pAsk,UBYTE1* pAnswer);
	  static int onSetPara(UBYTE1 *pAsk,UBYTE1* pAnswer,FBYTE4* val1,FBYTE4* val2);

	  static int toReadStatus(UBYTE1 *pAsk,UBYTE2 devID,UBYTE2 register_addr);
      static int onReadStatus(UBYTE1 *pAsk,UBYTE1* pAnswer);

	  static int toReadCoil(UBYTE1 *pAsk,UBYTE2 devID,UBYTE2 register_addr);	
	  static int onReadCoil(UBYTE1 *pAsk,UBYTE1* pAnswer);

	  static int toWriteCoil(UBYTE1 *pAsk,UBYTE2 devID,UBYTE2 register_addr);
	  static int onWriteCoil(UBYTE1 *pAsk,UBYTE1* pAnswer);

	  static int toReadAnalog(UBYTE1 *pAsk,UBYTE2 devID,UBYTE2 register_addr,UBYTE2 register_num);
      static int onReadAnalog(UBYTE1 *pAsk,UBYTE1* pAnswer);

	  static int toTeleControl(UBYTE1 *pAsk,UBYTE2 devID,UBYTE2 register_addr);
      static int onTeleControl(UBYTE1 *pAsk,UBYTE1* pAnswer);

	  static int toReadTime(UBYTE1 *pAsk,UBYTE2 devId);
      static int onReadTime(UBYTE1 *pAsk,UBYTE1* pAnswer);

	  static int toAdjustTime(UBYTE1 *pAsk,UBYTE2 devId);
	  static int toAutoAdjust(UBYTE1 *pAsk, UBYTE2 devId, UBYTE2 paraId);
	  static int toExitParaSet(UBYTE1 *pAsk, UBYTE2 devId);
      static int onAdjustTime(UBYTE1 *pAsk,UBYTE1* pAnswer);

	  static int toReadEvent(UBYTE1 *pAsk, UBYTE2 devId);
      static int onReadEvent(UBYTE1 *pAsk,UBYTE1* pAnswer);

	  static int toSetParas(UBYTE1* pAsk,tDEVPARAM& devParam);
	  static int onSetParas(UBYTE1 *pAsk,UBYTE1* pAnswer);

	  static int get_status_sub(UBYTE2 devId, int register_addr);

	  static int get_analog_sub(UBYTE2 devId, int register_addr);

	  static int get_para_sub(UBYTE2 devId, int register_addr);

	  static FBYTE4 to_float(UBYTE1* buff);

	  static BYTE4  to_int(UBYTE1* buff);

	  static int    to_buff(FBYTE4,UBYTE1* buff);

	  static int    to_buff(BYTE4,UBYTE1* buff);

	  static UBYTE2 to_word(UBYTE1* buff);

	  static int    to_buff(UBYTE2,UBYTE1* buff);

	  static int    status_to_buff(UBYTE2,UBYTE1* buff);
	  static bool   buff_to_status(UBYTE1* buff,int bit);
      static int    set_crc(UBYTE1* pAnswer,int len);

	  static int    to_buff(tm&,UBYTE1* buff);

	  static int    parsebuffer(UBYTE1* buff,int register_addr,int register_num,list<modbus_item>& lstItems);

	  static time_t to_time(UBYTE1*buff);
	  
	  static UBYTE1   BCD_TO_HEX(UBYTE1 bcdByte);
	  static UBYTE1   HEX_TO_BCD(UBYTE1 btHex);
	  static UBYTE1   BCD_TO_HEX(UBYTE1* bcdByte,UBYTE1 nLen);
	  static UBYTE1   HEX_TO_BCD(UBYTE1* btHex,  UBYTE1 nLen);


	  static FBYTE4   pAnalog_Value[MAX_DEV_NUM*MAX_ANALOG_PER_DEV];
	  static FBYTE4   pPara_Value[MAX_DEV_NUM*MAX_PARA_PER_DEV];
	  static UBYTE1   pStatus_Value[MAX_DEV_NUM*MAX_STATUS_PER_DEV];
	  static UBYTE4   pTime[MAX_DEV_NUM];
	  static UBYTE1   dev_state[MAX_DEV_NUM];
	 
	  static map<int,int> id_to_status_sub;
      static int status_id[MAX_STATUS_PER_DEV];

	  static map<int,int> id_to_analog_sub;
      static int analog_id[MAX_ANALOG_PER_DEV];

	  static map<int,int> id_to_para_sub;
      static int para_id[MAX_PARA_PER_DEV];

	  static map<int,int> control_to_analog_sub;

	  static Crc* crc;
};


#endif