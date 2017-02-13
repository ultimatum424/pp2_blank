#include "Bank.h"

CBank::CBank()
{

	m_clients = std::vector<CBankClient>();
	m_threads = std::vector<HANDLE>();
	m_totalBalance = 0;
}


CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	m_threads.push_back(CreateThread(NULL, 0, &client->ThreadFunction, &*client, 0, NULL));
	return client;
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations();
	

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance + value < 0) 
	{
		std::cout << "! ERROR !" << std::endl;
	}
	else { SetTotalBalance(totalBalance + value); }

	
}

size_t CBank::GetClientCount() const
{
	return  m_clients.size();
}

DWORD CBank::WaitForClients()
{
	return WaitForMultipleObjects(m_threads.size(), m_threads.data(), true, INFINITY);
}


int CBank::GetTotalBalance() const
{
	return m_totalBalance;
}


void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations()
{
	// fixed TODO
	Sleep(200);
}