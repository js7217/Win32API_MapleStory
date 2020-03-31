#include "stdafx.h"
#include "Explosion.h"


CExplosion::CExplosion()
{
}


CExplosion::~CExplosion()
{
}

void CExplosion::Initialize()
{
	m_tInfo.fCX = 162.f;
	m_tInfo.fCY = 135.f;
	m_fSpeed = 0.f;
	m_iDamage = m_Well512.GetValue(400, 600);
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/Boss/Explosion.bmp", L"Explosion");

	m_pFrameKey = L"Explosion";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eID = ObjID::BOSS;
}

int CExplosion::Update()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect(2.f, 2.f, 2.f, 2.f);
	if (m_bIsDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CExplosion::LateUpdate()
{
	CObj::UpdateRect();
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_bIsDead = true;
}

void CExplosion::Render(HDC hDC)
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
		RGB(255, 0, 255));
}

void CExplosion::Release()
{
}
