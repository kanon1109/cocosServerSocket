#include "Test.h"
Test::Test(void)
{
	
}

Test::~Test(void)
{
}

bool Test::init()
{
	ServerSocket::sharedDelegate()->connectServer("127.0.0.1", 8000, this);
	return true;
}
