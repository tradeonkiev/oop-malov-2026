#pragma once

#include <iostream>
#include <mutex>
#include <sstream>

inline bool g_quiet = false;

class Log
{
public:
	~Log()
	{
		if (g_quiet)
			return;
		static std::mutex outputMutex;
		std::lock_guard lock(outputMutex);
		std::cout << stream_.str() << '\n';
	}

	template <typename T>
	Log& operator<<(const T& value)
	{
		if (!g_quiet)
			stream_ << value;
		return *this;
	}

private:
	std::ostringstream stream_;
};
