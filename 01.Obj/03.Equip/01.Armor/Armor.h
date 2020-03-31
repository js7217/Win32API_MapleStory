#pragma once
#include "Obj.h"
class CArmor :
	public CObj
{
public:
	CArmor();
	CArmor(int iOption, float fX, float fY);
	virtual ~CArmor();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	int m_iGold;
};

