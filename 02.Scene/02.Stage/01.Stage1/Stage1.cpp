#include "stdafx.h"
#include "Stage1.h"
#include "Player.h"
#include "Slime.h"
#include "Portal.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"

CStage1::CStage1()
{
}


CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	//CScrollMgr::Set_ScrollX(-1920);
	//CScrollMgr::Set_ScrollY(-681);
	//	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Main.bmp", L"Main");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Stage1.bmp", L"Stage1");
	// 플레이어 추가.(첫 스테이지니까 Add)
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CPortal>::Create(1150, 165));
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CPortal>::Create(1600, 1120));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(200.f, 300.f));
	CLineMgr::Get_Instance()->LoadData(L"../Data/Stage1_Line.dat");
	CTileMgr::Get_Instance()->LoadData(L"../Data/Stage1_Tile.dat");
	m_iMapCX = 1773;
	m_iMapCY = 1464;
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1600, 1200);
	CScrollMgr::Set_Scroll(-973, -744);
	CSoundMgr::Get_Instance()->PlayBGM(L"헤네시스필드.wav");
}

void CStage1::LateInitialize()
{
}

void CStage1::Update()
{
	CObjMgr::Get_Instance()->Update();
	if (m_iOption == 1)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::POTAL);
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE2);
		CSoundMgr::Get_Instance()->PlayEffect(L"포탈.mp3", CSoundMgr::POTAL);
	}
	if (m_iOption == 2)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::POTAL);
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(200, 400);
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_VILLAGE);
		CSoundMgr::Get_Instance()->PlayEffect(L"포탈.mp3", CSoundMgr::POTAL);
	}
}

void CStage1::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->DeleteBullet();
	CScrollMgr::ScrollLock((float)m_iMapCX, (float)m_iMapCY);
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->PlayerLock((float)m_iMapCX); //해결 -> 맵의 크기를 알아야하므로 스테이지에서 진행.
	CTileMgr::Get_Instance()->TileCollision(CObjMgr::Get_Instance()->Get_Player(), this);
	if (CObjMgr::Get_Instance()->Get_List(ObjID::MONSTER).empty())
		MonsterCreate();
}

void CStage1::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBackBuffer = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"Stage1");

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

void CStage1::Release()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CObjMgr::Get_Instance()->DeleteID(ObjID::MONSTER);
	CObjMgr::Get_Instance()->DeleteID(ObjID::UI);
	CTileMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->DeleteID(ObjID::GOLD);
}

void CStage1::MonsterCreate()
{
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(200.f, 300.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(500.f, 1000.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(300.f, 500.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(1200.f, 165.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(1200.f, 800.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(800.f, 900.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(500.f, 600.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(1000.f, 700.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(900.f, 600.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(800.f, 900.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(700.f, 200.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(600.f, 400.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(500.f, 600.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(400.f, 800.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(300.f, 900.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(200.f, 300.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(1000.f, 850.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(900.f, 950.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(700.f, 450.f));

}
