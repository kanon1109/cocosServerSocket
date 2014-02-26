#include "Net.h"
static ServerSocket* m_serverSocket;
Net::Net()
{
}

Net::~Net()
{
}

void Net::init(ServerSocket* serverSocket)
{
	m_serverSocket = serverSocket;
	m_serverSocket->connectServer("127.0.0.1", 8000);
}

void Net::send(unsigned int actionName, unsigned int type, ...)
{
	
}