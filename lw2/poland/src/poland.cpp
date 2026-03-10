#include "poland.h"
#include <sstream>
#include <stack>
#include <stdexcept>
#include <vector>

struct Frame
{
	char operation;
	std::vector<int> args;
};

static int ComputeFrame(const Frame& frame)
{
    if (frame.args.empty())
        throw std::invalid_argument("Operation must have at least one argument");

    int result = frame.args[0];
    for (size_t i = 1; i < frame.args.size(); ++i)
    {
        if (frame.operation == '+')
            result += frame.args[i];
        else
            result *= frame.args[i];
    }
    return result;
}

static void HandleOpenParen(std::istream& input, std::stack<Frame>& stack)
{
    char op;
    if (!(input >> op))
        throw std::invalid_argument("Expected operation after '('");
    if (op != '+' && op != '*')
        throw std::invalid_argument(std::string("Unknown operation: ") + op);

    stack.push({ op, {} });
}

static int HandleCloseParen(std::stack<Frame>& stack, bool& done)
{
    if (stack.empty())
        throw std::invalid_argument("Unexpected ')'");

    Frame frame = std::move(stack.top());
    stack.pop();

    int result = ComputeFrame(frame);

    if (stack.empty())
    {
        done = true;
        return result;
    }

    stack.top().args.push_back(result);
    return 0;
}

static void HandleNumber(std::istream& input, std::stack<Frame>& stack)
{
    input.unget();
    int number;
    if (!(input >> number))
        throw std::invalid_argument("Expected a number");

    if (stack.empty())
        throw std::invalid_argument("Number outside of expression");

    stack.top().args.push_back(number);
}

int EvaluateExpression(std::istream& input)
{
    std::stack<Frame> stack;
    char ch;

    while (input >> ch)
    {
        if (ch == '(')
        {
            HandleOpenParen(input, stack);
        }
        else if (ch == ')')
        {
            bool done = false;
            int result = HandleCloseParen(stack, done);
            if (done) return result;
        }
        else
        {
            HandleNumber(input, stack);
        }
    }

    throw std::invalid_argument("Unexpected end of input");
}

int EvaluateFromString(const std::string& str)
{
    std::istringstream iss(str);
    int result = EvaluateExpression(iss);

    char leftover;
    if (iss >> leftover)
        throw std::invalid_argument("Unexpected characters after expression");

    return result;
}