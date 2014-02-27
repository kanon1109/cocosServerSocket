#pragma once
#ifndef _UTILS_TIMER_
#define _UTILS_TIMER_
#include "cocos2d.h"
USING_NS_CC;
//һ����ʱ��ʱ�����ʱ�ص�
typedef void (CCObject::*SEL_TIMER_SELECTOR)(CCObject*);
#define timer_selector(_SELECTOR) (SEL_TIMER_SELECTOR)(&_SELECTOR)

class Timer:public CCNode
{
public:
	/**
	* ��ʱ��
	* @param delay				��ʱ���¼�����ӳ٣��Ժ���Ϊ��λ���� 
	* @param repeatCount		���õļ�ʱ�������ܴ����� 
	*/
	Timer(float delay, int repeatCount = 0);
	~Timer();
	static Timer* create(float delay, int repeatCount = 0);
	void addEventListener(CCObject* target, SEL_TIMER_SELECTOR timeFunc);
	//��ʼ����ͣ
	void start();
	void stop();
	//�����ʱ���������У���ֹͣ��ʱ�������� currentCount �������Ϊ 0�����������������ð�ť��
	void reset();
	//��ʱ���Ƿ�������
	bool running;
	int currentCount;
	//�����ظ�����
	void setRepeatCount(int count);
	//���ü�ʱ�����
	void setDelay(float delay);
private:
	float m_delay;
	int m_repeatCount;
	CCObject* target;
	SEL_TIMER_SELECTOR timeHandler;
	void loop(float dt);
};
#endif
