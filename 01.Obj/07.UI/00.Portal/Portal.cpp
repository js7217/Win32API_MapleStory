#include "stdafx.h"
#include "Portal.h"


CPortal::CPortal()
{
}

CPortal::CPortal(float fX, float fY)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
}


CPortal::~CPortal()
{
	Release();
}

void CPortal::Initialize()
{
	m_tInfo.fCX = 89.f;
	m_tInfo.fCY = 257.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/MapObject/Portal/portal.bmp", L"Portal");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_pFrameKey = L"Portal";
}

int CPortal::Update()
{
	return 0;
}

void CPortal::LateUpdate()
{
	CObj::FrameMove(0);
}

void CPortal::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CPortal::Release()
{
}
