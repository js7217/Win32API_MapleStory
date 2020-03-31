#pragma once
class CObj;
class CScene;
class CTileMgr
{
	DECLARE_SINGLETON(CTileMgr)
private:
	CTileMgr();
	~CTileMgr();
public:
	void TileCollision(CObj* pDst, CScene* pScene);
	bool CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY);
public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
public:
	void LoadData(TCHAR* pSaveKey);
private:
	list<CObj*> m_listTile;
};

