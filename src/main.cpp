/**
	Including the headers.
*/
#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/loader/Loader.hpp>
using namespace geode::prelude;
/**
	Hooks to the EndLevel Layer
*/

/*
Geode Hasn't got some Important Ui String names so i needed to do it
*/
// This just Makes it so you can get the texture by Sprite and stuff 
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

class $modify(endLayer,EndLevelLayer){
	void SetupIDS(CCLayer* WinLayer) { // this functions setups names for suntle as he is less knowing of c++ code
	WinLayer->setID("End-Level-UI");
		if(auto LevelComplete = getChildBySpriteFrameName(WinLayer, "GJ_levelComplete_001.png")) {
        		LevelComplete->setID("Level-Complete");
    		}
	 for(auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            if(std::string_view(bmFont->getString()).starts_with("Time:")) {
                bmFont->setID("Time-label");
                break;
            }
        }
    }
for(auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            if(std::string_view(bmFont->getString()).starts_with("Jumps:")) {
                bmFont->setID("Jump-label");
                break;
            }
        }
    }
for(auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            if(std::string_view(bmFont->getString()).starts_with("Attempts:")) {
                bmFont->setID("Attempts-label");
                break;
            }
        }
    }

	if (auto CCSprite0 = getChildOfType<CCSprite>(WinLayer, 0)) {
        CCSprite0->setID("Chain_Left");
    }
	if (auto CCSprite1 = getChildOfType<CCSprite>(WinLayer, 1)) {
        CCSprite1->setID("Chain_Right");
    }

    if (auto CCMENU0 = getChildOfType<CCMenu>(WinLayer, 0)) {
        CCMENU0->setID("Top_Menu");
    }
	 if (auto CCMENU1 = getChildOfType<CCMenu>(WinLayer, 1)) {
        CCMENU1->setID("Buttons_Layer");
		 if (auto CCMENUITEMS0 = getChildOfType<CCMenuItemSpriteExtra>(CCMENU1, 0)) {
			CCMENUITEMS0->setID("Retry");
		 }
		  if (auto MenuButton = getChildOfType<CCMenuItemSpriteExtra>(CCMENU1, 1)) {
			MenuButton->setID("MenuButton");
		 }
		 if (auto EditButton = getChildOfType<CCMenuItemSpriteExtra>(CCMENU1, 2)) {
			EditButton->setID("EditButton");
		 }
		  if (Loader::get()->isModLoaded("absolllute.megahack")) {
		  	if (auto MEGAHACK_INFO = getChildOfType<CCMenuItemSpriteExtra>(CCMENU1, 3)) {
				MEGAHACK_INFO->setID("MEGAHACK_INFO");
		 	}
			if (auto MEGAHACK_ARROW = getChildOfType<CCMenuItemSpriteExtra>(CCMENU1, 4)) {
				MEGAHACK_ARROW->setID("MEGAHACK_ARROW");
		 	}
		  };
    }
	if (auto textField = getChildOfType<TextArea>(WinLayer, 0)) {
  	  textField->setID("LevelVerified_TextField");
	}
	if (auto gdlist = getChildOfType<GJListLayer>(WinLayer, 0)) {
        gdlist->setID("Background");
    }
}
	void customSetup() {
		EndLevelLayer::customSetup();
		auto WinLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0)); // CCLAYER REAL
		endLayer::SetupIDS(WinLayer);
		// add yo ui stuff here
		auto winSize = CCDirector::get()->getWinSize(); // screen size
		
		auto label = CCLabelBMFont::create("i am a text text", "bigFont.fnt");
		label->setScale(0.5);
		label->setID("TestText");
        label->setPosition(winSize.width-286, winSize.height-244);
        WinLayer->addChild(label);

		auto SS = CCLabelBMFont::create("_", "bigFont.fnt");
        SS->setPosition(winSize.width, winSize.height);
		SS->setID("Window Helper");
		SS->setVisible(false);
        WinLayer->addChild(SS);

		WinLayer->setPosition(winSize.width-number, winSize.height)
	}
};
