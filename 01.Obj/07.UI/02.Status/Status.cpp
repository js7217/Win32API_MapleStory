#include "stdafx.h"
#include "Status.h"
#include "ObjMgr.h"

CStatus::CStatus()
{
}


CStatus::~CStatus()
{
}

void CStatus::Initialize()
{
	m_tInfo.fX = 300.f;
	m_tInfo.fY = 200.f;
	m_tInfo.fCX = 212.f;
	m_tInfo.fCY = 373.f;
	m_bIsDead = true;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/Status.bmp", L"Status");
	m_pFrameKey = L"Status";
}

int CStatus::Update()
{
	_stprintf_s(m_CurLv, L"%d", CObjMgr::Get_Instance()->Get_Player()->Get_Level());
	_stprintf_s(m_CurExp, L"%d", CObjMgr::Get_Instance()->Get_Player()->Get_Exp());
	_stprintf_s(m_MaxExp, L"%d", CObjMgr::Get_Instance()->Get_Player()->Get_MaxExp());
	_stprintf_s(m_CurHp, L"%d", CObjMgr::Get_Instance()->Get_Player()->Get_Hp());
	_stprintf_s(m_MaxHp, L"%d", CObjMgr::Get_Instance()->Get_Player()->Get_MaxHp());
	_stprintf_s(m_CurMp, L"%d", CObjMgr::Get_Instance()->Get_Player()->Get_Mp());
	_stprintf_s(m_MaxMp, L"%d", CObjMgr::Get_Instance()->Get_Player()->Get_MaxMp());
	_stprintf_s(m_CurAtt, L"%d", CObjMgr::Get_Instance()->Get_Player()->Get_Att());
	if (CKeyMgr::Get_Instance()->KeyDown('P'))
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::INVENTORY);
		m_bIsDead = !m_bIsDead;
		if (m_bIsDead)
			CSoundMgr::Get_Instance()->PlayEffect(L"창끌때.mp3", CSoundMgr::INVENTORY);
		else
			CSoundMgr::Get_Instance()->PlayEffect(L"창열때.mp3", CSoundMgr::INVENTORY);
	}
	return 0;
}

void CStatus::LateUpdate()
{
	CObj::UpdateRect();
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (!m_bIsDead)
	{
		if (PtInRect(&m_tRect, pt))
		{
			if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON))
			{
				m_tInfo.fX = pt.x;
				m_tInfo.fY = pt.y;
			}
		}
	}
}

void CStatus::Render(HDC hDC)
{
	CObj::UpdateRect();
	if (m_bIsDead)
		return;
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(0, 255, 0));
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, m_tInfo.fX, m_tInfo.fY - 157, L"차재성", lstrlen(L"차재성"));

	TextOut(hDC, m_tInfo.fX + 16, m_tInfo.fY - 121, m_CurLv, lstrlen(m_CurLv));

	TextOut(hDC, m_tInfo.fX - 10, m_tInfo.fY - 103, m_CurExp, lstrlen(m_CurExp));
	TextOut(hDC, m_tInfo.fX + 16, m_tInfo.fY - 103, L"/", lstrlen(L"/"));
	TextOut(hDC, m_tInfo.fX + 26, m_tInfo.fY - 103, m_MaxExp, lstrlen(m_MaxExp));

	TextOut(hDC, m_tInfo.fX - 20, m_tInfo.fY - 30, m_CurHp, lstrlen(m_CurHp));
	TextOut(hDC, m_tInfo.fX + 16, m_tInfo.fY - 30, L"/", lstrlen(L"/"));
	TextOut(hDC, m_tInfo.fX + 26, m_tInfo.fY - 30, m_MaxHp, lstrlen(m_MaxHp));

	TextOut(hDC, m_tInfo.fX - 20, m_tInfo.fY - 12, m_CurMp, lstrlen(m_CurMp));
	TextOut(hDC, m_tInfo.fX + 16, m_tInfo.fY - 12, L"/", lstrlen(L"/"));
	TextOut(hDC, m_tInfo.fX + 26, m_tInfo.fY - 12, m_MaxMp, lstrlen(m_MaxMp));

	TextOut(hDC, m_tInfo.fX + 16, m_tInfo.fY + 75, m_CurAtt, lstrlen(m_CurAtt));
}

void CStatus::Release()
{
}
