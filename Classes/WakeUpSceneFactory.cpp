#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

#include "WakeUpSceneFactory.h"
#include "Title.h"

USING_NS_CC;

cocos2d::Scene* WakeUpSceneFactory::create() {

	AudioEngine::preload("thinking.ogg");
	AudioEngine::preload("pachin4.ogg");
	AudioEngine::preload("pochi.ogg");
	AudioEngine::preload("pochib.ogg");
	AudioEngine::preload("fall.ogg");

	auto scene = Scene::create();

	auto title = Title::create();
	scene->addChild(title, 0, 0);

	return scene;
}
