#pragma once

typedef struct tagInfo
{
	float fCX;
	float fCY;
	float fX;
	float fY;
}INFO;


typedef struct tagFrame
{
	int iFrameStart; // x시작점
	int iFrameEnd;   // x끝지점
	int iFrameScene; // y좌표.
	DWORD dwFrameSpeed; // 반복 속도.
	DWORD dwFrameTime; // 얼마만큼 빠르게 움직일지.
}FRAME;

typedef struct tagLinePos
{
	tagLinePos()
	{
		ZeroMemory(this, sizeof(tagLinePos));
	}
	tagLinePos(float x, float y)
		: fX(x)
		, fY(y)
	{

	}
	float fX;
	float fY;
}LINEPOS;

typedef struct tagLine
{
	tagLine()
	{
		ZeroMemory(this, sizeof(tagLine));
	}
	tagLine(LINEPOS& rLPoint, LINEPOS& rRPoint)
		: tLPoint(rLPoint)
		, tRPoint(rRPoint)
	{}

	LINEPOS tLPoint;
	LINEPOS tRPoint;
}LINE;