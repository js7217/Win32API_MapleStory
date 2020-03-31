#pragma once
class CWell512
{
public:
	CWell512();
	~CWell512();
public:
	unsigned int GetValue();
	unsigned int GetValue(unsigned int nMinValue, unsigned int nMaxValue); // 정수
	float GetFloatValue();
	float GetFloatValue(float fMinValue, float fMaxValue); // 실수
private:
	unsigned long state[16];
	unsigned int index;
};

