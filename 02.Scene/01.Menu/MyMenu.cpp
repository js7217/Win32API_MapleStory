#include "stdafx.h"
#include "MyMenu.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Logo/START.bmp", L"Start");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Logo/EDITER.bmp", L"Edit");
//	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Button/Exit.bmp", L"Exit");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Logo/MENU.bmp", L"MenuBackGround");
	CObj* pButton = CAbstractFactory<CMyButton>::Create(400.f, 300.f);
	dynamic_cast<CMyButton*>(pButton)->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, pButton);

	pButton = CAbstractFactory<CMyButton>::Create(400.f, 360.f);
	dynamic_cast<CMyButton*>(pButton)->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, pButton);
	//pButton = CAbstractFactory<CMyButton>::Create(600.f, 500.f);
	//dynamic_cast<CMyButton*>(pButton)->Set_FrameKey(L"Exit");
	//CObjMgr::Get_Instance()->AddObject(ObjID::UI, pButton);
}

void CMyMenu::LateInitialize()
{
}

void CMyMenu::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CMyMenu::Render(HDC hDC)
{
	HDC hBackBuffer = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"MenuBackGround");
	BitBlt(hBackBuffer, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hBackBuffer);
	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->DeleteID(ObjID::UI);
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
}
