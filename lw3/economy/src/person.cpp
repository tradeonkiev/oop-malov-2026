#include "person.h"
#include "town.h"
#include "logger.h"

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
		Log() << "[" << name_ << "] open account, id: " << accountId_;
	}
	return accountId_;
}

void Person::CloseBankAccount()
{
	if (hasAccount_)
	{
		hasAccount_ = false;
		ReceiveCash(bank_.CloseAccount(accountId_));
		Log() << "[" << name_ << "] close account, id: " << accountId_;
	}
}

void Person::Deposit(Money amount)
{
	if (hasAccount_ && amount > 0 && TakeCash(amount))
	{
		try
		{
			bank_.DepositMoney(accountId_, amount);
			Log() << "[" << name_ << "] deposited " << amount;
		}
		catch (const BankOperationError& e)
		{
			ReceiveCash(amount);
			Log() << "[" << name_ << "] failed to deposit: " << e.what();
		}
	}
}

void Person::DepositAll()
{
	Deposit(GetPocketCash());
}

bool Person::TryWithdraw(Money amount)
{
	if (!hasAccount_)
	{
		return false;
	}

	if (bank_.TryWithdrawMoney(accountId_, amount))
	{
		ReceiveCash(amount);
		return true;
	}

	return false;
}

bool Person::GiveCashTo(Person& other, Money amount)
{
	if (!TakeCash(amount))
	{
		return false;
	}

	other.ReceiveCash(amount);
	return true;
}

void Person::ReceiveCash(Money amount)
{
	std::lock_guard lock(walletMutex_);
	pocketCash_ += amount;
}

bool Person::TakeCash(Money amount)
{
	std::lock_guard lock(walletMutex_);
	if (pocketCash_ < amount)
	{
		return false;
	}
	pocketCash_ -= amount;
	return true;
}

const std::string& Person::GetName() const { return name_; }
Money Person::GetPocketCash() const
{
	std::lock_guard lock(walletMutex_); // зачем он мне нужен можно ли без него
	return pocketCash_;
}
AccountId Person::GetAccountId() const { return accountId_; }
bool Person::HasAccount() const { return hasAccount_; }
Bank& Person::GetBank() const { return bank_; }

void Person::SetBehavior(Behavior b) { behavior_ = b; }