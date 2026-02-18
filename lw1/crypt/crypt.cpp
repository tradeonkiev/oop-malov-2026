#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

uint8_t MixBits(uint8_t byte);
uint8_t UnmixBits(uint8_t byte);
uint8_t EncryptByte(uint8_t byte, uint8_t key);
uint8_t DecryptByte(uint8_t byte, uint8_t key);

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Usage: crypt.exe <crypt | decrypt> <input file> <output file> <key>" << std::endl;
		return 1;
	}

	std::string mode = argv[1];
	if (mode != "crypt" && mode != "decrypt")
	{
		std::cout << "first arg must be \"crypt\" or \"decrypt\"" << std::endl;
		return 1;
	}

	std::string keyStr = argv[4];
	int key = 0;
	for (char ch : keyStr)
	{
		if (ch < '0' || ch > '9')
		{
			std::cout << "key must be in range 0-255" << std::endl;
			return 1;
		}
		key = key * 10 + (ch - '0');
	}
	if (key > 255)
	{
		std::cout << "key must be in range 0-255" << std::endl;
		return 1;
	}

	std::ifstream input(argv[2]);
	if (!input.is_open())
	{
		std::cout << "cant open input file \"" << argv[2] << "\"" << std::endl;
		return 1;
	}

	std::ofstream output(argv[3]);
	if (!output.is_open())
	{
		std::cout << "cant open output file \"" << argv[3] << "\"" << std::endl;
		return 1;
	}

	input >> std::noskipws;
	char byte;
	while (input >> byte)
	{
		uint8_t result;
		if (mode == "crypt")
		{
			result = EncryptByte(static_cast<uint8_t>(byte), static_cast<uint8_t>(key));
		}
		else
		{
			result = DecryptByte(static_cast<uint8_t>(byte), static_cast<uint8_t>(key));
		}
		output << static_cast<char>(result);
	}

	if (!input.eof())
	{
		std::cout << "failed to read input file" << std::endl;
		return 1;
	}

	if (output.fail())
	{
		std::cout << "failed to write output file" << std::endl;
		return 1;
	}

	return 0;
}

// Табла шифра
// 0 1 2 3 4 5 6 7
// 2 3 4 6 7 0 1 5

uint8_t EncryptByte(uint8_t byte, uint8_t key)
{
	return MixBits(byte ^ key);
}

uint8_t MixBits(uint8_t byte)
{
	uint8_t result = 0;
	result |= ((byte >> 7) & 1) << 5;
	result |= ((byte >> 6) & 1) << 1;
	result |= ((byte >> 5) & 1) << 0;
	result |= ((byte >> 4) & 1) << 7;
	result |= ((byte >> 3) & 1) << 6;
	result |= ((byte >> 2) & 1) << 4;
	result |= ((byte >> 1) & 1) << 3;
	result |= ((byte >> 0) & 1) << 2;
	return result;
}

uint8_t DecryptByte(uint8_t byte, uint8_t key)
{
	return UnmixBits(byte) ^ key;
}

uint8_t UnmixBits(uint8_t byte)
{
	uint8_t result = 0;
	result |= ((byte >> 5) & 1) << 7;
	result |= ((byte >> 1) & 1) << 6;
	result |= ((byte >> 0) & 1) << 5;
	result |= ((byte >> 7) & 1) << 4;
	result |= ((byte >> 6) & 1) << 3;
	result |= ((byte >> 4) & 1) << 2;
	result |= ((byte >> 3) & 1) << 1;
	result |= ((byte >> 2) & 1) << 0;
	return result;
}
