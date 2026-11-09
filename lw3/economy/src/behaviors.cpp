#include "behaviors.h"
#include "town.h"
#include "logger.h"

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
		Log() << "[Mr. Burns] Paid salary " << kSalary << " to Homer";
	else
		Log() << "[Mr. Burns] Cannt pay Homer's salary";
	try
	{
		if (smithers.HasAccount() && bank.TrySendMoney(self.GetAccountId(), smithers.GetAccountId(), kSalary))
			Log() << "[Mr. Burns] Paid salary " << kSalary << " to Smither";
		else
			Log() << "[Mr. Burns] Cannt pay Smither's salary";
	}
	catch (const BankOperationError&)
	{
		Log() << "[Mr. Burns] Smithers' account is closed right now";
	}
};

Behavior HomerBehavior = [](Person& self, Town& town) {
	Person& marge = town.GetPerson("Marge");
	Person& burns = town.GetPerson("Mr. Burns");
	Person& bart = town.GetPerson("Bart");
	Person& lisa = town.GetPerson("Lisa");
	Bank& bank = self.GetBank();

	if (bank.TrySendMoney(self.GetAccountId(), marge.GetAccountId(), kMargeAllowance))
		Log() << "[Homer] Sent " << kMargeAllowance << " to Marge";
	else
		Log() << "[Homer] Cannt send money to Marge";

	if (bank.TrySendMoney(self.GetAccountId(), burns.GetAccountId(), kElectricityHomer))
		Log() << "[Homer] Paid " << kElectricityHomer << " for electricity";
	else
		Log() << "[Homer] Cannt pay electricity";

	if (self.TryWithdraw(kBartAllowance))
	{
		self.GiveCashTo(bart, kBartAllowance);
		Log() << "[Homer] Gave " << kBartAllowance << " cash to Bart";
	}
	else
		Log() << "[Homer] Cannt give cash to Bart";

	if (self.TryWithdraw(kLisaAllowance))
	{
		self.GiveCashTo(lisa, kLisaAllowance);
		Log() << "[Homer] Gave " << kLisaAllowance << " cash to Lisa";
	}
	else
		Log() << "[Homer] Cannt give cash to Lisa";
};

Behavior MargeBehavior = [](Person& self, Town& town) {
	Person& apu = town.GetPerson("Apu");
	Bank& bank = self.GetBank();

	if (bank.TrySendMoney(self.GetAccountId(), apu.GetAccountId(), kGroceryCost))
		Log() << "[Marge] Bought products for " << kGroceryCost;
	else
		Log() << "[Marge] Cannt buy products";
};

Behavior BartBehavior = [](Person& self, Town& town) {
	Person& apu = town.GetPerson("Apu");

	if (self.GiveCashTo(apu, kBartSpenging))
		Log() << "[Bart] Spent " << kBartSpenging << " cash at Apu's";
	else
		Log() << "[Bart] No cash to spend";
};

Behavior LisaBehavior = [](Person& self, Town& town) {
	Person& apu = town.GetPerson("Apu");

	if (self.GiveCashTo(apu, kLisaSpending))
		Log() << "[Lisa] Spent " << kLisaSpending << " cash at Apu's";
	else
		Log() << "[Lisa] No cash to spend";
};

Behavior ApuBehavior = [](Person& self, Town& town) {
	auto& burns = town.GetPerson("Mr. Burns");
	Bank& bank = self.GetBank();

	self.DepositAll();

	if (bank.TrySendMoney(self.GetAccountId(), burns.GetAccountId(), kElectricityApu))
		Log() << "[Apu] Paid " << kElectricityApu << " for electricity";
	else
		Log() << "[Apu] Cannt pay electricity";
};

Behavior NelsonBehavior = [turn = 0](Person& self, Town& town) mutable {
	auto& bart = town.GetPerson("Bart");
	auto& apu = town.GetPerson("Apu");

	++turn;

	if (turn % 2 == 0)
	{
		Money stolen = 20;
		if (bart.GiveCashTo(self, stolen))
			Log() << "[Nelson] Stole " << stolen << " cash from Bart";
		else
			Log() << "[Nelson] Bart has no cash to steal";
	}

	if (self.GiveCashTo(apu, kCigarettes))
		Log() << "[Nelson] Bought cigarettes for " << kCigarettes << " at Apu's";
	else
		Log() << "[Nelson] No cash for cigarettes";
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
	// 			Log() << "[Snake] Hacked Homer's account for " << kSnakeHack;
	// 		else
	// 			Log() << "[Snake] Hack fail - Homer is broke";
	// 	}
	// 	catch (const BankOperationError& e)
	// 	{
	// 		Log() << "[Snake] Hack failed: " << e.what();
	// 	}
	// }

	if (self.HasAccount() && apu.HasAccount())
	{
		if (bank.TrySendMoney(self.GetAccountId(), apu.GetAccountId(), kSnakeGrocery))
			Log() << "[Snake] Bought products for " << kSnakeGrocery << " at Apus Store";
		else
			Log() << "[Snake] Cannt buy products";
	}
};

Behavior SmithersBehavior = [turn = 0](Person& self, Town& town) mutable {
	auto& apu = town.GetPerson("Apu");
	Bank& bank = self.GetBank();

	++turn;

	if (turn % 5 == 0)
	{
		Log() << "[Smithers] Paranoia event - reopening account";
		self.CloseBankAccount();
		self.OpenBankAccount();
		self.DepositAll();
	}

	if (self.HasAccount() && apu.HasAccount())
	{
		if (bank.TrySendMoney(self.GetAccountId(), apu.GetAccountId(), kSmithersGrocery))
			Log() << "[Smithers] Bought products for " << kSmithersGrocery;
		else
			Log() << "[Smithers] Cannt buy products";
	}
};