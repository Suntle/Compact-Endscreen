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
		auto winSize = CCDirector::get()->getWinSize(); // screen size
		auto WinLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0)); // CCLAYER REAL
		auto label = CCLabelBMFont::create("i am a text text", "bigFont.fnt");
		label->setScale(0.5);
        label->setPosition(winSize.width-286, winSize.height-244);
        WinLayer->addChild(label);

		auto SS = CCLabelBMFont::create("_", "bigFont.fnt");
        SS->setPosition(winSize.width, winSize.height);
		SS->setID("Window Helper");
        WinLayer->addChild(SS);
	}
};