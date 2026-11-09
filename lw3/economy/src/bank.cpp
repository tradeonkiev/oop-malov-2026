#include "bank.h"

Bank::Bank(Money cash)
    : cash_(cash)
    , initialCash_(cash)
{
    if (cash < 0)
    {
        throw std::out_of_range("Cannt init bank with negative cash");
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
    operationsCount_++;
    std::lock_guard lock(m_mutex);
    return cash_;
}

Money Bank::GetAccountBalance(AccountId accountId) const
{
    operationsCount_++;
    std::lock_guard lock(m_mutex);
    ValidateAccount(accountId);
    return accounts_.at(accountId);
}

AccountId Bank::OpenAccount()
{
    operationsCount_++;
    std::lock_guard lock(m_mutex);
    AccountId id = nextAccountId_++;
    accounts_[id] = 0;
    return id;
}

Money Bank::CloseAccount(AccountId accountId)
{
    operationsCount_++;
    std::lock_guard lock(m_mutex);
    ValidateAccount(accountId);
    Money balance = accounts_.at(accountId);
    accounts_.erase(accountId);
    cash_ += balance;
    return balance;
}

void Bank::DepositMoney(AccountId account, Money amount)
{
    operationsCount_++;
    std::lock_guard lock(m_mutex);
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
    operationsCount_++;
    std::lock_guard lock(m_mutex);
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
    operationsCount_++;
    std::lock_guard lock(m_mutex);
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
    operationsCount_++;
    std::lock_guard lock(m_mutex);
    ValidatePositiveAmount(amount);
    ValidateAccount(srcAccountId);
    ValidateAccount(dstAccountId);

    if (accounts_[srcAccountId] < amount)
    {
        throw BankOperationError("Not enough money on source account " + std::to_string(srcAccountId));
    }

    accounts_[srcAccountId] -= amount;
    accounts_[dstAccountId] += amount;
}

bool Bank::TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
    operationsCount_++;
    std::lock_guard lock(m_mutex);
    ValidatePositiveAmount(amount);
    ValidateAccount(srcAccountId);
    ValidateAccount(dstAccountId);

    if (accounts_[srcAccountId] < amount)
    {
        return false;
    }

    accounts_[srcAccountId] -= amount;
    accounts_[dstAccountId] += amount;

    return true;
}

Money Bank::GetTotalMoney() const
{
    operationsCount_++;
    std::lock_guard lock(m_mutex);
    Money total = cash_;
    for (const auto& [id, balance] : accounts_)
    {
        total += balance;
    }
    return total;
}

Money Bank::GetTotalAccountBalance() const
{
    operationsCount_++;
    std::lock_guard lock(m_mutex);
    Money total = 0;
    for (const auto& [id, balance] : accounts_)
    {
        total += balance;
    }
    return total;
}

unsigned long long Bank::GetOperationsCount() const
{
    return operationsCount_;
}
