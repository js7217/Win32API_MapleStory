#include "stdafx.h"
#include "JBalok.h"
#include "Coin.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
CJBalok::CJBalok()
{
}


CJBalok::~CJBalok()
{
}

void CJBalok::MonsterWalk()
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
		m_pFrameKey = L"JBalokRight";
		m_eCurState = WALK_RIGHT;
	}
	else if (m_tInfo.fX >= m_fLineRX)
	{
		m_fSpeed *= -1.f;
		m_pFrameKey = L"JBalokLeft";
		m_eCurState = WALK_LEFT;
	}
}

void CJBalok::MotionChange()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CObj::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::WALK_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_iRotate = -1;
			break;
		case CObj::WALK_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_iRotate = 1;
			break;
		case CObj::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CJBalok::Initialize()
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;
	m_fSpeed = 1.f;
	m_iHp = 2000;
	m_iMp = 0;
	m_iExp = 90;
	m_iDamage = m_Well512.GetValue(50, 100);

	m_pFrameKey = L"JBalokLeft";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 1;
	m_tFrame.dwFrameSpeed = (DWORD)150.f;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eCurState = WALK_LEFT;
	m_iRotate = -1;
	m_eID = ObjID::MONSTER;
	m_bHit = false;
	m_iGold = m_Well512.GetValue(500, 700);
}

int CJBalok::Update()
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
	CObj* pTarget = CObjMgr::Get_Instance()->Get_Target(ObjID::PLAYER);

	if (pTarget->Get_PosX() > m_tInfo.fX)
	{
		m_iRotate = 1;
		m_pFrameKey = L"JBalokRight";
		m_tInfo.fX += m_fSpeed;
	}
	else
	{
		m_iRotate = -1;
		m_pFrameKey = L"JBalokLeft";
		m_tInfo.fX -= m_fSpeed;
	}

	return OBJ_NOEVENT;
}

void CJBalok::LateUpdate()
{
	CObj::UpdateRect();
	if (m_eCurState == HIT)	// Hit 당했을때.
	{
		m_bHit = true;
		CObj* pTarget = CObjMgr::Get_Instance()->Get_Target(ObjID::PLAYER);
		if (pTarget->Get_PosX() >= m_tInfo.fX)
			m_tInfo.fX -= m_fSpeed * 1.5f;
		else
			m_tInfo.fX += m_fSpeed * 1.5f;
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			if (pTarget->Get_PosX() >= m_tInfo.fX)
				m_eCurState = WALK_LEFT;
			else
				m_eCurState = WALK_RIGHT;
		}
	}
	if (m_eCurState == DEAD)	//죽은 상태일때만 이걸 수행.
	{
		m_fSpeed = 0.f;			//제자리에서 죽기.
		m_bHit = false;
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
			m_bIsDead = true;	// frameMove
	}
	if (m_bHit)			// Hit때 플레이어 쫓아오기(라인 끝에서 제자리 걸음)
	{
		if (m_tRect.left < m_fLineLX)
		{
			m_tInfo.fX = m_fLineLX + m_tInfo.fCX * 0.5f;

		}
		else if (m_tRect.right > m_fLineRX)
		{
			m_tInfo.fX = m_fLineRX - m_tInfo.fCX * 0.5f;
		}
	}
	CObj::FrameMove(0);
	CObj::UpdateCollisionRect(2.f, 2.5f, 2.f, 2.f);
}

void CJBalok::Render(HDC hDC)
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

void CJBalok::Release()
{
}
