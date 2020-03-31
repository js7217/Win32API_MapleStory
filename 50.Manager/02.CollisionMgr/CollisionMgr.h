#pragma once
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();
public:
	static void CollisionRect(OBJLIST& rDst, OBJLIST& rSrc);
	static void CollisionRectExtra(OBJLIST& rDst, OBJLIST& rSrc);
	static void CollisionSphere(OBJLIST& rDst, OBJLIST& rSrc);
private:
	static bool CheckSphere(CObj* pDst, CObj* pSrc);
	static bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);
public:
	static DWORD m_dwOldTime;
};

