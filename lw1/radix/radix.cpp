#include "pch.h"

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

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	wasError = false;

	if (str.empty() || radix < 2 || radix > 36)
	{
		wasError = true;
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


	int result = 0;

	for (int i = startPos; i < str.size(); i++)
	{
		int digit = CharToDigit(str[i]);

		if (digit == -1 || digit >= radix)
		{
			wasError = true;
			return 0;
		}
		if (result < (INT_MIN + digit) / radix)
		{
			wasError = true;
			return 0;
		}

		result = result * radix - digit;
	}

	if (!negative)
	{
		if (result < -INT_MAX)
		{
			wasError = true;
			return 0;
		}
		result = -result;
	}

	return result;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	wasError = false;

	if (radix < 2 || radix > 36)
	{
		wasError = true;
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
  
  // TODO: разобраться что возращаетис бегин енд
	std::reverse(result.begin(), result.end());
	return result;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Usage: radix.exe <source notation> <destination notation> <value>" << std::endl;
		return 1;
	}


	bool wasError = false;
  // TODO: ловить ошибку
	int sourceRadix = StringToInt(static_cast<std::string>(argv[1]), 10, wasError);

	if (sourceRadix < 2 || sourceRadix > 36 || wasError)
	{
		std::cout << "Invalid source notation" << std::endl;
		return 1;
	}

	int destRadix = StringToInt(static_cast<std::string>(argv[2]), 10, wasError);
  // TODO: повторы
	if (destRadix < 2 || destRadix > 36)
	{
		std::cout << "Invalid destination notation" << std::endl;
		return 1;
	}
	std::string value = argv[3];

	int number = StringToInt(value, sourceRadix, wasError);
  // TODO: конкретизировать 
	if (wasError)
	{
		std::cout << "Invalid value for the given source notation" << std::endl;
		return 1;
	}

	std::string result = IntToString(number, destRadix, wasError);

	if (wasError)
	{
		std::cout << "Conversion error" << std::endl;
		return 1;
	}

	std::cout << result << std::endl;
	return 0;
}
