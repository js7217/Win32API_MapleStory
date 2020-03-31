#include "stdafx.h"
#include "MainStage.h"
#include "Player.h"
#include "Weapon.h"
#include "ShopBow.h"
#include "Portal.h"
#include "ShopNpc.h"
#include "MainUI.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"

#include "Slime.h"
CMainStage::CMainStage()
	:m_iMapCX(0)
	, m_iMapCY(0)
{
}


CMainStage::~CMainStage()
{
	Release();
}

void CMainStage::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"헤네시스.wav");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Main.bmp", L"Main");
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CPortal>::Create(1700, 470));
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CShopNpc>::Create(400, 550));
	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(100, 100));
	CLineMgr::Get_Instance()->LoadData(L"../Data/Main_Line.dat");
	CTileMgr::Get_Instance()->LoadData(L"../Data/Main_Tile.dat");
	m_iMapCX = 1920;
	m_iMapCY = 681;
}

void CMainStage::LateInitialize()
{
	// 플레이어 추가.(첫 스테이지니까 Add)
	CObjMgr::Get_Instance()->AddObject(ObjID::MAINUI, CAbstractFactory<CMainUI>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::WEAPON, CAbstractFactory<CWeapon>::Create());
}

void CMainStage::Update()
{
	CScene::LateInitialize();
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	if (m_iOption == 1)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::POTAL);
		CScrollMgr::Set_ScrollX(-3000);
		CScrollMgr::Set_ScrollY(-2000);			//씬전환시 플레이어 자리로 맵 render 시작.
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE1);
		CSoundMgr::Get_Instance()->PlayEffect(L"포탈.mp3", CSoundMgr::POTAL);
	}
	if (CKeyMgr::Get_Instance()->KeyDown('1'))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_BOSS);
	}
	/*if (CObjMgr::Get_Instance()->Get_List(ObjID::MONSTER).empty())
	{
		CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CGolem>::Create(600, 400));

	}*/
}

void CMainStage::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->DeleteBullet();
	CScrollMgr::ScrollLock((float)m_iMapCX, (float)m_iMapCY);
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->PlayerLock((float)m_iMapCX); //해결 -> 맵의 크기를 알아야하므로 스테이지에서 진행.
	CTileMgr::Get_Instance()->TileCollision(CObjMgr::Get_Instance()->Get_Player(), this);
}

void CMainStage::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBackBuffer = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"Main");

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

void CMainStage::Release()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CTileMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->DeleteID(ObjID::MONSTER);
	CObjMgr::Get_Instance()->DeleteID(ObjID::UI);
	CObjMgr::Get_Instance()->DeleteID(ObjID::GOLD);
}