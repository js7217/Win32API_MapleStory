#pragma once
#include "Obj.h"
class CStatus :
	public CObj
{
public:
	CStatus();
	virtual ~CStatus();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	TCHAR m_CurLv[3];
	TCHAR m_CurHp[10];
	TCHAR m_MaxHp[10];
	TCHAR m_CurMp[10];
	TCHAR m_MaxMp[10];
	TCHAR m_CurAtt[10];
	TCHAR m_CurExp[10];
	TCHAR m_MaxExp[10];
};
