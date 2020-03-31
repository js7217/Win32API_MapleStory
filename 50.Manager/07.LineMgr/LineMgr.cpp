#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"
#include "Player.h"
#include "ObjMgr.h"
IMPLEMENT_SINGLETON(CLineMgr)

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::LineCollision(float fInX, float fInY, float * pOutY, float * pOutLineLX, float * pOutLineRX)
{		// 1,2 : 객체 x,y좌표, 3 : 충돌할 당시의 y좌표, 4,5 : 라인의 처음과 끝지점.(x좌표)
	if (m_LineList.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& pLine : m_LineList)
	{
		float inclination = pLine->Get_inclination();	//a기울기
		float x = pLine->Get_Line().tLPoint.fX;
		float y = pLine->Get_Line().tLPoint.fY;
		float LineY = inclination * (fInX - x) + y;	//ax + b = y 라인의 y좌표값.

		if (fInY <= LineY)	// 플레이어 y 축이랑 라인 y축이랑 비교
		{
			if (fInX >= pLine->Get_Line().tLPoint.fX && fInX <= pLine->Get_Line().tRPoint.fX)
			{
				pTarget = pLine;
			}
		}
	}
	if (nullptr == pTarget)
		return false;
	// 직선의 방정식 사용.
	// y = m(x - x1) + y1;
	// y = (y2 - y1) / (x2 - x1) *(x - x1) + y1; // x,y는 플레이어 좌표.
	// x1,y1 : Left
	// x2,y2 : Right
	float x1 = pTarget->Get_Line().tLPoint.fX;
	float y1 = pTarget->Get_Line().tLPoint.fY;
	float x2 = pTarget->Get_Line().tRPoint.fX;
	float y2 = pTarget->Get_Line().tRPoint.fY;
	*pOutY = (y2 - y1) / (x2 - x1) * (fInX - x1) + y1;
	*pOutLineLX = pTarget->Get_Line().tLPoint.fX;
	*pOutLineRX = pTarget->Get_Line().tRPoint.fX;
	return true;
}

void CLineMgr::LoadData(TCHAR* pSaveKey)
{
	HANDLE hFile = CreateFile(pSaveKey, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
	//	MessageBox(g_hWnd, L"실패!", L"로드 실패창!", MB_OK);
		return;
	}
	LINE tInfo = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		if (0 == dwByte)
			break;

		m_LineList.emplace_back(new CLine(tInfo));
	}
	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"성공!", L"로드 성공창!", MB_OK);
}

void CLineMgr::Initialize()
{
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& pLine : m_LineList)
		pLine->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}
