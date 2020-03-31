#pragma once
#include "Scene.h"
class CBossStage :
	public CScene
{
public:
	CBossStage();
	virtual ~CBossStage();
public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void BossPattern();
private:
	int m_iMapCX;
	int m_iMapCY;
	int m_iBossHp;
	int m_iBossMaxHp;
	CObj* m_pBoss;
	CObj* m_pBoss_hand_left;
	CObj* m_pBoss_hand_right;
	DWORD m_dwPatternTime;
	DWORD m_dwTime;
};

