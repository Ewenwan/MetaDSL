#ifndef __LockEx_H__
#define __LockEx_H__

#if defined(__WINDOWS__)

class MyLock
{
public:
	MyLock()
	{ 
		::InitializeCriticalSection(&m_Lock);
	}
	~MyLock()
	{ 
		::DeleteCriticalSection(&m_Lock); 
	}

	VOID Lock(VOID)
	{ 
		::EnterCriticalSection(&m_Lock); 
	}

	VOID Unlock(VOID)
	{ 
		::LeaveCriticalSection(&m_Lock); 
	}

private:
	CRITICAL_SECTION m_Lock ;
};

#elif defined(__LINUX__)

class MyLock
{
public :
	MyLock()
	{ 
		pthread_mutex_init(&m_Mutex , NULL);
	}
	~MyLock()
	{ 
		pthread_mutex_destroy(&m_Mutex);
	}

	VOID Lock(VOID)
	{ 
		pthread_mutex_lock(&m_Mutex); 
	}

	VOID Unlock(VOID)
	{ 
		pthread_mutex_unlock(&m_Mutex); 
	}

private:
	pthread_mutex_t 	m_Mutex;
};

#endif

//�Զ�����������
class AutoLock_T
{
public:
	AutoLock_T(MyLock& rLock)
	{
		m_pLock = &rLock;
		m_pLock->Lock();
	}

	AutoLock_T(MyLock* pLock)
	{
		m_pLock = pLock;

		if(m_pLock)
		{
			m_pLock->Lock();
		}
	}

	~AutoLock_T()
	{
		if(m_pLock)
		{
			m_pLock->Unlock();
			m_pLock = 0;
		}
	}

private:
	AutoLock_T();
	MyLock* m_pLock;
};

//FB_Lock.h���AutoLock_T��ģ��汾����Ҫ���ڱ���ʱ�л������벻�����Ĵ��롣
//�Զ�����������
template<typename LockT>
class AutoLockT
{
public:
	AutoLockT(LockT& rLock)
	{
		m_pLock = &rLock;
		m_pLock->Lock();
	}
	AutoLockT(LockT* pLock)
	{
		m_pLock = pLock;

		if(m_pLock)
		{
			m_pLock->Lock();
		}
	}
	~AutoLockT(VOID)
	{
		if(m_pLock)
		{
			m_pLock->Unlock();
			m_pLock = 0;
		}
	}
private:
	AutoLockT(VOID);
	LockT* m_pLock;
};

//������������MyLock�Ľӿڣ�����ִ����������
class DummyLock
{
public :
	DummyLock(VOID){}
	~DummyLock(VOID){}	
	VOID Lock(VOID){}
	VOID Unlock(VOID){}
};

#endif //__LockEx_H__