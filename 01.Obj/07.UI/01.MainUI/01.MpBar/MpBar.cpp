#include "stdafx.h"
#include "MpBar.h"

#include "ObjMgr.h"
CMpBar::CMpBar()
{
}

CMpBar::~CMpBar()
{
}

void CMpBar::Initialize()
{
	m_tInfo.fX = 490.f;
	m_tInfo.fY = 567.f;
	m_tInfo.fCX = 141.f;
	m_tInfo.fCY = 14.f;
	m_fMaxfCX = m_tInfo.fCX;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/MPBar.bmp", L"MPBar");
	m_pFrameKey = L"MPBar";
	CObj::UpdateRect();
}

int CMpBar::Update()
{
	m_iMaxMp = CObjMgr::Get_Instance()->Get_Player()->Get_MaxMp();
	m_iMp = CObjMgr::Get_Instance()->Get_Player()->Get_Mp();
	m_tInfo.fCX = (m_fMaxfCX * m_iMp) / m_iMaxMp;
	return 0;
}

void CMpBar::LateUpdate()
{
}

void CMpBar::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		SRCCOPY);
}

void CMpBar::Release()
{
}
