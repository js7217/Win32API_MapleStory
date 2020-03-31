#pragma once
#include "Monster.h"
class CTile;
class CBoss :
	public CMonster
{
public:
	enum BossState {IDLE, LIGHTNING, EXPLOSION, ICE};
public:
	CBoss();
	virtual ~CBoss();
public:
	void MonsterWalk();
	void MotionChange();
public:
	BossState Get_BossState() { return m_eCurState; }
	void Set_BossState(BossState eState) { m_eCurState = eState; }
public:
	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	float m_fJumpAccel;
	BossState m_eCurState;
	BossState m_ePreState;
	CTile* m_Exit;
	DWORD m_dwOldTime;
	DWORD m_dwTime;
};

