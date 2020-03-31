#include "stdafx.h"
#include "DragonArrow.h"
#include "Effect.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CDragonArrow::CDragonArrow()
{
}

CDragonArrow::CDragonArrow(float fX, float fY, int Rotate)
{
	m_tInfo.fX = fX + 50.f * Rotate;
	m_tInfo.fY = fY + 10.f;
	m_iRotate = Rotate;
	m_eID = ObjID::PLAYER;
}

CDragonArrow::~CDragonArrow()
{
	Release();
}

void CDragonArrow::Initialize()
{
	m_tInfo.fCX = 281.f;
	m_tInfo.fCY = 116.f;
	m_fSpeed = 10.f;
	m_iAtt = CObjMgr::Get_Instance()->Get_Player()->Get_Att();
	m_iDamage = m_Well512.GetValue(130, 200) + m_iAtt;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Skill/Dragon/Arrow/DragonArrow_left.bmp", L"DragonArrow_left");	
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Skill/Dragon/Arrow/DragonArrow_right.bmp", L"DragonArrow_right");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Skill/Dragon/Effect/DragonEffect_left.bmp", L"DragonEffect_left");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Skill/Dragon/Effect/DragonEffect_right.bmp", L"DragonEffect_right");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Skill/DragonSprite/Hit.bmp", L"DragonEffect_Hit");
	m_pFrameKey = L"DragonArrow_right";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CDragonArrow::Update()
{
	CObj::UpdateRect();
	if (m_bIsDead)
	{
		HitSound();
		HitSound();
		if(m_iRotate == 1)
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::Create((float)m_tRect.right, m_tInfo.fY, 212.f, 205.f, L"DragonEffect_Hit", 7));
		if(m_iRotate == -1)
			CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::Create((float)m_tRect.left, m_tInfo.fY, 212.f, 205.f, L"DragonEffect_Hit", 7));
		return OBJ_DEAD;
	}
	m_tInfo.fX += m_iRotate * m_fSpeed;
	return OBJ_NOEVENT;
}

void CDragonArrow::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect(4.f, 2.f, 4.f, 2.f); // 충돌용 렉트.
	MotionChange(L"DragonArrow_left", L"DragonArrow_right");
	CObj::FrameMove(0);
}

void CDragonArrow::Render(HDC hDC)
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
		RGB(255, 255, 255));
}

void CDragonArrow::Release()
{
}
