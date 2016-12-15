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
	int mMode;
	bool mCom;
	bool mMenumega;
	BorW mComturn;
	//BorW mComFlag;
	//ComType mComtype;
	int mDifficult;

	void onTouchEnd(cocos2d::Touch *touch, cocos2d::Event *event);
	void TouchAction();
	
};