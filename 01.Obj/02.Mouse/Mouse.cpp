#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}

CMouse::~CMouse()
{
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_tInfo.fX = WINCX * 0.5f;
	m_tInfo.fY = WINCY * 0.5f;

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Mouse/cursor.bmp", L"cursor");

	m_tFrame.iFrameStart = 0;	//y축!!!!!!!!!!!!
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CMouse::Update()
{
	POINT pt = {};
	// 마우스 받아오기
	GetCursorPos(&pt);
	//스크린 좌표에서 클라 좌표로 변경 
	ScreenToClient(g_hWnd, &pt);

	m_tInfo.fX = float(pt.x) + m_tInfo.fCX * 0.4f;
	m_tInfo.fY = float(pt.y) + m_tInfo.fCY * 0.4f;
	return OBJ_NOEVENT;
}

void CMouse::LateUpdate()
{
	KeyCheck();
}

void CMouse::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"cursor");
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameScene, (int)m_tInfo.fCY * m_tFrame.iFrameStart,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CMouse::Release()
{
}

void CMouse::KeyCheck()
{
	if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON) || CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		FrameMouse();
	else if (CKeyMgr::Get_Instance()->KeyUp(VK_LBUTTON) || CKeyMgr::Get_Instance()->KeyUp(VK_RBUTTON))
		m_tFrame.iFrameStart = 0;
}

void CMouse::FrameMouse()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
}
