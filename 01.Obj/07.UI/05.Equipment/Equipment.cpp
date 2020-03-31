#include "stdafx.h"
#include "Equipment.h"


CEquipment::CEquipment()
{
}


CEquipment::~CEquipment()
{
}

void CEquipment::UpdateScrollRect()
{
	m_tCollisionRect.left = LONG(m_tCollInfo.fX - (m_tCollInfo.fCX / 2.f));
	m_tCollisionRect.top = LONG(m_tCollInfo.fY - (m_tCollInfo.fCY / 2.f));
	m_tCollisionRect.right = LONG(m_tCollInfo.fX + (m_tCollInfo.fCX / 2.f));
	m_tCollisionRect.bottom = LONG(m_tCollInfo.fY + (m_tCollInfo.fCY / 2.f));
}

void CEquipment::UpdateInvenRect()
{
	m_tRect.left = m_tCollisionRect.left;
	m_tRect.top = m_tCollisionRect.top;
	m_tRect.right = m_tCollisionRect.right;
	m_tRect.bottom = m_tCollisionRect.bottom + 311.f;
}

void CEquipment::Set_Equip(CObj * pEquip, int iOption)
{
	if (iOption == 1) // 무기
	{
		m_pWeapon = pEquip;
		m_pWeapon->Set_Pos(m_tWeaponPt.x, m_tWeaponPt.y);
		m_pWeapon->Set_Rotate(2);
	}
	else if (iOption == 2)
	{
		m_pArmor = pEquip;
		m_pArmor->Set_Pos(m_tArmorPt.x, m_tArmorPt.y);
		m_pArmor->Set_Rotate(2);
	}
}

void CEquipment::Initialize()
{
	m_tInfo.fX = 320.f;
	m_tInfo.fY = 320.f;
	m_tInfo.fCX = 237.f;
	m_tInfo.fCY = 332.f;

	m_tCollInfo.fX = 320.f;
	m_tCollInfo.fY = m_tInfo.fY - 155.f;
	m_tCollInfo.fCX = 172.f;
	m_tCollInfo.fCY = 23.f;

	m_tWeaponPt.x = 78.f;
	m_tWeaponPt.y = 193.f;
	m_tArmorPt.x = 118.f;
	m_tArmorPt.y = 193.f;
	m_pArmor = nullptr;
	m_pWeapon = nullptr;
	m_bIsDead = true;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/Equipment.bmp", L"Equipment");
	m_pFrameKey = L"Equipment";
}

int CEquipment::Update()
{
	UpdateScrollRect();
	UpdateInvenRect();

	m_tWeaponPt.x = 78.f + m_tRect.left;
	m_tWeaponPt.y = 193.f + m_tRect.top;
	m_tArmorPt.x = 118.f + m_tRect.left;
	m_tArmorPt.y = 193.f + m_tRect.top;

	if (m_pWeapon != nullptr && m_pWeapon->Get_Rotate() != 2)
		m_pWeapon = nullptr;
	if (m_pArmor != nullptr && m_pArmor->Get_Rotate() != 2)
		m_pArmor = nullptr;					//장비창에서 벗어나면 nullptr로 초기화.

	if (CKeyMgr::Get_Instance()->KeyDown('R'))
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::INVENTORY);
		m_bIsDead = !m_bIsDead;
		if (m_bIsDead)
			CSoundMgr::Get_Instance()->PlayEffect(L"창끌때.mp3", CSoundMgr::INVENTORY);
		else
			CSoundMgr::Get_Instance()->PlayEffect(L"창열때.mp3", CSoundMgr::INVENTORY);
	}
	return 0;
}

void CEquipment::LateUpdate()
{
	UpdateScrollRect();
	UpdateInvenRect();
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	if (!m_bIsDead)
	{
		if (PtInRect(&m_tCollisionRect, pt))
		{
			if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON))
			{
				m_tCollInfo.fX = pt.x;
				m_tCollInfo.fY = pt.y;
			}
		}

		if (m_pWeapon != nullptr)
		{
			m_pWeapon->Set_Pos(m_tWeaponPt.x, m_tWeaponPt.y);
			m_pWeapon->LateUpdate();
		}
		if (m_pArmor != nullptr)
		{
			m_pArmor->Set_Pos(m_tArmorPt.x, m_tArmorPt.y);
			m_pArmor->LateUpdate();
		}
	}
}

void CEquipment::Render(HDC hDC)
{
	UpdateInvenRect();
	if (m_bIsDead)
		return;
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(0, 255, 0));
	if(m_pWeapon != nullptr)
		m_pWeapon->Render(hDC);
	if(m_pArmor != nullptr)
		m_pArmor->Render(hDC);
}

void CEquipment::Release()
{
}
