#pragma once
#include "Bullet.h"
class CBasicArrow :
	public CBullet
{
public:
	CBasicArrow();
	CBasicArrow(float fX, float fY, int Rotate);
	virtual ~CBasicArrow();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

