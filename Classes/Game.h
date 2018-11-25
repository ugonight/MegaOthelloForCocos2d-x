#pragma once

#include "cocos2d.h"

#include "define.h"

class Hand;
class BoardNormal;

class Game : public cocos2d::Layer
{
public:
	Game();
	~Game();

	static cocos2d::Scene* createScene(Game* game);

	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(Game);

	void SetCom(bool com);
	void SetMode(int mode);
	void SetComturn(BorW comturn);
	void SetDifficult(int difficult);

	void initGame();


private:
	bool mGuide;

	bool mCom;
	int mMode;
	BorW mComturn;
	int mDifficult;

	BorW mComFlag;
	ComType mComtype;

	Hand* mHand;
	BoardNormal* mBoard;

	bool mFallFlag;
	bool mMessageFlag;
	int mTimer;
	int mInputX, mInputY;

	void initDraw();
	void updateDraw();
	void updateGame();
	void updateGameTouch();

	void GetResultMessage();
	void Pause();
};
