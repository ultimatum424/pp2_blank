#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include <string>

namespace
{
	void PrintHelpForStart()
	{
		std::cout << "Using command string : PP2.exe <count clients> <type SyncPrimitive>" << std::endl;
		std::cout << "Code for using  SyncPrimitive: " << std::endl;
		std::cout << "1 - critical section" << std::endl;
		std::cout << "2 - mutex" << std::endl;
		std::cout << "3 - semafor" << std::endl;
		std::cout << "4 - event" << std::endl;
		std::cout << "? - for Help" << std::endl;
	}

	SyncPrimitivesEnum FindSyncPrimitiveFormArgv(std::string param)
	{
		if (param == "1")
		{
			return SyncPrimitivesEnum::CriticalSection;
		}
		else if (param == "2")
		{
			return SyncPrimitivesEnum::Mutex;
		}
		else if (param == "3")
		{
			return SyncPrimitivesEnum::Semaphore;
		}
		else if (param == "4")
		{
			return SyncPrimitivesEnum::Event;
		}
		return SyncPrimitivesEnum::None;
	}
}


int main(int argc, char* argv[])
{
	PrintHelpForStart();

	if (argc > 1)
	{
		if (argv[1] == "/?")
		{
			PrintHelpForStart();
		}
		else
		{
			CBank* bank;
			unsigned cliensCount;
			// fixed TODO: WaitForMultipleObjects
			try
			{
				cliensCount = std::stoi(argv[1]);
			}
			catch (std::exception)
			{
				std::cout << "Invalid argument" << std::endl;
				return 1;
			}
			if (argc == 3)
			{
				bank = new CBank(cliensCount, FindSyncPrimitiveFormArgv(argv[2]));
			}

			else
			{
				bank = new CBank(cliensCount, SyncPrimitivesEnum::None);
			}

			while (true)
			{
				bank->WaitForClients();
			}
		}
	}
	
	return 0;
		
}