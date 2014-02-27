#include "Test.h"
#include "net/Protocols.h"
#include "CocosNet/CCBuffer.h"
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
	//监听失败消息
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
										this,                         
										callfuncO_selector(Test::loginHandler),  // 处理的消息的回调函数
										LOGIN,  // 感兴趣的消息名称
										NULL);   

	ServerSocket::sharedDelegate()->connectServer("127.0.0.1", 8000, this);
	return true;
}

void Test::loginHandler(CCBuffer* buffer)
{
	string str = buffer->readString(3);
	CCLOG("str %s", str.c_str());
	//不必写长度了，因为CCNetDelegate内部已经封装
	CCBuffer bf;
	bf.writeChar(88); // actionName   业务大类
	bf.writeChar(1);// type		 大类中的具体业务类型
	bf.writeString("nogizaka46");
	ServerSocket::sharedDelegate()->send(&bf);
}
