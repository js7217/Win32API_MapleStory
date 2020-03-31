#pragma once
#include "Obj.h"
class CEquipment :
	public CObj
{
public:
	CEquipment();
	virtual ~CEquipment();
public:
	void UpdateScrollRect();
	void UpdateInvenRect();
public:
	POINT& Get_WeaponPt() { return m_tWeaponPt; }
	POINT& Get_ArmorPt() { return m_tArmorPt; }
public:
	void Set_Equip(CObj* pEquip, int iOption);
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	list<CObj*> m_EquipList;
	CObj* m_pWeapon;
	CObj* m_pArmor;
	POINT m_tWeaponPt;
	POINT m_tArmorPt;
	INFO m_tCollInfo;
};

