#include "Test.h"
Test::Test(void)
{
	
}

Test::~Test(void)
{
}

bool Test::init()
{
	this->serverSocket = new ServerSocket(this);
	//Net::init(this->serverSocket);
	return true;
}
