#include "behaviors.h"
#include "town.h"
#include <iostream>
#include <random>

const Money kSalary = 150;
const Money kMargeAllowance = 80;
const Money kElectricityHomer = 30;
const Money kBartAllowance = 15;
const Money kLisaAllowance = 15;
const Money kGroceryCost = 60;
const Money kBartSpenging = 10;
const Money kLisaSpending = 10;
const Money kElectricityApu = 40;
const Money kCigarettes = 8;
const Money kSnakeHack = 50;
const Money kSnakeGrocery = 30;
const Money kSmithersGrocery = 40;

Behavior BurnsBehavior = [](Person& self, Town& town) {
	auto& homer = town.GetPerson("Homer");
	auto& smithers = town.GetPerson("Smithers");
	Bank& bank = self.GetBank();

	if (bank.TrySendMoney(self.GetAccountId(), homer.GetAccountId(), kSalary))
		std::cout << "[Mr. Burns] Paid salary " << kSalary << " to Homer" << std::endl;
	else
		std::cout << "[Mr. Burns] Cannt pay Homer's salary" << std::endl;

	if (smithers.HasAccount() && bank.TrySendMoney(self.GetAccountId(), smithers.GetAccountId(), kSalary))
	{
		std::cout << "[Mr. Burns] Paid salary " << kSalary << " to Smither" << std::endl;
	}
	else
	{
		std::cout << "[Mr. Burns] Cannt pay Smither's salary" << std::endl;
	}
};

Behavior HomerBehavior = [](Person& self, Town& town) {
	Person& marge = town.GetPerson("Marge");
	Person& burns = town.GetPerson("Mr. Burns");
	Person& bart = town.GetPerson("Bart");
	Person& lisa = town.GetPerson("Lisa");
	Bank& bank = self.GetBank();

	if (bank.TrySendMoney(self.GetAccountId(), marge.GetAccountId(), kMargeAllowance))
		std::cout << "[Homer] Sent " << kMargeAllowance << " to Marge" << std::endl;
	else
		std::cout << "[Homer] Cannt send money to Marge" << std::endl;

	if (bank.TrySendMoney(self.GetAccountId(), burns.GetAccountId(), kElectricityHomer))
		std::cout << "[Homer] Paid " << kElectricityHomer << " for electricity" << std::endl;
	else
		std::cout << "[Homer] Cannt pay electricity" << std::endl;

	if (self.TryWithdraw(kBartAllowance))
	{
		self.GiveCashTo(bart, kBartAllowance);
		std::cout << "[Homer] Gave " << kBartAllowance << " cash to Bart" << std::endl;
	}
	else
		std::cout << "[Homer] Cannt give cash to Bart" << std::endl;

	if (self.TryWithdraw(kLisaAllowance))
	{
		self.GiveCashTo(lisa, kLisaAllowance);
		std::cout << "[Homer] Gave " << kLisaAllowance << " cash to Lisa" << std::endl;
	}
	else
		std::cout << "[Homer] Cannt give cash to Lisa" << std::endl;
};

Behavior MargeBehavior = [](Person& self, Town& town) {
	Person& apu = town.GetPerson("Apu");
	Bank& bank = self.GetBank();

	if (bank.TrySendMoney(self.GetAccountId(), apu.GetAccountId(), kGroceryCost))
		std::cout << "[Marge] Bought products for " << kGroceryCost << std::endl;
	else
		std::cout << "[Marge] Cannt buy products" << std::endl;
};

Behavior BartBehavior = [](Person& self, Town& town) {
	Person& apu = town.GetPerson("Apu");

	if (self.GiveCashTo(apu, kBartSpenging))
		std::cout << "[Bart] Spent " << kBartSpenging << " cash at Apu's" << std::endl;
	else
		std::cout << "[Bart] No cash to spend" << std::endl;
};

Behavior LisaBehavior = [](Person& self, Town& town) {
	Person& apu = town.GetPerson("Apu");

	if (self.GiveCashTo(apu, kLisaSpending))
		std::cout << "[Lisa] Spent " << kLisaSpending << " cash at Apu's" << std::endl;
	else
		std::cout << "[Lisa] No cash to spend" << std::endl;
};

Behavior ApuBehavior = [](Person& self, Town& town) {
	auto& burns = town.GetPerson("Mr. Burns");
	Bank& bank = self.GetBank();

	self.DepositAll();

	if (bank.TrySendMoney(self.GetAccountId(), burns.GetAccountId(), kElectricityApu))
		std::cout << "[Apu] Paid " << kElectricityApu << " for electricity" << std::endl;
	else
		std::cout << "[Apu] Cannt pay electricity" << std::endl;
};

Behavior NelsonBehavior = [turn = 0](Person& self, Town& town) mutable {
	auto& bart = town.GetPerson("Bart");
	auto& apu = town.GetPerson("Apu");

	++turn;

	if (turn % 2 == 0)
	{
		Money stolen = 20;
		if (bart.GiveCashTo(self, stolen))
			std::cout << "[Nelson] Stole " << stolen << " cash from Bart" << std::endl;
		else
			std::cout << "[Nelson] Bart has no cash to steal" << std::endl;
	}

	if (self.GiveCashTo(apu, kCigarettes))
		std::cout << "[Nelson] Bought cigarettes for " << kCigarettes << " at Apu's" << std::endl;
	else
		std::cout << "[Nelson] No cash for cigarettes" << std::endl;
};

Behavior SnakeBehavior = [turn = 0](Person& self, Town& town) mutable {
	auto& homer = town.GetPerson("Homer");
	auto& apu = town.GetPerson("Apu");
	Bank& bank = self.GetBank();

	++turn;

	// if (turn % 4 == 0)
	// {
	// 	try
	// 	{
	// 		if (bank.TrySendMoney(homer.GetAccountId(), self.GetAccountId(), kSnakeHack))
	// 			std::cout << "[Snake] Hacked Homer's account for " << kSnakeHack << std::endl;
	// 		else
	// 			std::cout << "[Snake] Hack fail - Homer is broke" << std::endl;
	// 	}
	// 	catch (const BankOperationError& e)
	// 	{
	// 		std::cout << "[Snake] Hack failed: " << e.what() << std::endl;
	// 	}
	// }

	if (self.HasAccount() && apu.HasAccount())
	{
		if (bank.TrySendMoney(self.GetAccountId(), apu.GetAccountId(), kSnakeGrocery))
			std::cout << "[Snake] Bought products for " << kSnakeGrocery << " at Apus Store" << std::endl;
		else
			std::cout << "[Snake] Cannt buy products" << std::endl;
	}
};

Behavior SmithersBehavior = [turn = 0](Person& self, Town& town) mutable {
	auto& apu = town.GetPerson("Apu");
	Bank& bank = self.GetBank();

	++turn;

	if (turn % 5 == 0)
	{
		std::cout << "[Smithers] Paranoia event - reopening account" << std::endl;
		self.CloseBankAccount();
		self.OpenBankAccount();
		self.DepositAll();
	}

	if (self.HasAccount() && apu.HasAccount())
	{
		if (bank.TrySendMoney(self.GetAccountId(), apu.GetAccountId(), kSmithersGrocery))
			std::cout << "[Smithers] Bought products for " << kSmithersGrocery << std::endl;
		else
			std::cout << "[Smithers] Cannt buy products" << std::endl;
	}
};