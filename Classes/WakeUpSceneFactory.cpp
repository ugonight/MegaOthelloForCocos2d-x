#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "WakeUpSceneFactory.h"
#include "Title.h"

USING_NS_CC;

cocos2d::Scene* WakeUpSceneFactory::create() {

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("thinking.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("pachin4.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("pochi.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("pochib.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("fall.ogg");

	auto scene = Scene::create();

	auto title = Title::create();
	scene->addChild(title, 0, 0);

	return scene;
}
