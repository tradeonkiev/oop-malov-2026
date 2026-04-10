#pragma once

#include <map>
#include <stdexcept>
#include <string>

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : public std::runtime_error
{
public:
	using runtime_error::runtime_error;
};

class Bank
{
public:
	explicit Bank(Money cash);
	// TODO: разобраться с этим 
	Bank(const Bank&) = delete;
	Bank& operator=(const Bank&) = delete;

	void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
	[[nodiscard]] bool TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);

	[[nodiscard]] Money GetCash() const;
	Money GetAccountBalance(AccountId accountId) const;

	void WithdrawMoney(AccountId account, Money amount);
	[[nodiscard]] bool TryWithdrawMoney(AccountId account, Money amount);

	void DepositMoney(AccountId account, Money amount);

	[[nodiscard]] AccountId OpenAccount();
	[[nodiscard]] Money CloseAccount(AccountId accountId);

	Money GetTotalMoney() const;
	Money GetTotalAccountBalance() const;

private:
	Money cash_;
	Money initialCash_;
	std::map<AccountId, Money> accounts_;
	AccountId nextAccountId_ = 1;

	void ValidateAccount(AccountId id) const;
	void ValidatePositiveAmount(Money amount) const;
};