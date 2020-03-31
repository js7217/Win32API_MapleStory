#pragma once
#include "Monster.h"
class CCBalok :
	public CMonster
{
public:
	CCBalok();
	virtual ~CCBalok();
public:
	void MonsterWalk();
	void MotionChange();
public:
	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	float m_fJumpAccel;
	int m_iGold;
};

