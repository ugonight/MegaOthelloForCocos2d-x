#include "Util.h"

void Util::changeLabelText(cocos2d::Label* label, std::string text) {
	auto _label = label;
	auto fontSize = _label->getRenderingFontSize();

	// _label->autorelease();
	label = cocos2d::Label::createWithTTF(text, FONT_NAME, fontSize);
	label->setPosition(_label->getPosition());
	label->setColor(_label->getColor());
	label->setTextColor(_label->getTextColor());
	label->setAnchorPoint(_label->getAnchorPoint());
	// label->setString(text);

	auto parent = _label->getParent();
	parent->addChild(label, _label->getLocalZOrder(), _label->getName());
	parent->removeChild(_label);
}