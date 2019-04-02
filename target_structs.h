#ifndef  TARGET_STRUCTS_H
#define  TARGET_STRUCTS_H
#include "target_constants.h"
#include "qdatetime.h"
#include "qpoint.h"
#include "qlist.h"
struct TARGET_STATUS
{
	quint32  ready : 1;//׼����
	quint32  hidden : 1;//����
	quint32  invalid : 1;//��Ч��
	quint32  selected : 1;//ѡ����
	quint32  online : 1;//ͨѶ����
	quint32  broken : 1;//��
	quint32  shooting : 1;//�����
	quint32  completed : 1;//������
	quint32  preparing : 1;//׼����
	quint32  back1 : 1;//�����
	quint32  back2 : 1;//���ڱ���
	quint32  back3 : 1;//�澯
	quint32  back4 : 1;//����
	quint32  back5 : 1;//��������
	quint32  back6 : 1;//��������
};

struct SOLDIER_STATUS
{
	quint32  absent      : 1;//ȱϯ
	quint32  preparing   : 1;//Ԥ��
	quint32  waiting     : 1;//�ȴ�
	quint32  training    : 1;//ѵ����
	quint32  regSucce    : 1;//��¼�ɹ�
	quint32  regFailed   : 1;//��֤ʧ��
	quint32  illegal     : 1;//�Ƿ���
	quint32  canceled    : 1;//ȡ����
};
struct  TObjTable
{
	int tableid;
	int tableIndex;
	int valid;
	QString tableName;
	QString tableAlias;
};

struct TObjField
{
	int tableid;
	int fieldid;
	int valid;
	QString fieldName;
	QString fieldAlias;
	int type;
	//char fieldName[STRLEN_NAME_32];
	//char fieldAlias[STRLEN_ALIAS_48];
};

struct TTarget
{
	int tid;//���ݿ�id
	char name[STRLEN_NAME_32];//����
	QString tName;
	QString tMemo;
	int  type;   //��������״��
	int  subtype;//�������й�����
	int  prevTarget;//ǰһ��
	int  netxTarget;//��һ���б�
	int  gallery;  //�г�
	int  devNo;    //ͨѶװ�ñ��
	int  orderNo;  //�������
	int  targetNo; //�б���
	int  shootNo;  //��ǰ�������
	int  shootNum; //�������
	int  userId;  //�û�ID
	int  status;

	int  portNo;     //�б�Ķ˿�
	QString strIPAddr;//�б��IP

	unsigned short fault;     // ������Ϣ  ALARM_FLG_XXX������Ϣ
	unsigned short run_state;  // ����״̬  ��ֹ���𡢵���δ֪ �˶���������У���������  ��ҡ�ڰ�ʱΪҡ��λ�õĽǶ�
	unsigned short battery;    //��ص���
	unsigned short hit_total;  // ��������
	unsigned short cycle_hits;  // һ����ѯ���ڵ�������
	QList<QPointF>  m_points;

	int  curDirection;//���з�λ
	float  totalPoints;//�ܻ���
	float  currentPoints;//��ǰ����
	float  xPos;//����x
	float  yPos;//����y
	float  thelta;//��б�Ƕ�
	TARGET_STATUS     m_status;
	class QGraphicTarget* graphicTarget;
};

struct TGallery
{
	int tid;
	char name[STRLEN_NAME_32];
	int devNo;
	int objectType;
};

struct TMilitaryUnit
{
	int tid;
	char name[STRLEN_NAME_32];
	int devNo;
	int objectType;
};

struct TAdministrator
{
	int tid;
	char name[STRLEN_NAME_32];
	int devNo;
	int objectType;
};

struct TSoldier
{
	int tid;
	char name[STRLEN_NAME_32];
	int devNo;
	int objectType;
};

struct  TSoldierShot
{
	int  tid;
	char name[STRLEN_NAME_32];
	int  soldier;
	int  train;
	float points;
	float xPos;
	float yPos;
	int   direction;
};

struct TSoldierTrain
{
	int   tid;
	char  name[STRLEN_NAME_32];
	int   soldier;
	float totalPoints;
	int   shoots;
	int   status;
	int   admin;
	int   startTime;
	int   endTime;
	int   valid;
};

struct TargetSetting
{
	QString db_driver;
	QString db_url;
	QString db_usr;
	QString db_pwd;
	
	QString sys_caption;
	QString sys_version;
	QString sys_about;
	QString sys_background;
	
	int     tcp_port;
	int     tcp_maxclient;
	int     tcp_timeout;
	int     tcp_interval;

	QString com_name;
	int     com_databit;
	int     com_baudrate;
	int     com_flowcontrol;
	int     com_stopbit;
	int     com_direction;
	int     com_parity;

	QString   train_soldier_name;
	QString   train_soldier_id;
	QString   train_id;
	QDateTime tarin_start;
	QDateTime train_end;
};

struct TARGET_COMMAND
{
	int      cmdType;
	int      dataArr[4];
	int      timeout;//��ʱʱ��
	TTarget*  target;
	QDateTime tmStamp;
};


#define DEBUG_PARA1(x) qDebug()<<"<"<<__FILE__<<","<<__LINE__<<">"<<QString::fromLocal8Bit(x);
#define DEBUG_PARA2(x,y) qDebug()<<"<"<<__FILE__<<","<<__LINE__<<">"<<QString::fromLocal8Bit(x)<<":"<<y;
#endif