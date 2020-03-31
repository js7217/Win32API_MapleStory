#include "stdafx.h"
#include "Logo.h"
#include "SceneMgr.h"
CLogo::CLogo()
	:m_fCX(0.f)
	,m_fCY(0.f)
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	m_fCX = 800.f;
	m_fCY = 600.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Logo/Logo.bmp", L"Logo");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 800;
	m_tFrame.dwFrameTime = GetTickCount();
	CSoundMgr::Get_Instance()->PlayBGM(L"Logo.mp3");
}

void CLogo::LateInitialize()
{
}

void CLogo::Update()
{
}

void CLogo::LateUpdate()
{
	FrameMove();
	if (m_tFrame.iFrameEnd < m_tFrame.iFrameStart || GetAsyncKeyState(VK_RETURN))
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
}

void CLogo::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Logo");
	GdiTransparentBlt(hDC,
		0, 0,
		WINCX, WINCY,
		hMemDC,
		(int)m_fCX * m_tFrame.iFrameStart, (int)m_fCY * m_tFrame.iFrameScene,
		(int)m_fCX, (int)m_fCY, SRCCOPY);
}

void CLogo::Release()
{
}

void CLogo::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}
}
