#pragma once
#include "Scene.h"
class CEditor :
	public CScene
{
public:
	CEditor();
	virtual ~CEditor();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void KeyCheck();
private:
	float m_fCX;
	float m_fCY;
	TCHAR* m_pFrameKey;
	TCHAR* m_pLineKey;
	TCHAR* m_pTileKey;
};

