#include "stdafx.h"
#include "EffectDamage.h"

#include "ObjMgr.h"
CEffectDamage::CEffectDamage()
{
}

CEffectDamage::CEffectDamage(float fX, float fY, float fCX, float fCY, TCHAR * pFrameKey, int iDamage)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_tInfo.fCX = fCX;
	m_tInfo.fCY = fCY;
	m_pFrameKey = pFrameKey;
	m_tFrame.iFrameStart = iDamage;
	m_tFrame.iFrameEnd = iDamage;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = (DWORD)1000.f;
	m_tFrame.dwFrameTime = GetTickCount();
}


CEffectDamage::~CEffectDamage()
{
	Release();
}

void CEffectDamage::Initialize()
{
	m_fSpeed = 2.f;

}

int CEffectDamage::Update()
{
	m_tInfo.fY -= m_fSpeed;
	if (m_bIsDead)
		return OBJ_DEAD;
	CObj::UpdateRect();

	return OBJ_NOEVENT;
}

void CEffectDamage::LateUpdate()
{
	UpdateRect();
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed <= GetTickCount())
	{
		m_bIsDead = true;
	}
}

void CEffectDamage::Render(HDC hDC)
{
	UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(0, 255, 0));
}

void CEffectDamage::Release()
{
}
