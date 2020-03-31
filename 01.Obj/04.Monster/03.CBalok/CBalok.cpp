#include "stdafx.h"
#include "CBalok.h"
#include "Coin.h"
#include "ObjMgr.h"
#include "LineMgr.h"

#include "AbstractFactory.h"
CCBalok::CCBalok()
{
}


CCBalok::~CCBalok()
{
}

void CCBalok::MonsterWalk()
{
	float fY = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fY, &m_fLineLX, &m_fLineRX);
	//v * sin@ * t -g * t* t *0.5f
	m_tInfo.fY -= -9.8f * m_fJumpAccel * m_fJumpAccel * 0.5f;//중력먹이기.
	m_fJumpAccel += 0.1f;
	if (bIsColl && m_tInfo.fY + m_tInfo.fCY * 0.5f > fY)
	{
		m_fJumpAccel = 0.f;
		m_tInfo.fY = fY - m_tInfo.fCY *0.5f;
	}
	if (m_tInfo.fX <= m_fLineLX)
	{
		m_fSpeed *= -1.f;
		m_pFrameKey = L"CBalokRight";
		m_eCurState = WALK_RIGHT;
	}
	else if (m_tInfo.fX >= m_fLineRX)
	{
		m_fSpeed *= -1.f;
		m_pFrameKey = L"CBalokLeft";
		m_eCurState = WALK_LEFT;
	}
}

void CCBalok::MotionChange()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CObj::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::WALK_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_iRotate = -1;
			break;
		case CObj::WALK_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_iRotate = 1;
			break;
		case CObj::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 4;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CCBalok::Initialize()
{
	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 400.f;
	m_fSpeed = 1.f;
	m_iHp = 3000;
	m_iMp = 0;
	m_iExp = 150;
	m_iDamage = m_Well512.GetValue(50, 100);

	m_pFrameKey = L"CBalokLeft";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 1;
	m_tFrame.dwFrameSpeed = (DWORD)150.f;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eCurState = WALK_LEFT;
	m_iRotate = -1;
	m_eID = ObjID::MONSTER;
	m_bHit = false;
	m_iGold = m_Well512.GetValue(700, 900);
}

int CCBalok::Update()
{
	if (m_bIsDead)
	{
		CObjMgr::Get_Instance()->AddObject(ObjID::GOLD, CAbstractFactory<CCoin>::Create(m_tInfo.fX, m_tInfo.fY, 3, m_iGold));
		CObjMgr::Get_Instance()->Get_Player()->Set_Exp(m_iExp);
		return OBJ_DEAD;
	}
	CObj::UpdateRect();
	MotionChange();
	MonsterWalk();
	m_tInfo.fX -= m_fSpeed;
	return OBJ_NOEVENT;
}

void CCBalok::LateUpdate()
{
	CObj::UpdateRect();
	if (m_eCurState == HIT)
	{
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			if (m_iRotate == 1)
				m_eCurState = WALK_RIGHT;
			else if (m_iRotate == -1)
				m_eCurState = WALK_LEFT;
		}
	}
	if (m_eCurState == DEAD)
	{
		m_fSpeed = 0.f;			//제자리에서 죽기.
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
			m_bIsDead = true;	// frameMove
	}
	CObj::FrameMove(0);
	CObj::UpdateCollisionRect(4.f, 4.f, 4.f, 2.f);
}

void CCBalok::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CCBalok::Release()
{
}
