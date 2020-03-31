#pragma once
#include "Obj.h"
class CMainUI :
	public CObj
{
public:
	CMainUI();
	virtual ~CMainUI();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

