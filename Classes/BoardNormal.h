#pragma once

#include"cocos2d.h"

#include "define.h"

class BoardNormal
{
//実際にオセロをする部分。ひっくり返したりターン制御したり。
public:
	BoardNormal();
	~BoardNormal();
	void reset();
	void resetMurora();
	void resetMega();
	void resetMoroi();
	bool TurnChange();
	bool CheckPass(BorW turn);
	BorW GetBoard(int x, int y);
	void SetBoard(int x, int y, BorW bw);
	BorW GetTurn();
	int GetBoardSize();
	int CountStone(BorW color);
	bool put(int x, int y, bool checkOnly = false, BorW turn = none);
	int Fall();
	void finish();
	BorW NotTurn(BorW turn);

	void Com1();
	void Com1Murora();
	void Com1Mega();
	void Com1moroi();
	void Com2();
	void Com2Murora();
	void Com2Mega();
	void Com2moroi();

private:
	BorW board[16][16];
	BorW turn;
	int boardsize = 7;
	int pass=0;

	int check(BorW board, int c, int turn);
};
