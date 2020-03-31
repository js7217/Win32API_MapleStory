#pragma once
template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(float fX, float fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(fX, fY);
		return pObj;
	}
	static CObj* Create(float fX, float fY, int Rotate)		//ÃÑ¾Ë!!!!
	{
		CObj* pObj = new T(fX, fY, Rotate);
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(float fX, float fY, int iFrameScene, int iGold)		//°ñµå
	{
		CObj* pObj = new T(fX, fY, iFrameScene, iGold);
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(int iOption, float fX, float fY)		// ¾ÆÀÌÅÛµé ¼Ó¼º°ª...
	{
		CObj* pObj = new T(iOption, fX, fY);
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(float fX, float fY, float fCX, float fCY, TCHAR* pFrameKey, int iFrameend) // ÀÌÆåÆ® Àü¿ë.
	{
		CObj* pObj = new T(fX, fY, fCX, fCY, pFrameKey, iFrameend);
		pObj->Initialize();
		return pObj;
	}
	//static CObj* Create(float fX, float fY, float fAngle)
	//{
	//	CObj* pObj = new T;
	//	pObj->Initialize();
	//	pObj->Set_Pos(fX, fY);
	//	pObj->Set_Angle(fAngle);
	//	return pObj;
	//}

};