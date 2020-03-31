#include "stdafx.h"
#include "Coin.h"
#include "Player.h"
#include "LineMgr.h"
#include "ObjMgr.h"
CCoin::CCoin()
{
}

CCoin::CCoin(float fX, float fY, int iFrameScene, int iGold)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Item/coin.bmp", L"coin");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = iFrameScene;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_pFrameKey = L"coin";
	m_iGold = iGold;
	m_bIsCollision = false;
}


CCoin::~CCoin()
{
	Release();
}

void CCoin::IsJumping()
{
	float fY = 0.f;
	float m_fLineLX = 0.f;
	float m_fLineRX = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fY, &m_fLineLX, &m_fLineRX);
	//v * sin@ * t -g * t* t *0.5f
	m_tInfo.fY -= m_fJumpPower * m_fJumpAccel - 4.9f * m_fJumpAccel * m_fJumpAccel * 0.5f;//중력먹이기.
	m_fJumpAccel += 0.1f;
	if (m_bIsJump)
	{
		m_eCurState = JUMP;
		m_fJumpPower = 5.f;
		if (bIsColl && m_tInfo.fY > fY)
		{
			m_bIsJump = false;
			m_fJumpAccel = 0.f;
			m_tInfo.fY = fY - m_tInfo.fCY *0.3f;
		}
	}
	else
	{
		m_fJumpPower = 0.0f;
		if (bIsColl && m_tInfo.fY + m_tInfo.fCY * 0.3f > fY)
		{
			m_fJumpAccel = 0.f;
			m_tInfo.fY = fY - m_tInfo.fCY *0.3f;
		}
	}
}

void CCoin::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = 2.5f;
	m_bIsJump = true;
	m_bIsMotion = false;
	m_eID = ObjID::GOLD;
	m_dwOldTime = GetTickCount();
}

int CCoin::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	if (m_bIsMotion)
	{
		CObj* pTarget = CObjMgr::Get_Instance()->Get_Player();
		float m_fAngle = CMathMgr::CalcRadian(pTarget, this);
		m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle) * m_fSpeed;
		if (m_dwOldTime + 1000 < GetTickCount())
		{
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Gold(-m_iGold); // 한번만 골드 올라가기 위해서 여따 넣음.
			m_bIsDead = true;
		}
	}
	else
	{
		m_dwOldTime = GetTickCount();
		IsJumping();
	}
	return OBJ_NOEVENT;
}

void CCoin::LateUpdate()
{
	CObj::UpdateCollisionRect(2.f, 2.f, 2.f, 2.f);
	if (m_bIsCollision)
	{
		if (CKeyMgr::Get_Instance()->KeyDown('Z'))
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM_GET);
			m_bIsMotion = true;
			CSoundMgr::Get_Instance()->PlayEffect(L"템습득.mp3", CSoundMgr::ITEM_GET);
		}
	}
	CObj::FrameMove(0);
}

void CCoin::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(0, 255, 0));
}

void CCoin::Release()
{
}
