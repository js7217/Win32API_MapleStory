#pragma once
class CLine;
class CLineMgr
{
	DECLARE_SINGLETON(CLineMgr)
private:
	CLineMgr();
	~CLineMgr();
public:
	bool LineCollision(float fInX, float fInY, float * pOutY, float * pOutLineX, float * pOutLineY);
	void LoadData(TCHAR* pSaveKey);
public:
	void Initialize();
	void Render(HDC hDC);
	void Release();

private:
	list<CLine*> m_LineList;
};

