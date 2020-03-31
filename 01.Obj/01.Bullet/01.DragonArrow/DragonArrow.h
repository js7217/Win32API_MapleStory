#pragma once
#include "Bullet.h"
class CWell512;
class CDragonArrow :
	public CBullet
{
public:
	CDragonArrow();
	CDragonArrow(float fX, float fY, int Rotate);
	virtual ~CDragonArrow();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	float m_fPlayerX;
	float m_fPlayerY;
};

