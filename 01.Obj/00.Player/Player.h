#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	void KeyCheck(); // 기본 플레이어 키
	void LopeKeyCheck(); // 점프시
	void IsJumping();
	void LopeJumping();
	void IsOffSet();
	void MotionChange();
	void PlayerLock(float fX);		//맵 크기를 벗어나지 못하게 함.
	void LevelUp();
public:
	int& Get_Gold() { return m_iGold; }
public:
	void Set_Lope(bool IsLope) { m_bIsLope = IsLope; }
	void Set_Gold(int iGold) { m_iGold -= iGold; }
	void Set_HpHeal(int iHeal)
	{
		m_iHp += iHeal;
		if (m_iHp >= m_iMaxHp)
			m_iHp = m_iMaxHp;
	}
	void Set_MpHeal(int iHeal)
	{
		m_iMp += iHeal;
		if (m_iMp >= m_iMaxMp)
			m_iMp = m_iMaxMp;
	}
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	bool m_bIsJump;
	bool m_bIsLope;
	bool m_bIsColl;		// bool값으로 깜빡임
	int m_iIsColl;		// int값으로 깜빡임
	int m_iGold;
	float m_fJumpPower; // v
	float m_fJumpAccel; // t
	float m_fLineLX;
	float m_fLineRX;
	DWORD m_dwOldTime;
};

