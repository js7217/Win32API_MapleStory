#include "stdafx.h"
#include "Stage.h"
#include "Player.h"
#include "Weapon.h"
#include "Slime.h"

#include "ObjMgr.h"
#include "LineMgr.h"
#include "EditMgr.h"
#include "AbstractFactory.h"
CStage::CStage()
	:m_iMapCX(0)
	,m_iMapCY(0)
{
}


CStage::~CStage()
{
}

void CStage::Initialize()
{
//	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Main.bmp", L"Main");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Stage1.bmp", L"Stage1");
	// 플레이어 추가.(첫 스테이지니까 Add)
	CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::WEAPON, CAbstractFactory<CWeapon>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(200.f, 300.f));
	CLineMgr::Get_Instance()->LoadData(L"../Data/Stage1.dat");
	m_iMapCX = 1773;
	m_iMapCY = 1464;
}

void CStage::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CStage::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
	CScrollMgr::ScrollLock((float)m_iMapCX, (float)m_iMapCY);
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->PlayerLock((float)m_iMapCX); //해결 -> 맵의 크기를 알아야하므로 스테이지에서 진행.

}

void CStage::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBackBuffer = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"Stage1");

	BitBlt(hBackBuffer, iScrollX, iScrollY, m_iMapCX, m_iMapCY,
		hBack, 0, 0, SRCCOPY); // 맵 사이즈만큼 해줘야함.
	CObjMgr::Get_Instance()->Render(hBackBuffer);

	if(CKeyMgr::Get_Instance()->KeyPressing('Q'))
		CLineMgr::Get_Instance()->Render(hBackBuffer); // 백버퍼에 그리기 전에 라인을 그려야 스크롤 값이 제대로 먹는듯 하다.

	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CStage::Release()
{
	//마을에서 사라질거 추가하자.
}
