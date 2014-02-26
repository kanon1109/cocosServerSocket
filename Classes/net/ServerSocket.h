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
	//�������
	int reconnentDelay;
	//��ʱ��ѭ��
	void timeLoop(float dt);
	//����������ʱ��
};

class ServerSocket :public CCNetDelegate
{
public:
	ServerSocket(CCNode* parent);
	~ServerSocket();
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
	*/
	void connectServer(const char* ip, unsigned short port);
private:
	//��ʱ��node
	TimerNode* timerNode;
};
#endif
