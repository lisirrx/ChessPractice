//CHESSBOARD.h  -- stock class interface
#pragma once
#include <string>

#ifndef CHESSBOARD
#define CHESSBOARD CB
#define BLANK 0
#define WIDTH 15

class Board {
private:
	unsigned long long status[WIDTH];
	unsigned short black_cnt;
	unsigned short white_cnt;
	unsigned short steps_cnt;
    bool turn_mrk;//回合标记。
	void cnt_pieces();
	void update(const unsigned short x,const unsigned short y);
public:
	Board();
	Board(const unsigned long long stat[], const bool first, const short step_now);
	~Board();
	void show_chessbrd() const;
	bool place_piece(const unsigned short x,const unsigned short y);
	void get_order(std::string &x) const;
};

#endif