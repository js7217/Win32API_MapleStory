#include "stdafx.h"
#include "SoundMgr.h"

IMPLEMENT_SINGLETON(CSoundMgr)
CSoundMgr::CSoundMgr()
{
	m_pSystem = nullptr;
	ZeroMemory(m_pChannelArr, sizeof(FMOD_CHANNEL*) * MAXCHANNEL);
}


CSoundMgr::~CSoundMgr()
{
	Release();
}

void CSoundMgr::Initialize()
{
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();
}

void CSoundMgr::Update()
{
}

void CSoundMgr::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}

void CSoundMgr::PlayEffect(TCHAR * pSoundKey, CHANNELID eID)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter = m_mapSound.begin();
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [=](auto& Pair)
	{
		return !lstrcmp(Pair.first, pSoundKey);
	}
	);

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL isPlay;

	if (FMOD_Channel_IsPlaying(m_pChannelArr[eID], &isPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[eID]);
	}
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlayBGM(TCHAR * pSoundKey)
{
	if (m_mapSound.empty())
	{
		return;
	}
	auto& iter = find_if(m_mapSound.begin(), m_mapSound.end(), [=](auto& Pair)
	{
		return !lstrcmp(Pair.first, pSoundKey);
	}
	);

	if (iter == m_mapSound.end())
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[BGM]);

	FMOD_Channel_SetMode(m_pChannelArr[BGM], FMOD_LOOP_NORMAL);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::StopSound(CHANNELID eId)
{
	FMOD_Channel_Stop(m_pChannelArr[eId]);
}

void CSoundMgr::AllStop()
{
	for (int i = 0; i < MAXCHANNEL; ++i)
	{
		FMOD_Channel_Stop(m_pChannelArr[i]);
	}
}

void CSoundMgr::LoadSoundFile()
{
	_finddata_t fd;

	long handle = _findfirst("../Maple_Resource/Sound/*.*", &fd);

	if (handle == 0)
		return;

	int iResult = 0;

	char szCurPath[128] = "../Maple_Resource/Sound/";
	char szFullPath[128] = "";

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath);
		strcat_s(szFullPath, fd.name);

		FMOD_SOUND* pSound = nullptr;
		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];

			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}
		iResult = _findnext(handle, &fd);
	}
	FMOD_System_Update(m_pSystem);
}
