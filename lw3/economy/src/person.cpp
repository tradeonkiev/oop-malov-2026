#include "person.h"
#include "town.h"
#include <iostream>

Person::Person(const std::string& name, Bank& bank, Money pocketCash, Behavior behavior)
	: name_(name)
	, bank_(bank)
	, pocketCash_(pocketCash)
	, behavior_(behavior)
{
}

void Person::Step(Town& town)
{
	if (behavior_)
		behavior_(*this, town);
}

AccountId Person::OpenBankAccount()
{
	if (!hasAccount_)
	{
		accountId_ = bank_.OpenAccount();
		hasAccount_ = true;
		std::cout << "[" << name_ << "] open account, id: " << accountId_ << std::endl;
	}
	return accountId_;
}

void Person::CloseBankAccount()
{
	if (hasAccount_)
	{
		pocketCash_ += bank_.CloseAccount(accountId_);
		hasAccount_ = false;
		std::cout << "[" << name_ << "] close account, id: " << accountId_ << std::endl;
	}
}

void Person::Deposit(Money amount)
{
	if (hasAccount_ && amount <= pocketCash_ && amount > 0)
	{
		try
		{
			bank_.DepositMoney(accountId_, amount);
			std::cout << "[" << name_ << "] deposited " << amount << "\n";
			pocketCash_ -= amount;
		}
		catch (const BankOperationError& e)
		{
			std::cout << "[" << name_ << "] failed to deposit: " << e.what() << "\n";
		}
	}
}

void Person::DepositAll()
{
	Deposit(pocketCash_);
}

bool Person::TryWithdraw(Money amount)
{
	if (!hasAccount_)
	{
		return false;
	}

	if (bank_.TryWithdrawMoney(accountId_, amount))
	{
		pocketCash_ += amount;
		return true;
	}

	return false;
}

bool Person::GiveCashTo(Person& other, Money amount)
{
	if (pocketCash_ < amount)
	{
		return false;
	}

	pocketCash_ -= amount;
	other.pocketCash_ += amount;
	return true;
}

void Person::ReceiveCash(Money amount)
{
	pocketCash_ += amount;
}

const std::string& Person::GetName() const { return name_; }
Money Person::GetPocketCash() const { return pocketCash_; }
AccountId Person::GetAccountId() const { return accountId_; }
bool Person::HasAccount() const { return hasAccount_; }
Bank& Person::GetBank() const { return bank_; }

void Person::SetBehavior(Behavior b) { behavior_ = b; }