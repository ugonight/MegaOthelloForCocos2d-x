#pragma execution_character_set("utf-8")

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "Title.h"
#include "Option.h"
#include "Game.h"

USING_NS_CC;


Scene* Title::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Title::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

Title::Title()
{

}


bool Title::init() {
	if (!Layer::init())
	{
		return false;
	}

	mStep = 1;
	mPoint = 0;

	//FONT_NAME = "fonts/mgenplus-1cp-medium.ttf";


	mMenumega = false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景
	Rect rect = Rect(0, 0, visibleSize.width, visibleSize.height);
	Sprite* square = Sprite::create();
	square->setTextureRect(rect);
	square->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	square->setColor(Color3B(255, 180, 200));
	this->addChild(square, 0, "back");

	//タイトル
	auto titleLabel = Label::createWithTTF("リバーシ", FONT_NAME, 128);
	titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - ( 50 + 64 )));
	titleLabel->setTextColor(Color4B::BLACK);
	this->addChild(titleLabel, 1, "titleLabel");

	//ボタン1
	Rect rect1 = Rect(0, 0, 100 * 7-2, 140-2);
	Rect rect1_ = Rect(0, 0, 100 * 7, 140);
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
	auto ButtonLabel1 = Label::createWithTTF("ひとりでプレイ", FONT_NAME, 100);
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
	listener->onTouchEnded = CC_CALLBACK_2(Title::onTouchEnd, this);
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
	auto ButtonLabel2 = Label::createWithTTF("ふたりでプレイ", FONT_NAME, 100);
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
	listener2->onTouchEnded = CC_CALLBACK_2(Title::onTouchEnd, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, square2);

	//戻るボタン
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
	auto ButtonLabel3 = Label::createWithTTF("終了", FONT_NAME, 64);
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
	listener3->onTouchEnded =  CC_CALLBACK_2(Title::onTouchEnd, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3, square3);

	//設定ボタン
	Sprite* square4 = Sprite::create();
	Sprite* square4_ = Sprite::create();
	square4->setTextureRect(rect2);
	square4->setPosition((visibleSize.width / 2) + (100 * 3.5) + (64 * 2.5), visibleSize.height - 577);
	square4->setColor(Color3B(0, 250, 0));
	square4_->setTextureRect(rect2_);
	square4_->setPosition(square4->getPosition());
	square4_->setColor(Color3B(0, 0, 0));
	this->addChild(square4, 2, "button4");
	this->addChild(square4_, 1, "button4_");
	auto ButtonLabel4 = Label::createWithTTF("設定", FONT_NAME, 64);
	ButtonLabel4->setPosition(square4->getPosition());
	ButtonLabel4->setColor(Color3B(0, 0, 0));
	this->addChild(ButtonLabel4, 3, "ButtonLabel4");
	auto listener4 = EventListenerTouchOneByOne::create();
	listener4->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);	
		
		if (targetBox.containsPoint(touchPoint))
		{
			target->setColor(Color3B(255, 255, 0));
			mPoint = 4;

		}
		return true;
	};
	listener4->onTouchMoved = [this](Touch* touch, Event* event) {};
	listener4->onTouchEnded = CC_CALLBACK_2(Title::onTouchEnd, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener4, square4);

	//スクロールボタン
	Rect rect3 = Rect(0, 0, 106 - 2, 100 - 2);
	Rect rect3_ = Rect(0, 0, 106, 100);
	Sprite* square5 = Sprite::create();
	Sprite* square5_ = Sprite::create();
	square5->setTextureRect(rect3);
	square5->setPosition((visibleSize.width / 2) + (100 * 3.5) + (64 * 2) - 5, visibleSize.height - 450);
	square5->setColor(Color3B(0, 250, 0));
	square5_->setTextureRect(rect3_);
	square5_->setPosition(square5->getPosition());
	square5_->setColor(Color3B(0, 0, 0));
	this->addChild(square5, 2, "button5");
	this->addChild(square5_, 1, "button5_");
	auto ButtonLabel5 = Label::createWithTTF("▼", FONT_NAME, 64);
	ButtonLabel5->setPosition(square5->getPosition());
	ButtonLabel5->setColor(Color3B(0, 0, 0));
	this->addChild(ButtonLabel5, 3, "ButtonLabel5");
	auto listener5 = EventListenerTouchOneByOne::create();
	listener5->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			target->setColor(Color3B(255, 255, 0));
			mPoint = 5;
		}
		return true;
	};
	listener5->onTouchMoved = [this](Touch* touch, Event* event) {};
	listener5->onTouchEnded = CC_CALLBACK_2(Title::onTouchEnd, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener5, square5);
	//最初は非表示
	square5->setVisible(false);
	square5_->setVisible(false);
	ButtonLabel5->setVisible(false);


	return true;
}

void Title::onTouchEnd(Touch *touch, Event *event) {
	auto target = (Sprite*)event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();
	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
	target->setColor(Color3B(0, 255, 0));
	if (targetBox.containsPoint(touchPoint))
	{
		TouchAction();
	}
}

void Title::TouchAction() {	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto button1 = (Label*)this->getChildByName("ButtonLabel1");
	auto button2 = (Label*)this->getChildByName("ButtonLabel2");

	if (mPoint == 3) {
		if (mStep == 1) {
			SimpleAudioEngine::getInstance()->playEffect(cancel, false);
			//Close the cocos2d-x game scene and quit the application
			Director::getInstance()->end();
			
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			    exit(0);
			#endif
		}
		mMenumega = false;
		mStep--;
	}

	if (mPoint == 4) {
		SimpleAudioEngine::getInstance()->playEffect(pochi, false);	
		//scene = OPTION;

		if (mStep == 1) {	//オプション
			Director::getInstance()->replaceScene(Option::createScene());
		}
		else {	//戦歴
			auto layer = Layer::create();
			this->addChild(layer, 5, "layer_h");
			
			//背景
			Rect rect = Rect(0, 0, visibleSize.width, visibleSize.height);
			Sprite* square = Sprite::create();
			square->setTextureRect(rect);
			square->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			square->setColor(Color3B(255, 255, 100));
			layer->addChild(square, 0, "back_h");
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = [this](Touch* touch, Event* event) {
				return true;
			};
			listener->onTouchMoved = [this](Touch* touch, Event* event) {};
			listener->onTouchEnded = [this](Touch* touch, Event* event) {
				this->removeChildByName("layer_h");
				SimpleAudioEngine::getInstance()->playEffect(cancel, false);
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, square);

			//タイトル
			auto titleLabel = Label::createWithTTF("戦歴", FONT_NAME, 64);
			titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 32));
			titleLabel->setTextColor(Color4B::BLACK);
			layer->addChild(titleLabel, 1, "titleLabel");

			//リバーシ
			Label* label[4];
			for (int i = 0; i < 4; i++) { 
				label[i] = Label::createWithTTF("", FONT_NAME, 64); 
				label[i]->setPosition(Vec2(origin.x + visibleSize.width / 6, origin.y + (visibleSize.height / 5) * (4 - i)));
				label[i]->setColor(Color3B(0, 0, 0));
				layer->addChild(label[i], 1);
			}
			label[0]->setString("普通のリバーシ");
			label[1]->setString("へんなリバーシ");
			label[2]->setString("メガリバーシ");
			label[3]->setString("もろいリバーシ");

			//やさしい・たいへん
			Label* label1[8];
			for (int i = 0; i < 4; i++) {
				label1[2 * i] = Label::createWithTTF("やさしい", FONT_NAME, 64);
				label1[2 * i]->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 5) * (4 - i) + 32));
				label1[2 * i]->setColor(Color3B(0, 0, 0));
				layer->addChild(label1[2 * i], 1);
				label1[2 * i + 1] = Label::createWithTTF("たいへん", FONT_NAME, 64);
				label1[2 * i + 1]->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 5) * (4 - i) - 32));
				label1[2 * i + 1]->setColor(Color3B(0, 0, 0));
				layer->addChild(label1[2 * i + 1], 1);
			}

			//結果
			Label* label2[8];
			auto _userDef = UserDefault::getInstance();	
			std::stringstream str1, str2, str3;
			for (int i = 0; i < 4; i++) {
				str1 << "mode" << i + 1 << "easywin";
				str2 << "mode" << i + 1 << "easylose";
				str3 << _userDef->getIntegerForKey(str1.str().c_str()) << "勝" << _userDef->getIntegerForKey(str2.str().c_str()) << "敗";
				label2[2 * i] = Label::createWithTTF(str3.str(), FONT_NAME, 64);
				label2[2 * i]->setPosition(Vec2(origin.x + visibleSize.width * 3 / 4, origin.y + (visibleSize.height / 5) * (4 - i) + 32));
				label2[2 * i]->setColor(Color3B(0, 0, 0));
				layer->addChild(label2[2 * i], 1);
				str1.str(""); str2.str(""); str3.str("");
				str1.clear(); str2.clear(); str3.clear();
				str1 << "mode" << i + 1 << "hardwin";
				str2 << "mode" << i + 1 << "hardlose";
				str3 << _userDef->getIntegerForKey(str1.str().c_str()) << "勝" << _userDef->getIntegerForKey(str2.str().c_str()) << "敗";
				label2[2 * i + 1] = Label::createWithTTF(str3.str(), FONT_NAME, 64);
				label2[2 * i + 1]->setPosition(Vec2(origin.x + visibleSize.width * 3 / 4, origin.y + (visibleSize.height / 5) * (4 - i) - 32));
				label2[2 * i + 1]->setColor(Color3B(0, 0, 0));
				layer->addChild(label2[2 * i + 1], 1);
				str1.str(""); str2.str(""); str3.str("");
				str1.clear(); str2.clear(); str3.clear();
			}

			//プレイ回数
			auto label3 = Label::createWithTTF("プレイ回数", FONT_NAME, 64);
			label3->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + 32));
			label3->setTextColor(Color4B::BLACK);
			layer->addChild(label3, 1);
			std::stringstream str;
			str << _userDef->getIntegerForKey("playcount") << "回";
			auto label4 = Label::createWithTTF(str.str(), FONT_NAME, 64);
			label4->setPosition(Vec2(origin.x + visibleSize.width * 3 / 4, origin.y + 32));
			label4->setTextColor(Color4B::BLACK);
			layer->addChild(label4, 1);

		}
	}

	switch (mStep)
	{
	case 1:
		if (mPoint == 1) {
			mCom = true;
		}
		else if (mPoint == 2) {
			mCom = false;

		}
		if (mPoint == 1 || mPoint == 2) {
			mStep = 2;
			mMenumega = false;
		}
		break;

	case 2:
		if (mPoint == 1) {
			if (mMenumega == false) {
				mMode = 0;
			}
			else {
				mMode = 2;
			}
		}
		else if (mPoint == 2) {
			if (mMenumega == false) {
				mMode = 1;
			}
			else {
				mMode = 3;
			}

		}
		if (mPoint == 1 || mPoint == 2) {
			if (mCom == true) {
				mStep = 3;
			}
			else {
				mStep = 9;
			}
		}

		if (mPoint == 5) {
			if (mMenumega == false) {
				mMenumega = true;
				//sprintf_s(button1, " メガリバーシ");
				//sprintf_s(button2, "もろいリバーシ");
				button1->setString("メガリバーシ");
				button2->setString("もろいリバーシ");
			}
			else {
				mMenumega = false;
				//sprintf_s(button1, "普通のリバーシ");
				//sprintf_s(button2, "へんなリバーシ");
				button1->setString("普通のリバーシ");
				button2->setString("へんなリバーシ");
			}
		}
		break;

	case 3:
		if (mPoint == 1) {
			mComturn = white;
		}
		else if (mPoint == 2) {
			mComturn = black;
		}
		if (mPoint == 1 || mPoint == 2) {
			if (mCom == false) {
				mStep = 9;
			}
			else {
				mStep = 4;
			}
		}
		break;

	case 4:
		if (mPoint == 1) {
			mDifficult = 0;
			mStep = 9;
		}
		else if (mPoint == 2) {
			mDifficult = 1;
			mStep = 9;
		}
		break;
	default:
		break;
	}

	switch (mStep)
	{
	case 1:
		//sprintf_s(button1, "ひとりでプレイ");
		//sprintf_s(button2, "ふたりでプレイ");
		button1->setString("ひとりでプレイ");
		button2->setString("ふたりでプレイ");
		break;
	case 2:
		if (mMenumega == false) {
			button1->setString( "普通のリバーシ");
			button2->setString( "へんなリバーシ");
		}
		else {
			button1->setString( "メガリバーシ");
			button2->setString( "もろいリバーシ");
		}
		break;
	case 3:
		button1->setString( "先攻で始める");
		button2->setString( "後攻で始める");
		break;
	case 4:
		button1->setString( "やさしい");
		button2->setString( "たいへん");
		break;
	case 9:

		//mStep = 1;

		//button1->setString("ひとりでプレイ");
		//button2->setString("ふたりでプレイ");

		SimpleAudioEngine::getInstance()->playBackgroundMusic(thinking, true);
		//scene = GAME;

		auto game = Game::create();
		game->SetCom(mCom);
		game->SetMode(mMode);
		game->SetComturn(mComturn);
		game->SetDifficult(mDifficult);
		game->initGame();
		Director::getInstance()->replaceScene(TransitionTurnOffTiles::create(0.5f, Game::createScene(game)));

		break;
	}

	if (mPoint == 1 || mPoint == 2 || mPoint == 5) {
		SimpleAudioEngine::getInstance()->playEffect(pochi,false);
	}
	else if (mPoint == 3) {
		SimpleAudioEngine::getInstance()->playEffect(cancel, false);
	}

	//設定ボタンの表示・非表示
	auto square4 = this->getChildByName("button4");
	auto square4_ = this->getChildByName("button4_");
	auto label4 = (Label*)this->getChildByName("ButtonLabel4");
	if (mStep == 1 || ( mStep == 2 && mCom == true )) {
		square4->setVisible(true);
		square4_->setVisible(true);
		label4->setVisible(true);
		this->getEventDispatcher()->resumeEventListenersForTarget(square4);
		if (mStep == 1) {
			label4->setString("設定");
		}
		else {
			label4->setString("戦歴");
		}
	}
	else {
		square4->setVisible(false);
		square4_->setVisible(false);
		label4->setVisible(false);
		this->getEventDispatcher()->pauseEventListenersForTarget(square4);
	}

	//戻る・終了
	auto label3 = (Label*)this->getChildByName("ButtonLabel3");
	if (mStep != 1) {
		label3->setString("戻る");
	}
	else {
		label3->setString("終了");
	}

	//スクロールボタン
	auto square5 = this->getChildByName("button5");
	auto square5_ = this->getChildByName("button5_");
	auto label5 = (Label*)this->getChildByName("ButtonLabel5");
	if (mStep == 2) {
		square5->setVisible(true);
		square5_->setVisible(true);
		label5->setVisible(true);
		this->getEventDispatcher()->resumeEventListenersForTarget(square5);
	}
	else {
		square5->setVisible(false);
		square5_->setVisible(false);
		label5->setVisible(false);
		this->getEventDispatcher()->pauseEventListenersForTarget(square5);
	}
	if (!mMenumega) {
		label5->setString("▼");
	}
	else {
		label5->setString("▲");
	}
}
