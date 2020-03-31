#pragma once
#include "Bullet.h"
class CMeteo :
	public CBullet
{
public:
	CMeteo();
	virtual ~CMeteo();

	// CBullet��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInitialize();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	float m_fSizeX;
};
