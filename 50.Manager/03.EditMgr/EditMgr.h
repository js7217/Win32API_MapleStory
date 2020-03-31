#pragma once
class CLine;
class CObj;
class CEditMgr
{
	DECLARE_SINGLETON(CEditMgr)
private:
	CEditMgr();
	~CEditMgr();
public:
	void Set_SaveKey(TCHAR* LineKey, TCHAR* TileKey)
	{
		m_pLineKey = LineKey; 
		m_pTileKey = TileKey;
	}
public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
public:
	void SaveLine();
	void LoadLine(TCHAR* pEditKey);
	void SaveTile();
	void LoadTile(TCHAR* pEditKey);
public:
	void EditLine();
	void EditTile();
private:
	list<CLine*> m_LineList;
	list<CObj*> m_TileList;
	TCHAR* m_pLineKey;
	TCHAR* m_pTileKey;
	int m_iEditType;
};

