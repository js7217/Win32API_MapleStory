#pragma once

#define WINCX 800
#define WINCY 600

#define OBJ_NOEVENT 0
#define OBJ_DEAD 1

#define MAIN_STAGECX	1920
#define MAIN_STAGECY	681

#define DECLARE_SINGLETON(ClassName)			\
public:											\
	static ClassName* Get_Instance()			\
	{											\
		if (nullptr == m_pInstance)				\
			m_pInstance = new ClassName;		\
		return m_pInstance;						\
	}											\
	static void Destory_Instance()				\
	{											\
		if(m_pInstance != nullptr)				\
		{										\
			delete m_pInstance;					\
			m_pInstance = nullptr;				\
		}										\
	}											\
private:										\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;