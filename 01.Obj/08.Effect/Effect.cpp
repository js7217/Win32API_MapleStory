#include "stdafx.h"
#include "Effect.h"


CEffect::CEffect()
{
}

CEffect::CEffect(float fX, float fY, float fCX, float fCY, TCHAR* pFrameKey, int iFrameend)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_tInfo.fCX = fCX;
	m_tInfo.fCY = fCY;
	m_pFrameKey = pFrameKey;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = iFrameend;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = (DWORD)50.f;
	m_tFrame.dwFrameTime = GetTickCount();
}


CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize()
{
}

int CEffect::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	CObj::UpdateRect();

	return OBJ_NOEVENT;
}

void CEffect::LateUpdate()
{
	UpdateRect();
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_bIsDead = true;
}

void CEffect::Render(HDC hDC)
{
	UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(0, 255, 0));
}

void CEffect::Release()
{
}
