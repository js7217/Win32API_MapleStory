#pragma once
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();
public:
	static float Get_ScrollX() { return m_fScrollX; }
	static void Set_ScrollX(float fX) { m_fScrollX += fX; }

	static float Get_ScrollY() { return m_fScrollY; }
	static void Set_ScrollY(float fY) { m_fScrollY += fY; }

	static void Set_Scroll(float fX, float fY) { m_fScrollX = fX; m_fScrollY = fY; }

	static void ScrollLock(float fCX, float fCY);
private:
	static float m_fScrollX;
	static float m_fScrollY;
};

