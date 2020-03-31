#include "stdafx.h"
#include "ExpBar.h"

#include "ObjMgr.h"
CExpBar::CExpBar()
{
}


CExpBar::~CExpBar()
{
}

void CExpBar::Initialize()
{
	m_tInfo.fX = 404.f;
	m_tInfo.fY = 583.f;
	m_tInfo.fCX = 310.f;
	m_tInfo.fCY = 14.f;
	m_fMaxfCX = m_tInfo.fCX;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/ExpBar.bmp", L"ExpBar");
	m_pFrameKey = L"ExpBar";
	CObj::UpdateRect();
}

int CExpBar::Update()
{
	m_iMaxExp = CObjMgr::Get_Instance()->Get_Player()->Get_MaxExp();
	m_iExp = CObjMgr::Get_Instance()->Get_Player()->Get_Exp();
	m_tInfo.fCX = (m_fMaxfCX * m_iExp) / m_iMaxExp;
	return 0;
}

void CExpBar::LateUpdate()
{
}

void CExpBar::Render(HDC hDC)
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

void CExpBar::Release()
{
}
