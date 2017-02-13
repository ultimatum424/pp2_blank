#pragma once
#include <vector>
#include "CSyncPrimitives.h"
#include "BankClient.h"


class CBank
{
public:
	CBank(const unsigned& clientsCount, SyncPrimitivesEnum primitivesType);
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	size_t GetClientCount() const;
	DWORD WaitForClients();

private:
	std::vector<HANDLE> m_threads;
	std::vector<CBankClient> m_clients;
	int m_totalBalance;
	CSyncPrimitives m_syncPrimitives;

	int GetTotalBalance() const;
	void SetTotalBalance(int value);
	static void SomeLongOperations();
};