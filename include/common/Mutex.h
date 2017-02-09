#ifndef _MUTEX_H_
#define _MUTEX_H_
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#else
#include <sys/time.h>
#include <pthread.h>
#endif
#include <vector>
using namespace std;

#ifdef UTIL_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif


class DLL_EXPORT CMutex
{
public:

	CMutex()
	{
#ifdef WIN32
		//先在用户态进行锁，失败才进入内核态，节省近千个CPU指令周期
		InitializeCriticalSectionAndSpinCount(&m_Mutex,4000);
#else
		pthread_mutex_init(&m_Mutex,NULL);
#endif
	}
	~CMutex()
	{
#ifdef WIN32
		DeleteCriticalSection(&m_Mutex);
#else
		pthread_mutex_destroy(&m_Mutex);
#endif
	}

	inline void Lock() 
	{
#ifdef WIN32
		::EnterCriticalSection(&m_Mutex);
#else
		(void)pthread_mutex_lock(&m_Mutex);
#endif
	};


	inline void Unlock() 
	{
#ifdef WIN32
		::LeaveCriticalSection(&m_Mutex);
#else
		pthread_mutex_unlock(&m_Mutex);
#endif
	};

#ifdef WIN32
	inline CRITICAL_SECTION& getMutex(){return m_Mutex;}
#else
	inline pthread_mutex_t& getMutex(){return m_Mutex;}
#endif

private:

#ifdef WIN32
	CRITICAL_SECTION m_Mutex;                     
#else
	pthread_mutex_t m_Mutex;       
#endif       
};

class DLL_EXPORT CLock
{
public:
	CLock(CMutex& mutex):_mutex(mutex)
	{
		_mutex.Lock();
	}
	
	~CLock()
	{
		_mutex.Unlock();
	}

private:
	CMutex&	_mutex;
};

#endif
