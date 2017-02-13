#pragma once
#include <windows.h>

enum class SyncPrimitivesEnum
{
	CriticalSection,
	Mutex,
	Semaphore,
	Event,
	None,
};

class CSyncPrimitives
{
public:
	CSyncPrimitives(SyncPrimitivesEnum primitive);
	~CSyncPrimitives();

	void CreatePrimitive();
	void StartOfSyncZone();
	void EndOfSyncZone();

private:
	SyncPrimitivesEnum m_primitiveEnum;
	HANDLE m_mutex;
	HANDLE m_semaphore;
	HANDLE m_event;
	CRITICAL_SECTION m_criticalSection;
};