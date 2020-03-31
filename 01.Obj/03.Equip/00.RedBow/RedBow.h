#pragma once
#include "Obj.h"
class CRedBow :
	public CObj
{
public:
	CRedBow();
	CRedBow(int iOption, float fX, float fY);
	virtual ~CRedBow();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	int m_iPower;
	int m_iGold;
};

