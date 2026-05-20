#include "StringList.h"
#include <iostream>
#include <string>

StringList::StringList() noexcept
	: m_size(0)
{
}

StringList::StringList(const StringList& other)
	: StringList()
{

	StringList temp;

	for (const std::string& str : other)
	{
		temp.PushBack(str);
	}

	*this = std::move(temp);
}

StringList::StringList(StringList&& other)
	: m_size(other.m_size)
	, m_nodeController(std::move(other.m_nodeController))
{
	other.m_size = 0;
}

StringList& StringList::operator=(const StringList& other)
{
	if (this == &other)
	{
		return *this;
	}

	StringList temp;
	for (const std::string str : other)
	{
		temp.PushBack(str);
	}

	return *this = std::move(temp);
}

StringList& StringList::operator=(StringList&& other)
{
	if (this == &other)
	{
		return *this;
	}

	Clear();
	m_nodeController = std::move(other.m_nodeController);
	m_size = other.m_size;
	other.m_size = 0;

	return *this;
}

StringList::Iterator StringList::PushBack(const std::string& data)
{
	return Insert(end(), data);
}

std::string& StringList::Front()
{
	return *begin();
}

std::string& StringList::Back()
{
	return *rbegin();
}

StringList::Iterator StringList::PushFront(const std::string& data)
{
	return Insert(begin(), data);
}

StringList::Iterator StringList::Insert(Iterator iter, const std::string& data)
{
	Node* itNode = iter.GetNode();
	Node* node = new Node(data, itNode->prev, itNode);
	m_size++;

	return node;
}

bool StringList::IsEmpty() const
{
	return !m_size;
}

size_t StringList::Size() const
{
	return m_size;
}

void StringList::Clear() noexcept
{
	Node* node = m_nodeController.next;
	while (node != &m_nodeController)
	{
		Node* next = node->next;
		delete node;
		node = next;
	}

	m_nodeController.prev = &m_nodeController;
	m_nodeController.next = &m_nodeController;
	m_size = 0;
}

StringList::~StringList()
{
	Clear();
}

StringList::Iterator StringList::Delete(Iterator it)
{
	if (it == end())
	{
		throw std::runtime_error("Invalid node");
	}

	Node* node = it.GetNode();
	Node* nextNode = node->next;

	--m_size;
	delete node;

	return nextNode;
}

StringList::Iterator StringList::begin()
{

	return m_nodeController.next;
}

StringList::Iterator StringList::end()
{
	return &m_nodeController;
}

StringList::ConstIterator StringList::begin() const
{
	return m_nodeController.next;
}

StringList::ConstIterator StringList::end() const
{
	return &m_nodeController;
}

StringList::ConstIterator StringList::cbegin() const
{
	return ConstIterator(begin());
}

StringList::ConstIterator StringList::cend() const
{
	return ConstIterator(end());
}

StringList::ReverseIterator StringList::rbegin()
{
	return ReverseIterator(end());
}

StringList::ReverseIterator StringList::rend()
{
	return ReverseIterator(begin());
}

StringList::ConstReverseIterator StringList::crbegin() const
{
	return ConstReverseIterator(end());
}

StringList::ConstReverseIterator StringList::crend() const
{
	return ConstReverseIterator(begin());
}
