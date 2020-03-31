#include "stdafx.h"
#include "BossHpBar.h"
#include "ObjMgr.h"

CBossHpBar::CBossHpBar()
{
}


CBossHpBar::~CBossHpBar()
{
}

void CBossHpBar::UpdateHpBarRect()
{
	m_tHpBarRect.left = LONG(m_tHpBarInfo.fX - (m_tHpBarInfo.fCX / 2.f));
	m_tHpBarRect.top = LONG(m_tHpBarInfo.fY - (m_tHpBarInfo.fCY / 2.f));
	m_tHpBarRect.right = LONG(m_tHpBarInfo.fX + (m_tHpBarInfo.fCX / 2.f));
	m_tHpBarRect.bottom = LONG(m_tHpBarInfo.fY + (m_tHpBarInfo.fCY / 2.f));
}

void CBossHpBar::Initialize()
{
	m_tInfo.fX = 415.f;
	m_tInfo.fY = 48.f;
	m_tInfo.fCX = 597.f;
	m_tInfo.fCY = 28.f;			//Hp

	m_tHpBarInfo.fX = 400.f;
	m_tHpBarInfo.fY = 50.f;
	m_tHpBarInfo.fCX = 634.f;
	m_tHpBarInfo.fCY = 35.f;	//HpBar

	m_fMaxfCX = m_tInfo.fCX;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/BossHpBar.bmp", L"BossHpBar"); // BossHp
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/BossHp.bmp", L"BossHp");
	m_pFrameKey = L"BossHpBar";
	m_pHpBarKey = L"BossHp";
	CObj::UpdateRect();
	UpdateHpBarRect();
}

int CBossHpBar::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	m_iMaxHp = CObjMgr::Get_Instance()->Get_Boss()->Get_MaxHp();
	m_iHp = CObjMgr::Get_Instance()->Get_Boss()->Get_Hp();
	m_tInfo.fCX = (m_fMaxfCX * m_iHp) / m_iMaxHp;
	return OBJ_NOEVENT;
}

void CBossHpBar::LateUpdate()
{
	if (m_iHp <= 0)
		m_bIsDead = true;
}

void CBossHpBar::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	HDC hHpDC = CBitmapMgr::Get_Instance()->FindImage(m_pHpBarKey);
	GdiTransparentBlt(hDC,
		(int)m_tHpBarRect.left, (int)m_tHpBarRect.top,
		(int)m_tHpBarInfo.fCX, (int)m_tHpBarInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tHpBarInfo.fCX, (int)m_tHpBarInfo.fCY,
		SRCCOPY);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hHpDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		SRCCOPY);
}

void CBossHpBar::Release()
{
}
