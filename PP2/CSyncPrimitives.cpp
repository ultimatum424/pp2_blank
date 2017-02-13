#include "CSyncPrimitives.h"

CSyncPrimitives::CSyncPrimitives(SyncPrimitivesEnum primitive)
{
	m_primitiveEnum = primitive;
}

CSyncPrimitives::~CSyncPrimitives()
{
	if (m_primitiveEnum == SyncPrimitivesEnum::CriticalSection)
	{
		DeleteCriticalSection(&m_criticalSection);
	}
}

void CSyncPrimitives::CreatePrimitive()
{

	if (m_primitiveEnum == SyncPrimitivesEnum::CriticalSection)
	{
		InitializeCriticalSection(&m_criticalSection);
	}

	else if (m_primitiveEnum == SyncPrimitivesEnum::Mutex)
	{
		m_mutex = CreateMutex(NULL, false, NULL);
	}

	else if (m_primitiveEnum == SyncPrimitivesEnum::Semaphore)
	{
		m_semaphore = CreateSemaphore(NULL, 1, 1, NULL);
	}

	else if (m_primitiveEnum == SyncPrimitivesEnum::Event)
	{
		m_event = CreateEvent(NULL, false, true, NULL);
	}
}

void CSyncPrimitives::StartOfSyncZone()
{
	if (m_primitiveEnum == SyncPrimitivesEnum::CriticalSection)
	{
		EnterCriticalSection(&m_criticalSection);
	}
	else if (m_primitiveEnum == SyncPrimitivesEnum::Mutex)
	{
		WaitForSingleObject(m_semaphore, INFINITE);
	}
	else if (m_primitiveEnum == SyncPrimitivesEnum::Semaphore)
	{
		WaitForSingleObject(m_mutex, INFINITE);
	}
	else if (m_primitiveEnum == SyncPrimitivesEnum::Event)
	{
		WaitForSingleObject(m_event, INFINITE);
	}
}

void CSyncPrimitives::EndOfSyncZone()
{
	if (m_primitiveEnum == SyncPrimitivesEnum::CriticalSection)
	{
		LeaveCriticalSection(&m_criticalSection);
	}
	else if (m_primitiveEnum == SyncPrimitivesEnum::Mutex)
	{
		ReleaseMutex(m_mutex);
	}
	else if (m_primitiveEnum == SyncPrimitivesEnum::Semaphore)
	{
		ReleaseSemaphore(m_semaphore, 1, NULL);
	}
	else if (m_primitiveEnum == SyncPrimitivesEnum::Event)
	{
		SetEvent(m_event);
	}
}