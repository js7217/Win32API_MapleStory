#include "stdafx.h"
#include "TileMgr.h"
#include "Player.h"
#include "Tile.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
IMPLEMENT_SINGLETON(CTileMgr)
CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::TileCollision(CObj* pDst, CScene* pScene)
{
	RECT rc = {};
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& rTileObj : m_listTile)
	{
		int iOption = dynamic_cast<CTile*>(rTileObj)->Get_Option();
		if (CheckRect(pDst, rTileObj, &fMoveX, &fMoveY))
		{
			if (iOption == 0)
			{
				float x = pDst->Get_Info().fX;
				float y = pDst->Get_Info().fY;
				if (fMoveX > fMoveY)
				{
					if (y < rTileObj->Get_Info().fY)
						fMoveY *= -1.f;
					pDst->Set_Pos(x, y + fMoveY);
				}
				else
				{

					if (x < rTileObj->Get_Info().fX)
						fMoveX *= -1.f;

					pDst->Set_Pos(x + fMoveX, y);
				}
			}
			if (iOption == 1 || iOption == 2)
			{
				if(CKeyMgr::Get_Instance()->KeyDown(VK_UP))
					pScene->Set_Option(iOption);
			}
			if (iOption == 3)
			{
				if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP) && pDst->Get_PosY() > rTileObj->Get_PosY())
				{
					pDst->Set_FrameKey(L"Player_LOPE");
					pDst->Set_State(CObj::LOPE);
					pDst->Set_Pos(rTileObj->Get_PosX(), pDst->Get_PosY());
					dynamic_cast<CPlayer*>(pDst)->Set_Lope(true);
				}
				if(CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN) && pDst->Get_PosY() < rTileObj->Get_PosY())
				{
					pDst->Set_FrameKey(L"Player_LOPE");
					pDst->Set_State(CObj::LOPE);
					pDst->Set_Pos(rTileObj->Get_PosX(), pDst->Get_PosY());
					dynamic_cast<CPlayer*>(pDst)->Set_Lope(true);
				}
				
			}
		}
	}
}

bool CTileMgr::CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
{
	float fRadSumX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.2f;
	float fRadSumY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	float fDistX = fabs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float fDistY = fabs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	if (fRadSumX >= fDistX && fRadSumY >= fDistY)
	{
		*pMoveX = fRadSumX - fDistX;
		*pMoveY = fRadSumY - fDistY;
		return true;
	}
	return false;
}

void CTileMgr::Initialize()
{
}
void CTileMgr::Update()
{
}

void CTileMgr::LateUpdate()
{
}

void CTileMgr::Render(HDC hDC)
{
	for (auto& pTile : m_listTile)
		pTile->Render(hDC);
}

void CTileMgr::Release()
{
	for_each(m_listTile.begin(), m_listTile.end(), Safe_Delete<CObj*>);
	m_listTile.clear();
}

void CTileMgr::LoadData(TCHAR * pSaveKey)
{
	HANDLE hFile = CreateFile(pSaveKey, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		//MessageBox(g_hWnd, L"실패!", L"로드 실패창!", MB_OK);
		return;
	}
	INFO tInfo = {};
	int iDrawID = 0, iOption = 0;
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->Set_Option(iOption);

		m_listTile.emplace_back(pTile);
	}
	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"성공!", L"로드 성공창!", MB_OK);
}
