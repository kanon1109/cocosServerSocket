#pragma once
#ifndef _SERVER_SOCKET_
#define _SERVER_SOCKET_
#include "cocos2d.h"
#include "CocosNet/CCNetDelegate.h"
USING_NS_CC;
//��ʱ���ص���������
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
	//��������
	void addEventListener(CCObject* target, SEL_TIME_COMPLETE_SELECTOR callBackFunc);
private:
	//�������
	int reconnentDelay;
	//��ʱ��ѭ��
	void timeLoop(float dt);
	//�ⲿ�ص�������
	SEL_TIME_COMPLETE_SELECTOR callBackFunc;
	//���ûص���Ŀ��ָ��
	CCObject* target;
};

class ServerSocket :public CCNetDelegate
{
public:
	ServerSocket();
	~ServerSocket();
	SINGLE_DELEGATE_INSTANCE_FUNC(ServerSocket);
	//������Ϣ
	virtual void onMessageReceived(CCBuffer& oBuffer);
	//����
	virtual void onConnected();
	//���ӳ�ʱ
	virtual void onConnectTimeout();
	//�Ͽ�����
	virtual void onDisconnected();
	//�����쳣
	virtual void onExceptionCaught(CCSocketStatus eStatus);

	/**
	* ��ʼ��
	* @param	ip		 �����ip��ַ
	* @param	port	 ����˶˿�
	* @param	parent	 �ⲿ������
	*/
	void connectServer(const char* ip, unsigned short port, CCNode* parent);
	/**
	* ������Ϣ
	* @param	actionName   ҵ�����
	* @param	type		 �����еľ���ҵ������
	* @param	...     	 ��Ҫ��������˵Ĳ���
	*/
	void send(unsigned int actionName, unsigned int type, ...);
private:
	//��ʱ��node
	TimerNode* timerNode;
	void timeCompleteHandler();
};
#endif
