#include "stdafx.h"
#include "RedBow.h"
#include "Player.h"
#include "ShopBow.h"
#include "Weapon.h"
#include "Equipment.h"
#include "Inventory.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CRedBow::CRedBow()
{
}

CRedBow::CRedBow(int iOption, float fX, float fY)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_iRotate = iOption;
}


CRedBow::~CRedBow()
{
}

void CRedBow::Initialize()
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_iPower = 100;
	m_iGold = 1000;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Item/RedBow.bmp", L"RedBow");
	m_pFrameKey = L"RedBow";
	CObj::UpdateRect();
}

int CRedBow::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CRedBow::LateUpdate()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM_CLICK);
			m_tInfo.fX = pt.x;
			m_tInfo.fY = pt.y;
			CSoundMgr::Get_Instance()->PlayEffect(L"아이템클릭.mp3", CSoundMgr::ITEM_CLICK);
		}
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EQUIP_CLICK);
			if (m_iRotate == 1)	//인벤 에서 우측키 누를시 장비창으로 ㄱㄱ
			{
				// 장비창으로의 이동이 필요하다.
				CObjMgr::Get_Instance()->DeleteID(ObjID::WEAPON);
				CObjMgr::Get_Instance()->AddObject(ObjID::WEAPON, CAbstractFactory<CShopBow>::Create());
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Att(m_iPower);
				dynamic_cast<CEquipment*>(CObjMgr::Get_Instance()->Get_Equipment())->Set_Equip(this, 1);
				CSoundMgr::Get_Instance()->PlayEffect(L"장비소비.mp3", CSoundMgr::EQUIP_CLICK);
			}
			else if (m_iRotate == 2) // 장비창일때...
			{
				CObjMgr::Get_Instance()->DeleteID(ObjID::WEAPON);
				CObjMgr::Get_Instance()->AddObject(ObjID::WEAPON, CAbstractFactory<CWeapon>::Create());
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Att(-m_iPower);
				m_iRotate = 1; // 인벤으로 가기 위해선 이렇게함.
			}
			else if (m_iRotate == -1)	//상점
			{
				if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Gold() < m_iGold)
					return;
				else
				{
					dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inventory())->Buy_Equip(this, 1);
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Gold(m_iGold);
				}
			}
			else if (m_iRotate == 0) // 판매
			{
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Gold(-(m_iGold * 0.5));
				m_bIsDead = true;
			}
		}
	}
}

void CRedBow::Render(HDC hDC)
{
	CObj::UpdateRect();
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

	if (m_iRotate == -1)
	{
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, m_tInfo.fX + 40.f, m_tInfo.fY - m_tInfo.fCY / 2, L"파이어 아룬드", lstrlen(L"파이어 아룬드"));
		TextOut(hDC, m_tInfo.fX + 50.f, m_tInfo.fY, L"1000 메소", lstrlen(L"1000 메소"));
	}
}

void CRedBow::Release()
{
}
