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
	* 初始化
	* @param	ServerSocket   socket服务
	*/
	static void init(ServerSocket* serverSocket);

	/**
	* 发送消息
	* @param	actionName   业务大类
	* @param	type		 大类中的具体业务类型
	* @param	reset     	 需要传给服务端的参数
	*/
	static void send(unsigned int actionName, unsigned int type, ...);
};
#endif
