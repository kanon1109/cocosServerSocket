#pragma once
#ifndef _SERVER_SOCKET_NET_
#define _SERVER_SOCKET_NET_
#include "ServerSocket.h"
class Net
{
public:
	Net();
	~Net();
	/**
	* ��ʼ��
	* @param	ServerSocket   socket����
	*/
	static void init(ServerSocket* serverSocket);

	/**
	* ������Ϣ
	* @param	actionName   ҵ�����
	* @param	type		 �����еľ���ҵ������
	* @param	reset     	 ��Ҫ��������˵Ĳ���
	*/
	static void send(unsigned int actionName, unsigned int type, ...);
};
#endif
