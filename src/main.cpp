/**
	Including the headers.
*/
#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
using namespace geode::prelude;
/**
	Hooks to the EndLevel Layer
*/

/*
Geode Hasn't got some Important Ui Stuff
*/
CCNode* getChildBySpriteFrameName(CCNode* parent, const char* name) {
    auto cache = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
    if (!cache) return nullptr;

    auto* texture = cache->getTexture();
    auto rect = cache->getRect();

    for (int i = 0; i < parent->getChildrenCount(); ++i) {
        auto* child = parent->getChildren()->objectAtIndex(i);
        if (auto* spr = typeinfo_cast<CCSprite*>(child)) {
            if (spr->getTexture() == texture && spr->getTextureRect() == rect) {
                return spr;
            }
        } else if (auto* btn = typeinfo_cast<CCMenuItemSprite*>(child)) {
            auto* img = btn->getNormalImage();
            if (auto* spr = typeinfo_cast<CCSprite*>(img)) {
                if (spr->getTexture() == texture && spr->getTextureRect() == rect) {
                    return btn;
                }
            }
        }
    }
    return nullptr;
}
// This just Makes it so you can get the texture by Sprite and stuff
class $modify(endLayer,EndLevelLayer){
	void SetupIDS(CCLayer* WinLayer) {
		if(auto LevelComplete = getChildBySpriteFrameName(WinLayer, "GJ_levelComplete_001.png")) {
        		LevelComplete->setID("Level Complete");
    		}
	 for(auto child : CCArrayExt<CCNode*>(this->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            if(std::string_view(bmFont->getString()).starts_with("Time:") && bmFont->getID().empty()) {
                bmFont->setID("Time-label");
                break;
            }
        }
    }
for(auto child : CCArrayExt<CCNode*>(this->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            if(std::string_view(bmFont->getString()).starts_with("Jumps:") && bmFont->getID().empty()) {
                bmFont->setID("Jump-label");
                break;
            }
        }
    }
for(auto child : CCArrayExt<CCNode*>(this->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            if(std::string_view(bmFont->getString()).starts_with("Attempts:") && bmFont->getID().empty()) {
                bmFont->setID("Attempts-label");
                break;
            }
        }
    }
	auto Index = static_cast<cocos2d::CCMenu*>(WinLayer->getChildren()->objectAtIndex(0)); // Index Number 0
		Index->setID("CCMenu_0")
	}
	auto Index = static_cast<cocos2d::CCMenu*>(WinLayer->getChildren()->objectAtIndex(1)); // Index Number 1
		Index->setID("CCMenu_1")
	}
	void customSetup() {
		EndLevelLayer::customSetup();
		auto WinLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0)); // CCLAYER REAL
		endLayer::SetupIDS(WinLayer);
		// add yo ui stuff here
		auto winSize = CCDirector::get()->getWinSize(); // screen size
		
		auto label = CCLabelBMFont::create("i am a text text", "bigFont.fnt");
		label->setScale(0.5);
        label->setPosition(winSize.width-286, winSize.height-244);
        WinLayer->addChild(label);

		auto SS = CCLabelBMFont::create("_", "bigFont.fnt");
        SS->setPosition(winSize.width, winSize.height);
		SS->setID("Window Helper");
		SS->setVisible(false);
        WinLayer->addChild(SS);
	}
};
