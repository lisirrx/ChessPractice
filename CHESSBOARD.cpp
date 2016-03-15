//CHESSBOARD.cpp -- implementing the Board class
#include "stdafx.h"

Board::Board() {
	std::cout << "New Chessboard Constructed!" << std::endl << std::endl;
	std::memset(status, BLANK, sizeof(status));
	steps_cnt = 0;
	black_cnt = 0;
	white_cnt = 0;
	turn_mrk = true;
}

Board::Board(const unsigned long long stat[], const bool first, const short step_now) {
	std::memcpy(status, stat, sizeof(stat));
	steps_cnt = step_now;
	turn_mrk = first;
	update(0,0);
}

Board::~Board() {
	std::cout << "Chessboard Destructed!" << std::endl << std::endl;
}

void Board::show_chessbrd() const {
	std::cout << std::endl;
	for (short i = 0; i < WIDTH; i++) {
		unsigned long long detect_right = 1 << (WIDTH - 1);
		unsigned long long detect_left = 1 << ((WIDTH << 1) - 1);
		for (short row = 1; row <= WIDTH; row++) {
			if (row > 1) {
				detect_right >>= 1;
				detect_left >>= 1;
			}
			if (((detect_right&status[i]) == detect_right) && ((detect_left&status[i]) == detect_left)) {
				std::cout << "B";
			}
			else if(((detect_right&status[i]) == detect_right) && ((detect_left&status[i]) != detect_left)) {
				std::cout << "W";
			}
			else {
				std::cout << "+";
			}
		}
		std::cout << std::endl;
	}

	std::cout << black_cnt+white_cnt << " Pieces on board:" << std::endl
		<< "Black:" << black_cnt << std::endl
		<< "White:" << white_cnt << std::endl;
	std::cout << "At step " << (steps_cnt + 1)
		<< ((turn_mrk & 1) == 1 ? " Black" : " White")
		<< " goes" << std::endl;
}

void Board::cnt_pieces() {
	black_cnt = 0;
	white_cnt = 0;
	for (short i = 0; i < WIDTH; i++) {
		unsigned long long detect_right = 1 << (WIDTH - 1);
		unsigned long long detect_left = 1 << ((WIDTH << 1) - 1);
		for (short row = 1; row <= WIDTH; row++) {
			if (row > 1) {
				detect_right >>= 1;
				detect_left >>= 1;
			}
			if (((detect_right&status[i]) == detect_right) && ((detect_left&status[i]) == detect_left)) {
				black_cnt++;
			}
			else if (((detect_right&status[i]) == detect_right) && ((detect_left&status[i]) != detect_left)) {
				white_cnt++;
			}
		}
	}
}

void Board::update(const unsigned short x,const unsigned short y) {
	if ((x > 0 && x <= WIDTH) && (y > 0 && y <= WIDTH)) {
		unsigned long long detect_right = 1 << (WIDTH - y);
		unsigned long long detect_left = 1 << ((WIDTH << 1) - y);
		detect_left = (turn_mrk == 0 ? 0 : detect_left);
		status[x - 1] |= detect_right;
		status[x - 1] |= detect_left;
		turn_mrk ^= 1;
		steps_cnt++;
	}

	//check if pieces need taking
	//if so,take them off the board

	cnt_pieces();
	show_chessbrd();
}

bool Board::place_piece(const unsigned short x, const unsigned short y) {
	if ((x <= 0 || x > WIDTH) || (y <= 0 || y > WIDTH)) {
		std::cerr << "The piece is placed out of the board!" << std::endl;
		return false;
	}
	unsigned long long detect_right = 1 << (WIDTH - y);
	unsigned long long detect_left = 1 << ((WIDTH << 1) - y);
	if (((detect_right&status[x - 1]) != detect_right) && ((detect_left&status[x - 1]) != detect_left)) {
		update(x,y);
		return true;
	}
	else {
		std::cerr << "The spot is already occupied!" << std::endl;
		return false;
	}
}

void Board::get_order(std::string &x) const {
	if (turn_mrk) {
		x="Black";
	}
	else {
		x="White";
	}
}