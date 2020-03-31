#pragma once
class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)
private:
	CSoundMgr();
	~CSoundMgr();
public:
	enum CHANNELID { BGM, PLAYER_JUMP, PLAYER_SHOOT, PLAYER_HIT,
		SKILL_FIRE, SKILL_TORNADO, POTION, ITEM_GET, ITEM_CLICK, ITEM_UP, INVENTORY, 
		MONSTER_HIT, MONSTER_DEAD, EFFECT, UI, SHOP, POTAL, EQUIP_CLICK, 
		MOUSE_COLLISION, MOUSE_CLICK, MAXCHANNEL };

	void Initialize();
	void Update();
	void Release();

public:
	void PlayEffect(TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNELID eId);
	void AllStop();
private:
	void LoadSoundFile();
private:
	// FMOD_SOUND 사운드 리소스 정보를 갖는 객체 .
	map<TCHAR*, FMOD_SOUND*> m_mapSound;

	//FMOD_CHANNEL 재생하고 있는 사운드를 관리할 객체  
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];

	// 사운드 채널 객체 및 장치를 관리하는 객체. 
	FMOD_SYSTEM* m_pSystem;
};

