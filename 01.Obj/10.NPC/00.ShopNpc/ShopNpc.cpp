#include "stdafx.h"
#include "ShopNpc.h"
#include "Shop.h"
#include "Inventory.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CShopNpc::CShopNpc()
{
}


CShopNpc::~CShopNpc()
{
	Release();
}

void CShopNpc::Initialize()
{
	m_tInfo.fCX = 58.f;
	m_tInfo.fCY = 76.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/NPC/PotionNpc.bmp", L"NPC");
	m_pFrameKey = L"NPC";
	CObj::UpdateRect();
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 27;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CShopNpc::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CShopNpc::LateUpdate()
{
	CObj::UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	pt.x -= iScrollX;
	pt.y -= iScrollY;
	if (PtInRect(&m_tRect, pt))
	{
		cout << "»óÁ¡" << endl;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CShop>::Create());
			dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inventory())->Set_Option(0);
		}
	}
	CObj::FrameMove(0);
}

void CShopNpc::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(0, 0, 1));
}

void CShopNpc::Release()
{
	for_each(m_VectorShop.begin(), m_VectorShop.end(), Safe_Delete<CObj*>);
}
