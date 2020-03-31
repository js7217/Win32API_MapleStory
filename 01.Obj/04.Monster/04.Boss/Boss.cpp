#include "stdafx.h"
#include "Boss.h"
#include "BossHpBar.h"
#include "Tile.h"
#include "Effect.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "Portal.h"
#include "AbstractFactory.h"
CBoss::CBoss()
{
}


CBoss::~CBoss()
{

}

void CBoss::MonsterWalk()
{
	float fY = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fY, &m_fLineLX, &m_fLineRX);
	//v * sin@ * t -g * t* t *0.5f
	m_tInfo.fY -= -9.8f * m_fJumpAccel * m_fJumpAccel * 0.5f;//중력먹이기.
	m_fJumpAccel += 0.1f;
	if (bIsColl && m_tInfo.fY + m_tInfo.fCY * 0.275f > fY)
	{
		m_fJumpAccel = 0.f;
		m_tInfo.fY = fY - m_tInfo.fCY *0.275f;
	}
	// 충돌한 라인의 left x, right x 좌표값을 LineCollision으로 받아올 수 있고 중력값도 먹인다.
	// 충돌한 라인을 계속 몬스터가 타게끔했다.
}

void CBoss::MotionChange()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CBoss::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 26;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = (DWORD)200.f;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CBoss::LIGHTNING:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 21;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = (DWORD)200.f;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CBoss::EXPLOSION:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 23;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = (DWORD)200.f;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CBoss::ICE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 22;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = (DWORD)200.f;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CBoss::Initialize()
{
	m_tInfo.fCX = 1000.f;
	m_tInfo.fCY = 1000.f;
	m_fSpeed = 0.5f;
	m_iMaxHp = 59700;
	m_iHp = m_iMaxHp;
	m_iMp = 0;
	m_iAtt = 120;
	m_pFrameKey = L"Boss";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 26;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = (DWORD)200.f;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eID = ObjID::BOSS;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/Boss/Boom.bmp", L"Boom");
	m_dwOldTime = GetTickCount();
	m_dwTime = GetTickCount();
}

int CBoss::Update()
{
	if (m_bIsDead)
	{
		for (auto& iter : CObjMgr::Get_Instance()->Get_List(ObjID::MONSTER))
		{
			iter->Set_Dead();
		}
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
		CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CPortal>::Create(m_tInfo.fX + 10.f, m_tInfo.fY + m_tInfo.fCY * 0.15f));
		CSoundMgr::Get_Instance()->PlayEffect(L"Clear.wav", CSoundMgr::EFFECT);
		return OBJ_DEAD;
	}
	if (CObj::m_eCurState != CObj::STATE::DEAD)
	{
		CObj::UpdateRect();
		MotionChange();
		return OBJ_NOEVENT;
	}
	return OBJ_NOEVENT;
}

void CBoss::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect(4.f, 2.f, 4.f, 2.f);
	if (CObj::m_eCurState == CObj::STATE::DEAD)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
		if (m_dwTime + 10000 > GetTickCount())
		{
			float fX = m_Well512.GetFloatValue(m_tInfo.fX - 200.f, m_tInfo.fX + 200.f);
			float fY = m_Well512.GetFloatValue(m_tInfo.fY - 200.f, m_tInfo.fY + 200.f);
			if (m_dwOldTime + 50 < GetTickCount())
			{
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
				CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::
					Create(fX, fY, 150, 196, L"Boom", 5));
				CSoundMgr::Get_Instance()->PlayEffect(L"폭파_큰화염.wav", CSoundMgr::EFFECT);
				m_dwOldTime = GetTickCount();
			}
		}
		else
			m_bIsDead = true;
	}
	else if (m_eCurState != BossState::IDLE)
	{
		m_dwTime = GetTickCount();
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}

		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
			m_eCurState = BossState::IDLE;
	}
	else
		CObj::FrameMove(0);
}

void CBoss::Render(HDC hDC)
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
		RGB(0, 0, 255));
}

void CBoss::Release()
{
}
