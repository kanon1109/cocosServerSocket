#include "ServerSocket.h"
ServerSocket::ServerSocket()
{
	
}

ServerSocket::~ServerSocket()
{
	this->timerNode->removeFromParentAndCleanup(true);
}

void ServerSocket::onMessageReceived(CCBuffer& oBuffer)
{
	int id = oBuffer.readInt();
	CCLOG("id = %d", id);
}

void ServerSocket::onConnected()
{
	CCLOG("connect success");
}

void ServerSocket::onConnectTimeout()
{
	CCLOG("connect timeout");
	this->timerNode->start();
}

void ServerSocket::onDisconnected()
{
	CCLOG("connect close");
	this->timerNode->start();
}

void ServerSocket::onExceptionCaught(CCSocketStatus eStatus)
{
	CCLOG("onExceptionCaught %d", (int)eStatus);
	if ((int)eStatus == CCSocketStatus::eSocketConnectFailed ||
		(int)eStatus == CCSocketStatus::eSocketConnectTimeout ||
		(int)eStatus == CCSocketStatus::eSocketDisconnected||
		(int)eStatus == CCSocketStatus::eSocketIoError)
	{
		this->timerNode->start();
	}
}

void ServerSocket::connectServer(const char* ip, unsigned short port, CCNode* parent)
{
	CCInetAddress address;
	address.setIp(ip);
	address.setPort(port);
	this->setInetAddress(address);
	//创建计时器
	if(!this->timerNode) 
	{
		this->timerNode = TimerNode::create();
		this->timerNode->addEventListener(this, time_complete_selector(ServerSocket::timeCompleteHandler));
		parent->addChild(this->timerNode);
	}
	this->connect();
}

void ServerSocket::timeCompleteHandler()
{
	CCLOG("reconnect");
	this->connect();
}

void ServerSocket::send(unsigned int actionName, unsigned int type, ...)
{

}

TimerNode::TimerNode()
{
	
}

TimerNode::~TimerNode()
{
}

void TimerNode::timeLoop(float dt)
{
	CCLOG("timeLoop %d", this->reconnentDelay);
	this->reconnentDelay--;
	if (this->reconnentDelay <= 0)
	{
		this->reconnentDelay = 0;
		if(this->target && this->callBackFunc)
		{
			(this->target->*callBackFunc)();
		}
		this->stop();
	}
}

void TimerNode::start()
{
	this->reconnentDelay = 15;
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

void TimerNode::addEventListener( CCObject* target, SEL_TIME_COMPLETE_SELECTOR callBackFunc )
{
	this->callBackFunc = callBackFunc;
	this->target = target;
}

void TimerNode::stop()
{
	this->unschedule(schedule_selector(TimerNode::timeLoop));
}
