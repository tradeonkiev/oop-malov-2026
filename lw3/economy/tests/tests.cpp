#include "bank.h"
#include "behaviors.h"
#include "person.h"
#include "town.h"
#include <gtest/gtest.h>

TEST(Bank, ConstructorAndNegativeThrows)
{
	Bank bank(1000);
	EXPECT_EQ(bank.GetCash(), 1000);
	EXPECT_THROW(Bank(-1), BankOperationError);
}

TEST(Bank, OpenCloseAccount)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	EXPECT_EQ(bank.GetAccountBalance(id), 0);
	bank.DepositMoney(id, 400);
	Money returned = bank.CloseAccount(id);
	EXPECT_EQ(returned, 400);
	EXPECT_EQ(bank.GetCash(), 1000);
}

TEST(Bank, DepositAndWithdraw)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 500);
	EXPECT_EQ(bank.GetAccountBalance(id), 500);
	EXPECT_EQ(bank.GetCash(), 500);
	bank.WithdrawMoney(id, 200);
	EXPECT_EQ(bank.GetAccountBalance(id), 300);
	EXPECT_EQ(bank.GetCash(), 700);
}

TEST(Bank, DepositErrors)
{
	Bank bank(100);
	AccountId id = bank.OpenAccount();
	EXPECT_THROW(bank.DepositMoney(id, 200), BankOperationError);
	EXPECT_THROW(bank.DepositMoney(id, -1), std::out_of_range);
	EXPECT_THROW(bank.DepositMoney(999, 10), BankOperationError);
}

TEST(Bank, WithdrawErrors)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 100);
	EXPECT_THROW(bank.WithdrawMoney(id, 200), BankOperationError);
	EXPECT_THROW(bank.WithdrawMoney(id, -1), std::out_of_range);
	EXPECT_FALSE(bank.TryWithdrawMoney(id, 200));
	EXPECT_EQ(bank.GetAccountBalance(id), 100);
}

TEST(Bank, SendMoney)
{
	Bank bank(1000);
	AccountId a = bank.OpenAccount();
	AccountId b = bank.OpenAccount();
	bank.DepositMoney(a, 500);
	bank.SendMoney(a, b, 200);
	EXPECT_EQ(bank.GetAccountBalance(a), 300);
	EXPECT_EQ(bank.GetAccountBalance(b), 200);
	EXPECT_EQ(bank.GetCash(), 500);
}

TEST(Bank, SendMoneyErrors)
{
	Bank bank(1000);
	AccountId a = bank.OpenAccount();
	AccountId b = bank.OpenAccount();
	bank.DepositMoney(a, 100);
	EXPECT_THROW(bank.SendMoney(a, b, 200), BankOperationError);
	EXPECT_THROW(bank.SendMoney(a, b, -1), std::out_of_range);
	EXPECT_THROW(bank.SendMoney(a, 999, 10), BankOperationError);
	EXPECT_FALSE(bank.TrySendMoney(a, b, 200));
	EXPECT_EQ(bank.GetAccountBalance(a), 100);
}

TEST(Bank, TotalMoneyConserved)
{
	Bank bank(1000);
	AccountId a = bank.OpenAccount();
	AccountId b = bank.OpenAccount();
	bank.DepositMoney(a, 400);
	bank.SendMoney(a, b, 100);
	bank.WithdrawMoney(b, 50);
	Money cash = bank.CloseAccount(a);
	EXPECT_EQ(bank.GetTotalMoney(), 1000);
}

TEST(Person, BasicOperations)
{
	Bank bank(1000);
	Person p("Alice", bank, 500);
	EXPECT_EQ(p.GetPocketCash(), 500);
	EXPECT_FALSE(p.HasAccount());

	p.OpenBankAccount();
	EXPECT_TRUE(p.HasAccount());
	p.DepositAll();
	EXPECT_EQ(p.GetPocketCash(), 0);

	EXPECT_TRUE(p.TryWithdraw(200));
	EXPECT_EQ(p.GetPocketCash(), 200);
	EXPECT_FALSE(p.TryWithdraw(400));
}

TEST(Person, GiveCash)
{
	Bank bank(1000);
	Person a("A", bank, 100);
	Person b("B", bank, 50);
	EXPECT_TRUE(a.GiveCashTo(b, 30));
	EXPECT_EQ(a.GetPocketCash(), 70);
	EXPECT_EQ(b.GetPocketCash(), 80);
	EXPECT_FALSE(a.GiveCashTo(b, 200));
}

TEST(Town, AddGetAndOrder)
{
	Bank bank(1000);
	Town town(bank);
	town.AddPerson("First", 100);
	town.AddPerson("Second", 200);
	EXPECT_EQ(town.GetPerson("First").GetPocketCash(), 100);
	EXPECT_THROW(town.AddPerson("First", 50), std::invalid_argument);
	EXPECT_THROW(town.GetPerson("Nobody"), std::runtime_error);
	EXPECT_EQ(town.Everyone()[0]->GetName(), "First");
	EXPECT_EQ(town.Everyone()[1]->GetName(), "Second");
}

TEST(Behaviors, NelsonStealsEverySecondTurn)
{
	Bank bank(1000);
	Town town(bank);
	town.AddPerson("Bart", 200);
	town.AddPerson("Apu", 0);
	town.AddPerson("Nelson", 100).SetBehavior(NelsonBehavior);
	town.GetPerson("Apu").OpenBankAccount();

	town.GetPerson("Nelson").Step(town);
	EXPECT_EQ(town.GetPerson("Bart").GetPocketCash(), 200);

	town.GetPerson("Nelson").Step(town);
	EXPECT_EQ(town.GetPerson("Bart").GetPocketCash(), 180);
}

TEST(Behaviors, SnakeHacksEveryFourthTurn)
{
	Bank bank(2000);
	Town town(bank);
	town.AddPerson("Homer", 1000);
	town.AddPerson("Apu", 0);
	town.AddPerson("Snake", 500).SetBehavior(SnakeBehavior);
	town.GetPerson("Homer").OpenBankAccount();
	town.GetPerson("Homer").DepositAll();
	town.GetPerson("Apu").OpenBankAccount();
	town.GetPerson("Snake").OpenBankAccount();
	town.GetPerson("Snake").DepositAll();

	for (int i = 0; i < 3; ++i)
		town.GetPerson("Snake").Step(town);
	EXPECT_EQ(bank.GetAccountBalance(town.GetPerson("Homer").GetAccountId()), 1000);

	town.GetPerson("Snake").Step(town);
	EXPECT_EQ(bank.GetAccountBalance(town.GetPerson("Homer").GetAccountId()), 1000 - kSnakeHack);
}

TEST(Behaviors, SmithersReopensEveryFifthTurn)
{
	Bank bank(2000);
	Town town(bank);
	town.AddPerson("Apu", 0);
	town.AddPerson("Smithers", 500).SetBehavior(SmithersBehavior);
	town.GetPerson("Apu").OpenBankAccount();
	town.GetPerson("Smithers").OpenBankAccount();
	town.GetPerson("Smithers").DepositAll();

	AccountId oldId = town.GetPerson("Smithers").GetAccountId();
	town.GetPerson("Smithers").Step(town);
	town.GetPerson("Smithers").Step(town);
	town.GetPerson("Smithers").Step(town);
	town.GetPerson("Smithers").Step(town);
	EXPECT_EQ(town.GetPerson("Smithers").GetAccountId(), oldId);

	town.GetPerson("Smithers").Step(town);
	EXPECT_NE(town.GetPerson("Smithers").GetAccountId(), oldId);
}

TEST(Simulation, MoneyConserved50Iterations)
{
	const Money TOTAL = 10000;
	const int NUM = 9;
	const Money PER = TOTAL / NUM;

	Bank bank(TOTAL);
	Town town(bank);

	town.AddPerson("Mr. Burns", PER + TOTAL % NUM).SetBehavior(BurnsBehavior);
	town.AddPerson("Homer", PER).SetBehavior(HomerBehavior);
	town.AddPerson("Marge", PER).SetBehavior(MargeBehavior);
	town.AddPerson("Bart", PER).SetBehavior(BartBehavior);
	town.AddPerson("Lisa", PER).SetBehavior(LisaBehavior);
	town.AddPerson("Apu", PER).SetBehavior(ApuBehavior);
	town.AddPerson("Nelson", PER).SetBehavior(NelsonBehavior);
	town.AddPerson("Snake", PER).SetBehavior(SnakeBehavior);
	town.AddPerson("Smithers", PER).SetBehavior(SmithersBehavior);

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

	for (int i = 0; i < 50; ++i)
	{
		town.StepAll();

		Money totalPocket = 0;
		for (auto* p : town.Everyone())
			totalPocket += p->GetPocketCash();

		EXPECT_EQ(totalPocket, bank.GetCash()) << "Iter" << i + 1;
		EXPECT_EQ(bank.GetTotalMoney(), TOTAL) << "Iter" << i + 1;
	}
}