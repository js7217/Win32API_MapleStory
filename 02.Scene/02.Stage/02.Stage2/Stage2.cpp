#include "stdafx.h"
#include "Stage2.h"
#include "Player.h"
#include "Slime.h"
#include "Golem.h"
#include "ShopNpc.h"
#include "Portal.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"

CStage2::CStage2()
	:m_iMapCX(0)
	, m_iMapCY(0)
{
}


CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Stage2.bmp", L"Stage2");

	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CShopNpc>::Create(1550, 220));
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CPortal>::Create(205, 560));
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CPortal>::Create(1245, 140));
	CLineMgr::Get_Instance()->LoadData(L"../Data/Stage2_Line.dat");
	CTileMgr::Get_Instance()->LoadData(L"../Data/Stage2_Tile.dat");
	m_iMapCX = 1890;
	m_iMapCY = 941;
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(194.f, 642.f);
	CSoundMgr::Get_Instance()->PlayBGM(L"헤네시스필드2.wav");
}

void CStage2::LateInitialize()
{
}

void CStage2::Update()
{
	CObjMgr::Get_Instance()->Update();
	if (m_iOption == 1)
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_BOSS);
	if (m_iOption == 2)
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE1);
}

void CStage2::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->DeleteBullet();
	CScrollMgr::ScrollLock((float)m_iMapCX, (float)m_iMapCY);
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->PlayerLock((float)m_iMapCX); //해결 -> 맵의 크기를 알아야하므로 스테이지에서 진행.
	CTileMgr::Get_Instance()->TileCollision(CObjMgr::Get_Instance()->Get_Player(), this);
	if (CObjMgr::Get_Instance()->Get_List(ObjID::MONSTER).empty())
		MonsterCreate();
}

void CStage2::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBackBuffer = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"Stage2");

	BitBlt(hBackBuffer, iScrollX, iScrollY, m_iMapCX, m_iMapCY,
		hBack, 0, 0, SRCCOPY); // 맵 사이즈만큼 해줘야함.
	CObjMgr::Get_Instance()->Render(hBackBuffer);

	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
	{
		CLineMgr::Get_Instance()->Render(hBackBuffer); // 백버퍼에 그리기 전에 라인을 그려야 스크롤 값이 제대로 먹는듯 하다.
		CTileMgr::Get_Instance()->Render(hBackBuffer);
	}
	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CStage2::Release()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CObjMgr::Get_Instance()->DeleteID(ObjID::MONSTER);
	CTileMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->DeleteID(ObjID::UI);
	CObjMgr::Get_Instance()->DeleteID(ObjID::GOLD);
}

void CStage2::MonsterCreate()
{
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(200.f, 300.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(300.f, 500.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CGolem>::Create(1200.f, 165.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CGolem>::Create(500.f, 600.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(1000.f, 700.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CGolem>::Create(900.f, 600.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(700.f, 200.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CGolem>::Create(600.f, 400.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(500.f, 600.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CGolem>::Create(200.f, 300.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(700.f, 450.f));
}
