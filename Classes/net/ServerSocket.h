#pragma once
#ifndef _SERVER_SOCKET_
#define _SERVER_SOCKET_
#include "cocos2d.h"
#include "CocosNet/CCNetDelegate.h"
USING_NS_CC;
//计时器回调函数类型
typedef void (CCObject::*SEL_TIME_COMPLETE_SELECTOR)();
#define time_complete_selector(_SELECTOR) (SEL_TIME_COMPLETE_SELECTOR)(&_SELECTOR)
class TimerNode :public CCNode
{
public:
	TimerNode();
	~TimerNode();
	static TimerNode* create();
	void start();
	void stop();
	//监听函数
	void addEventListener(CCObject* target, SEL_TIME_COMPLETE_SELECTOR callBackFunc);
private:
	//重链间隔
	int reconnentDelay;
	//计时器循环
	void timeLoop(float dt);
	//外部回调方法。
	SEL_TIME_COMPLETE_SELECTOR callBackFunc;
	//调用回调的目标指针
	CCObject* target;
};

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
	* @param	actionName   业务大类
	* @param	type		 大类中的具体业务类型
	* @param	...     	 需要传给服务端的参数
	*/
	void send(unsigned int actionName, unsigned int type, ...);
private:
	//计时器node
	TimerNode* timerNode;
	void timeCompleteHandler();
};
#endif
