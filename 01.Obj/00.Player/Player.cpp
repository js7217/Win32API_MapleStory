#include "stdafx.h"
#include "Player.h"
#include "Weapon.h"
#include "Effect.h"
#include "BasicArrow.h"
#include "DragonArrow.h"
#include "Meteo.h"
#include "HpBar.h"
#include "MpBar.h"
#include "ExpBar.h"
#include "LevelUI.h"
#include "Status.h"
#include "Inventory.h"
#include "Equipment.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "LineMgr.h"
#include "CollisionMgr.h"

#include "AbstractFactory.h"
CPlayer::CPlayer()
	:m_bIsJump(FALSE)
	,m_bIsLope(FALSE)
	,m_bIsColl(FALSE)
	, m_fJumpAccel(0.f)
	, m_fJumpPower(0.f)
	, m_fLineLX(0.f)
	, m_fLineRX(0.f)
	, m_iIsColl(0)
	, m_iGold(0)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::KeyCheck()
{
	if (CKeyMgr::Get_Instance()->KeyDown('M'))
		m_iMp = m_iMaxMp;
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
	{
		m_iRotate = -1;
		m_tInfo.fX -= m_fSpeed;
		m_pFrameKey = L"Player_LEFT";
		m_eCurState = WALK_LEFT;
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
	{
		m_iRotate = 1;
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_RIGHT";
		m_eCurState = WALK_RIGHT;
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
	{
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_CONTROL))
			m_eCurState = DOWNATT;		// 앉아서 때리기
		else
			m_eCurState = DOWN;
	}
	else
	{
		m_eCurState = IDLE;
	}

	if (CKeyMgr::Get_Instance()->KeyDown(VK_SPACE))
	{
		m_bIsJump = true;
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_CONTROL) && m_eCurState != JUMP)
	{
		m_eCurState = ATTACK;
		CSoundMgr::Get_Instance()->PlayEffect(L"활쏘기.mp3", CSoundMgr::PLAYER_SHOOT);
		if (m_dwOldTime + 600 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER_SHOOT);
			CObjMgr::Get_Instance()->AddObject(ObjID::BULLET, CAbstractFactory<CBasicArrow>::Create(m_tInfo.fX, m_tInfo.fY, m_iRotate));
			m_dwOldTime = GetTickCount();
		}
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_SHIFT))
	{	// 스킬 : 모션은 공격모션을 따라가되 생성과정에서 스킬클래스로 생성하게 한다.
		if (m_iMp <= 10)
			return;
		m_eCurState = ATTACK;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_SHIFT) && m_eCurState != JUMP)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::BULLET, CAbstractFactory<CDragonArrow>::Create(m_tInfo.fX, m_tInfo.fY, m_iRotate));
			m_iMp -= 10;
			CSoundMgr::Get_Instance()->PlayEffect(L"불공올라옴.wav", CSoundMgr::SKILL_TORNADO);
			if(m_iRotate == 1)
				CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::
					Create(m_tInfo.fX + 55.f * m_iRotate, m_tInfo.fY + 5.f, 324, 350, L"DragonEffect_right", 11));
			else
				CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::
					Create(m_tInfo.fX + 55.f * m_iRotate, m_tInfo.fY + 5.f, 324, 350, L"DragonEffect_left", 11));
		}
	}
	if (CKeyMgr::Get_Instance()->KeyDown('A'))
	{ // Effect_Fire
		if (m_iMp <= 30)
			return;
		m_iMp -= 30;
		CSoundMgr::Get_Instance()->PlayEffect(L"Fire.wav", CSoundMgr::SKILL_FIRE);
		CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::
			Create(m_tInfo.fX, (m_tInfo.fY + m_tInfo.fCY * 0.8f) - 252, 659, 454, L"Effect_Fire", 16));
		CObjMgr::Get_Instance()->AddObject(ObjID::BULLET, CAbstractFactory<CMeteo>::Create(m_tInfo.fX, m_tInfo.fY));

	}
}

void CPlayer::LopeKeyCheck()
{
	float fY = 0;
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_tFrame.iFrameEnd = 1;
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_tFrame.iFrameEnd = 1;
	}
	else
	{
		m_eCurState = LOPE;
		m_tFrame.iFrameEnd = 0;
	}
	if (CKeyMgr::Get_Instance()->KeyDown(VK_SPACE))
	{
		m_bIsJump = true;
		m_bIsLope = false;
	}
}


void CPlayer::IsJumping()
{
	float fY = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fY, &m_fLineLX, &m_fLineRX);
		//v * sin@ * t -g * t* t *0.5f
	m_tInfo.fY -= m_fJumpPower * m_fJumpAccel - 9.8f * m_fJumpAccel * m_fJumpAccel * 0.5f;//중력먹이기.
	m_fJumpAccel += 0.1f;
	if (m_bIsJump)
	{
		m_eCurState = JUMP;
		m_fJumpPower = 11.f;
		if (bIsColl && m_tInfo.fY > fY)
		{
			m_bIsJump = false;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER_JUMP);
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

void CPlayer::LopeJumping()
{
	float fY = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fY, &m_fLineLX, &m_fLineRX);
	//v * sin@ * t -g * t* t *0.5f
	m_tInfo.fY -= m_fJumpPower * m_fJumpAccel - 9.8f * m_fJumpAccel * m_fJumpAccel * 0.5f;//중력먹이기.
	m_fJumpAccel += 0.1f;
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER_JUMP);
	if (m_bIsLope)
		m_fJumpAccel = 0.f;
	if (m_bIsJump)
	{
		m_eCurState = LOPE;
		m_fJumpPower = 11.f;
		if (m_tInfo.fY + m_tInfo.fCY * 0.5f > fY)
		{
			m_bIsJump = false;
			m_fJumpAccel = 0.f;
			m_bIsLope = false;
			m_tInfo.fY = fY - m_tInfo.fCY *0.3f;
			if (m_iRotate == 1)
				m_pFrameKey = L"Player_RIGHT";
			else if(m_iRotate == -1)
				m_pFrameKey = L"Player_LEFT";
		}
	}
	else // 점프 안하고 로프탈때.
	{
		m_eCurState = LOPE;
		m_fJumpPower = 0.0f;
		if (bIsColl && m_tInfo.fY + m_tInfo.fCY * 0.3f > fY)
		{
			if (CKeyMgr::Get_Instance()->KeyDown(VK_UP))
			{
				m_fJumpAccel = 0.f;
				m_bIsLope = false;
				m_tInfo.fY = fY - m_tInfo.fCY *0.3f;
				if (m_iRotate == 1)
					m_pFrameKey = L"Player_RIGHT";
				else if (m_iRotate == -1)
					m_pFrameKey = L"Player_LEFT";
			}
			else if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
			{
				cout << "내려가라" << endl;
				m_fJumpAccel = 0.f;
			}
			else
			{
				if (m_iRotate == 1)
					m_pFrameKey = L"Player_RIGHT";
				else if (m_iRotate == -1)
					m_pFrameKey = L"Player_LEFT";
				m_bIsLope = false;
			}
		}
	}
}

void CPlayer::IsOffSet()
{
	int iOffSet = int(WINCX * 0.5f);
	int iOffSetY = int(WINCY * 0.45f);
	int iScrollX = int(CScrollMgr::Get_ScrollX());
	int iScrollY = int(CScrollMgr::Get_ScrollY());

	if (iOffSet + 200 < int(m_tInfo.fX + iScrollX))
	{
		CScrollMgr::Set_ScrollX(-m_fSpeed);
	}
	if (iOffSet - 200 > int(m_tInfo.fX + iScrollX))
	{
		CScrollMgr::Set_ScrollX(m_fSpeed);
	}

	if (iOffSetY + 200  < int(m_tInfo.fY + iScrollY))
	{
		CScrollMgr::Set_ScrollY(-m_fSpeed);
	}
	if (iOffSetY - 200 > int(m_tInfo.fY + iScrollY))
	{
		CScrollMgr::Set_ScrollY(m_fSpeed);
	}
}

void CPlayer::MotionChange()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CPlayer::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::WALK_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::WALK_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::ATTACK:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 6;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 6;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			CSoundMgr::Get_Instance()->PlayEffect(L"점프.mp3", CSoundMgr::PLAYER_JUMP);
			break;
		case CPlayer::DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 5;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::DOWNATT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 4;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::LOPE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 500;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 7;
			m_tFrame.dwFrameSpeed = 1000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 19;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			//나중에 해보기.
			break;
		default:
			break;
		}
		m_iFrameStart = m_tFrame.iFrameStart;
		m_ePreState = m_eCurState;
	}
}

void CPlayer::PlayerLock(float fX)
{
	if (m_tRect.left < 0)
	{
		m_tInfo.fX = m_tInfo.fCX * 0.5f;
		m_pFrameKey = L"Player_LEFT";
		m_eCurState = WALK_LEFT;
	}
	else if (m_tRect.right > fX)
	{
		m_tInfo.fX = fX - m_tInfo.fCX * 0.5f;
		m_pFrameKey = L"Player_RIGHT";
		m_eCurState = WALK_RIGHT;
	}
}

void CPlayer::LevelUp()
{
	//301 362
	if (m_iMaxExp <= m_iExp)
	{
		CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::
			Create(m_tInfo.fX, (float)m_tRect.top - m_tInfo.fCY * 1.5f, 301, 362, L"LevelUp", 20));
		m_iMaxExp += m_iMaxExp;
		m_iExp = 0;
		m_iAtt += 20;
		m_iLv++;
		m_iMaxHp += 282;
		m_iHp = m_iMaxHp;
		m_iMaxMp += 141;
		m_iMp = m_iMaxMp;
	}
	else
		return;
}

void CPlayer::Initialize()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_tInfo.fX = 50.f;
	m_tInfo.fY = 500.f;
	m_fSpeed = 3.f;
	m_iFrameStart = 0;
	m_iHp = 1410;
	m_iMp = 282;
	m_iAtt = 50;
	m_iExp = 0;
	m_iLv = 1;
	m_iMaxExp = 100;
	m_iMaxHp = m_iHp;
	m_iMaxMp = m_iMp;
	m_eID = ObjID::PLAYER;
	m_bIsCollision = false;
	m_iGold = 2000;
	m_bIsDead = false;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Player/Player_LEFT.bmp", L"Player_LEFT"); // 캐릭터 초기화.
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Player/Player_LOPE.bmp", L"Player_LOPE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Player/Tomb.bmp", L"Tomb");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/LevelUp.bmp", L"LevelUp");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Skill/Fire/Effect/Effect.bmp", L"Effect_Fire");

	CObjMgr::Get_Instance()->AddObject(ObjID::MAINUI, CAbstractFactory<CHpBar>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::MAINUI, CAbstractFactory<CMpBar>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::MAINUI, CAbstractFactory<CExpBar>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::MAINUI, CAbstractFactory<CLevelUI>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::MAINUI, CAbstractFactory<CStatus>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::INVENTORY, CAbstractFactory<CInventory>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::EQUIPMENT, CAbstractFactory<CEquipment>::Create());
	m_pFrameKey = L"Player_RIGHT";

	m_eCurState = STATE::IDLE;

	m_tFrame.iFrameStart = 0;		//x축 시작
	m_tFrame.iFrameEnd = 4;			//x축 끝	->끝을 알아야 시작으로 되돌릴 수 있다.
	m_tFrame.iFrameScene = 0;		//y축 시작
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwOldTime = GetTickCount();
}

int CPlayer::Update()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect(4.f, 2.85f, 4.f, 2.85f);
	cout << m_tInfo.fX << ", " << m_tInfo.fY << endl;
	if (!m_bIsLope)
	{
		KeyCheck();
		IsJumping();
	}
	else
	{
		LopeKeyCheck();
		LopeJumping();
	}
	if (m_iHp > m_iMaxHp)
		m_iHp = m_iMaxHp;			//옷 장착시 체력이 오르는데 옷 탈의시 값 오류 방지.
	IsOffSet();
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{
	CObj::UpdateRect();
	MotionChange();
	if (m_eCurState == HIT)
	{
		if (m_iRotate == -1)
			m_tInfo.fX += m_fSpeed * 2.f;
		else
			m_tInfo.fX -= m_fSpeed * 2.f;
		m_tInfo.fY -= m_fSpeed * 1.5f;
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			if (m_iRotate == -1)
				m_eCurState = WALK_LEFT;
			else
				m_eCurState = WALK_RIGHT;
		}
	}
	else
		CObj::FrameMove(m_iFrameStart);
	LevelUp();
}

void CPlayer::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	if (m_bIsCollision) //무적이면 true 아니면 false로 깜빡거리게 만들어버리기
	{
		m_bIsColl = !m_bIsColl;
		m_iIsColl++;
		if (3 <= m_iIsColl)
		{
			GdiTransparentBlt(hDC,
				(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
				(int)m_tInfo.fCX, (int)m_tInfo.fCY,
				hMemDC,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iFrameScene,
				(int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(0, 255, 0));
			m_iIsColl = 0;
		}
	}
	else
	{
		GdiTransparentBlt(hDC,
			(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,
			hMemDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iFrameScene,
			(int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(0, 255, 0));

	}
}

void CPlayer::Release()
{
}
