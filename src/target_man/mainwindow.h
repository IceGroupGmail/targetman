#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "target_global.h"
#include "target_structs.h"
#include <QMainWindow>
class QtProperty;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	static MainWindow* getInstance();
private:
    Ui::MainWindow *ui;
	static MainWindow* m_instance;
	TargetSetting  m_target_setting;
	QLabel*       m_status_label[eslCount];

	QAction*      m_target_action[etmCount];
public slots:
	void slotCreateServer();
	void slotTargetItemAction(QAction*);
	void updateServer(QString,int);
//--file menu---
	void on_actionNew_triggered();
	void on_actionOpen_triggered();
	void on_actionSave_triggered();
	void on_actionSaveAs_triggered();
	void on_actionPrint_triggered();

	void on_actionExit_triggered();
	void on_actionRefresh_triggered();

	void on_actionImport_triggered();
	void on_actionExport_triggered();

	void on_actionDataBase_triggered();

	void on_actionMouseSelect_triggered(bool);
	void on_actionMouseDrag_triggered(bool);
	void on_actionAntiAlias_triggered(bool);
	void on_actionOpenGL_triggered(bool);

	void on_actionZoomIn_triggered();
	void on_actionZoomOut_triggered();
	void on_actionRotateClock_triggered();
	void on_actionRotateAnti_triggered();
	void on_actionBgColor_triggered();
	void on_actionBgImage_triggered();
	void on_actionFullScreen_triggered();
	void on_actionResetGraph_triggered();
public:
	bool initConfig(const QString& strFile);
	bool initDB();
	bool initControl();
	bool iniConnects();
	bool initGraphic();
	bool initProperty();
	QWidget* initProperty(QWidget* parent);
	bool init();
	bool   showStatusMessage(QString& msg,int pos);
	bool   showFadeMessage(QString& msg,int  ms);
	QMenu* getContextMenu(TTarget* target);
	bool   updateProperty(TTarget* target);
private:
	virtual void timerEvent(QTimerEvent *);
	virtual void customEvent(QEvent *);


/***************************property manager*********************************/
public Q_SLOTS:
	void valueChanged(QtProperty *property, double value);
	void valueChanged(QtProperty *property, int value);
	void valueChanged(QtProperty *property, const QString &value);
	void valueChanged(QtProperty *property, const QColor &value);
	void valueChanged(QtProperty *property, const QFont &value);
	void valueChanged(QtProperty *property, const QPoint &value);
	void valueChanged(QtProperty *property, const QSize &value);
	void valueChanged(QtProperty *property, const QPointF &value);
	void valueChanged(QtProperty *property, const QSizeF &value);
private:
	class QtDoublePropertyManager *doubleManager; //��������
	class QtStringPropertyManager *stringManager; //��������
	class QtColorPropertyManager  *colorManager;  //��ɫ����
	class QtFontPropertyManager   *fontManager;   //��������
	class QtPointPropertyManager  *pointManager;  //������
	class QtPointFPropertyManager  *pointFManager;  //������(����)
	class QtSizePropertyManager   *sizeManager;   //�ߴ�����
	class QtSizeFPropertyManager   *sizeFManager;   //�ߴ�����(����)
	class QtEnumPropertyManager   *enumManager;  //ö������
	class QtTreePropertyBrowser   *propertyEditor; //��������

	QMap<QtProperty *, QString>   propertyToId;   //������IDӳ��
	QMap<QString, QtProperty *>   idToProperty;   //ID������ӳ��
	QMap<QString, bool>          idToExpanded;   //�����Ƿ��Ѿ�չ��

	//�������Ա�ǩչ��״̬
	void updateExpandState();

	//�������Կ���Ŀ
	void resetProperty();

	//׷��һ������
	void addProperty(QtProperty *property, const QString &id);
	/*****************************************************************************/
	QWidget* customWidgetItem(QWidget* p, int id);
};

#endif // MAINWINDOW_H
