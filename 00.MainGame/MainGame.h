#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
private:
	HDC m_hDC;
};

