#include "bank.h"

Bank::Bank(Money cash)
    : cash_(cash)
    , initialCash_(cash)
{
    if (cash < 0)
    {
        throw BankOperationError("Cannt init bank with negative cash");
    }
}

void Bank::ValidateAccount(AccountId id) const
{
    if (accounts_.find(id) == accounts_.end())
    {
        throw BankOperationError("Account " + std::to_string(id) + " does not exist");
    }
}

void Bank::ValidatePositiveAmount(Money amount) const
{
    if (amount < 0)
    {
        throw std::out_of_range("Amount cannt be negative: " + std::to_string(amount));
    }
}

Money Bank::GetCash() const
{
    return cash_;
}

Money Bank::GetAccountBalance(AccountId accountId) const
{
    ValidateAccount(accountId);
    return accounts_.at(accountId);
}

AccountId Bank::OpenAccount()
{
    AccountId id = nextAccountId_++;
    accounts_[id] = 0;
    return id;
}

Money Bank::CloseAccount(AccountId accountId)
{
    ValidateAccount(accountId);
    Money balance = accounts_.at(accountId);
    accounts_.erase(accountId);
    cash_ += balance;
    return balance;
}

void Bank::DepositMoney(AccountId account, Money amount)
{
    ValidatePositiveAmount(amount);
    ValidateAccount(account);

    if (amount > cash_)
    {
        throw BankOperationError("Not enough cash in circulation to deposit " + std::to_string(amount));
    }

    cash_ -= amount;
    accounts_[account] += amount;
}

void Bank::WithdrawMoney(AccountId account, Money amount)
{
    ValidatePositiveAmount(amount);
    ValidateAccount(account);

    if (accounts_[account] < amount)
    {
        throw BankOperationError("Not enough money on account " + std::to_string(account));
    }

    accounts_[account] -= amount;
    cash_ += amount;
}

bool Bank::TryWithdrawMoney(AccountId account, Money amount)
{
    ValidatePositiveAmount(amount);
    ValidateAccount(account);

    if (accounts_[account] < amount)
    {
        return false;
    }

    accounts_[account] -= amount;
    cash_ += amount;
    return true;
}

void Bank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
    ValidatePositiveAmount(amount);
    ValidateAccount(srcAccountId);
    ValidateAccount(dstAccountId);

    if (accounts_[srcAccountId] < amount)
    {
        throw BankOperationError("Not enough money on source account " + std::to_string(srcAccountId));
    }

    Money srcOld = accounts_[srcAccountId];
    Money dstOld = accounts_[dstAccountId];

    try
    {
        accounts_[srcAccountId] -= amount;
        accounts_[dstAccountId] += amount;
    }
    catch (...)
    {
        accounts_[srcAccountId] = srcOld;
        accounts_[dstAccountId] = dstOld;
        throw;
    }
}

bool Bank::TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
    ValidatePositiveAmount(amount);
    ValidateAccount(srcAccountId);
    ValidateAccount(dstAccountId);

    if (accounts_[srcAccountId] < amount)
    {
        return false;
    }

    Money srcOld = accounts_[srcAccountId];
    Money dstOld = accounts_[dstAccountId];

    try
    {
        accounts_[srcAccountId] -= amount;
        accounts_[dstAccountId] += amount;
    }
    catch (...)
    {
        accounts_[srcAccountId] = srcOld;
        accounts_[dstAccountId] = dstOld;
        throw;
    }

    return true;
}

Money Bank::GetTotalMoney() const
{
    Money total = cash_;
    for (const auto& [id, balance] : accounts_)
    {
        total += balance;
    }
    return total;
}

Money Bank::GetTotalAccountBalance() const
{
    Money total = 0;
    for (const auto& [id, balance] : accounts_)
    {
        total += balance;
    }
    return total;
}