#pragma execution_character_set("utf-8")

#include "Game.h"
#include "SimpleAudioEngine.h"

#include "Hand.h"
#include "BoardNormal.h"

#include "Title.h"

using namespace CocosDenshion;
USING_NS_CC;
Game::Game() {
	mHand = new Hand();
	mBoard = new BoardNormal();
}

Game::~Game() {
	delete mHand;
	delete mBoard;
}

Scene* Game::createScene(Game* game)
{
	auto scene = Scene::create();
	//auto layer = Game::create();
	scene->addChild(game);
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->scheduleUpdate();

	auto _userDef = UserDefault::getInstance();
	mGuide = _userDef->getBoolForKey("guide");

	mFallFlag = false;
	mMessageFlag = false;
	mTimer = 0;

	//この時点では盤面が初期化されていないのでinitDrawに初期描画を記述

	return true;
}

void Game::update(float delta) {
	updateGame();
}

void Game::SetCom(bool com) { mCom = com; }
void Game::SetMode(int mode) { mMode = mode; }
void Game::SetComturn(BorW comturn) { mComturn = comturn; }
void Game::SetDifficult(int difficult) { mDifficult = difficult; }

void Game::initGame() {
	mBoard->resetMurora();

	mHand->SetInputFlag(true);
	if (mCom == true) {
		mComFlag = mComturn;
		if (mComFlag == black) {
			mHand->SetInputFlag(false);
		}
	}
	else {
		mComFlag = none;

	}
	if (mMode == 0) {
		mBoard->reset();
		if (mDifficult == 0) {
			mComtype = com2;
		}
		else {
			mComtype = com1;
		}
	}
	else if (mMode == 1) {
		mBoard->resetMurora();
		if (mDifficult == 0) {
			mComtype = com2murora;
		}
		else {
			mComtype = com1murora;
		}
	}
	else if (mMode == 2) {
		mBoard->resetMega();
		if (mDifficult == 0) {
			mComtype = com2mega;
		}
		else {
			mComtype = com1mega;
		}
	}
	else if (mMode == 3) {
		mBoard->resetMoroi();
		if (mDifficult == 0) {
			mComtype = com2moroi;
		}
		else {
			mComtype = com1moroi;
		}

	}

	initDraw();
}

void Game::initDraw() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//ここでは変化しないものを描画

	//盤面描画----------------------------------------------------

	//石などを配置するレイヤー
	auto boardLayer = Layer::create();
	this->addChild(boardLayer, 2, "boardLayer");



	//盤面の背景
	Rect rect = Rect(0, 0, 720, 720);
	Sprite* square = Sprite::create();
	square->setTextureRect(rect);
	square->setPosition(origin.x + 720 / 2, origin.y + 720 / 2);
	square->setColor(Color3B(0, 255, 0));
	this->addChild(square, 0, "back");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) { 
		//カーソル
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		if (mHand->GetInputFlag() == true && mBoard->GetTurn() != gray) {
			for (int i = 0; i < mBoard->GetBoardSize() + 1; i++) {
				for (int j = 0; j < (mBoard->GetBoardSize() + 1); j++) {
					if (i*(720 / (mBoard->GetBoardSize() + 1)) < touch->getLocationInView().x && j*(720 / (mBoard->GetBoardSize() + 1)) < touch->getLocationInView().y && touch->getLocationInView().x < (i + 1)*(720 / (mBoard->GetBoardSize() + 1)) && touch->getLocationInView().y < (j + 1)*(720 / (mBoard->GetBoardSize() + 1))) {
						//DrawBox(i*(720 / (board.GetBoardSize() + 1)), j*(720 / (board.GetBoardSize() + 1)), (i + 1)*(720 / (board.GetBoardSize() + 1)), (j + 1)*(720 / (board.GetBoardSize() + 1)), GetColor(255, 255, 0), TRUE);
						auto cursor = getChildByName("boardLayer")->getChildByName("cursor");
						cursor->setVisible(true);
						cursor->setPosition(origin.x + i*(720 / (mBoard->GetBoardSize() + 1)) + 1, origin.y + visibleSize.height - (j*(720 / (mBoard->GetBoardSize() + 1)) + 1));
					}
				}
			}
		}

		return true; 
	};
	listener->onTouchMoved = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{

			//カーソル
			auto visibleSize = Director::getInstance()->getVisibleSize();
			Vec2 origin = Director::getInstance()->getVisibleOrigin();

			if (mHand->GetInputFlag() == true && mBoard->GetTurn() != gray) {
				for (int i = 0; i < mBoard->GetBoardSize() + 1; i++) {
					for (int j = 0; j < (mBoard->GetBoardSize() + 1); j++) {
						if (i*(720 / (mBoard->GetBoardSize() + 1)) < touch->getLocationInView().x && j*(720 / (mBoard->GetBoardSize() + 1)) < touch->getLocationInView().y && touch->getLocationInView().x < (i + 1)*(720 / (mBoard->GetBoardSize() + 1)) && touch->getLocationInView().y < (j + 1)*(720 / (mBoard->GetBoardSize() + 1))) {
							//DrawBox(i*(720 / (board.GetBoardSize() + 1)), j*(720 / (board.GetBoardSize() + 1)), (i + 1)*(720 / (board.GetBoardSize() + 1)), (j + 1)*(720 / (board.GetBoardSize() + 1)), GetColor(255, 255, 0), TRUE);
							auto cursor = getChildByName("boardLayer")->getChildByName("cursor");
							cursor->setVisible(true);
							cursor->setPosition(origin.x + i*(720 / (mBoard->GetBoardSize() + 1)) + 1, origin.y + visibleSize.height - (j*(720 / (mBoard->GetBoardSize() + 1)) + 1));
						}
					}
				}
			}
		}
	};
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		mHand->CheckPoint(touch->getLocationInView().x, touch->getLocationInView().y, mBoard->GetBoardSize());
		auto cursor = getChildByName("boardLayer")->getChildByName("cursor");
		cursor->setVisible(false);

		this->updateGameTouch();
		
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, square);

	//縦の線
	for (int i = 0; i < mBoard->GetBoardSize() + 1 + 1; i++) {
		DrawNode* line = DrawNode::create();
		line->drawSegment(Vec2(origin.x + i*(720 / (mBoard->GetBoardSize() + 1)), 0), Vec2(origin.x + i*(720 / (mBoard->GetBoardSize() + 1)), 720), 1.0f, Color4F::BLACK);
		this->addChild(line, 1);
	}

	//横の線を引く
	for (int i = 0; i < mBoard->GetBoardSize() + 1 + 1; i++) {
		//DrawLine(0, i*(720 / (board.GetBoardSize() + 1)), 720, i*(720 / (board.GetBoardSize() + 1)), GetColor(0, 0, 0), 2);
		DrawNode* line = DrawNode::create();
		line->drawSegment(Vec2(origin.x + 0, origin.y + i*(720 / (mBoard->GetBoardSize() + 1))), Vec2(origin.x + 720, origin.y + i*(720 / (mBoard->GetBoardSize() + 1))), 1.0f, Color4F::BLACK);
		this->addChild(line, 1);
	}


	//情報描画----------------------------------------------
	Rect rect2 = Rect(0, 0, 1280 - 721, 720);
	Sprite* square2 = Sprite::create();
	square2->setTextureRect(rect2);
	square2->setPosition(origin.x + (1280 + 721) / 2, origin.y + 720 / 2);
	square2->setColor(Color3B(150, 150, 255));
	this->addChild(square2, 0);

	std::stringstream sblack, swhite;
	sblack << "黒　" << mBoard->CountStone(black) << "個";
	swhite << "白　" << mBoard->CountStone(white) << "個";

	auto blackLabel = Label::createWithTTF(sblack.str(), FONT_NAME, 64);
	blackLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	blackLabel->setPosition(Vec2(origin.x + 800, origin.y + visibleSize.height - (45)));
	blackLabel->setTextColor(Color4B::BLACK);
	this->addChild(blackLabel, 1, "blackLabel");

	auto whiteLabel = Label::createWithTTF(swhite.str(), FONT_NAME, 64);
	whiteLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	whiteLabel->setPosition(Vec2(origin.x + 800, origin.y + visibleSize.height - (125)));
	whiteLabel->setTextColor(Color4B::BLACK);
	this->addChild(whiteLabel, 1, "whiteLabel");

	std::string TurnMsg;
	if (mBoard->GetTurn() == black) {
		TurnMsg = "黒の番です";
	}
	else if (mBoard->GetTurn() == white) {
		TurnMsg = "白の番です";
	}

	auto stateLabel = Label::createWithTTF(TurnMsg, FONT_NAME, 64);
	stateLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	stateLabel->setPosition(Vec2(origin.x + 800, origin.y + visibleSize.height - 300));
	stateLabel->setTextColor(Color4B::BLACK);
	this->addChild(stateLabel, 1, "stateLabel");



	//ポーズ
	Rect rect3 = Rect(0, 0, 1202 - 990 - 2, 674 - 590 - 2);
	Rect rect3_ = Rect(0, 0, 1202 - 990, 674 - 590);
	Sprite* square3 = Sprite::create();
	Sprite* square3_ = Sprite::create();
	square3->setTextureRect(rect3);
	square3->setPosition(origin.x + (1202 + 990) / 2, origin.y + visibleSize.height - (674 + 590) / 2);
	square3->setColor(Color3B(255, 50, 50));
	square3_->setTextureRect(rect3_);
	square3_->setPosition(square3->getPosition());
	square3_->setColor(Color3B(0, 0, 0));
	this->addChild(square3, 2, "button3");
	this->addChild(square3_, 1, "button3_");
	auto ButtonLabel3 = Label::createWithTTF("ポーズ", FONT_NAME, 64);
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
			target->setColor(Color3B(255, 255, 50));
		}
		return true;
	};
	listener3->onTouchMoved = [this](Touch* touch, Event* event) {};
	listener3->onTouchEnded = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		target->setColor(Color3B(255, 50, 50));
		if (targetBox.containsPoint(touchPoint))
		{
			if (mHand->GetInputFlag() == true) {
				//PlaySoundMem(buttonsound, DX_PLAYTYPE_BACK);
				SimpleAudioEngine::getInstance()->playEffect(pochi, false);

				//scene = PAUSE;

				Pause();
			}
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3, square3);

	updateDraw();
}

void Game::updateDraw() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto boardLayer = this->getChildByName("boardLayer");
	boardLayer->removeAllChildren();	//全部消す


	//置ける場所の色を変える(ガイド)	
	Rect rect = Rect(0, 0, 720 / (mBoard->GetBoardSize() + 1)-2, 720 / (mBoard->GetBoardSize() + 1)-2);
	if (mGuide == true) {
		if (mHand->GetInputFlag() == true) {
			for (int i = 0; i < mBoard->GetBoardSize() + 1; i++) {
				for (int j = 0; j < (mBoard->GetBoardSize() + 1); j++) {
					if (mBoard->put(i, j, true)) {
						//DrawBox(i*(720 / (board.GetBoardSize() + 1)), j*(720 / (board.GetBoardSize() + 1)), (i + 1)*(720 / (board.GetBoardSize() + 1)), (j + 1)*(720 / (board.GetBoardSize() + 1)), GetColor(255, 186, 216), TRUE);
						Sprite* square = Sprite::create();
						square->setTextureRect(rect);
						square->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
						square->setPosition(Vec2(origin.x + i*(720 / (mBoard->GetBoardSize() + 1)) + 1, origin.y + visibleSize.height - (j*(720 / (mBoard->GetBoardSize() + 1)))-1));
						square->setColor(Color3B(255, 186, 216));
						boardLayer->addChild(square, 0);
					}
				}
			}
		}
	}

	//カーソル
	Rect rect0 = Rect(0, 0, 720 / (mBoard->GetBoardSize() + 1) - 2, 720 / (mBoard->GetBoardSize() + 1) - 2);
	Sprite* square0 = Sprite::create();
	square0->setTextureRect(rect0);
	square0->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	//square->setPosition(origin.x + i*(720 / (mBoard->GetBoardSize() + 1)) + 1, origin.y + visibleSize.height - (j*(720 / (mBoard->GetBoardSize() + 1)) + 1));
	square0->setPosition(origin.x, origin.y);
	square0->setColor(Color3B(255, 255, 0));
	square0->setVisible(false);
	boardLayer->addChild(square0, 1, "cursor");

	//石を置く
	for (int i = 0; i < mBoard->GetBoardSize() + 1; i++) {
		for (int j = 0; j < mBoard->GetBoardSize() + 1; j++) {
			if (mBoard->GetBoard(i, j) == black) {
				//DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(0, 0, 0), TRUE);
				DrawNode *dot = DrawNode::create();
				dot->drawDot(Vec2::ZERO, (720 / (mBoard->GetBoardSize() + 1)) / 2 * 0.8, Color4F::BLACK);
				dot->setPosition(Vec2(origin.x + (i + 0.5)*(720 / (mBoard->GetBoardSize() + 1)), origin.y + visibleSize.height - (j + 0.5)*(720 / (mBoard->GetBoardSize() + 1))));
				boardLayer->addChild(dot, 2);
			}
			else if (mBoard->GetBoard(i, j) == white) {
				//DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(255, 255, 255), TRUE);
				//DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(0, 0, 0), FALSE);
				DrawNode *dot = DrawNode::create();
				dot->drawDot(Vec2::ZERO, (720 / (mBoard->GetBoardSize() + 1)) / 2 * 0.8, Color4F::WHITE);
				dot->setPosition(Vec2(origin.x + (i + 0.5)*(720 / (mBoard->GetBoardSize() + 1)), origin.y + visibleSize.height - (j + 0.5)*(720 / (mBoard->GetBoardSize() + 1))));
				boardLayer->addChild(dot, 2);
				DrawNode *cirlce = DrawNode::create();
				// 中心座標、半径、角度、頂点数、中心に向かう線を描画するか、倍率x、倍率y
				cirlce->drawCircle(Vec2::ZERO, (720 / (mBoard->GetBoardSize() + 1)) / 2 * 0.8, 45, 360, false, 1, 1, Color4F::BLACK);
				cirlce->setPosition(dot->getPosition());
				boardLayer->addChild(cirlce, 2);
			}
			else if (mBoard->GetBoard(i, j) == gray) {
				//DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(100, 100, 100), TRUE);
				//DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(0, 0, 0), FALSE);

				//DrawBox(i*(720 / (board.GetBoardSize() + 1)), j*(720 / (board.GetBoardSize() + 1)), (i + 1)*(720 / (board.GetBoardSize() + 1)), (j + 1)*(720 / (board.GetBoardSize() + 1)), GetColor(0, 0, 0), TRUE);
			
				Sprite* square = Sprite::create();
				square->setColor(Color3B::BLACK);
				square->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
				square->setTextureRect(rect);
				square->setPosition(origin.x + i*(720 / (mBoard->GetBoardSize() + 1)) + 1, origin.y + visibleSize.height - (j*(720 / (mBoard->GetBoardSize() + 1)) + 1));
				boardLayer->addChild(square, 2);
			}
		}


	}
	
	auto state = (Label*)this->getChildByName("stateLabel");
	if (mBoard->GetTurn() == black) {
		state->setString("黒の番です");
	}
	else if (mBoard->GetTurn() == white) {
		state->setString("白の番です");
	}

	std::stringstream sblack, swhite;
	sblack << "黒　" << mBoard->CountStone(black) << "個";
	swhite << "白　" << mBoard->CountStone(white) << "個";
	auto blabel = (Label*)this->getChildByName("blackLabel");
	auto wlabel = (Label*)this->getChildByName("whiteLabel");
	blabel->setString(sblack.str());
	wlabel->setString(swhite.str());
}

void Game::updateGame() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (mFallFlag == true && mBoard->GetTurn() != gray) {
		mTimer++;
		if (mTimer > FALLWAIT) {
			mBoard->Fall();

			if (mBoard->CheckPass(mBoard->GetTurn()) == false) {
				if (mBoard->CheckPass(mBoard->NotTurn(mBoard->GetTurn())) == true) {
					mHand->SetInputFlag(false);
					mMessageFlag = true;
					mBoard->TurnChange();
				}
				else
				{
					GetResultMessage();
					mMessageFlag = true;
					mHand->SetInputFlag(false);
					mBoard->finish();
				}
			}

			//PlaySoundMem(fallsound, DX_PLAYTYPE_BACK);
			SimpleAudioEngine::getInstance()->playEffect(fall, false);

			if (mBoard->GetTurn() != mComFlag && mBoard->GetTurn() != gray && mMessageFlag == false) {
				mHand->SetInputFlag(true);
			}

			mFallFlag = false;
			mTimer = 0;
			updateDraw();
		}
	}
	else if (mMessageFlag == true) {
		if (mBoard->GetTurn() != gray) {
			if (mTimer == 0) {
				//DrawBox(SCREEN_SIZE_X / 2 - 100 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 255, 255), true);
				//DrawBox(SCREEN_SIZE_X / 2 - 100 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 0, 0), false);
				//DrawStringToHandle(SCREEN_SIZE_X / 2 - 100, SCREEN_SIZE_Y / 2 - 100 / 2, "パス", GetColor(0, 0, 0), font100);
				Sprite* square_ = Sprite::create();
				square_->setColor(Color3B::BLACK);
				square_->setTextureRect(Rect(0, 0, 220, 120));
				square_->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
				this->addChild(square_, 3, "pass_");
				Sprite* square = Sprite::create();
				square->setColor(Color3B(0, 255, 255));
				square->setTextureRect(Rect(0, 0, 220 - 2, 120 - 2));
				square->setPosition(square_->getPosition());
				this->addChild(square, 4, "pass");
				auto Label = Label::createWithTTF("パス", FONT_NAME, 100);
				Label->setPosition(square_->getPosition());
				Label->setTextColor(Color4B::BLACK);
				this->addChild(Label, 5, "passLabel");
			}
		}
		else {
			if (mTimer == 0) {
				//DrawBox(SCREEN_SIZE_X / 2 - 100 * 2.5 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 * 2.5 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 255, 255), true);
				//DrawBox(SCREEN_SIZE_X / 2 - 100 * 2.5 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 * 2.5 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 0, 0), false);
				//DrawStringToHandle(SCREEN_SIZE_X / 2 - 100 * 2.5, SCREEN_SIZE_Y / 2 - 100 / 2, "ゲーム終了", GetColor(0, 0, 0), font100);
				Sprite* square_ = Sprite::create();
				square_->setColor(Color3B::BLACK);
				square_->setTextureRect(Rect(0, 0, 520, 120));
				square_->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
				this->addChild(square_, 3, "pass_");
				Sprite* square = Sprite::create();
				square->setColor(Color3B(0, 255, 255));
				square->setTextureRect(Rect(0, 0, 520 - 2, 120 - 2));
				square->setPosition(square_->getPosition());
				this->addChild(square, 4, "pass");
				auto Label = Label::createWithTTF("ゲーム終了", FONT_NAME, 100);
				Label->setPosition(square_->getPosition());
				Label->setTextColor(Color4B::BLACK);
				this->addChild(Label, 5, "passLabel");
			}
		}
		mTimer++;
		if (mTimer > MESSAGEWAIT) {
			mMessageFlag = false;
			mFallFlag = false;
			if (mBoard->GetTurn() != mComFlag) {
				mHand->SetInputFlag(true);
			}
			mTimer = 0;
			updateDraw();
			this->removeChildByName("pass_");
			this->removeChildByName("pass");
			this->removeChildByName("passLabel");
		}


	}
	else if (mMessageFlag == false && (mBoard->GetTurn() == mComFlag)) {
		mTimer++;
		if (mTimer > COMWAIT) {
			if (mComtype == com1) {
				mBoard->Com1();
			}
			else if (mComtype == com1murora) {
				mBoard->Com1Murora();
			}
			else if (mComtype == com1mega)
			{
				mBoard->Com1();
			}
			else if (mComtype == com1moroi) {
				mBoard->Com1moroi();
			}
			else if (mComtype == com2) {
				mBoard->Com2();
			}
			else if (mComtype == com2murora) {
				mBoard->Com2Murora();
			}
			else if (mComtype == com2mega) {
				mBoard->Com2Mega();
			}
			else if (mComtype == com2moroi) {
				mBoard->Com2moroi();
			}

			//PlaySoundMem(putsound, DX_PLAYTYPE_BACK);
			SimpleAudioEngine::getInstance()->playEffect(pachin, false);

			//if (1) {
			//if (0) {
			if (mBoard->TurnChange() == false) {
				if (mBoard->TurnChange() == false) {

					GetResultMessage();
					mMessageFlag = true;
					mBoard->finish();
					//break;

				}
				else {
					mHand->SetInputFlag(false);
					mMessageFlag = true;
				}
			}
			else {
				mHand->SetInputFlag(true);

			}
			if (mComtype == com1moroi || mComtype == com2moroi) {
				mHand->SetInputFlag(false);
				mFallFlag = true;
			}

			mTimer = 0;
			updateDraw();
		}
	}

}

void Game::GetResultMessage() {
	std::string str;
	if (mBoard->CountStone(black) > mBoard->CountStone(white)) {
		str = "黒の勝ちです";
	}
	else if (mBoard->CountStone(black) < mBoard->CountStone(white)) {
		str = "白の勝ちです";
	}
	else {
		str = "引き分けです";
	}

	auto state = (Label*)this->getChildByName("stateLabel");
	state->setString(str);

	auto _userDef = UserDefault::getInstance();
	_userDef->setIntegerForKey("playcount", _userDef->getIntegerForKey("playcount") + 1);

	if (mCom) {
		std::stringstream key;
		key << "mode" << mMode + 1;
		if (mDifficult == 0) {
			key << "easy";
		}
		else {
			key << "hard";
		}
		if (mBoard->CountStone(mComturn) < mBoard->CountStone(mBoard->NotTurn(mComturn))) {
			key << "win";
		}
		else {
			key << "lose";
		}
		_userDef->setIntegerForKey(key.str().c_str(), _userDef->getIntegerForKey(key.str().c_str()) + 1);
	}
	_userDef->flush();
}

void Game::updateGameTouch() {

	if (mHand->GetInputFlag() == true) {
		if (mBoard->put(mHand->GetPointX(), mHand->GetPointY()) == true) {
			//PlaySoundMem(putsound, DX_PLAYTYPE_BACK);
			SimpleAudioEngine::getInstance()->playEffect(pachin, false);

			if (mBoard->TurnChange() == false) {
				if (mBoard->TurnChange() == false) {
					GetResultMessage();
					mMessageFlag = true;
					mHand->SetInputFlag(false);
					mBoard->finish();
					//break;

				}
				else {
					mHand->SetInputFlag(false);
					mMessageFlag = true;
				}
			}

			if (mBoard->GetTurn() == mComFlag) {
				mHand->SetInputFlag(false);
			}

			if (mComtype == com1moroi || mComtype == com2moroi) {
				mHand->SetInputFlag(false);
				mFallFlag = true;
			}
		}

	}
	
	updateDraw();
}

void Game::Pause() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto layer = Layer::create();
	this->addChild(layer, 5, "pauseLayer");

	//背景
	Rect rect = Rect(0, 0, visibleSize.width, visibleSize.height);
	Sprite* square = Sprite::create();
	square->setTextureRect(rect);
	square->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	square->setColor(Color3B(0, 100, 0));
	layer->addChild(square, 0, "back_p");
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		return true;
	};
	listener->onTouchMoved = [this](Touch* touch, Event* event) {};
	listener->onTouchEnded = [this](Touch* touch, Event* event) {};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, square);


	//ボタン1
	Rect rect1 = Rect(0, 0, 370 * 2 - 2, 140 - 2);
	Rect rect1_ = Rect(0, 0, 370 * 2, 140);
	Sprite* square1 = Sprite::create();
	Sprite* square1_ = Sprite::create();
	square1->setTextureRect(rect1);
	square1->setPosition(origin.x + (visibleSize.width / 2), origin.y + visibleSize.height - 150);
	square1->setColor(Color3B(0, 255, 0));
	square1_->setTextureRect(rect1_);
	square1_->setPosition(square1->getPosition());
	square1_->setColor(Color3B(0, 0, 0));
	layer->addChild(square1, 2, "button1");
	layer->addChild(square1_, 1, "button1_");
	auto ButtonLabel1 = Label::createWithTTF("ゲームを続ける", FONT_NAME, 100);
	ButtonLabel1->setPosition(square1->getPosition());
	ButtonLabel1->setColor(Color3B(0, 0, 0));
	layer->addChild(ButtonLabel1, 3, "ButtonLabel1");
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			target->setColor(Color3B(255, 255, 0));
		}
		return true;
	};
	listener1->onTouchMoved = [this](Touch* touch, Event* event) {};
	listener1->onTouchEnded = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		target->setColor(Color3B(0, 255, 0));
		if (targetBox.containsPoint(touchPoint))
		{
			SimpleAudioEngine::getInstance()->playEffect(cancel, false);

			this->removeChildByName("pauseLayer");
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, square1);

	//ボタン2
	Sprite* square2 = Sprite::create();
	Sprite* square2_ = Sprite::create();
	square2->setTextureRect(rect1);
	square2->setPosition(origin.x + (visibleSize.width / 2), origin.y + visibleSize.height - 350);
	square2->setColor(Color3B(0, 255, 0));
	square2_->setTextureRect(rect1_);
	square2_->setPosition(square2->getPosition());
	square2_->setColor(Color3B(0, 0, 0));
	layer->addChild(square2, 2, "button2");
	layer->addChild(square2_, 1, "button2_");
	auto ButtonLabel2 = Label::createWithTTF("最初から始める", FONT_NAME, 100);
	ButtonLabel2->setPosition(square2->getPosition());
	ButtonLabel2->setColor(Color3B(0, 0, 0));
	layer->addChild(ButtonLabel2, 3, "ButtonLabel2");
	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			target->setColor(Color3B(255, 255, 0));
		}
		return true;
	};
	listener2->onTouchMoved = [this](Touch* touch, Event* event) {};
	listener2->onTouchEnded = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		target->setColor(Color3B(0, 255, 0));
		if (targetBox.containsPoint(touchPoint))
		{
			SimpleAudioEngine::getInstance()->playEffect(pochi, false);
			mHand->SetInputFlag(true);
			if (mBoard->GetBoardSize() == 7) {
				mBoard->reset();
			}
			else if (mBoard->GetBoardSize() == 9) {
				mBoard->resetMurora();
			}
			else if (mBoard->GetBoardSize() == 15) {
				mBoard->resetMega();
			}
			else {
				mBoard->resetMoroi();
			}
			if (mComFlag == black) {
				mHand->SetInputFlag(false);
			}
			this->removeChildByName("pauseLayer");
			updateDraw();
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, square2);

	//ボタン3
	Sprite* square3 = Sprite::create();
	Sprite* square3_ = Sprite::create();
	square3->setTextureRect(rect1);
	square3->setPosition(origin.x + (visibleSize.width / 2), origin.y + visibleSize.height - 550);
	square3->setColor(Color3B(0, 255, 0));
	square3_->setTextureRect(rect1_);
	square3_->setPosition(square3->getPosition());
	square3_->setColor(Color3B(0, 0, 0));
	layer->addChild(square3, 2, "button3");
	layer->addChild(square3_, 1, "button3_");
	auto ButtonLabel3 = Label::createWithTTF("タイトルに戻る", FONT_NAME, 100);
	ButtonLabel3->setPosition(square3->getPosition());
	ButtonLabel3->setColor(Color3B(0, 0, 0));
	layer->addChild(ButtonLabel3, 3, "ButtonLabel3");
	auto listener3 = EventListenerTouchOneByOne::create();
	listener3->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			target->setColor(Color3B(255, 255, 0));
		}
		return true;
	};
	listener3->onTouchMoved = [this](Touch* touch, Event* event) {};
	listener3->onTouchEnded = [this](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		target->setColor(Color3B(0, 255, 0));
		if (targetBox.containsPoint(touchPoint))
		{
			SimpleAudioEngine::getInstance()->playEffect(cancel, false);
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(thinking);
			Director::getInstance()->replaceScene(TransitionRotoZoom::create(0.5f, Title::createScene()));
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3, square3);

}