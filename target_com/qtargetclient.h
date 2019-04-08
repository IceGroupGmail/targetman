#ifndef QTARGETCLIENT_H
#define QTARGETCLIENT_H
#include "target_global.h"
#include "target_structs.h"
class MainWindow;

class QTargetClient : public QTcpSocket
{
	Q_OBJECT

public:
	QTargetClient(QObject *parent,TTarget* pTarget);
	~QTargetClient();
 	TTarget* m_target;
signals:
	void sigUpdateClient(QString,int);
	void sigUpdateClientData(QByteArray da);
	void sigDisconnected(TTarget*);
	void sigConnected(TTarget*);
	void sigError(TTarget*, SocketError);
	void sigChanged(TTarget*, SocketState);
public slots:

   //���ݽ���
	void slotDisconnected();

    //���ӶϿ�
	void slotDataReceived();

	//���ӽ���
	void slotConnected();   

	//״̬�ı�
	void slotStateChanged(SocketState);

	//��������
	void slotError(SocketError);

};

#endif // QTARGETCLIENT_H
