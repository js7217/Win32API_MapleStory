#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Player.h"
DWORD CCollisionMgr::m_dwOldTime = GetTickCount();
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(OBJLIST & rDst, OBJLIST & rSrc)
{
	RECT rc = {};
	for (auto& rDestObj : rDst)
	{
		for (auto& rSourceObj : rSrc)
		{
			if (rSourceObj->Get_State() == CObj::STATE::DEAD)
				return;
			if (IntersectRect(&rc, &rDestObj->Get_CollisionRect(), &rSourceObj->Get_CollisionRect()))
			{
				if (rSourceObj->Get_IsCollision())
					continue;
				if (rDestObj->Get_ID() != rSourceObj->Get_ID())
				{
					int iDstAtt = rDestObj->Get_Damage();
					float fY = rSourceObj->Get_Rect().top;
					if (rSourceObj->Get_ID() == ObjID::BOSS)
						fY = rSourceObj->Get_Info().fY;
					if (!lstrcmp(rDestObj->Get_FrameKey(), L"Arrow_right") || !lstrcmp(rDestObj->Get_FrameKey(), L"Arrow_left"))
					{
						rSourceObj->Set_Damage(iDstAtt);
						rSourceObj->DamageUI(iDstAtt, rSourceObj->Get_PosX(), fY);
						rSourceObj->Set_State(CObj::STATE::HIT);
						rDestObj->Set_Dead();
					}
					else if (!lstrcmp(rDestObj->Get_FrameKey(), L"DragonArrow_right") || !lstrcmp(rDestObj->Get_FrameKey(), L"DragonArrow_left"))
					{
						rSourceObj->Set_Damage(iDstAtt);
						rSourceObj->DamageUI(iDstAtt, rSourceObj->Get_PosX(), fY);
						rSourceObj->Set_Damage(iDstAtt);
						rSourceObj->DamageUI(iDstAtt, rSourceObj->Get_PosX(), fY + 25.f);
						rSourceObj->Set_State(CObj::STATE::HIT);
						rDestObj->Set_Dead();
					}
					else if (!lstrcmp(rDestObj->Get_FrameKey(), L"Fire_Hit"))
					{
						for (int i = 0; i < 3; ++i)
						{
							rSourceObj->Set_Damage(iDstAtt);
							rSourceObj->DamageUI(iDstAtt, rSourceObj->Get_PosX(), fY + (i* 25.f));
						}
						rSourceObj->Set_State(CObj::STATE::HIT);
					}
					else if (!lstrcmp(rDestObj->Get_FrameKey(), L"coin"))
					{
						rDestObj->Set_IsCollision(true);
					}
					if (rSourceObj->Get_Hp() <= 0)
						rSourceObj->Set_State(CObj::STATE::DEAD);
				}
			}
			else
				rDestObj->Set_IsCollision(false);
		}
	}
}


void CCollisionMgr::CollisionRectExtra(OBJLIST & rDst, OBJLIST & rSrc)		//플레이어, 몬스터? , 플레이어, 보스총알
{
	RECT rc = {};
	for (auto& rDestObj : rDst)
	{
		if (!rDestObj->Get_IsCollision())
		{
			for (auto& rSourceObj : rSrc)
			{
				if (rSourceObj->Get_State() == CObj::STATE::DEAD)
					return;
				if (IntersectRect(&rc, &rDestObj->Get_CollisionRect(), &rSourceObj->Get_CollisionRect()))
				{
					int iSourAtt = rSourceObj->Get_Damage();

					if (rDestObj->Get_Hp() <= 0)
					{
						rDestObj->DamageUI(iSourAtt, rDestObj->Get_PosX(), rDestObj->Get_Rect().top);
						rDestObj->Set_State(CObj::STATE::DEAD);
					}
					else
					{
						rDestObj->Set_Damage(iSourAtt);
						rDestObj->DamageUI(iSourAtt, rDestObj->Get_PosX(), rDestObj->Get_Rect().top);
						rDestObj->Set_State(CObj::STATE::HIT);
					}
					cout << "충돌 함" << endl;
					rDestObj->Set_IsCollision(true);
					m_dwOldTime = GetTickCount();
					CSoundMgr::Get_Instance()->PlayEffect(L"캐릭터피격.mp3", CSoundMgr::PLAYER_HIT);
				}
			}
		}
		else
		{
			if (m_dwOldTime + 3000 < GetTickCount())
			{
				cout << "무적 " << endl;
				rDestObj->Set_IsCollision(false);
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER_HIT);
				
			}
		}
	}
}

void CCollisionMgr::CollisionSphere(OBJLIST & rDst, OBJLIST & rSrc)
{
	for (auto& rDestObj : rDst)
	{
		for (auto& rSourceObj : rSrc)
		{
			if (CheckSphere(rDestObj, rSourceObj))
			{
				rDestObj->Set_Dead();
				rSourceObj->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::CheckSphere(CObj * pDst, CObj * pSrc)
{
	//C^2 = a^2 + b^2
	//반지름의 합. 
	float fSumRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

	// 밑변
	float fWidth = pDst->Get_Info().fX - pSrc->Get_Info().fX;
	// 높이 
	float fHeight = pDst->Get_Info().fY - pSrc->Get_Info().fY;

	float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fSumRadius >= fDistance;
}

bool CCollisionMgr::CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
{
	float fRadSumX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float fRadSumY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	float fDistX = fabs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float fDistY = fabs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	if (fRadSumX >= fDistX && fRadSumY >= fDistY)
	{
		*pMoveX = fRadSumX - fDistX;
		*pMoveY = fRadSumY - fDistY;
		return true;
	}
	return false;
}
