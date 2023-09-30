#pragma once

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include "greenhouse.h"
#include "ui_greenhouse.h"

#define IP_ADDR		"192.168.119.26"
#define PORT		9999

class Server  : public GreenHouse
{
	Q_OBJECT

public:
	Server(GreenHouse*parent);
	~Server();

	
	

public slots:
	void mNewConnetion();
	void mReceiveMessages();
	void mStateChanged(QAbstractSocket::SocketState socketState);
	//void on_sendBtn_clicked();
	void on_openWifi_3_clicked();
	void off_openWifi_3_clicked();

private:
	QTcpServer *tcpServer;
};
