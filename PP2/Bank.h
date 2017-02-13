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

private:
	std::vector<CBankClient> m_clients;
	int m_totalBalance;

	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations();
};