#include "stdafx.h"
#include "Inventory.h"
#include "RedPotion.h"
#include "MpPotion.h"
#include "RedBow.h"
#include "Armor.h"
#include "Player.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CInventory::CInventory()
{
}


CInventory::~CInventory()
{
	Release();
}

void CInventory::UpdateScrollRect()
{
	m_tCollisionRect.left = LONG(m_tCollInfo.fX - (m_tCollInfo.fCX / 2.f));
	m_tCollisionRect.top = LONG(m_tCollInfo.fY - (m_tCollInfo.fCY / 2.f));
	m_tCollisionRect.right = LONG(m_tCollInfo.fX + (m_tCollInfo.fCX / 2.f));
	m_tCollisionRect.bottom = LONG(m_tCollInfo.fY + (m_tCollInfo.fCY / 2.f));
}

void CInventory::UpdateInvenRect()
{
	m_tRect.left = m_tCollisionRect.left;
	m_tRect.top = m_tCollisionRect.top;
	m_tRect.right = m_tCollisionRect.right;
	m_tRect.bottom = m_tCollisionRect.bottom + 311.f;
}

void CInventory::Buy_Item(CObj* pItem, int iOption) // 옵션 1: 빨간물약, 옵션 2: 파란물약
{
	CObj* pBuyItem = nullptr;
	if (iOption == 1)
	{
		pBuyItem = CAbstractFactory<CRedPotion>::Create();
		pBuyItem->Set_Rotate(0);
	}
	else if (iOption == 2)
	{
		pBuyItem = CAbstractFactory<CMpPotion>::Create();
		pBuyItem->Set_Rotate(0);
	}
	m_PotionVector.emplace_back(pBuyItem);
	for (int i = 0; i < m_PotionVector.size(); ++i)			// 인벤토리에서의 정렬?? 물어보기..
	{
		int Column = i % 4;
		int line = i / 4;
		m_PotionVector[i]->Set_Pos(m_fItemX + (m_fDistanceX * Column), m_fItemY + (m_fDistnaceY * line));
	}
}

void CInventory::Buy_Equip(CObj * pEquip, int iOption)
{
	CObj* pBuyItem = nullptr;
	if (iOption == 1)
	{
		pBuyItem = CAbstractFactory<CRedBow>::Create();
		pBuyItem->Set_Rotate(0);
	}
	else if (iOption == 2)
	{
		//옵션 2일때 방어구
		pBuyItem = CAbstractFactory<CArmor>::Create();
		pBuyItem->Set_Rotate(0);
	}
	m_EquipVector.emplace_back(pBuyItem);
	for (int i = 0; i < m_EquipVector.size(); ++i)			// 인벤토리에서의 정렬?? 물어보기..
	{
		int Column = i % 4;
		int line = i / 4;
		m_EquipVector[i]->Set_Pos(m_fItemX + (m_fDistanceX * Column), m_fItemY + (m_fDistnaceY * line));
	}
}

void CInventory::Set_Option(int iOption)
{
	if (!m_PotionVector.empty())
	{
		for (int i = 0; i < m_PotionVector.size(); ++i)	
		{
			m_PotionVector[i]->Set_Rotate(iOption);
		}
	}
	if (!m_EquipVector.empty())
	{
		for (int i = 0; i < m_EquipVector.size(); ++i)
		{
			if(m_EquipVector[i]->Get_Rotate() != 2)
				m_EquipVector[i]->Set_Rotate(iOption);
		}
	}
}

void CInventory::Initialize()
{
	//Inventory_Portion Inventory_Equip
	m_tInfo.fX = 320.f;
	m_tInfo.fY = 320.f;
	m_tInfo.fCX = 172.f;
	m_tInfo.fCY = 335.f;

	m_tCollInfo.fX = 320.f;
	m_tCollInfo.fY = m_tInfo.fY - 155.f;
	m_tCollInfo.fCX = 172.f;
	m_tCollInfo.fCY = 23.f;
	m_fItemX = m_tInfo.fX - 60.f;
	m_fItemY = m_tInfo.fY - 102.f;
	m_fDistanceX = 35.f;
	m_fDistnaceY = 35.f;
	m_bIsDead = true;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/Inventory_Portion.bmp", L"Inventory_Portion");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/Inventory_Equip.bmp", L"Inventory_Equip");
	m_pFrameKey = L"Inventory_Portion";
	CObj::UpdateRect();
}

int CInventory::Update()
{
	UpdateScrollRect();
	UpdateInvenRect();
	_stprintf_s(m_szGold, L"%d", dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Gold());
	if (CKeyMgr::Get_Instance()->KeyDown('I'))
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::INVENTORY);
		m_bIsDead = !m_bIsDead;
		if (m_bIsDead)
			CSoundMgr::Get_Instance()->PlayEffect(L"창끌때.mp3", CSoundMgr::INVENTORY);
		else
			CSoundMgr::Get_Instance()->PlayEffect(L"창열때.mp3", CSoundMgr::INVENTORY);
	}
	if (CKeyMgr::Get_Instance()->KeyDown(VK_TAB))
	{
		if(m_pFrameKey == L"Inventory_Portion")
			m_pFrameKey = L"Inventory_Equip";
		else if (m_pFrameKey == L"Inventory_Equip")
			m_pFrameKey = L"Inventory_Portion";
	}
	for (int i = 0; i < m_PotionVector.size(); ++i)			//드래그 시 아이템 따라오게 하려고 함.
	{
		int Column = i % 4;
		int line = i / 4;
		m_PotionVector[i]->Set_Pos(m_fItemX + (m_fDistanceX * Column), m_fItemY + (m_fDistnaceY * line));
	}
	for (int i = 0; i < m_EquipVector.size(); ++i)			//드래그 시 아이템 따라오게 하려고 함.
	{
		int Column = i % 4;
		int line = i / 4;
		m_EquipVector[i]->Set_Pos(m_fItemX + (m_fDistanceX * Column), m_fItemY + (m_fDistnaceY * line));
	}
	return 0;
}

void CInventory::LateUpdate()
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
				m_fItemX = m_tCollInfo.fX - 60.f;
				m_fItemY = m_tCollInfo.fY + 55.f;
			}
		}
		if (m_pFrameKey == L"Inventory_Portion")
		{
			for (auto& iter : m_PotionVector)
				iter->LateUpdate();
		}
		else if (m_pFrameKey == L"Inventory_Equip")
		{
			for (auto& iter : m_EquipVector)
			{
				if(iter->Get_Rotate() != 2)
					iter->LateUpdate();
			}
		}
	}
}

void CInventory::Render(HDC hDC)
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

	if (m_pFrameKey == L"Inventory_Portion")
	{
		for (auto& iter : m_PotionVector)
		{
			iter->Render(hDC);
		}
	}
	else if (m_pFrameKey == L"Inventory_Equip")
	{
		for (auto& iter : m_EquipVector)
		{
			if (iter->Get_Rotate() != 2)
				iter->Render(hDC);
		}
	}

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC,m_tRect.right - 90.f, m_tRect.bottom - 68.f, m_szGold, lstrlen(m_szGold));
}

void CInventory::Release()
{
	for_each(m_EquipVector.begin(), m_EquipVector.end(), Safe_Delete<CObj*>);
	for_each(m_PotionVector.begin(), m_PotionVector.end(), Safe_Delete<CObj*>);
}
