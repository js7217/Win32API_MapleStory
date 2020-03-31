#include "stdafx.h"
#include "BasicArrow.h"

#include "ObjMgr.h"
#include "Effect.h"
#include "AbstractFactory.h"
CBasicArrow::CBasicArrow()
{
}

CBasicArrow::CBasicArrow(float fX, float fY, int Rotate)
{
	m_tInfo.fX = fX + 50.f * Rotate;
	m_tInfo.fY = fY + 10.f;
	m_iRotate = Rotate;
	m_eID = ObjID::PLAYER;
}


CBasicArrow::~CBasicArrow()
{
	Release();
}

void CBasicArrow::Initialize()
{
	m_tInfo.fCX = 86.f;
	m_tInfo.fCY = 23.f;
	m_fSpeed = 20.f;
	m_iDamage = m_Well512.GetValue(130, 200) + m_iAtt;
	m_pFrameKey = L"Arrow_right";
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Weapon/LEFT/Arrow.bmp", L"Arrow_left");	// Maple_Resource\Skill\Dragon\Arrow
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Weapon/RIGHT/ArrowR.bmp", L"Arrow_right");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Weapon/ATTACK/Hiteffect.bmp", L"Hiteffect");
}

int CBasicArrow::Update()
{
	if (m_bIsDead)
	{
		HitSound();
		if(m_iRotate == 1)
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::Create((float)m_tRect.right, m_tInfo.fY, 155.f, 98.f, L"Hiteffect", 4));
		if(m_iRotate == -1)
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::Create((float)m_tRect.left, m_tInfo.fY, 155.f, 98.f, L"Hiteffect", 4));
		return OBJ_DEAD;
	}
	m_tInfo.fX += m_iRotate * m_fSpeed;
	return OBJ_NOEVENT;
}

void CBasicArrow::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect(4.f, 2.f, 4.f, 2.f);
	if (m_iRotate == 1)
		m_pFrameKey = L"Arrow_right";
	else if (m_iRotate == -1)
		m_pFrameKey = L"Arrow_left";
}

void CBasicArrow::Render(HDC hDC)
{
	UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(0, 255, 0));
}

void CBasicArrow::Release()
{
}
