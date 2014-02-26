#pragma once
#ifndef _SERVER_SOCKET_
#define _SERVER_SOCKET_
#include "cocos2d.h"
#include "CocosNet/CCNetDelegate.h"
USING_NS_CC;
class TimerNode :public CCNode
{
public:
	TimerNode();
	~TimerNode();
	static TimerNode* create();
	void createReconnectTimer();
private:
	//重链间隔
	int reconnentDelay;
	//计时器循环
	void timeLoop(float dt);
	//创建重链计时器
};

class ServerSocket :public CCNetDelegate
{
public:
	ServerSocket(CCNode* parent);
	~ServerSocket();
	//接收消息
	virtual void onMessageReceived(CCBuffer& oBuffer);
	//链接
	virtual void onConnected();
	//链接超时
	virtual void onConnectTimeout();
	//断开连接
	virtual void onDisconnected();
	//捕获异常
	virtual void onExceptionCaught(CCSocketStatus eStatus);
	/**
	* 初始化
	* @param	ip		 服务端ip地址
	* @param	port	 服务端端口
	*/
	void connectServer(const char* ip, unsigned short port);
private:
	//计时器node
	TimerNode* timerNode;
};
#endif
