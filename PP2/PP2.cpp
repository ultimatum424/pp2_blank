#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"


int main()
{
	CBank* bank = new CBank(2, SyncPrimitivesEnum::Mutex);
	

	// fixed TODO: WaitForMultipleObjects
	while (true)
	{
		bank->WaitForClients();
	}

    return 0;
}