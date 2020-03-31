#include "stdafx.h"
#include "Well512.h"
#include <time.h>
enum
{
	DIFFER_VALUE = 100,
};

CWell512::CWell512()
{
	index = 0;
	unsigned int s = static_cast<unsigned int>(time(NULL));

	for (int i = 0; i < 16; ++i)
	{
		state[i] = s;
		s += s + DIFFER_VALUE;
	}
}


CWell512::~CWell512()
{
}

unsigned int CWell512::GetValue()
{
	unsigned int a, b, c, d;

	a = state[index];
	c = state[(index + 13) & 15];
	b = a ^ c ^ (a << 16) ^ (c << 15);
	c = state[(index + 9) & 15];
	c ^= (c >> 11);
	a = state[index] = b ^ c;
	d = a ^ ((a << 5) & 0xda442d24U);
	index = (index + 15) & 15;
	a = state[index];
	state[index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);
	return state[index];
}

unsigned int CWell512::GetValue(unsigned int nMinValue, unsigned int nMaxValue)
{
	return nMinValue + (GetValue() % (nMaxValue - nMinValue));
}

float CWell512::GetFloatValue()
{
	unsigned int nRandValue = GetValue();
	union { unsigned long ul; float f; }p;
	p.ul = (((nRandValue *= 16807) & 0x007fffff) - 1 | 0x3f800000);
	return p.f - 1.f;
}

float CWell512::GetFloatValue(float fMinValue, float fMaxValue)
{
	return fMinValue + GetFloatValue() * (fMaxValue - fMinValue);
}
