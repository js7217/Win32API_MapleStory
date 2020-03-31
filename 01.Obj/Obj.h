#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	enum STATE { IDLE, WALK_LEFT, WALK_RIGHT, ATTACK, JUMP, DOWN, DOWNATT, LOPE, HIT, DEAD }; // 상태..
public:
	void UpdateRect();
	void UpdateCollisionRect(float fleft, float fup, float fright, float fbottom);
	void FrameMove(int start);
	void DamageUI(int iHit, float fX, float fY);
public:
	void Set_Pos(float fX, float fY)
	{
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}
	void Set_Dead() { m_bIsDead = true; }
	void Set_Att(int iDamage) { m_iAtt += iDamage; }
	void Set_Damage(int iDamage) { m_iHp -= iDamage; }
	void Set_State(STATE eState) { m_eCurState = eState; }
	void Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	void Set_IsCollision(bool IsColl) { m_bIsCollision = IsColl; }
	void Set_Exp(int iExp) { m_iExp += iExp; }
	void Set_Rotate(int iRotate) { m_iRotate = iRotate; }
	void Set_MaxHp(int iMaxHp) { m_iMaxHp += iMaxHp; }
public:
	bool Get_IsCollision() { return m_bIsCollision; }
	INFO& Get_Info() { return m_tInfo; }
	float& Get_PosX() { return m_tInfo.fX; }
	float& Get_PosY() { return m_tInfo.fY; }
	STATE& Get_State() { return m_eCurState; }
	int& Get_Rotate() { return m_iRotate; }
	RECT& Get_Rect() { return m_tRect; }
	RECT& Get_CollisionRect() { return m_tCollisionRect; }
	int& Get_Att() { return m_iAtt; }
	int& Get_Damage() { return m_iDamage; }
	int& Get_Hp() { return m_iHp; }
	int Get_MaxHp() { return m_iMaxHp; }
	int Get_Mp() { return m_iMp; }
	int Get_MaxMp() { return m_iMaxMp; }
	int Get_Exp() { return m_iExp; }
	int Get_MaxExp() { return m_iMaxExp; }
	ObjID::ID Get_ID() { return m_eID; }
	int Get_Level() { return m_iLv; }
	TCHAR* Get_FrameKey() { return m_pFrameKey; }
public:
	virtual void Initialize() = 0;
	virtual void LateInitialize();
	virtual int  Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
protected:
	bool m_bInit;	//LateInit에서 사용
	bool m_bIsDead;	//죽었는지 살았는지 판별.
	bool m_bIsCollision;	// 충돌이 됐는지 아닌지
	float m_fSpeed;
	int m_iFrameStart;
	int m_iRotate;			// 왼쪽 : -1, 오른쪽 : 1 , 물약 : -1(상점), 1(인벤)
	int m_iHp;
	int m_iMaxHp;
	int m_iMp;
	int m_iMaxMp;
	int m_iAtt; // 기본 공격력
	int m_iDamage; // 공격력 + 무기데미지
	int m_iHit;	//맞았을 때 값.
	int m_iExp;	//경험치
	int m_iMaxExp;
	int m_iLv; // 레벨
	TCHAR* m_pFrameKey; // 프레임 키.
	INFO m_tInfo;	//크기 및 좌표
	RECT m_tRect;	//해당 렉트
	RECT m_tCollisionRect; // 충돌 렉트
	FRAME m_tFrame; //프레임 구조체(애니메이션)
	STATE m_eCurState;
	STATE m_ePreState;
	ObjID::ID m_eID;
	CWell512 m_Well512;
};

