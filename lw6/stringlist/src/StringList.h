#pragma once

#include "Node.h"
#include "OwnIterator.h"
#include <string>

class StringList
{

public:
	using Iterator = OwnIterator<Node, std::string>;
	using ConstIterator = OwnIterator<const Node, const std::string>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	StringList() noexcept;

	StringList(const StringList& other);
	StringList(StringList&& other);

	StringList& operator=(const StringList& other);
	StringList& operator=(StringList&& other);

	Iterator PushFront(const std::string& data);
	Iterator PushBack(const std::string& data);
	std::string& Front();
	std::string& Back();

	Iterator Insert(Iterator it, const std::string& data);
	Iterator Delete(Iterator it);

	bool IsEmpty() const;
	size_t Size() const;

	void Clear() noexcept;
	~StringList();

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator crbegin() const;
	ConstReverseIterator crend() const;

private:
	Node m_nodeController;
	size_t m_size;
};