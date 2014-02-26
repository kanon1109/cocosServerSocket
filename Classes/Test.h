#pragma once
#include "cocos2d.h"
#include "net/ServerSocket.h"
#include "net/Net.h"
USING_NS_CC;
class Test:public CCScene
{
public:
	Test(void);
	~Test(void);
	virtual bool init();
	CREATE_FUNC(Test);
private:
	ServerSocket* serverSocket;
};

