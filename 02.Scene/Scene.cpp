#include "stdafx.h"
#include "Scene.h"

bool CScene::m_bInit = false;
CScene::CScene()
	:m_iOption(0)
{
}


CScene::~CScene()
{
}

void CScene::LateInitialize()
{
	if (!m_bInit)
	{
		this->LateInitialize();
		m_bInit = true;
	}
}
