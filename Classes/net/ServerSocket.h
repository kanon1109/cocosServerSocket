#pragma once
#ifndef _SERVER_SOCKET_
#define _SERVER_SOCKET_
#include "cocos2d.h"
#include "CocosNet/CCNetDelegate.h"
#include "geckosCocos2dxUtils/utils/Timer.h"
USING_NS_CC;
class ServerSocket :public CCNetDelegate
{
public:
	ServerSocket();
	~ServerSocket();
	SINGLE_DELEGATE_INSTANCE_FUNC(ServerSocket);
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
	* @param	parent	 外部父容器
	*/
	void connectServer(const char* ip, unsigned short port, CCNode* parent);
	/**
	* 发送消息
	*/
	virtual void send(CCBuffer* pBuffer);
private:
	//计时器node
	Timer* timer;
	void timeCompleteHandler(Timer* timer);
};
#endif
