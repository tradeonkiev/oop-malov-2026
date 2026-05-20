#include <string>

struct Node
{
	std::string data;
	Node* prev;
	Node* next;

	Node() noexcept;
	Node(const std::string& value);
	Node(const std::string& value, Node* p, Node* n);
	Node(Node&& other);
	Node& operator=(Node&& other);

	~Node();
};