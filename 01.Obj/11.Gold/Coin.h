#pragma once
#include "Obj.h"
class CCoin :
	public CObj
{
public:
	CCoin();
	CCoin(float fX, float fY, int iFrameScene, int iGold);
	virtual ~CCoin();
public:
	void IsJumping();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	bool m_bIsJump;
	bool m_bIsMotion;
	int m_iGold;
	float m_fJumpPower;
	float m_fJumpAccel;
	DWORD m_dwOldTime;
};

