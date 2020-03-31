#include "stdafx.h"
#include "Meteo.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"
CMeteo::CMeteo()
{
}


CMeteo::~CMeteo()
{
	Release();
}

void CMeteo::Initialize()
{
	m_tInfo.fCX = 800.f;
	m_tInfo.fCY = 291.f;
	m_fSizeX = 308.f;
	m_iAtt = CObjMgr::Get_Instance()->Get_Player()->Get_Att();
	m_iDamage = m_Well512.GetValue(500, 900) + m_iAtt;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Skill/Fire/Hit/Fire_Hit.bmp", L"Fire_Hit");
	m_pFrameKey = L"Fire_Hit";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eID = ObjID::PLAYER;
}

void CMeteo::LateInitialize()
{
	m_tInfo.fY -= 70.5f;
}

int CMeteo::Update()
{
	CObj::LateInitialize();
	if (m_bIsDead)
	{
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CMeteo::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect(0.f, 0.f, 0.f, 0.f);
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		if (m_tFrame.iFrameStart == 1)
			CObj::UpdateCollisionRect(2.f, 8.f, 2.f, 2.f);
		else
			CObj::UpdateCollisionRect(0.f, 0.f, 0.f, 0.f);
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_bIsDead = true;
	}
}

void CMeteo::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_fSizeX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_fSizeX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iFrameScene,
		(int)m_fSizeX, (int)m_tInfo.fCY,
		RGB(0, 255, 0));
	GdiTransparentBlt(hDC,
		(int)m_tRect.left + 200.f + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_fSizeX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_fSizeX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iFrameScene,
		(int)m_fSizeX, (int)m_tInfo.fCY,
		RGB(0, 255, 0));
	GdiTransparentBlt(hDC,
		(int)m_tRect.left + 400.f + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_fSizeX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_fSizeX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iFrameScene,
		(int)m_fSizeX, (int)m_tInfo.fCY,
		RGB(0, 255, 0));
	GdiTransparentBlt(hDC,
		(int)m_tRect.left + 600.f + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_fSizeX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_fSizeX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iFrameScene,
		(int)m_fSizeX, (int)m_tInfo.fCY,
		RGB(0, 255, 0));
}

void CMeteo::Release()
{
}
