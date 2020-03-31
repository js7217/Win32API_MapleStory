#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();
public:
	void Set_Option(int iOption) { m_iOption = iOption; }
public:
	virtual void Initialize() = 0;
	virtual void LateInitialize();
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
protected:
	static bool m_bInit;
	int m_iOption;
};

