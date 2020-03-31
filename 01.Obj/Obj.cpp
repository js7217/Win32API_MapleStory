#include "stdafx.h"
#include "Obj.h"
#include "Slime.h"
#include "Golem.h"
#include "EffectDamage.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CObj::CObj()
	:m_bInit(FALSE)
	, m_bIsDead(FALSE)
	, m_bIsCollision(FALSE)
	,m_fSpeed(0.f)
	,m_iFrameStart(0)
	,m_pFrameKey(nullptr)
	,m_eCurState(STATE::IDLE)
	,m_ePreState(STATE::IDLE)
	,m_iRotate(1)
	,m_iHp(0)
	,m_iMp(0)
	,m_iAtt(0)
	,m_iHit(0)
	,m_iExp(0)
	,m_iLv(0)
	,m_iMaxExp(0)
	,m_iMaxHp(0)
	,m_iMaxMp(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/DamageEffect.bmp", L"DamageEffect");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/DamageEffect_Player.bmp", L"DamageEffect_Player");
}


CObj::~CObj()
{
}
void CObj::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}

void CObj::UpdateCollisionRect(float fleft, float fup, float fright, float fbottom)
{
	m_tCollisionRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / fleft));
	m_tCollisionRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / fup));
	m_tCollisionRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / fright));
	m_tCollisionRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / fbottom));
}

void CObj::FrameMove(int start)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = start;
}

void CObj::DamageUI(int iHit, float fX, float fY)
{
	int iThousand = (int)(iHit * 0.001f);
	int ihundred = (int)(iHit % 1000 * 0.01f); // 100 / 100 
	int iTen = (int)(iHit % 100 * 0.1f); // 100 / 10 
	int iOne = iHit % 10;	// 1의 자리
	if (this->Get_ID() == ObjID::PLAYER) // 플레이어 데미지 히트
	{
		if (iHit >= 1000)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX + 48.f, (float)fY + 5.f, 149, 69, L"DamageEffect_Player", iOne));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX + 24.f, (float)fY, 149, 69, L"DamageEffect_Player", iTen));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX - 24.f, (float)fY + 2.5f, 149, 69, L"DamageEffect_Player", ihundred));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX - 48.f, (float)fY + 2.5f, 149, 69, L"DamageEffect_Player", iThousand));
		}
		else if (iHit < 1000 && iHit >= 100)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX + 24.f, (float)fY + 5.f, 149, 69, L"DamageEffect_Player", iOne));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX, (float)fY, 149, 69, L"DamageEffect_Player", iTen));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX - 24.f, (float)fY + 2.5f, 149, 69, L"DamageEffect_Player", ihundred));
		}
		else if (iHit < 100 && iHit >= 10)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX + 12.f, (float)fY + 2.5f, 149, 69, L"DamageEffect_Player", iOne));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX - 12.f, (float)fY, 149, 69, L"DamageEffect_Player", iTen));
		}
		else if (iHit < 10)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX, (float)fY, 149, 69, L"DamageEffect_Player", iOne));
		}
		else
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX, (float)fY, 149, 69, L"DamageEffect_Player", 10));
	}
	else if (this->Get_ID() == ObjID::MONSTER || this->Get_ID() == ObjID::BOSS) // 플레이어 데미지 히트
	{
		if (iHit >= 1000)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX + 36.f, (float)fY + 5.f, 149, 69, L"DamageEffect", iOne));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX + 12.f, (float)fY, 149, 69, L"DamageEffect", iTen));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX - 12.f, (float)fY + 2.5f, 149, 69, L"DamageEffect", ihundred));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX - 36.f, (float)fY + 2.5f, 149, 69, L"DamageEffect", iThousand));
		}
		else if (iHit < 1000 && iHit >= 100)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX + 24.f, (float)fY + 5.f, 149, 69, L"DamageEffect", iOne));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX, (float)fY, 149, 69, L"DamageEffect", iTen));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX - 24.f, (float)fY + 2.5f, 149, 69, L"DamageEffect", ihundred));
		}
		else if (iHit < 100 && iHit >= 10)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX + 12.f, (float)fY + 2.5f, 149, 69, L"DamageEffect", iOne));
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX - 12.f, (float)fY, 149, 69, L"DamageEffect", iTen));
		}
		else if (iHit < 10)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX, (float)fY, 149, 69, L"DamageEffect", iOne));
		}
		else
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT_DAMAGE, CAbstractFactory<CEffectDamage>::
				Create(fX + 24.f, (float)fY, 149, 69, L"DamageEffect", 10));
	}
}

void CObj::LateInitialize()
{
	if (!m_bInit)
	{
		this->LateInitialize();
		m_bInit = true;
	}
}
