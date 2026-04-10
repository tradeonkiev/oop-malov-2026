#pragma once

#include "bank.h"
#include <functional>
#include <string>

class Person;
class Town;
using Behavior = std::function<void(Person& self, Town& town)>;

class Person
{
public:
	explicit Person(const std::string& name, Bank& bank, Money pocketCash, Behavior behavior = nullptr);

	void Step(Town& town);
	AccountId OpenBankAccount();
	void CloseBankAccount();
	void Deposit(Money amount);
	void DepositAll();
	bool TryWithdraw(Money amount);
	bool GiveCashTo(Person& other, Money amount);
	void ReceiveCash(Money amount);

    const std::string& GetName() const;
	Money GetPocketCash() const;
	AccountId GetAccountId() const;
	bool HasAccount() const;
	Bank& GetBank() const;
	void SetBehavior(Behavior b);

private:
	std::string name_;
	Bank& bank_;
	Money pocketCash_;
	AccountId accountId_ = 0;
	bool hasAccount_ = false;
	Behavior behavior_;
};