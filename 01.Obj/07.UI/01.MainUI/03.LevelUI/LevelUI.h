#pragma once
#include "Obj.h"
class CLevelUI :
	public CObj
{
public:
	CLevelUI();
	virtual ~CLevelUI();
public:
	void UpdateRect_Lv1();
	void UpdateRect_Lv10();
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	int m_iLevel_1;
	int m_iLevel_10;
	INFO m_tInfo_Lv1;
	INFO m_tInfo_Lv10;
	RECT m_tRect_Lv1;
	RECT m_tRect_Lv10;
};

