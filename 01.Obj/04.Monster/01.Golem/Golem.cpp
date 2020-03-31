#include "stdafx.h"
#include "Golem.h"
#include "Coin.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
CGolem::CGolem()
{
}


CGolem::~CGolem()
{
}

void CGolem::MonsterWalk()
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
		m_pFrameKey = L"Golem_RIGHT";
		m_eCurState = WALK_RIGHT;
	}
	else if (m_tInfo.fX >= m_fLineRX)
	{
		m_fSpeed *= -1.f;
		m_pFrameKey = L"Golem_LEFT";
		m_eCurState = WALK_LEFT;
	}
	// 충돌한 라인의 left x, right x 좌표값을 LineCollision으로 받아올 수 있고 중력값도 먹인다.
	// 충돌한 라인을 계속 몬스터가 타게끔했다.
}

void CGolem::MotionChange()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CObj::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 4;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::WALK_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_iRotate = -1;
			break;
		case CObj::WALK_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_iRotate = 1;
			break;
		case CObj::ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CGolem::Initialize()
{
	m_tInfo.fCX = 228.f;
	m_tInfo.fCY = 228.f;
	m_fSpeed = 1.f;
	m_iHp = 1050;
	m_iMp = 0;
	m_iExp = 45;
	m_iDamage = m_Well512.GetValue(50, 100);

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/Golem/Golem_LEFT.bmp", L"Golem_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/Golem/Golem_RIGHT.bmp", L"Golem_RIGHT");

	m_pFrameKey = L"Golem_LEFT";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iFrameScene = 2;
	m_tFrame.dwFrameSpeed = (DWORD)150.f;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eCurState = WALK_LEFT;
	m_iRotate = -1;
	m_eID = ObjID::MONSTER;
	m_bHit = false;
	m_iGold = m_Well512.GetValue(100, 300);
}

int CGolem::Update()
{
	if (m_bIsDead)
	{
		CObjMgr::Get_Instance()->AddObject(ObjID::GOLD, CAbstractFactory<CCoin>::Create(m_tInfo.fX, m_tInfo.fY, 2, m_iGold));
		CObjMgr::Get_Instance()->Get_Player()->Set_Exp(m_iExp);
		return OBJ_DEAD;
	}
	CObj::UpdateRect();
	MotionChange();
	MonsterWalk();
	CObj* pTarget = CObjMgr::Get_Instance()->Get_Target(ObjID::PLAYER);
	if (m_bHit)
	{
		if (pTarget->Get_PosX() > m_tInfo.fX)
		{
			m_iRotate = 1;
			m_pFrameKey = L"Golem_RIGHT";
			m_tInfo.fX += m_fSpeed;
		}
		else
		{
			m_iRotate = -1;
			m_pFrameKey = L"Golem_LEFT";
			m_tInfo.fX -= m_fSpeed;
		}
	}
	else
	{
		if(m_iRotate == 1)
			m_tInfo.fX += m_fSpeed;
		if(m_iRotate == -1)
			m_tInfo.fX -= m_fSpeed;
	}
		
	return OBJ_NOEVENT;
}

void CGolem::LateUpdate()
{
	CObj::UpdateRect();
	if (m_eCurState == HIT)	// Hit 당했을때.
	{
		m_bHit = true;
		CObj* pTarget = CObjMgr::Get_Instance()->Get_Target(ObjID::PLAYER);
		if (pTarget->Get_PosX() >= m_tInfo.fX)
			m_tInfo.fX -= m_fSpeed * 2.f;
		else
			m_tInfo.fX += m_fSpeed * 2.f;
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
	if (m_bHit)			// Hit때 플레이어 쫓아오기
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
	CObj::UpdateCollisionRect(2.88f, 6.7f, 2.88f, 2.f);
}

void CGolem::Render(HDC hDC)
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

void CGolem::Release()
{
}
