#include "stdafx.h"
#include "BitmapMgr.h"
#include "MyBitmap.h"
IMPLEMENT_SINGLETON(CBitmapMgr)

CBitmapMgr::CBitmapMgr()
{
}


CBitmapMgr::~CBitmapMgr()
{
	Release();
}

HDC CBitmapMgr::FindImage(const TCHAR * pImageKey)
{
	auto iter_find = m_mapBit.find(pImageKey);

	if (m_mapBit.end() == iter_find)
	{
		return nullptr;
	}

	return iter_find->second->Get_MemDC();
}

void CBitmapMgr::InsertBmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto iter_find = m_mapBit.find(pImgKey);

	if (m_mapBit.end() == iter_find)
	{
		CMyBitmap* pBmp = new CMyBitmap;
		pBmp->LoadBmp(pFilePath);
		m_mapBit.emplace(pImgKey, pBmp);
	}
}

void CBitmapMgr::Release()
{
	for (auto& iter : m_mapBit)
	{
		if (iter.second != nullptr)
		{
			Safe_Delete<CMyBitmap*>(iter.second);
			iter.second = nullptr;
		}
	}
	m_mapBit.clear();
}
