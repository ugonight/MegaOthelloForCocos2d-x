#pragma execution_character_set("utf-8")
#include "audio/include/AudioEngine.h"
// using namespace cocos2d::experimental;

#include "Option.h"
#include "define.h"
#include "Title.h"
#include "Util.h"

USING_NS_CC;


Scene* Option::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Option::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Option::init() {
	if (!Layer::init())
	{
		return false;
	}

	auto _userDef = UserDefault::getInstance();
	mGuide = _userDef->getBoolForKey("guide");
	
	std::string guideText;
	if (mGuide) {
		guideText = "ガイド：オン";
	}
	else {
		guideText = "ガイド：オフ";
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景
	Rect rect = Rect(0, 0, visibleSize.width, visibleSize.height);
	Sprite* square = Sprite::create();
	square->setTextureRect(rect);
	square->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	square->setColor(Color3B(200, 200, 255));
	this->addChild(square, 0, "back");

	//タイトル
	auto titleLabel = Label::createWithTTF("設定", FONT_NAME, 128);
	titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - (50 + 64)));
	titleLabel->setTextColor(Color4B::BLACK);
	this->addChild(titleLabel, 1, "titleLabel");

	//ボタン1
	Rect rect1 = Rect(0, 0, 740 - 2, 140 - 2);
	Rect rect1_ = Rect(0, 0, 740, 140);
	Sprite* square1 = Sprite::create();
	Sprite* square1_ = Sprite::create();
	square1->setTextureRect(rect1);
	square1->setPosition((visibleSize.width / 2) - 20, visibleSize.height - ((280 + 420) / 2));
	square1->setColor(Color3B(0, 250, 0));
	square1_->setTextureRect(rect1_);
	square1_->setPosition(square1->getPosition());
	square1_->setColor(Color3B(0, 0, 0));
	this->addChild(square1, 2, "button1");
	this->addChild(square1_, 1, "button1_");
	auto ButtonLabel1 = Label::createWithTTF(guideText, FONT_NAME, 100);
	ButtonLabel1->setPosition(square1->getPosition());
	ButtonLabel1->setColor(Color3B(0, 0, 0));
	this->addChild(ButtonLabel1, 3, "ButtonLabel1");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			target->setColor(Color3B(255, 255, 0));
			mPoint = 1;
		}
		return true;
	};
	listener->onTouchMoved = [this](Touch* touch, Event* event) {};
	listener->onTouchEnded = CC_CALLBACK_2(Option::onTouchEnd, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, square1);

	//ボタン2
	Sprite* square2 = Sprite::create();
	Sprite* square2_ = Sprite::create();
	square2->setTextureRect(rect1);
	square2->setPosition((visibleSize.width / 2) - 20, visibleSize.height - ((480 + 620) / 2));
	square2->setColor(Color3B(0, 250, 0));
	square2_->setTextureRect(rect1_);
	square2_->setPosition(square2->getPosition());
	square2_->setColor(Color3B(0, 0, 0));
	this->addChild(square2, 2, "button2");
	this->addChild(square2_, 1, "button2_");
	auto ButtonLabel2 = Label::createWithTTF("クレジット", FONT_NAME, 100);
	ButtonLabel2->setPosition(square2->getPosition());
	ButtonLabel2->setColor(Color3B(0, 0, 0));
	this->addChild(ButtonLabel2, 3, "ButtonLabel2");
	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			target->setColor(Color3B(255, 255, 0));
			mPoint = 2;
		}
		return true;
	};
	listener2->onTouchMoved = [this](Touch* touch, Event* event) {};
	listener2->onTouchEnded = CC_CALLBACK_2(Option::onTouchEnd, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, square2);

	//戻る
	Rect rect2 = Rect(0, 0, 148 - 2, 86 - 2);
	Rect rect2_ = Rect(0, 0, 148, 86);
	Sprite* square3 = Sprite::create();
	Sprite* square3_ = Sprite::create();
	square3->setTextureRect(rect2);
	square3->setPosition((visibleSize.width / 2) - (100 * 3.5) - (64 * 2.5), visibleSize.height - 577);
	square3->setColor(Color3B(0, 250, 0));
	square3_->setTextureRect(rect2_);
	square3_->setPosition(square3->getPosition());
	square3_->setColor(Color3B(0, 0, 0));
	this->addChild(square3, 2, "button3");
	this->addChild(square3_, 1, "button3_");
	auto ButtonLabel3 = Label::createWithTTF("戻る", FONT_NAME, 64);
	ButtonLabel3->setPosition(square3->getPosition());
	ButtonLabel3->setColor(Color3B(0, 0, 0));
	this->addChild(ButtonLabel3, 3, "ButtonLabel3");
	auto listener3 = EventListenerTouchOneByOne::create();
	listener3->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			target->setColor(Color3B(255, 255, 0));
			mPoint = 3;
		}
		return true;
	};
	listener3->onTouchMoved = [this](Touch* touch, Event* event) {};
	listener3->onTouchEnded = CC_CALLBACK_2(Option::onTouchEnd, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3, square3);

	return true;
}

void Option::onTouchEnd(Touch *touch, Event *event) {
	auto target = (Sprite*)event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();
	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
	target->setColor(Color3B(0, 255, 0));
	if (targetBox.containsPoint(touchPoint))
	{
		TouchAction();
	}
}

void Option::TouchAction() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	
	
	auto button1 = (Label*)this->getChildByName("ButtonLabel1");
	auto button2 = (Label*)this->getChildByName("ButtonLabel2");

	switch (mPoint)
	{
	case 1:
		AudioEngine::play2d(pochi, false);
		if (mGuide == true) {
			mGuide = false;
			Util::changeLabelText(button1, "ガイド：オフ");
		}
		else {
			mGuide = true;
			Util::changeLabelText(button1, "ガイド：オン");
		}
		break;
	case 2: {
		AudioEngine::play2d(pochi, false);
		//scene = CREDIT;

		//背景
		Rect rect = Rect(0, 0, visibleSize.width, visibleSize.height);
		Sprite* square = Sprite::create();
		square->setTextureRect(rect);
		square->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		square->setColor(Color3B(100, 255, 255));
		this->addChild(square, 5, "back_c");

		//文字
		auto Labelc = Label::createWithTTF("プログラム・BGM・効果音\n  ドスカルゴン\n\nアイコン・スマホアプリ化\n  ugonight\n\n\n遊んでくださった皆様、特にネットでの配信を希望してくださった方に\n深く感謝します。\n\n\n感想、要望はtwitter(@dosscargon)までお願いします。\n\n                                                                  クリックで戻る", FONT_NAME, 32);
		Labelc->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		Labelc->setPosition(Vec2(64, visibleSize.height - 64));
		Labelc->setColor(Color3B(0, 0, 0));
		this->addChild(Labelc, 6, "label_c");

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [this](Touch* touch, Event* event) {
			return true;
		};
		listener->onTouchMoved = [this](Touch* touch, Event* event) {};
		listener->onTouchEnded = [this](Touch* touch, Event* event) {
			this->removeChildByName("back_c");
			this->removeChildByName("label_c");
			AudioEngine::play2d(cancel, false);
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, square);

		break; }
	case 3:
		AudioEngine::play2d(cancel, false);
		auto _userDef = UserDefault::getInstance();
		_userDef->setBoolForKey("guide",mGuide);
		_userDef->flush();
		//scene = TITLE;
		Director::getInstance()->replaceScene(Title::createScene());
		break;
	}

}