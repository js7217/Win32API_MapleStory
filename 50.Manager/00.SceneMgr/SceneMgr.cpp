#include "stdafx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "MyMenu.h"
#include "MainStage.h"
#include "Stage1.h"
#include "Stage2.h"
#include "BossStage.h"
#include "Editor.h"
IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
	,m_bInit(FALSE)
	,m_eCurScene(SCENE_END)
	,m_eNextScene(SCENE_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SceneChange(SCENEID eSceneID)
{
	m_eNextScene = eSceneID;
	if (m_eNextScene != m_eCurScene)
	{
		m_bInit = false;
		CScene* pTemp = m_pScene;
		switch (m_eNextScene)
		{
		case CSceneMgr::SCENE_LOGO:
			m_pScene = new CLogo;
			break;
		case CSceneMgr::SCENE_MENU:
			m_pScene = new CMyMenu;
			break;
		case CSceneMgr::SCENE_VILLAGE:
			m_pScene = new CMainStage;
			break;
		case CSceneMgr::SCENE_STAGE1:
			m_pScene = new CStage1;
			break;
		case CSceneMgr::SCENE_STAGE2:
			m_pScene = new CStage2;
			break;
		case CSceneMgr::SCENE_BOSS:
			m_pScene = new CBossStage;
			break;
		case CSceneMgr::SCENE_EDIT:
			m_pScene = new CEditor;
			break;
		default:
			MessageBox(g_hWnd, L"ㅇㅇ?잘못탔는데??", L"오류창", MB_OK);
			break;
		}
		Safe_Delete(pTemp);
//		m_pScene->Initialize();
		m_eCurScene = m_eNextScene;
	}

}

void CSceneMgr::Update()
{
	if (!m_bInit)
	{
		m_pScene->Initialize();
		m_bInit = true;
	}
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	cout << iScrollX << ", " << iScrollY << endl;
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
