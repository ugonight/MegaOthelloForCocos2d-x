#pragma once

#include"cocos2d.h"

#include "define.h"

class Title : public cocos2d::Layer {
public:
	Title();
	virtual bool init();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(Title);
private:
	int mPoint;
	int mStep;
	int mMode;	// どんなリバーシ？
	bool mCom;
	int mMenumega;
	BorW mComturn;
	//BorW mComFlag;
	//ComType mComtype;
	int mDifficult;
	int mPageHistory;	// 戦歴のページ

	void onTouchEnd(cocos2d::Touch* touch, cocos2d::Event* event);
	void TouchAction();
};