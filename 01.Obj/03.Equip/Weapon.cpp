#include "stdafx.h"
#include "Weapon.h"

#include "ObjMgr.h"
CWeapon::CWeapon()
{
}


CWeapon::~CWeapon()
{
}

void CWeapon::Initialize()
{
	m_tInfo.fCX = 24.f;
	m_tInfo.fCY = 12.f;
	m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_PosX();
	m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_PosY();
	m_eCurState = CObjMgr::Get_Instance()->Get_Player()->Get_State();
	m_iRotate = CObjMgr::Get_Instance()->Get_Player()->Get_Rotate();
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Weapon/LEFT/Stand0.bmp", L"Stand_left");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Weapon/LEFT/Shoot_left.bmp", L"Shoot_left");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Weapon/RIGHT/Stand0.bmp", L"Stand_right");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Weapon/RIGHT/Shoot_right.bmp", L"Shoot_right");

	m_eCurState = WALK_RIGHT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_pFrameKey = L"Stand0";
}

int CWeapon::Update()
{
	CObj::UpdateRect();
	m_iRotate = CObjMgr::Get_Instance()->Get_Player()->Get_Rotate();
	m_eCurState = CObjMgr::Get_Instance()->Get_Player()->Get_State();
	MotionChange();
	return 0;
}

void CWeapon::LateUpdate()
{
	CObj::UpdateRect();
	CObj::FrameMove(0);
}

void CWeapon::Render(HDC hDC)
{
	UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		int(m_tRect.left + iScrollX), int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX), int(m_tInfo.fCY),
		hMemDC,
		(int)(m_tInfo.fCX * m_tFrame.iFrameStart), (int)(m_tInfo.fCY * m_tFrame.iFrameScene),
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(0, 255, 0));
}

void CWeapon::Release()
{
}

void CWeapon::MotionChange()
{
		switch (m_eCurState)
		{
		case CObj::IDLE:
			m_tInfo.fCX = 24.f;
			m_tInfo.fCY = 12.f;
			if (m_iRotate == -1 || m_ePreState == ATTACK)
			{
				m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_PosX() + 5.f;
				m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_PosY() + 25.f;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iFrameScene = 0;
				m_tFrame.dwFrameSpeed = 200;
				m_tFrame.dwFrameTime = GetTickCount();
				m_pFrameKey = L"Stand_left";
			}
			else if (m_iRotate == 1 || m_ePreState == ATTACK)
			{
				m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_PosX() - 5.f;
				m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_PosY() + 25.f;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iFrameScene = 0;
				m_tFrame.dwFrameSpeed = 200;
				m_tFrame.dwFrameTime = GetTickCount();
				m_pFrameKey = L"Stand_right";
			}
			break;
		case CObj::WALK_LEFT:
			m_tInfo.fCX = 24.f;
			m_tInfo.fCY = 12.f;
			m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_PosX() + 5.f;
			m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_PosY() + 25.f;
			if (m_eCurState != m_ePreState)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iFrameScene = 0;
				m_tFrame.dwFrameSpeed = 200;
				m_tFrame.dwFrameTime = GetTickCount();
				m_pFrameKey = L"Stand_left";
			}
			break;
		case CObj::WALK_RIGHT:
			m_tInfo.fCX = 24.f;
			m_tInfo.fCY = 12.f;
			m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_PosX() - 5.f;
			m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_PosY() + 25.f;
			if (m_eCurState != m_ePreState)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iFrameScene = 0;
				m_tFrame.dwFrameSpeed = 200;
				m_tFrame.dwFrameTime = GetTickCount();
				m_pFrameKey = L"Stand_right";
			}
			break;
		case CObj::ATTACK:
			m_tInfo.fCX = 63.f;
			m_tInfo.fCY = 133.f;
			if (m_iRotate == -1)
			{
				m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_PosX() - 35.f;
				m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_PosY() + 15.f;
				if (m_eCurState != m_ePreState)
				{
					m_tFrame.iFrameStart = 0;
					m_tFrame.iFrameEnd = 2;
					m_tFrame.iFrameScene = 0;
					m_tFrame.dwFrameSpeed = 200;
					m_tFrame.dwFrameTime = GetTickCount();
					m_pFrameKey = L"Shoot_left";
				}
			}
			else if (m_iRotate == 1)
			{
				m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_PosX() + 35.f;
				m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_PosY() + 15.f;
				if (m_eCurState != m_ePreState)
				{
					m_tFrame.iFrameStart = 0;
					m_tFrame.iFrameEnd = 2;
					m_tFrame.iFrameScene = 0;
					m_tFrame.dwFrameSpeed = 200;
					m_tFrame.dwFrameTime = GetTickCount();
					m_pFrameKey = L"Shoot_right";
				}
			}
			break;
		case CObj::JUMP:					//지표로 나타낼 수 있는 기준을 따로 만들어보는것도 방법일듯 함.
			m_tInfo.fCX = 24.f;
			m_tInfo.fCY = 12.f;
			if (m_iRotate == -1)
			{
				m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_PosX() + 5.f;
				m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_PosY() + 5.f;
				m_pFrameKey = L"Shoot_left";
			}
			else if (m_iRotate == 1)
			{
				m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_PosX() - 5.f;
				m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_PosY() + 5.f;
				m_pFrameKey = L"Shoot_right";
			}
			m_pFrameKey = L"Stand_right";
			break;
		case CObj::LOPE:
			m_tInfo.fCX = 24.f;
			m_tInfo.fCY = 12.f;
			m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_PosX() + 5.f;
			m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_PosY() + 25.f;
			break;
		case CObj::DOWN:
			break;
		case CObj::DOWNATT:
			break;
		case CObj::HIT:
			break;
		case CObj::DEAD:
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
}
