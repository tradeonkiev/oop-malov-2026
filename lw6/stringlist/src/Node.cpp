#include "Node.h"
#include "string"

Node::Node() noexcept
{
	prev = this;
	next = this;
}

Node::Node(const std::string& str)
	: data(str) {};

Node::Node(const std::string& value, Node* p, Node* n)
	: data(value)
	, prev(p)
	, next(n)
{
	p->next = this;
	n->prev = this;
}

Node::Node(Node&& other)
	: prev(other.prev)
	, next(other.next)
{
	prev->next = this;
	next->prev = this;

	other.prev = &other;
	other.next = &other;
}

Node::~Node()
{
	prev->next = next;
	next->prev = prev;
}

Node& Node::operator=(Node&& other)
{
	prev = other.prev;
	next = other.next;

	prev->next = this;
	next->prev = this;

	other.prev = &other;
	other.next = &other;

	return *this;
}