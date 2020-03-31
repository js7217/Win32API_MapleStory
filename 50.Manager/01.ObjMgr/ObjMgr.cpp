#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"
IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::AddObject(ObjID::ID eID, CObj * pObj)
{
	m_ObjList[eID].emplace_back(pObj);
}

void CObjMgr::DeleteID(ObjID::ID eID)
{
	OBJITER iter = m_ObjList[eID].begin();
	for (; iter != m_ObjList[eID].end(); )
	{
		int iEvent = (*iter)->Update();
		if (*iter)
		{
			delete *iter;
			iter = m_ObjList[eID].erase(iter);
		}
		else
			++iter;
	}
	m_ObjList[eID].clear();
}

void CObjMgr::DeleteBullet()
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	float BulletX = 0;
	for (auto& pBullet : m_ObjList[ObjID::BULLET])
	{
		BulletX = pBullet->Get_PosX();
		if (-iScrollX >= BulletX || (WINCX - iScrollX) <= BulletX)
			pBullet->Set_Dead();
	}
}

int CObjMgr::Update()
{
	for (int i = 0; i < ObjID::END; ++i)
	{
		OBJITER iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end(); )
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	return OBJ_NOEVENT;
}

void CObjMgr::LateUpdate()
{
	for (int i = 0; i < ObjID::END; ++i)
	{
		OBJITER iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->LateUpdate();
			if (m_ObjList[i].empty())
			{
				break;
			}
		}
	}
	CCollisionMgr::CollisionRect(m_ObjList[ObjID::BULLET], m_ObjList[ObjID::MONSTER]);
	CCollisionMgr::CollisionRect(m_ObjList[ObjID::BULLET], m_ObjList[ObjID::BOSS]);
	CCollisionMgr::CollisionRect(m_ObjList[ObjID::GOLD], m_ObjList[ObjID::PLAYER]);
	CCollisionMgr::CollisionRectExtra(m_ObjList[ObjID::PLAYER], m_ObjList[ObjID::MONSTER]);
	CCollisionMgr::CollisionRectExtra(m_ObjList[ObjID::PLAYER], m_ObjList[ObjID::BULLET_BOSS]);
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < ObjID::END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Render(hDC);
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < ObjID::END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), [](CObj*& rObj)
		{
			if (nullptr != rObj)
			{
				delete rObj;
				rObj = nullptr;
			}
		});
		m_ObjList[i].clear();
	}
}
