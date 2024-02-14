/**
	Including the headers.
*/
#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
using namespace geode::prelude;
/**
	Hooks to the EndLevel Layer
*/
class $modify(EndLevelLayer){
	void customSetup() {
		EndLevelLayer::customSetup();
		// add yo ui stuff here
		auto winSize = CCDirector::get()->getWinSize();
		auto WinLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0));
		auto label = CCLabelBMFont::create("Hello End Screen", "bigFont.fnt");
        label->setPosition(100, 100);
        WinLayer->addChild(label);

		auto SS = CCLabelBMFont::create("_", "bigFont.fnt");
        SS->setPosition(winSize.width, winSize.height);
		SS->setID("Window Helper");
        WinLayer->addChild(SS);
	}
};