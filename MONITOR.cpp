//MONITOR.cpp -- monitoring game process
#include "stdafx.h"

extern Board first;
extern bool game_still_on;
extern std::string cur_order;

void game_process() {
	first.show_chessbrd();
	first.get_order(cur_order);
	std::cout << cur_order << " please place your piece:";
	unsigned short x, y;
	std::cin >> x >> y;
	if (!first.place_piece(x, y)) {
		std::cout << "Placing error.Please place your piece again." << std::endl;
	}
	else {
		std::cout << "Continue?(y/n)" << std::endl;
		char choose = 0;
		while (std::cin >> choose) {
			if (tolower(choose) == 'n') {
				std::cout << "Game Over." << cur_order << " failed." << std::endl;
				game_still_on = false;
				break;
			}
			else if (tolower(choose) == 'y') {
				break;
			}
			else {
				std::cout << "Input error.Please try again." << std::endl;
			}
		}
	}
}