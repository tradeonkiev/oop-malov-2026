#pragma once

#include <atomic>

void RunEconomy(bool parallel, int seconds, const std::atomic<bool>& stop);
