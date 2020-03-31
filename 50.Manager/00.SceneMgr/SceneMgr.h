#pragma once
class CScene;
class CSceneMgr
{
public:
	DECLARE_SINGLETON(CSceneMgr)
private:
	CSceneMgr();
	~CSceneMgr();
public:
	enum SCENEID { SCENE_LOGO, SCENE_MENU, SCENE_VILLAGE, SCENE_STAGE1, SCENE_STAGE2, SCENE_BOSS, SCENE_EDIT, SCENE_END };
public:
	void SceneChange(SCENEID eSceneID);	// Scene을 전환시키기 위한 함수.
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
private:
	bool m_bInit;
	CScene* m_pScene;
	SCENEID m_eCurScene;	//현재 씬
	SCENEID m_eNextScene;	//받아온 씬
};

