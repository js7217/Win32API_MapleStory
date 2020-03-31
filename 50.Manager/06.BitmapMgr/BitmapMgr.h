#pragma once
class CMyBitmap;
class CBitmapMgr
{
	DECLARE_SINGLETON(CBitmapMgr)
private:
	CBitmapMgr();
	~CBitmapMgr();
public:
	HDC FindImage(const TCHAR* pImageKey);
	void InsertBmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	void Release();
private:
	map<const TCHAR*, CMyBitmap*> m_mapBit;
};

