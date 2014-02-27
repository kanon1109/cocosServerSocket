#include "ServerSocket.h"
ServerSocket::ServerSocket()
{
	this->timer = NULL;
}

ServerSocket::~ServerSocket()
{
	this->timer->removeFromParentAndCleanup(true);
}

void ServerSocket::onMessageReceived(CCBuffer& oBuffer)
{
	int id = oBuffer.readInt();
	char protocol[33];
	sprintf(protocol, "%d", id);
	CCLOG("protocol = %s", protocol);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(protocol, &oBuffer);
}

void ServerSocket::onConnected()
{
	CCLOG("connect success");
}

void ServerSocket::onConnectTimeout()
{
	CCLOG("connect timeout");
	if (this->timer) this->timer->start();
}

void ServerSocket::onDisconnected()
{
	CCLOG("connect close");
	if (this->timer) this->timer->start();
}

void ServerSocket::onExceptionCaught(CCSocketStatus eStatus)
{
	CCLOG("onExceptionCaught %d", (int)eStatus);
	if ((int)eStatus == CCSocketStatus::eSocketConnectFailed ||
		(int)eStatus == CCSocketStatus::eSocketConnectTimeout ||
		(int)eStatus == CCSocketStatus::eSocketDisconnected||
		(int)eStatus == CCSocketStatus::eSocketIoError)
	{
		if (this->timer) this->timer->start();
	}
}

void ServerSocket::connectServer(const char* ip, unsigned short port, CCNode* parent)
{
	CCInetAddress address;
	address.setIp(ip);
	address.setPort(port);
	this->setInetAddress(address);
	//创建计时器
	if (!this->timer)
	{
		this->timer = Timer::create(15000, 1);
		this->timer->addEventListener(this, timer_selector(ServerSocket::timeCompleteHandler));
		parent->addChild(this->timer);
	}
	this->connect();
}

void ServerSocket::timeCompleteHandler(Timer* timer)
{
	CCLOG("reconnect");
	this->connect();
}

void ServerSocket::send(CCBuffer* pBuffer)
{
	CCNetDelegate::send(pBuffer);
}