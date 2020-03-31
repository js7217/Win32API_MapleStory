#include "stdafx.h"
#include "Tile.h"


CTile::CTile()
	:m_iDrawID(0)
	,m_iOption(0)
{
}

CTile::CTile(float fX, float fY)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Tile.bmp", L"Tile");
}

int CTile::Update()
{
	CObj::LateInitialize();
	return 0;
}

void CTile::LateUpdate()
{
}

void CTile::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Tile");
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();

	BitBlt(hDC, (int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, (int)m_iDrawID * (int)m_tInfo.fCX, (int)0, SRCCOPY);
}

void CTile::Release()
{
}
