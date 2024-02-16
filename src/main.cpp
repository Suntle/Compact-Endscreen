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
bool DONOTCRASH = false;
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
static void onModify(auto & self)
    {
        self.setHookPriority("EndLevelLayer::init", -10000);
    }
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
		 if (auto CCMENUITEMS0 = getChildBySpriteFrameName(CCMENU1,"GJ_replayBtn_001.png")) {
			CCMENUITEMS0->setID("Retry");
		 }
		  if (auto MenuButton = getChildBySpriteFrameName(CCMENU1,"GJ_menuBtn_001.png")) {
			MenuButton->setID("MenuButton");
		 }
		 if (auto EditButton = getChildBySpriteFrameName(CCMENU1,"GJ_editBtn_001.png")) {
			EditButton->setID("EditButton");
		 }
		  if (Loader::get()->isModLoaded("absolllute.megahack")) {
		if(auto MEGAHACK_INFO = getChildBySpriteFrameName(CCMENU1, "GJ_infoIcon_001.png")) {
        		MEGAHACK_INFO->setID("MEGAHACK_INFO");
    		}
		if(auto MEGAHACK_ARROW = getChildBySpriteFrameName(CCMENU1, "GJ_arrow_02_001.png")) {
        		MEGAHACK_ARROW->setID("MEGAHACK_ARROW");
    		}
		if(auto GJ_practiceBtn_001 = getChildBySpriteFrameName(CCMENU1, "GJ_practiceBtn_001.png")) {
        		GJ_practiceBtn_001->setID("MEGAHACK_PRACTICEBTN");
    		}
		  };
    }
	if (auto textField = getChildOfType<TextArea>(WinLayer, 0)) {
  	  textField->setID("LevelVerified_TextField");
	}
	if (auto gdlist = getChildOfType<GJListLayer>(WinLayer, 0)) {
        gdlist->setID("Background_Textures");
    }

}
	void customSetup() {
		EndLevelLayer::customSetup();
		auto WinLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0)); // CCLAYER REAL
		endLayer::SetupIDS(WinLayer);
		auto winSize = CCDirector::get()->getWinSize();
		// add yo ui stuff here
		 // screen size
		/*
		EXAMPLE
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
		*/
		
		DONOTCRASH = false;
		auto Buttons = WinLayer->getChildByID("Buttons_Layer");
		if (Loader::get()->isModLoaded("absolllute.megahack")) {
			if (Buttons->getChildByID("MEGAHACK_PRACTICEBTN")) {
				DONOTCRASH = true;
				Buttons->getChildByID("MEGAHACK_PRACTICEBTN")->setPosition(winSize.width-328,-30);	
			}
			if (Buttons->getChildByID("MEGAHACK_INFO")) {
		        	Buttons->getChildByID("MEGAHACK_INFO")->setPosition(-138, 120);
			}
		}
			WinLayer->getChildByID("LevelVerified_TextField")->setPosition(73,winSize.height -211);
			WinLayer->getChildByID("LevelVerified_TextField")->setScale(0.5);
			WinLayer->getChildByID("Attempts-label")->setPosition(73,winSize.height -125);
			WinLayer->getChildByID("Jump-label")->setPosition(73,winSize.height -149);
			WinLayer->getChildByID("Background_Textures")->setPosition(-213,32);
			WinLayer->getChildByID("Time-label")->setPosition(73,winSize.height -173);
			Buttons->getChildByID("Retry")->setPosition(winSize.width-328,winSize.height-206);
			Buttons->getChildByID("MenuButton")->setPosition(winSize.width-328,-133);
			Buttons->getChildByID("EditButton")->setPosition(winSize.width-328,-1);	
			WinLayer->getChildByID("Chain_Right")->setVisible(false);
			WinLayer->getChildByID("Chain_Left")->setVisible(false);
			if (!DONOTCRASH) {
				WinLayer->getChildByID("Level-Complete")->setVisible(false);
			}
			else {
				WinLayer->getChildByID("Level-Complete")->setPosition(winSize.width*20,winSize.height*2);	
			};	
		//WinLayer->setPosition(winSize.width-number, winSize.height)
		// And… behold! My famous Shrek’s warty penis skin quesadillas with Pinocchio’s squeezed testicles and a side of Lord Farquaad’s cum
	}
};
