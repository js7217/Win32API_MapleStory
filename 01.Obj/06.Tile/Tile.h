#pragma once
#include "Obj.h"
class CTile :
	public CObj
{
public:
	CTile();
	CTile(float fX, float fY);
	virtual ~CTile();
public:
	// save
	int Get_DrawID() { return m_iDrawID; }
	int Get_Option() { return m_iOption; }
	// load
	void Set_DrawID(int iDraw) { m_iDrawID = iDraw; }
	void Set_Option(int iOption) { m_iOption = iOption; }
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int m_iDrawID;
	int m_iOption;
};

