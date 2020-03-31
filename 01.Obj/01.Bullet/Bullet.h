#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();
public:
	void MotionChange(TCHAR* pFrameKey_left, TCHAR* pFrameKey_right);
	void HitSound();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
};