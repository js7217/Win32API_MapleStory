#include "stdafx.h"
#include "MyButton.h"
#include "SceneMgr.h"

CMyButton::CMyButton()
	:m_pFrameKey(nullptr)
	,m_iDrawID(0)
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 60.f;
}

void CMyButton::LateInitialize()
{
}

int CMyButton::Update()
{
	CObj::UpdateRect();
	CObj::LateInitialize();

	return OBJ_NOEVENT;
}

void CMyButton::LateUpdate()
{
	CObj::UpdateRect();
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		m_iDrawID = 1;
		CSoundMgr::Get_Instance()->PlayEffect(L"창끌때.mp3", CSoundMgr::MOUSE_COLLISION);
		if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlayEffect(L"창열때.mp3", CSoundMgr::MOUSE_CLICK);
			if (!lstrcmp(m_pFrameKey, L"Start"))
			{
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_VILLAGE);
			}
			else if (!lstrcmp(m_pFrameKey, L"Edit"))
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_EDIT);
			else if (!lstrcmp(m_pFrameKey, L"Exit"))
				DestroyWindow(g_hWnd);
			return;
		}

	}
	else
		m_iDrawID = 0;
}

void CMyButton::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_iDrawID, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(0, 0, 247));
}

void CMyButton::Release()
{
}
