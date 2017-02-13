#pragma once
#include <iostream>
#include <vector>

#include "BankClient.h"

class CBank
{
public:
	CBank();
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	size_t GetClientCount() const;
	DWORD WaitForClients();

private:
	std::vector<HANDLE> m_threads;
	std::vector<CBankClient> m_clients;
	int m_totalBalance;

	int GetTotalBalance() const;
	void SetTotalBalance(int value);
	static void SomeLongOperations();
};