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
	*/
	virtual void send(CCBuffer* pBuffer);
private:
	//��ʱ��node
	Timer* timer;
	void timeCompleteHandler(Timer* timer);
};
#endif
