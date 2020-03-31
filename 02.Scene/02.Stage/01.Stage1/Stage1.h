#pragma once
#include "Scene.h"
class CStage1 :
	public CScene
{
public:
	CStage1();
	virtual ~CStage1();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInitialize();
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void MonsterCreate();
private:
	int m_iMapCX;
	int m_iMapCY;
};

