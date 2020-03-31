#pragma once
#include "Obj.h"
class CMonster :	// IDLE, HIT, JUMP, WALK_LEFT, WAL_RIGHT, DIE
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();
public:
	void Set_Line(float fLineLX, float fLineRY) { m_fLineLX = fLineLX; m_fLineRX = fLineRY; }
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
protected:
	bool m_bHit;
	float m_fLineLX;			// 충돌한 라인의 왼쪽 x좌표
	float m_fLineRX;			// 충돌한 라인의 오른쪽 x좌표 
};

