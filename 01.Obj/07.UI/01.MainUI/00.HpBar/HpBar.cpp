#include "stdafx.h"
#include "HpBar.h"
#include "ObjMgr.h"

CHpBar::CHpBar()
{
}


CHpBar::~CHpBar()
{
}


void CHpBar::Initialize()
{
	m_tInfo.fX = 320.f;
	m_tInfo.fY = 567.f;
	m_tInfo.fCX = 141.f;
	m_tInfo.fCY = 14.f;
	m_fMaxfCX = m_tInfo.fCX; // 풀피상태일때를 하나의 변수로 받는다.
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/HPBar.bmp", L"HPBar");
	m_pFrameKey = L"HPBar";
	CObj::UpdateRect();
}

int CHpBar::Update()
{
	m_iMaxHp = CObjMgr::Get_Instance()->Get_Player()->Get_MaxHp();
	m_iHp = CObjMgr::Get_Instance()->Get_Player()->Get_Hp();
	m_tInfo.fCX = (m_fMaxfCX * m_iHp) / m_iMaxHp;
	return 0;
}

void CHpBar::LateUpdate()
{
}

void CHpBar::Render(HDC hDC)
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

void CHpBar::Release()
{
}
