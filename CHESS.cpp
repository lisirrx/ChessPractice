// CHESS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

Board first;
bool game_still_on = true;
std::string cur_order;

int main()
{
	unsigned long long starter[WIDTH];
	std::memset(starter, 0, sizeof(starter));

	while (game_still_on) {
		game_process();
	}

	return 0;
}

