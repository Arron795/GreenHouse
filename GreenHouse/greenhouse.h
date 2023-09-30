#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_greenhouse.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTimer>
#include <QStringEncoder>
#include <QTextCodec>

#define IP_ADDR		"192.168.137.134"        //Arm板IP
//#define IP_ADDR		"192.168.137.1"
#define PORT		8888

class GreenHouse : public QMainWindow
{
    Q_OBJECT

public:
    GreenHouse(QWidget *parent = nullptr);
    ~GreenHouse();
	

public slots:								//槽函数和按钮有关联
	// Version 1.0
	void mNewConnection();
	//void mReceiveMessages();
	void mStateChanged(QAbstractSocket::SocketState socketState);
	void on_openBtn_clicked();
	void on_closeBtn_clicked();
	
	void on_openHumAndTemBtn_clicked();
	//void on_openHumBtn_clicked();
	void on_openHumSoilBtn_clicked();
	//void on_openSmokeBtn_clicked();
	void on_openLightBtn_clicked();
	void on_openHCSR04Btn_clicked();
	void on_openHCSR501Btn_clicked();

	void on_fanBtn_clicked();
	void on_level1Btn_clicked();
	void on_level2Btn_clicked();
	void on_level3Btn_clicked();

	void on_cleanRecBtn_pressed();
	void on_cleanRecBtn_released();
	void on_sendBtn_clicked();
	void on_sendBtn_pressed();
	void on_sendBtn_released();
	void on_cleanSendBtn_pressed();
	void on_cleanSendBtn_released();
	void on_cleanAllBtn_pressed();
	void on_cleanAllBtn_released();


	void readyRead_Slot();

private:
    Ui::GreenHouseClass ui;
	QTcpServer* tcpServer;
	QTcpSocket* tcpSocket;

	bool fanFlag = false;
	bool humFlag = false;
	bool temFlag = false;
	bool humSoilFlag = false;
	bool HCSR04Flag = false;			//人体红外
	bool HCSR501Flag = false;
	bool lightFlag = false;
	bool cleanAllFlag = false;

	float	temp_data;
	float	humi_data;
	float	light_data;
	float	soil_data;
	float	mq2_data;
	float	rain_data;
};
