#pragma once
class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)
private:
	CObjMgr();
	~CObjMgr();
public:
	CObj* Get_Player() { return m_ObjList[ObjID::PLAYER].front(); }
	CObj* Get_Target(ObjID::ID eID) { return m_ObjList[eID].front(); }
	OBJLIST Get_List(ObjID::ID eID) { return m_ObjList[eID]; }
	CObj* Get_Mouse() { return m_ObjList[ObjID::MOUSE].front(); }
	CObj* Get_Inventory() { return m_ObjList[ObjID::INVENTORY].front(); }
	CObj* Get_Boss() { return m_ObjList[ObjID::BOSS].front(); }
	CObj* Get_Equipment() { return m_ObjList[ObjID::EQUIPMENT].front(); }
	OBJLIST Get_EffectDamage() { return m_ObjList[ObjID::EFFECT_DAMAGE]; }
public:
	void AddObject(ObjID::ID eID, CObj* pObj);
	void DeleteID(ObjID::ID eID);
	void DeleteBullet();
	int Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
private:
	OBJLIST m_ObjList[ObjID::END];
};

