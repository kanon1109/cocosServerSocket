#include "ServerSocket.h"
ServerSocket::ServerSocket(CCNode* parent)
{
	this->timerNode = TimerNode::create();
	parent->addChild(this->timerNode);
	this->timerNode->createReconnectTimer();
}

ServerSocket::~ServerSocket()
{
	this->timerNode->removeFromParentAndCleanup(true);
}

void ServerSocket::onMessageReceived(CCBuffer& oBuffer)
{

}

void ServerSocket::onConnected()
{
	CCLOG("connect success");
}

void ServerSocket::onConnectTimeout()
{
	CCLOG("connect timeout");
	
}

void ServerSocket::onDisconnected()
{
	CCLOG("connect close");
}

void ServerSocket::onExceptionCaught(CCSocketStatus eStatus)
{
	CCLOG("onExceptionCaught %d", (int)eStatus);
	if ((int)eStatus == CCSocketStatus::eSocketConnectFailed ||
		(int)eStatus == CCSocketStatus::eSocketConnectTimeout ||
		(int)eStatus == CCSocketStatus::eSocketDisconnected||
		(int)eStatus == CCSocketStatus::eSocketIoError)
	{
		
	}
}

void ServerSocket::connectServer(const char* ip, unsigned short port)
{
	CCInetAddress address;
	address.setIp(ip);
	address.setPort(port);
	//this->setInetAddress(address);
	//this->connect();
}

TimerNode::TimerNode()
{
	this->reconnentDelay = 2;
}

TimerNode::~TimerNode()
{

}

void TimerNode::timeLoop(float dt)
{
	CCLOG("%d", this->reconnentDelay);
	this->reconnentDelay--;
	if (this->reconnentDelay <= 0)
	{

	}
}

void TimerNode::createReconnectTimer()
{
	this->schedule(schedule_selector(TimerNode::timeLoop), 1.0f);
}

TimerNode* TimerNode::create()
{
	TimerNode* tn = new TimerNode();
	if (tn && tn->init())
	{
		tn->autorelease();
		return tn;
	}
	CC_SAFE_DELETE(tn);
	return NULL;
}
