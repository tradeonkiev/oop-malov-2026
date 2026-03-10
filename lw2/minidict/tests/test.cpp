#include "minidict.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(ToLower, Basic)
{
	EXPECT_EQ(ToLower("CaT"), "cat");
}

TEST(ToLower, AlreadyLower)
{
	EXPECT_EQ(ToLower("hello"), "hello");
}

TEST(ToLower, AllUpper)
{
	EXPECT_EQ(ToLower("HELLO"), "hello");
}

TEST(ToLower, Empty)
{
	EXPECT_EQ(ToLower(""), "");
}

TEST(JoinStrings, Multiple)
{
	EXPECT_EQ(JoinStrings({ "a", "b", "c" }, ", "), "a, b, c");
}

TEST(JoinStrings, Single)
{
	EXPECT_EQ(JoinStrings({ "hello" }, ", "), "hello");
}

TEST(JoinStrings, Empty)
{
	EXPECT_EQ(JoinStrings({}, ", "), "");
}

TEST(LoadDictionary, LoadsPairs)
{
	std::istringstream input("cat\nкошка\ndog\nсобака\n");
	Dictionary dict;
	LoadDictionary(input, dict);
	EXPECT_EQ(dict.size(), 2);
	EXPECT_EQ(dict["cat"][0], "кошка");
	EXPECT_EQ(dict["dog"][0], "собака");
}

TEST(LoadDictionary, SkipsEmpty)
{
	std::istringstream input("cat\n\n");
	Dictionary dict;
	LoadDictionary(input, dict);
	EXPECT_TRUE(dict.empty());
}

TEST(LoadDictionary, NoDuplicates)
{
	std::istringstream input("cat\nкошка\ncat\nкошка\n");
	Dictionary dict;
	LoadDictionary(input, dict);
	EXPECT_EQ(dict["cat"].size(), 1);
}

TEST(LoadDictionary, MultipleTranslations)
{
	std::istringstream input("cat\nкошка\ncat\nкот\n");
	Dictionary dict;
	LoadDictionary(input, dict);
	EXPECT_EQ(dict["cat"].size(), 2);
	EXPECT_EQ(dict["cat"][0], "кошка");
	EXPECT_EQ(dict["cat"][1], "кот");
}

TEST(LoadDictionary, CaseInsensitive)
{
	std::istringstream input("Cat\nкошка\nCAT\nкот\n");
	Dictionary dict;
	LoadDictionary(input, dict);
	EXPECT_EQ(dict["cat"].size(), 2);
}

TEST(LoadDictionary, EmptyInput)
{
	std::istringstream input("");
	Dictionary dict;
	LoadDictionary(input, dict);
	EXPECT_TRUE(dict.empty());
}

TEST(SaveDictionary, SavesAll)
{
	Dictionary dict;
	dict["cat"] = { "кошка", "кот" };
	dict["dog"] = { "собака" };
	std::ostringstream output;
	SaveDictionary(output, dict);
	EXPECT_EQ(output.str(), "cat\nкошка\ncat\nкот\ndog\nсобака\n");
}

TEST(SaveDictionary, EmptyDict)
{
	Dictionary dict;
	std::ostringstream output;
	SaveDictionary(output, dict);
	EXPECT_EQ(output.str(), "");
}

TEST(LookupWord, Found)
{
	Dictionary dict;
	dict["cat"] = { "кошка" };
	EXPECT_EQ(LookupWord(dict, "cat"), "кошка");
}

TEST(LookupWord, FoundMultiple)
{
	Dictionary dict;
	dict["cat"] = { "кошка", "кот" };
	EXPECT_EQ(LookupWord(dict, "cat"), "кошка, кот");
}

TEST(LookupWord, CaseInsensitive)
{
	Dictionary dict;
	dict["cat"] = { "кошка" };
	EXPECT_EQ(LookupWord(dict, "CaT"), "кошка");
}

TEST(LookupWord, NotFound)
{
	Dictionary dict;
	EXPECT_EQ(LookupWord(dict, "cat"), "");
}

TEST(ReverseLookup, Found)
{
	Dictionary dict;
	dict["cat"] = { "кошка" };
	EXPECT_EQ(ReverseLookup(dict, "кошка"), "cat");
}

TEST(ReverseLookup, MultipleMatches)
{
	Dictionary dict;
	dict["cat"] = { "кошка" };
	dict["kitty"] = { "кошка" };
	auto result = ReverseLookup(dict, "кошка");
	EXPECT_TRUE(result.find("cat") != std::string::npos);
	EXPECT_TRUE(result.find("kitty") != std::string::npos);
}

TEST(ReverseLookup, CaseInsensitive)
{
	Dictionary dict;
	dict["cat"] = { "koshka" };
	EXPECT_EQ(ReverseLookup(dict, "koshka"), "cat");
}

TEST(ReverseLookup, NotFound)
{
	Dictionary dict;
	dict["cat"] = { "кошка" };
	EXPECT_EQ(ReverseLookup(dict, "собака"), "");
}

TEST(Roundtrip, SaveAndLoad)
{
	Dictionary original;
	original["cat"] = { "koshka", "kot" };
	original["dog"] = { "sobaka" };

	std::stringstream stream;
	SaveDictionary(stream, original);

	Dictionary loaded;
	LoadDictionary(stream, loaded);

	EXPECT_EQ(loaded, original);
}