#include "stdafx.h"
#include "Shop.h"
#include "RedPotion.h"
#include "MpPotion.h"
#include "RedBow.h"
#include "Armor.h"
#include "Inventory.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CShop::CShop()
{
}


CShop::~CShop()
{
	Release();
}

void CShop::Initialize()
{
	m_tInfo.fX = 600.f;
	m_tInfo.fY = 250.f;
	m_tInfo.fCX = 276.f;
	m_tInfo.fCY = 505.f;

	m_fItemX = m_tInfo.fX - 110.f;
	m_fItemY = m_tInfo.fY - 110.f;
	m_fDistanceY = 41.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/store.bmp", L"store");
	m_VectorShop.emplace_back(CAbstractFactory<CRedPotion>::Create(-1, m_fItemX, m_fItemY));
	m_VectorShop.emplace_back(CAbstractFactory<CMpPotion>::Create(-1, m_fItemX, m_fItemY + m_fDistanceY));
	m_VectorShop.emplace_back(CAbstractFactory<CRedBow>::Create(-1, m_fItemX, m_fItemY + m_fDistanceY * 2));
	m_VectorShop.emplace_back(CAbstractFactory<CArmor>::Create(-1, m_fItemX, m_fItemY + m_fDistanceY * 3));
	m_pFrameKey = L"store";
}

int CShop::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	for (int i = 0; i < m_VectorShop.size(); ++i)
	{
		m_VectorShop[i]->Set_Pos(m_fItemX, m_fItemY + (m_fDistanceY * i));
	}
	return OBJ_NOEVENT;
}

void CShop::LateUpdate()
{
	if (CKeyMgr::Get_Instance()->KeyDown(VK_ESCAPE))
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SHOP);
		dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inventory())->Set_Option(1);
		CSoundMgr::Get_Instance()->PlayEffect(L"ESC.mp3", CSoundMgr::SHOP);
		m_bIsDead = true;
	}

	for (auto& iter : m_VectorShop)
		iter->LateUpdate();
}

void CShop::Render(HDC hDC)
{
	CObj::UpdateRect();

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(61, 52, 43));

	for (auto& iter : m_VectorShop)
	{
		iter->Render(hDC);

	}
}

void CShop::Release()
{
	for_each(m_VectorShop.begin(), m_VectorShop.end(), Safe_Delete<CObj*>);
}
