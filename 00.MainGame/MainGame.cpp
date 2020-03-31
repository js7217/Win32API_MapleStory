#include "stdafx.h"
#include "MainGame.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "BitmapMgr.h"
#include "AbstractFactory.h"
CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	CSoundMgr::Get_Instance()->Initialize();
	m_hDC = GetDC(g_hWnd);
	CObjMgr::Get_Instance()->AddObject(ObjID::MOUSE, CAbstractFactory<CMouse>::Create());
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/BackBuffer.bmp", L"BackBuffer");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/Boss/boss.bmp", L"Boss");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/Boss/boss_hand_left.bmp", L"Boss_hand_left");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/Boss/boss_hand_right.bmp", L"Boss_hand_right");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/JBalok/JBalokLeft.bmp", L"JBalokLeft");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/JBalok/JBalokRight.bmp", L"JBalokRight");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/CBalok/CBalokLeft.bmp", L"CBalokLeft");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Monster/CBalok/CBalokRight.bmp", L"CBalokRight");

	CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOGO);
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::Get_Instance()->LateUpdate();
	CKeyMgr::Get_Instance()->KeyUpdate();
}

void CMainGame::Render()
{
	CSceneMgr::Get_Instance()->Render(m_hDC);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CSoundMgr::Destory_Instance();
	CSceneMgr::Destory_Instance();
	CObjMgr::Destory_Instance();
}
