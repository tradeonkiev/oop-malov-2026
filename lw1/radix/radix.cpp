#include "pch.h"

int CharToDigit(char ch);
char DigitToChar(int digit);
int StringToInt(const std::string& str, int radix, std::string& errorMessage);
std::string IntToString(int n, int radix, std::string& errorMessage);

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Usage: radix.exe <source notation> <destination notation> <value>" << std::endl;
		return 1;
	}

	std::string errorMessage;

	int sourceRadix = StringToInt(static_cast<std::string>(argv[1]), 10, errorMessage);
	if (!errorMessage.empty() || sourceRadix < 2 || sourceRadix > 36)
	{
		std::cout << "Invalid source notation: must be a number from 2 to 36" << std::endl;
		return 1;
	}

	int destRadix = StringToInt(static_cast<std::string>(argv[2]), 10, errorMessage);
	if (!errorMessage.empty() || destRadix < 2 || destRadix > 36)
	{
		std::cout << "Invalid destination notation: must be a number from 2 to 36" << std::endl;
		return 1;
	}

	std::string value = argv[3];

	int number = StringToInt(value, sourceRadix, errorMessage);
	if (!errorMessage.empty())
	{
		std::cout << errorMessage << std::endl;
		return 1;
	}

	std::string result = IntToString(number, destRadix, errorMessage);
	if (!errorMessage.empty())
	{
		std::cout << errorMessage << std::endl;
		return 1;
	}

	std::cout << result << std::endl;
	return 0;
}

int StringToInt(const std::string& str, int radix, std::string& errorMessage)
{
	errorMessage.clear();

	if (str.empty())
	{
		errorMessage = "Empty string is not a valid number";
		return 0;
	}

	if (radix < 2 || radix > 36)
	{
		errorMessage = "Radix must be in range from 2 to 36";
		return 0;
	}

	int startPos = 0;
	bool negative = false;

	if (str[0] == '-')
	{
		negative = true;
		startPos = 1;
	}
	else if (str[0] == '+')
	{
		startPos = 1;
	}

	if (startPos >= static_cast<int>(str.size()))
	{
		errorMessage = "Expected digits after sign character";
		return 0;
	}

	int result = 0;

	for (int i = startPos; i < static_cast<int>(str.size()); i++)
	{
		int digit = CharToDigit(str[i]);

		if (digit == -1)
		{
			errorMessage = "Invalid character '" + std::string(1, str[i]) + "' in number";
			return 0;
		}

		if (digit >= radix)
		{
			errorMessage = "Digit " + std::string(1, str[i]) + " is out of range for base " + std::to_string(radix);
			return 0;
		}

		if (result < (INT_MIN + digit) / radix)
		{
			errorMessage = "Overflow: number is too large to convert";
			return 0;
		}

		result = result * radix - digit;
	}

	if (!negative)
	{
		if (result < -INT_MAX)
		{
			errorMessage = "Overflow: number is too large to convert";
			return 0;
		}
		result = -result;
	}

	return result;
}

std::string IntToString(int n, int radix, std::string& errorMessage)
{
	errorMessage.clear();

	if (radix < 2 || radix > 36)
	{
		errorMessage = "Radix must be in range from 2 to 36";
		return "";
	}

	if (n == 0)
	{
		return "0";
	}

	bool negative = n < 0;
	std::string result;

	if (!negative)
	{
		n = -n;
	}

	while (n != 0)
	{
		int remainder = -(n % radix);
		result += DigitToChar(remainder);
		n /= radix;
	}

	if (negative)
	{
		result += '-';
	}

	std::reverse(result.begin(), result.end());
	return result;
}

int CharToDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	ch = static_cast<char>(std::toupper(ch));
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A' + 10;
	return -1;
}

char DigitToChar(int digit)
{
	if (digit >= 0 && digit <= 9)
		return static_cast<char>('0' + digit);
	if (digit >= 10 && digit <= 35)
		return static_cast<char>('A' + digit - 10);
	return '#';
}
