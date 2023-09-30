#include "server.h"


Server::Server(QWidget*parent)
	: GreenHouse(parent)
{
	ui.setupUi(this);
	tcpServer = new QTcpServer(this);
	this->setWindowIcon(QIcon("icon/server.ico"));
	this->setWindowTitle("服务端");
	//新的连接
	connect(tcpServer, &QTcpServer::newConnection, this, &Server::mNewConnetion);

	//ui.stopBtn->setEnabled(false);
}

Server::~Server()
{}


void Server::mNewConnetion()
{
	//与客户端连接
	QTcpSocket* tmpTcpSocket = tcpServer->nextPendingConnection();

	//打印客户端连接的IP信息和端口信息
	ui.humBrowser->append("服务端: 客户端的IP地址: " + tmpTcpSocket->peerAddress().toString());
	ui.humBrowser->append("服务端: 客户端的端口号: " + QString::number(tmpTcpSocket->peerPort()));		//peerPort是一个quint16类型，需要用QString类型的number函数把整型转为字符串类型，才可以用append方法打印出来

	connect(tmpTcpSocket, &QTcpSocket::readyRead, this, &Server::mReceiveMessages);	//readyRead 是 QIODevice的信号，而QIODevice是QTcpSocket的子类
	connect(tmpTcpSocket, &QTcpSocket::stateChanged, this, &Server::mStateChanged);

}
void Server::mReceiveMessages()
{
	QTcpSocket* tmpTcpSocket = (QTcpSocket*)sender();
	//接收消息
	ui.humBrowser->append("	客户端: " + tmpTcpSocket->readAll());
}
void Server::mStateChanged(QAbstractSocket::SocketState socketState)
{
	QTcpSocket* tmpTcpSocket = (QTcpSocket*)sender();				//	tmpTcpSocket发出的信号 要操作这个tmpTcpSocket
																		//	用sender返回tmpTcpSocket
	switch (socketState)
	{
		//已断开
	case QAbstractSocket::UnconnectedState:
		ui.humBrowser->append("服务端: 客户端连接已断开");
		//delete tmpTcpSocket;										//销毁对象		这里这样写会出现bug
		tmpTcpSocket->deleteLater();
		qDebug() << "断开连接";
		break;

		//已连接
	case QAbstractSocket::ConnectedState:
		ui.humBrowser->append("服务端: 客户端连接成功!");
		qDebug() << "已连接";
		break;
	default:
		break;
	}
}
void Server::on_openWifi_3_clicked()
{
	//ui.openWifi_3->setEnabled(false);
	//ui.stopBtn->setEnabled(true);
	//绑定IP地址和端口
	tcpServer->listen(QHostAddress(IP_ADDR), PORT);
	QString str = "服务端 : 监听的IP地址为: " + QString::QString(IP_ADDR) + "	端口号为: " + QString::number(PORT);
	ui.humBrowser->append(str);
}
void Server::off_openWifi_3_clicked()
{
	//ui.openWifi_3->setEnabled(true);
	//ui.stopBtn->setEnabled(false);
	//停止监听
	ui.humBrowser->append("服务端 :停止监听");
	qDebug() << "停止监听";
	tcpServer->close();
}
