#include "Test.h"
#include "net/Protocols.h"
#include <stdlib.h>
using namespace std;
Test::Test(void)
{
	
}

Test::~Test(void)
{
}

bool Test::init()
{
	//����ʧ����Ϣ
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,                         
		callfuncO_selector(Test::loginHandler),  // �������Ϣ�Ļص�����
		LOGIN,  // ����Ȥ����Ϣ����
		NULL);   

	ServerSocket::sharedDelegate()->connectServer("127.0.0.1", 8000, this);
	return true;
}

void Test::loginHandler(CCBuffer* buffer)
{
	string str = buffer->readString(3);
	CCLOG("str %s", str.c_str());
}
