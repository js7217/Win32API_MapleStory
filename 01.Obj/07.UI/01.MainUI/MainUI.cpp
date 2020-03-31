#include "stdafx.h"
#include "MainUI.h"


CMainUI::CMainUI()
{
}


CMainUI::~CMainUI()
{
	Release();
}

void CMainUI::Initialize()
{
	m_tInfo.fX = WINCX * 0.5f;
	m_tInfo.fY = WINCY * 0.5f;
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/MainUI.bmp", L"MainUI");

	m_pFrameKey = L"MainUI";
}

int CMainUI::Update()
{
	return 0;
}

void CMainUI::LateUpdate()
{
}

void CMainUI::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(0, 0, 255));
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255,255));
	TextOut(hDC, 120, 567, L"차재성", lstrlen(L"차재성"));
}

void CMainUI::Release()
{
}
