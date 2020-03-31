#include "stdafx.h"
#include "MathMgr.h"

#include "Obj.h"
CMathMgr::CMathMgr()
{
}


CMathMgr::~CMathMgr()
{
}

float CMathMgr::CalcDistance(CObj * pDst, CObj * pSrc)
{
	float fX = pDst->Get_Info().fX - pSrc->Get_Info().fX;
	float fY = pDst->Get_Info().fY - pSrc->Get_Info().fY;
	float fDist = sqrtf(fX * fX + fY * fY);
	return fDist;
}

float CMathMgr::CalcRadian(CObj * pDst, CObj * pSrc)
{
	float fw = pDst->Get_Info().fX - pSrc->Get_Info().fX;
	float fh = pDst->Get_Info().fY - pSrc->Get_Info().fY;
	float fDist = sqrtf(fw * fw + fh * fh);

	float fAngle = acosf(fw / fDist);
	if (pSrc->Get_Info().fY < pDst->Get_Info().fY)
		fAngle *= -1.f;

	return fAngle;
}
