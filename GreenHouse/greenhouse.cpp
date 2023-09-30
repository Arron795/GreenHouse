#include "greenhouse.h"

GreenHouse::GreenHouse(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	tcpServer = new QTcpServer(this);
	tcpSocket = new QTcpSocket(this);

	//服务器等待新的连接
	connect(tcpServer, &QTcpServer::newConnection, this, &GreenHouse::mNewConnection);
	ui.closeBtn->setEnabled(false);
	ui.level1Btn->setEnabled(false);
	ui.level2Btn->setEnabled(false);
	ui.level3Btn->setEnabled(false);
    setWindowTitle("--基于物联网的温室大棚检测系统-- V2.0		23-04-25		By:Arron Sheh");
	setWindowIcon(QIcon(":/icon/server.ico"));

}

GreenHouse::~GreenHouse()
{
	delete tcpServer;
	delete tcpSocket;
}

void GreenHouse::mNewConnection()
{
	//与客户端连接
	QTcpSocket* tmpTcpSocket = tcpServer->nextPendingConnection();

	//打印ip和端口信息 到横条上
	ui.ipEdit->setText(tmpTcpSocket->peerAddress().toString());
//	ui.portEdit->setText(QString::number(tmpTcpSocket->peerPort()));
	ui.lcdNumber->display(QString::number(tmpTcpSocket->peerPort()));

	connect(tmpTcpSocket, &QTcpSocket::readyRead, this, &GreenHouse::readyRead_Slot);		//readyRead_Slot相当于receiveMessages
	connect(tmpTcpSocket, &QTcpSocket::stateChanged, this, &GreenHouse::mStateChanged);

}

//收到的数据放入接受框   解析

void GreenHouse::readyRead_Slot() {
	QTcpSocket* tmpTcpSocket = (QTcpSocket*)sender();
	QByteArray receiveDate;
	QTextCodec* tc = QTextCodec::codecForName("GBK");

	while (!tmpTcpSocket->atEnd()) {
		receiveDate = tmpTcpSocket->readAll();
	}

	if (!receiveDate.isEmpty())
	{
		QString strBuf = tc->toUnicode(receiveDate);
		//ui->RecvEdit->appendPlainText(strBuf);
		
		if (receiveDate.startsWith("Params"))
		{
			QString tem = strBuf.mid(receiveDate.indexOf("temp:") + ((QString)"temp:").length(), receiveDate.indexOf("humi:") - receiveDate.indexOf("temp:") - ((QString)"temp:").length() - 1);
			QString hum = strBuf.mid(receiveDate.indexOf("humi:") + ((QString)"humi:").length(), receiveDate.indexOf("}") - receiveDate.indexOf("humi:") - ((QString)"humi:").length() - 1);

			ui.humAndTemBrowser->append("温度: " + tem);
			ui.humAndTemBrowser->append("	湿度: " + hum);

		}
		if (receiveDate.startsWith("LIGHT"))
		{
			QString light = strBuf.mid(receiveDate.indexOf("light:") + ((QString)"light:").length(), receiveDate.indexOf("}") - receiveDate.indexOf("light:") - ((QString)"light:").length() - 1);

			ui.lightBrowser->append("光强: " + light);
		}
		if (receiveDate.startsWith("HUMENRAY"))
		{
			QString humenRay = strBuf.mid(receiveDate.indexOf("humenRay:") + ((QString)"humenRay:").length(), receiveDate.indexOf("}") - receiveDate.indexOf("humenRay:") - ((QString)"humenRay:").length() - 1);

			ui.HCSR501Browser->append("有无人经过: " + humenRay);
		}
		if (receiveDate.startsWith("HCSR04"))
		{
			QString hcsr04 = strBuf.mid(receiveDate.indexOf("hcsr04:") + ((QString)"hcsr04:").length(), receiveDate.indexOf("}") - receiveDate.indexOf("hcsr04:") - ((QString)"hcsr04:").length() - 1);

			ui.HCSR04Edit->append("距离为: " + hcsr04);
		}
		if (receiveDate.startsWith("HUMSOIL"))
		{
			QString humSoil = strBuf.mid(receiveDate.indexOf("humSoil:") + ((QString)"humSoil:").length(), receiveDate.indexOf("}") - receiveDate.indexOf("humSoil:") - ((QString)"humSoil:").length() - 1);

			ui.humSoilBrowser->append("土壤湿度为: " + humSoil);
		}
		//if (strBuf.contains("温度"))
		//{
		//	qDebug() << strBuf;
		//	ui.humAndTemBrowser->append("  " + strBuf);
		//}
		ui.recBrowser->append(strBuf);
	}
	receiveDate.clear();
}


void GreenHouse::mStateChanged(QAbstractSocket::SocketState socketState)
{
	QTcpSocket* tmpTcpSocket = (QTcpSocket*)sender();				//	tmpTcpSocket发出的信号 要操作这个tmpTcpSocket
																	//	用sender返回tmpTcpSocket
	switch (socketState)
	{
		//已断开
	case QAbstractSocket::UnconnectedState:
		ui.recBrowser->append("mStateChanged: 客户端连接已断开");
		//delete tmpTcpSocket;										//销毁对象		这里这样写会出现bug
		tmpTcpSocket->deleteLater();
		qDebug() << "断开连接";
		break;

		//已连接
	case QAbstractSocket::ConnectedState:
		ui.recBrowser->append("mStateChanged: 客户端连接成功!");
		qDebug() << "已连接";
		break;
	default:
		break;
	}
}

void GreenHouse::on_openBtn_clicked()
{
	ui.openBtn->setEnabled(false);
	ui.closeBtn->setEnabled(true);
	//绑定IP地址和端口
	tcpServer->listen(QHostAddress(IP_ADDR), PORT);
    QString str = "on_openBtn_clicked : 监听的IP地址为: " + QString(IP_ADDR) + "	端口号为: " + QString::number(PORT);
	ui.recBrowser->append(str);
	
}

void GreenHouse::on_closeBtn_clicked()
{
	ui.openBtn->setEnabled(true);
	ui.closeBtn->setEnabled(false);
	//停止监听
	ui.recBrowser->append("on_closeBtn_clicked :停止监听");
	qDebug() << "停止监听";
	tcpServer->close();
}

void GreenHouse::on_cleanRecBtn_pressed()
{
	ui.recBrowser->clear();
	ui.cleanRecBtn->setStyleSheet("border-image: url(:/img/clear_a.png)");
}

void GreenHouse::on_cleanRecBtn_released()
{
	ui.cleanRecBtn->setStyleSheet("border-image: url(:/img/clear_b.png)");
}

void GreenHouse::on_openHumAndTemBtn_clicked()
{
	temFlag = !temFlag;
	if (temFlag)
	{
		ui.openHumAndTemBtn->setText("关闭温湿度检测");
		/*	一对多发送	*/
		//QList <QTcpSocket*> socketList = tcpServer->findChildren<QTcpSocket*>();
		//for ( QTcpSocket * tmpTcpSocket : socketList)
		//{
		//	tmpTcpSocket->write("messages from openHumAndTemBtn");
		//}

		/*	一对一发送 */
		tcpServer->findChild<QTcpSocket*>()->write("f");
	}
	else
	{
		ui.openHumAndTemBtn->setText("开启温湿度检测");
		tcpServer->findChild<QTcpSocket*>()->write("d");
		//tmpRec.clear();
	}
}


void GreenHouse::on_openHumSoilBtn_clicked()
{
	humSoilFlag = !humSoilFlag;
	if (humSoilFlag)
	{
		ui.openHumSoilBtn->setText("关闭土壤湿度检测");
		tcpServer->findChild<QTcpSocket*>()->write("u");
	}
	else
	{
		ui.openHumSoilBtn->setText("开启土壤湿度检测");
		tcpServer->findChild<QTcpSocket*>()->write("y");		
	}
	
}

//void GreenHouse::on_openSmokeBtn_clicked()
//{
//	tcpServer->findChild<QTcpSocket*>()->write("...");
//}

void GreenHouse::on_openLightBtn_clicked()
{
	lightFlag = !lightFlag;
	if (lightFlag)
	{
		ui.openLightBtn->setText("关闭光照检测");
		tcpServer->findChild<QTcpSocket*>()->write("k");
	}
	else
	{
		ui.openLightBtn->setText("开启光照检测");
		tcpServer->findChild<QTcpSocket*>()->write("l");
	}
}

void GreenHouse::on_openHCSR04Btn_clicked()
{
	HCSR04Flag = !HCSR04Flag;
	if (HCSR04Flag)
	{
		ui.openHCSR04Btn->setText("关闭超声波检测");
		tcpServer->findChild<QTcpSocket*>()->write("0");
	}
	else
	{
		ui.openHCSR04Btn->setText("开启超声波检测");
		tcpServer->findChild<QTcpSocket*>()->write("9");
	}
}

void GreenHouse::on_openHCSR501Btn_clicked()
{
	HCSR501Flag = !HCSR501Flag;
	if (HCSR501Flag)
	{
		ui.openHCSR501Btn->setText("关闭人体红外检测");
		tcpServer->findChild<QTcpSocket*>()->write("j");
	}
	else
	{
		ui.openHCSR501Btn->setText("开启人体红外检测");
		tcpServer->findChild<QTcpSocket*>()->write("h");


		QEventLoop loop;
		QTimer::singleShot(1000, &loop, &QEventLoop::quit);
		loop.exec();

		ui.HCSR501Browser->clear();
		
	}
}


void GreenHouse::on_fanBtn_clicked()
{
	fanFlag = !fanFlag;
	if (fanFlag)
	{
		tcpServer->findChild<QTcpSocket*>()->write("o");
		ui.fanBtn->setStyleSheet("border-image: url(:/img/closeFan.png)");
		on_level1Btn_clicked();
	}
	else
	{
		tcpServer->findChild<QTcpSocket*>()->write("c");
		ui.fanBtn->setStyleSheet("border-image: url(:/img/fan.png)");
		ui.level1Btn->setEnabled(false);
		ui.level2Btn->setEnabled(false);
		ui.level3Btn->setEnabled(false);
	}
}

void GreenHouse::on_level1Btn_clicked()
{
	tcpServer->findChild<QTcpSocket*>()->write("1");
	ui.level1Btn->setEnabled(false);
	ui.level2Btn->setEnabled(true);
	ui.level3Btn->setEnabled(true);
}

void GreenHouse::on_level2Btn_clicked()
{
	tcpServer->findChild<QTcpSocket*>()->write("2");
	ui.level1Btn->setEnabled(true);
	ui.level2Btn->setEnabled(false);
	ui.level3Btn->setEnabled(true);
}

void GreenHouse::on_level3Btn_clicked()
{
	tcpServer->findChild<QTcpSocket*>()->write("3");
	ui.level1Btn->setEnabled(true);
	ui.level2Btn->setEnabled(true);
	ui.level3Btn->setEnabled(false);
}

//发送消息
void GreenHouse::on_sendBtn_clicked()
{
	//QList容器  数组
	QList <QTcpSocket*> socketList = tcpServer->findChildren<QTcpSocket*>();

	qDebug() << "tcpSocket数量 : " << socketList.count();
	if (socketList.count() == 0)
	{
		QMessageBox::critical(this, "提示", "当前没有客户端连接,请先与客户端连接!");
		ui.recBrowser->append("服务端 :当前没有客户端连接,请先与客户端连接!");
		return;
	}
	foreach(QTcpSocket * tmpTcpSocket, socketList)
	{
		//服务端向每个客户端发送消息
		tmpTcpSocket->write(ui.sendEdit->text().toUtf8());
	}
	ui.recBrowser->append("服务端: " + ui.sendEdit->text());
}

void GreenHouse::on_sendBtn_pressed()
{
	ui.sendBtn->setStyleSheet("border-image: url(:/img/send_a.png)");
}

void GreenHouse::on_sendBtn_released()
{
	ui.sendBtn->setStyleSheet("border-image: url(:/img/send.png)");
}

void GreenHouse::on_cleanSendBtn_pressed()
{
	ui.sendEdit->clear();
	ui.cleanSendBtn->setStyleSheet("border-image: url(:/img/clearS_a.png)");
}

void GreenHouse::on_cleanSendBtn_released()
{
	ui.cleanSendBtn->setStyleSheet("border-image: url(:/img/clearS.png)");
}

void GreenHouse::on_cleanAllBtn_pressed()
{
	ui.cleanAllBtn->setStyleSheet("border-image: url(:/img/clearS.png)");
	ui.HCSR501Browser->clear();
	ui.humAndTemBrowser->clear();
	ui.humSoilBrowser->clear();
	ui.lightBrowser->clear();
	ui.HCSR04Edit->clear();
}

void GreenHouse::on_cleanAllBtn_released()
{
	ui.cleanAllBtn->setStyleSheet("border-image: url(:/img/clear.png)");
}
