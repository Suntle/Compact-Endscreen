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
		
		auto label = CCLabelBMFont::create("Hello End Screen", "bigFont.fnt");
        label->setPosition(100, 100);
        this->addChild(label);
	}
};