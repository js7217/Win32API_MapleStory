#pragma once
#include "Obj.h"
class CMpPotion :
	public CObj
{
public:
	CMpPotion();
	CMpPotion(int iOption, float fX, float fY);
	virtual ~CMpPotion();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	int m_iHeal;
	int m_iGold;
};

