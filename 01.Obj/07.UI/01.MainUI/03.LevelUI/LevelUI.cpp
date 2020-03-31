#include "stdafx.h"
#include "LevelUI.h"

#include "ObjMgr.h"
CLevelUI::CLevelUI()
{
}


CLevelUI::~CLevelUI()
{
}

void CLevelUI::UpdateRect_Lv1()
{
	m_tRect_Lv1.left = LONG(m_tInfo_Lv1.fX - (m_tInfo_Lv1.fCX / 2.f));
	m_tRect_Lv1.top = LONG(m_tInfo_Lv1.fY - (m_tInfo_Lv1.fCY / 2.f));
	m_tRect_Lv1.right = LONG(m_tInfo_Lv1.fX + (m_tInfo_Lv1.fCX / 2.f));
	m_tRect_Lv1.bottom = LONG(m_tInfo_Lv1.fY + (m_tInfo_Lv1.fCY / 2.f));
}

void CLevelUI::UpdateRect_Lv10()
{
	m_tRect_Lv10.left = LONG(m_tInfo_Lv10.fX - (m_tInfo_Lv10.fCX / 2.f));
	m_tRect_Lv10.top = LONG(m_tInfo_Lv10.fY - (m_tInfo_Lv10.fCY / 2.f));
	m_tRect_Lv10.right = LONG(m_tInfo_Lv10.fX + (m_tInfo_Lv10.fCX / 2.f));
	m_tRect_Lv10.bottom = LONG(m_tInfo_Lv10.fY + (m_tInfo_Lv10.fCY / 2.f));
}

void CLevelUI::Initialize()
{
	m_tInfo_Lv1.fX = 50.f;
	m_tInfo_Lv1.fY = 575.f;
	m_tInfo_Lv1.fCX = 10.f;
	m_tInfo_Lv1.fCY = 12.f;

	m_tInfo_Lv10.fX = 45.f;
	m_tInfo_Lv10.fY = 575.f;
	m_tInfo_Lv10.fCX = 10.f;
	m_tInfo_Lv10.fCY = 12.f;
	m_iLevel_1 = 0;
	m_iLevel_10 = 0;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/LvNum.bmp", L"LvNum");
	m_pFrameKey = L"LvNum";
	UpdateRect_Lv1();
	UpdateRect_Lv10();
}

int CLevelUI::Update()
{
	m_iLevel_1 = CObjMgr::Get_Instance()->Get_Player()->Get_Level() % 10;
	m_iLevel_10 = CObjMgr::Get_Instance()->Get_Player()->Get_Level() / 10;
	if (m_iLevel_10 != 0)
		m_tInfo_Lv1.fX = 55.f;
	return 0;
}

void CLevelUI::LateUpdate()
{
}

void CLevelUI::Render(HDC hDC)
{
	UpdateRect_Lv1();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	if (m_iLevel_10 == 0)
	{
		GdiTransparentBlt(hDC,
			(int)m_tRect_Lv1.left, (int)m_tRect_Lv1.top,
			(int)m_tInfo_Lv1.fCX, (int)m_tInfo_Lv1.fCY,
			hMemDC,
			(int)m_tInfo_Lv1.fCX * m_iLevel_1, 0,
			(int)m_tInfo_Lv1.fCX, (int)m_tInfo_Lv1.fCY,
			SRCCOPY);
	}
	else
	{
		GdiTransparentBlt(hDC,
			(int)m_tRect_Lv1.left, (int)m_tRect_Lv1.top,
			(int)m_tInfo_Lv1.fCX, (int)m_tInfo_Lv1.fCY,
			hMemDC,
			(int)m_tInfo_Lv1.fCX * m_iLevel_1, 0,
			(int)m_tInfo_Lv1.fCX, (int)m_tInfo_Lv1.fCY,
			SRCCOPY);
		GdiTransparentBlt(hDC,
			(int)m_tRect_Lv10.left, (int)m_tRect_Lv10.top,
			(int)m_tInfo_Lv10.fCX, (int)m_tInfo_Lv10.fCY,
			hMemDC,
			(int)m_tInfo_Lv10.fCX * m_iLevel_10, 0,
			(int)m_tInfo_Lv10.fCX, (int)m_tInfo_Lv10.fCY,
			SRCCOPY);
	}
}

void CLevelUI::Release()
{
}
