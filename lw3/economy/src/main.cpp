#include "economy.h"
#include "logger.h"
#include <atomic>
#include <csignal>
#include <cstring>
#include <iostream>
#include <string>

std::atomic<bool> g_stop = false;

void OnCtrlC(int)
{
	g_stop = true;
}

int main(int argc, char* argv[])
{
	std::string mode;
	int seconds = 0;

	for (int i = 1; i < argc; ++i)
	{
		if (std::strcmp(argv[i], "--mode") == 0 && i + 1 < argc)
			mode = argv[++i];
		else if (std::strcmp(argv[i], "--seconds") == 0 && i + 1 < argc)
			seconds = std::atoi(argv[++i]);
		else if (std::strcmp(argv[i], "--quiet") == 0)
			g_quiet = true;
	}

	if ((mode != "single" && mode != "parallel") || seconds <= 0)
	{
		std::cerr << "Usage: bank --mode <single|parallel> --seconds <N> [--quiet]\n";
		return 1;
	}

	std::signal(SIGINT, OnCtrlC);
	RunEconomy(mode == "parallel", seconds, g_stop);

	return 0;
}
