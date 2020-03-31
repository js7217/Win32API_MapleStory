#include "stdafx.h"
#include "BossStage.h"
#include "Portal.h"
#include "Boss.h"
#include "BossHpBar.h"
#include "JBalok.h"
#include "CBalok.h"
#include "Boss_hand_left.h"
#include "Boss_hand_right.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "LineMgr.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
CBossStage::CBossStage()
	:m_iMapCX(0)
	,m_iMapCY(0)
	,m_pBoss(nullptr)
	,m_pBoss_hand_left(nullptr)
	,m_pBoss_hand_right(nullptr)
{
}


CBossStage::~CBossStage()
{
	Release();
}

void CBossStage::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Boss.bmp", L"BossMap");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Boss_back.bmp", L"BossMap_back");

	m_pBoss = CAbstractFactory<CBoss>::Create(1010.f, 280.f);
	CObjMgr::Get_Instance()->AddObject(ObjID::BOSS, m_pBoss);
	m_pBoss_hand_left = CAbstractFactory<CBoss_hand_left>::Create();
	m_pBoss_hand_right = CAbstractFactory<CBoss_hand_right>::Create();

	CObjMgr::Get_Instance()->AddObject(ObjID::BOSS_ARM, m_pBoss_hand_left);
	CObjMgr::Get_Instance()->AddObject(ObjID::BOSS_ARM, m_pBoss_hand_right);

	CObjMgr::Get_Instance()->AddObject(ObjID::MAINUI, CAbstractFactory<CBossHpBar>::Create());
	CLineMgr::Get_Instance()->LoadData(L"../Data/Boss_Line.dat");
	CTileMgr::Get_Instance()->LoadData(L"../Data/Boss_Tile.dat");
	m_iMapCX = 1799;
	m_iMapCY = 781;
	m_dwPatternTime = GetTickCount();
	m_dwTime = GetTickCount();
	m_iBossHp = m_pBoss->Get_Hp();
	m_iBossMaxHp = m_iBossHp;
	CScrollMgr::Set_Scroll(-999, -66);
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1621.f, 532.f);
	CSoundMgr::Get_Instance()->PlayBGM(L"Boss3.wav");
}

void CBossStage::Update()
{
	CObjMgr::Get_Instance()->Update();
	m_iBossHp = m_pBoss->Get_Hp();

	if(m_iBossHp > 0)
		BossPattern();
	if (m_iOption == 1 && m_iBossHp <= 0)
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_VILLAGE);
}

void CBossStage::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();

	CObjMgr::Get_Instance()->DeleteBullet();
	CScrollMgr::ScrollLock((float)m_iMapCX, (float)m_iMapCY);

	CTileMgr::Get_Instance()->TileCollision(CObjMgr::Get_Instance()->Get_Player(), this);
	if (CKeyMgr::Get_Instance()->KeyDown('A'))
	{
		dynamic_cast<CBoss*>(m_pBoss)->Set_BossState(CBoss::LIGHTNING);
		dynamic_cast<CBoss_hand_left*>(m_pBoss_hand_left)->Set_BossState_Left(CBoss_hand_left::LIGHTNING);
	}
	else if (CKeyMgr::Get_Instance()->KeyDown('S'))
	{
		dynamic_cast<CBoss*>(m_pBoss)->Set_BossState(CBoss::EXPLOSION);
		dynamic_cast<CBoss_hand_right*>(m_pBoss_hand_right)->Set_BossState_Right(CBoss_hand_right::EXPLOSION);
	}
	else if (CKeyMgr::Get_Instance()->KeyDown('D'))
	{
		dynamic_cast<CBoss*>(m_pBoss)->Set_BossState(CBoss::ICE);
		dynamic_cast<CBoss_hand_right*>(m_pBoss_hand_right)->Set_BossState_Right(CBoss_hand_right::ICE);
	}
}

void CBossStage::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBackBuffer = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	HDC hBoss = CBitmapMgr::Get_Instance()->FindImage(L"BossMap");
	HDC hBossBack = CBitmapMgr::Get_Instance()->FindImage(L"BossMap_back");
	BitBlt(hBackBuffer, iScrollX, iScrollY, m_iMapCX, m_iMapCY,
		hBossBack, 0, 0,SRCCOPY); // 맵 사이즈만큼 해줘야함.
	GdiTransparentBlt(hBackBuffer, iScrollX, iScrollY, m_iMapCX, m_iMapCY, hBoss, 0, 0, m_iMapCX, m_iMapCY, RGB(66, 66, 66));

	CObjMgr::Get_Instance()->Render(hBackBuffer);
	
	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
	{
		CLineMgr::Get_Instance()->Render(hBackBuffer); // 백버퍼에 그리기 전에 라인을 그려야 스크롤 값이 제대로 먹는듯 하다.
		CTileMgr::Get_Instance()->Render(hBackBuffer);
	}
	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CBossStage::Release()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CObjMgr::Get_Instance()->DeleteID(ObjID::BOSS);
	CObjMgr::Get_Instance()->DeleteID(ObjID::BOSS_ARM);
	CObjMgr::Get_Instance()->DeleteID(ObjID::MONSTER);
	CObjMgr::Get_Instance()->DeleteID(ObjID::GOLD);
	CObjMgr::Get_Instance()->DeleteID(ObjID::UI);
	CTileMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
}

void CBossStage::BossPattern()
{
	if (m_iBossHp >= m_iBossMaxHp * 0.5)				//피가 50% 이상일때.
	{
		if (dynamic_cast<CBoss*>(m_pBoss)->Get_BossState() == CBoss::IDLE)
		{
			static int PatternCnt = 1;
			switch (PatternCnt)
			{
			case 1:
				dynamic_cast<CBoss*>(m_pBoss)->Set_BossState(CBoss::LIGHTNING);
				dynamic_cast<CBoss_hand_left*>(m_pBoss_hand_left)->Set_BossState_Left(CBoss_hand_left::LIGHTNING);
				PatternCnt++;
				break;
			case 2:
				dynamic_cast<CBoss*>(m_pBoss)->Set_BossState(CBoss::EXPLOSION);
				dynamic_cast<CBoss_hand_right*>(m_pBoss_hand_right)->Set_BossState_Right(CBoss_hand_right::EXPLOSION);
				PatternCnt++;
				break;
			case 3:
				dynamic_cast<CBoss*>(m_pBoss)->Set_BossState(CBoss::LIGHTNING);
				dynamic_cast<CBoss_hand_left*>(m_pBoss_hand_left)->Set_BossState_Left(CBoss_hand_left::LIGHTNING);
				PatternCnt++;
				break;
			case 4:
				dynamic_cast<CBoss*>(m_pBoss)->Set_BossState(CBoss::EXPLOSION);
				dynamic_cast<CBoss_hand_right*>(m_pBoss_hand_right)->Set_BossState_Right(CBoss_hand_right::EXPLOSION);
				PatternCnt++;
			case 5:
				dynamic_cast<CBoss*>(m_pBoss)->Set_BossState(CBoss::ICE);
				dynamic_cast<CBoss_hand_right*>(m_pBoss_hand_right)->Set_BossState_Right(CBoss_hand_right::ICE);
				PatternCnt = 1;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		static int Cnt = 0;
		if (Cnt == 0)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CCBalok>::Create(900.f, 220.f));
			CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CCBalok>::Create(1500.f, 200.f));
			CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CCBalok>::Create(200.f, 200.f));
			CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CJBalok>::Create(1400.f, 200.f));
			CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CJBalok>::Create(1300.f, 200.f));
			CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CJBalok>::Create(1000.f, 200.f));
			CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CJBalok>::Create(900.f, 200.f));
			CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CJBalok>::Create(700.f, 200.f));
			Cnt++;
		}
		if (dynamic_cast<CBoss*>(m_pBoss)->Get_BossState() == CBoss::IDLE)
		{
			static int PatternCnt = 3;
			switch (PatternCnt)
			{
			case 1:
				dynamic_cast<CBoss*>(m_pBoss)->Set_BossState(CBoss::LIGHTNING);
				dynamic_cast<CBoss_hand_left*>(m_pBoss_hand_left)->Set_BossState_Left(CBoss_hand_left::LIGHTNING);
				PatternCnt = 3;
				break;
			case 2:
				dynamic_cast<CBoss*>(m_pBoss)->Set_BossState(CBoss::EXPLOSION);
				dynamic_cast<CBoss_hand_right*>(m_pBoss_hand_right)->Set_BossState_Right(CBoss_hand_right::EXPLOSION);
				PatternCnt--;
				break;
			case 3:
				dynamic_cast<CBoss*>(m_pBoss)->Set_BossState(CBoss::ICE);
				dynamic_cast<CBoss_hand_right*>(m_pBoss_hand_right)->Set_BossState_Right(CBoss_hand_right::ICE);
				PatternCnt--;
				break;
			default:
				break;
			}
		}
	}
}
