#pragma once
#include "Obj.h"
class CEffectDamage :
	public CObj
{
public:
	CEffectDamage();
	CEffectDamage(float fX, float fY, float fCX, float fCY, TCHAR* pFrameKey, int iDamage);
	virtual ~CEffectDamage();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

