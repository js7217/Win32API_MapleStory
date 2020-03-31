#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

void CBullet::MotionChange(TCHAR* pFrameKey_left, TCHAR* pFrameKey_right)
{
	if (m_iRotate == 1)			// 우측
		m_pFrameKey = pFrameKey_right;
	else if (m_iRotate == -1)
		m_pFrameKey = pFrameKey_left;
}

void CBullet::HitSound()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER_HIT);
	CSoundMgr::Get_Instance()->PlayEffect(L"몬스터맞음.mp3", CSoundMgr::MONSTER_HIT);
}
