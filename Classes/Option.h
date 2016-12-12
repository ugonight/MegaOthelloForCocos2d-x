#pragma once

#include"cocos2d.h"


class Option : public cocos2d::Layer {
public:
	virtual bool init();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(Option);
public:
	int mPoint;
	bool mGuide;

	void onTouchEnd(cocos2d::Touch *touch, cocos2d::Event *event);
	void TouchAction();
};