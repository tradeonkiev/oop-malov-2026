#include "economy.h"
#include "bank.h"
#include "behaviors.h"
#include "town.h"
#include <iostream>

static void PrintState(const std::string& title, Bank& bank, Town& town, Money totalCash)
{
	std::cout << std::endl
			  << title << std::endl;
	std::cout << "Total cash in system: " << totalCash << std::endl;
	std::cout << "Bank registered cash: " << bank.GetCash() << std::endl;

	for (Person* p : town.Everyone())
	{
		std::cout << p->GetName() << ": ";
		if (p->HasAccount())
			std::cout << "beznal=" << bank.GetAccountBalance(p->GetAccountId()) << " ";
		std::cout << "cash=" << p->GetPocketCash() << std::endl;
	}
}

static void CheckConsistency(Bank& bank, Town& town, Money totalCash)
{
	Money totalPocket = 0;
	for (Person* p : town.Everyone())
		totalPocket += p->GetPocketCash();

	Money bankCash = bank.GetCash();
	Money totalMoney = bank.GetTotalMoney();

	std::cout << std::endl
			  << "Consistency check" << std::endl;
	std::cout << "Sum of cash:   " << totalPocket << std::endl;
	std::cout << "Bank registered cash:  " << bankCash << std::endl;
	std::cout << "Total in accounts:     " << bank.GetTotalAccountBalance() << std::endl;
	std::cout << "Total money in system: " << totalMoney << std::endl;
	std::cout << "Initial total money:   " << totalCash << std::endl;

	if (totalPocket == bankCash && totalMoney == totalCash)
		std::cout << "System is OK\n";
	else
		std::cerr << "INCONSISTENCY\n";
}

void RunEconomy(int numIterations)
{
	const Money kTotalCash = 10000;
	const Money kNumPersons = 9;
	const Money kPerPerson = kTotalCash / kNumPersons;

	Bank bank(kTotalCash);
	Town town(bank);

	town.AddPerson("Mr. Burns", kPerPerson + kTotalCash % kNumPersons).SetBehavior(BurnsBehavior);
	town.AddPerson("Homer", kPerPerson).SetBehavior(HomerBehavior);
	town.AddPerson("Marge", kPerPerson).SetBehavior(MargeBehavior);
	town.AddPerson("Bart", kPerPerson).SetBehavior(BartBehavior);
	town.AddPerson("Lisa", kPerPerson).SetBehavior(LisaBehavior);
	town.AddPerson("Apu", kPerPerson).SetBehavior(ApuBehavior);
	town.AddPerson("Nelson", kPerPerson).SetBehavior(NelsonBehavior);
	town.AddPerson("Snake", kPerPerson).SetBehavior(SnakeBehavior);
	town.AddPerson("Smithers", kPerPerson).SetBehavior(SmithersBehavior);

	town.GetPerson("Mr. Burns").OpenBankAccount();
	town.GetPerson("Mr. Burns").DepositAll();
	town.GetPerson("Homer").OpenBankAccount();
	town.GetPerson("Homer").DepositAll();
	town.GetPerson("Marge").OpenBankAccount();
	town.GetPerson("Marge").DepositAll();
	town.GetPerson("Apu").OpenBankAccount();
	town.GetPerson("Apu").DepositAll();
	town.GetPerson("Snake").OpenBankAccount();
	town.GetPerson("Snake").DepositAll();
	town.GetPerson("Smithers").OpenBankAccount();
	town.GetPerson("Smithers").DepositAll();

	PrintState("Init state", bank, town, kTotalCash);

	for (int i = 1; i <= numIterations; ++i)
	{
		std::cout << std::endl
				  << "iter " << i << std::endl;
		town.StepAll();
	}

	PrintState("Final state", bank, town, kTotalCash);
	CheckConsistency(bank, town, kTotalCash);
}