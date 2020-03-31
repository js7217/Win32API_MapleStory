#pragma once
#include "Obj.h"
class CObj;
class CInventory :
	public CObj
{
public:
	CInventory();
	virtual ~CInventory();
public:
	void UpdateScrollRect();
	void UpdateInvenRect();
	void Buy_Item(CObj* pItem, int iOption); // 소모품
	void Buy_Equip(CObj* pEquip, int iOption); // 장비
	void Set_Option(int iOption);
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	vector<CObj*> m_EquipVector;
	vector<CObj*> m_PotionVector;
	float m_fItemX;
	float m_fItemY;
	float m_fDistanceX;
	float m_fDistnaceY;
	TCHAR m_szGold[5];
	INFO m_tCollInfo;
};

