#include "stdafx.h"
#include "Slime.h"

#include "Coin.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CSlime::CSlime()
{
}


CSlime::~CSlime()
{
}

void CSlime::MonsterWalk()
{
	float fY = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fY, &m_fLineLX, &m_fLineRX);
	//v * sin@ * t -g * t* t *0.5f
	m_tInfo.fY -= - 9.8f * m_fJumpAccel * m_fJumpAccel * 0.5f;//중력먹이기.
	m_fJumpAccel += 0.1f;
	if (bIsColl && m_tInfo.fY + m_tInfo.fCY * 0.5f > fY)
	{
		m_fJumpAccel = 0.f;
		m_tInfo.fY = fY - m_tInfo.fCY *0.5f;
	}
	// 충돌한 라인의 left x, right x 좌표값을 LineCollision으로 받아올 수 있고 중력값도 먹인다.
	// 충돌한 라인을 계속 몬스터가 타게끔했다.
}

void CSlime::MotionChange()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CObj::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::WALK_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_iRotate = -1;
			break;
		case CObj::WALK_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_iRotate = 1;
			break;
		case CObj::JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 4;
			m_tFrame.dwFrameSpeed = 400;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CSlime::Initialize()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_fSpeed = 2.f;
	m_iHp = 250;
	m_iMp = 0;
	m_iExp = 20;
	m_iDamage = m_Well512.GetValue(20, 40);
	m_iGold = m_Well512.GetValue(50, 100);
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/Slime/Slime_LEFT.bmp", L"Slime_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/Slime/Slime_RIGHT.bmp", L"Slime_RIGHT");

	m_pFrameKey = L"Slime_RIGHT";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = (DWORD)200.f;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eCurState = WALK_RIGHT;
	m_iRotate = 1;
	m_eID = ObjID::MONSTER;
}

int CSlime::Update()
{
	if (m_bIsDead)
	{
		CObjMgr::Get_Instance()->AddObject(ObjID::GOLD, CAbstractFactory<CCoin>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_iGold));
		CObjMgr::Get_Instance()->Get_Player()->Set_Exp(m_iExp);
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER_DEAD);
		return OBJ_DEAD;
	}
	CObj::UpdateRect();
	MotionChange();
	MonsterWalk();
	m_tInfo.fX += m_fSpeed;
	return OBJ_NOEVENT;
}

void CSlime::LateUpdate()
{
	CObj::UpdateRect();
	if (m_eCurState == HIT)
	{
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
			m_eCurState = WALK_LEFT;
	}
	if (m_eCurState == DEAD)
	{
		m_fSpeed = 0.f;			//제자리에서 죽기.
		CSoundMgr::Get_Instance()->PlayEffect(L"슬라임죽음.mp3", CSoundMgr::MONSTER_DEAD);
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			m_bIsDead = true;
		}
	}

	if (m_tInfo.fX <= m_fLineLX)
	{
		m_fSpeed *= -1.f;
		m_pFrameKey = L"Slime_RIGHT";
		m_eCurState = WALK_RIGHT;
	}
	else if (m_tInfo.fX >= m_fLineRX)
	{
		m_fSpeed *= -1.f;
		m_pFrameKey = L"Slime_LEFT";
		m_eCurState = WALK_LEFT;
	}
	CObj::FrameMove(0);
	CObj::UpdateCollisionRect(3.33f, 8.f, 3.33f, 2.f);
}

void CSlime::Render(HDC hDC)
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
		RGB(0, 255, 0));
}

void CSlime::Release()
{
}
