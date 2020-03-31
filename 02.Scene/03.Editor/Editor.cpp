#include "stdafx.h"
#include "Editor.h"
#include "EditMgr.h"
#include "LineMgr.h"
#include "TileMgr.h"
CEditor::CEditor()
{
}


CEditor::~CEditor()
{
	Release();
}

void CEditor::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Main.bmp", L"Main");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Stage1.bmp", L"Stage1");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Stage2.bmp", L"Stage2");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Map/Boss.bmp", L"BossMap");
	CEditMgr::Get_Instance()->Initialize();
	m_pFrameKey = L"Main";
	m_pLineKey = L"../Data/Main_Line.dat";
	m_pTileKey = L"../Data/Main_Tile.dat";
	m_fCX = MAIN_STAGECX;
	m_fCY = MAIN_STAGECY;
	CEditMgr::Get_Instance()->Set_SaveKey(m_pLineKey, m_pTileKey);
}

void CEditor::Update()
{
	CEditMgr::Get_Instance()->Update();
	KeyCheck();
}

void CEditor::LateUpdate()
{
	CEditMgr::Get_Instance()->LateUpdate();
	CScrollMgr::ScrollLock(m_fCX, m_fCY);
}

void CEditor::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBackBuffer = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	BitBlt(hBackBuffer, iScrollX, iScrollY, (int)m_fCX, (int)m_fCY,
		hBack, 0, 0, SRCCOPY); // ¸Ê »çÀÌÁî¸¸Å­ ÇØÁà¾ßÇÔ.
	CEditMgr::Get_Instance()->Render(hBackBuffer);
	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CEditor::Release()
{
	CEditMgr::Destory_Instance();
	CLineMgr::Get_Instance()->Destory_Instance();
	CTileMgr::Get_Instance()->Destory_Instance();
}

void CEditor::KeyCheck()
{
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
	{
		CScrollMgr::Set_ScrollX(10.f);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
	{
		CScrollMgr::Set_ScrollX(-10.f);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
	{
		CScrollMgr::Set_ScrollY(10.f);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
	{
		CScrollMgr::Set_ScrollY(-10.f);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
	{
		CEditMgr::Get_Instance()->Release();
		m_pFrameKey = L"Main";
		m_pLineKey = L"../Data/Main_Line.dat";
		m_pTileKey = L"../Data/Main_Tile.dat";
		m_fCX = MAIN_STAGECX;
		m_fCY = MAIN_STAGECY;
		CEditMgr::Get_Instance()->Set_SaveKey(m_pLineKey, m_pTileKey);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('W'))
	{
		CEditMgr::Get_Instance()->Release();
		m_pFrameKey = L"Stage1";
		m_pLineKey = L"../Data/Stage1_Line.dat";
		m_pTileKey = L"../Data/Stage1_Tile.dat";
		m_fCX = 1773;
		m_fCY = 1464;
		CEditMgr::Get_Instance()->Set_SaveKey(m_pLineKey, m_pTileKey);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('E'))
	{
		CEditMgr::Get_Instance()->Release();
		m_pFrameKey = L"Stage2";
		m_pLineKey = L"../Data/Stage2_Line.dat";
		m_pTileKey = L"../Data/Stage2_Tile.dat";
		m_fCX = 1890;
		m_fCY = 941;
		CEditMgr::Get_Instance()->Set_SaveKey(m_pLineKey, m_pTileKey);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('R'))
	{
		CEditMgr::Get_Instance()->Release();
		m_pFrameKey = L"BossMap";
		m_pLineKey = L"../Data/Boss_Line.dat";
		m_pTileKey = L"../Data/Boss_Tile.dat";
		m_fCX = 1799;
		m_fCY = 781;
		CEditMgr::Get_Instance()->Set_SaveKey(m_pLineKey, m_pTileKey);
	}
}
