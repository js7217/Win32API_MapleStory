#pragma once
#include "Bullet.h"
class CIce :
	public CBullet
{
public:
	CIce();
	virtual ~CIce();

	// CBullet을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

