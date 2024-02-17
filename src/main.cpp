/**
	Including the headers.
*/
#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/loader/Loader.hpp>
#include <cstdlib>
using namespace geode::prelude;
int randomnum = 0;
int t = 0;
/*
Geode as of writing this is adding node ids to the end level layer but 1, i did this before and just renaming the layers so when it comes out it doesn't break
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
	void SetupIDS(CCLayer* WinLayer) { 
		t=0;
		if(auto LevelComplete = getChildBySpriteFrameName(WinLayer, "GJ_levelComplete_001.png")) {
        		LevelComplete->setID("level-complete-text");
    		}
	else if (auto practiceTxt = getChildBySpriteFrameName(WinLayer, "GJ_practiceComplete_001.png")) {
       		 practiceTxt->setID("practice-complete-text");
  	  }
	 for(auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            if(std::string_view(bmFont->getString()).starts_with("Time:")) {
                bmFont->setID("time-label");
		t+=1;
                break;
            }
        }
    }
for(auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            if(std::string_view(bmFont->getString()).starts_with("Jumps:")) {
                bmFont->setID("jump-label");
		t+=1;
                break;
            }
        }
    }
for(auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            if(std::string_view(bmFont->getString()).starts_with("Attempts:")) {
                bmFont->setID("attempts-label");
		t+=1;
                break;
            }
        }
    }
for(auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            if(std::string_view(bmFont->getString()).starts_with("Points:")) {
                bmFont->setID("points-label");
		t+=1;
                break;
            }
        }
    }

	if (auto CCSprite0 = getChildOfType<CCSprite>(WinLayer, 0)) {
        CCSprite0->setID("chain-left");
    }
	if (auto CCSprite1 = getChildOfType<CCSprite>(WinLayer, 1)) {
        CCSprite1->setID("chain-right");
    }

    if (auto CCMENU0 = getChildOfType<CCMenu>(WinLayer, 0)) {
        CCMENU0->setID("hide-dropdown-menu");
    }
	 if (auto CCMENU1 = getChildOfType<CCMenu>(WinLayer, 1)) {
        CCMENU1->setID("button-menu");
		 if (auto CCMENUITEMS0 = getChildBySpriteFrameName(CCMENU1,"GJ_replayBtn_001.png")) {
			CCMENUITEMS0->setID("retry-button");
		 }
		  if (auto MenuButton = getChildBySpriteFrameName(CCMENU1,"GJ_menuBtn_001.png")) {
			MenuButton->setID("exit-button");
		 }
		 if (auto EditButton = getChildBySpriteFrameName(CCMENU1,"GJ_editBtn_001.png")) {
			EditButton->setID("edit-button");
		 }
		 if (auto leaderboardButton = getChildBySpriteFrameName(CCMENU1, "GJ_levelLeaderboardBtn_001.png")) {
        		leaderboardButton->setID("leaderboard-button");
   		 }

		  if (Loader::get()->isModLoaded("absolllute.megahack")) {
		if(auto MEGAHACK_INFO = getChildBySpriteFrameName(CCMENU1, "GJ_infoIcon_001.png")) {
        		MEGAHACK_INFO->setID("absolllute.megahack/cheat-indicator-info");
    		}
		if(auto MEGAHACK_ARROW = getChildBySpriteFrameName(CCMENU1, "GJ_arrow_02_001.png")) {
        		MEGAHACK_ARROW->setID("absolllute.megahack/hide-endscreen");
    		}
		if(auto GJ_practiceBtn_001 = getChildBySpriteFrameName(CCMENU1, "GJ_practiceBtn_001.png")) {
        		GJ_practiceBtn_001->setID("absolllute.megahack/practice-replay-button");
    		}
		  };
    }
	if (auto textField = getChildOfType<TextArea>(WinLayer, 0)) {
  	  textField->setID("complete-message");
	}
	else {
	if (auto end = getChildOfType<CCLabelBMFont>(WinLayer, t)) {
  	  		end->setID("end-text");
	}
	}
	if (auto gdlist = getChildOfType<GJListLayer>(WinLayer, 0)) {
        gdlist->setID("background");
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
		
		auto Buttons = WinLayer->getChildByID("button-menu");
		if (Loader::get()->isModLoaded("absolllute.megahack")) {
			if (Buttons->getChildByID("absolllute.megahack/practice-replay-button")) {
				Buttons->getChildByID("absolllute.megahack/practice-replay-button")->setPosition(winSize.width-328,-66);	
			}
			if (Buttons->getChildByID("absolllute.megahack/cheat-indicator-info")) {
		        	Buttons->getChildByID("absolllute.megahack/cheat-indicator-info")->setPosition(-138, 120);
			}
		}
			if (WinLayer->getChildByID("complete-message")) {  
				
				WinLayer->getChildByID("complete-message")->setPosition(73,winSize.height -211);
				WinLayer->getChildByID("complete-message")->setScale(0.5);
			}
			if (WinLayer->getChildByID("attempts-label")) { WinLayer->getChildByID("attempts-label")->setPosition(73,winSize.height -125); }
			if (WinLayer->getChildByID("jump-label")) { WinLayer->getChildByID("jump-label")->setPosition(73,winSize.height -149); }
			if (WinLayer->getChildByID("points-label")) { WinLayer->getChildByID("points-label")->setPosition(73,winSize.height -149); }
			if (WinLayer->getChildByID("time-label")) { 	WinLayer->getChildByID("time-label")->setPosition(73,winSize.height -173); }
			if (WinLayer->getChildByID("end-text")) { 	
				WinLayer->getChildByID("end-text")->setPosition(73,95);
				WinLayer->getChildByID("end-text")->setScale(0.425);
				randomnum = rand() % 8 + 1;
				if (randomnum == 1) {
				static_cast<cocos2d::CCLabelBMFont*>(WinLayer->getChildByID("end-text"))->setString("F in Chat");
				}
				if (randomnum == 2) {
				static_cast<cocos2d::CCLabelBMFont*>(WinLayer->getChildByID("end-text"))->setString("Take a Break");
				}
				if (randomnum == 3) {
				static_cast<cocos2d::CCLabelBMFont*>(WinLayer->getChildByID("end-text"))->setString(":0");
				}
				if (randomnum == 4) {
				static_cast<cocos2d::CCLabelBMFont*>(WinLayer->getChildByID("end-text"))->setString("oh my dayz");
				}
				if (randomnum == 5) {
				static_cast<cocos2d::CCLabelBMFont*>(WinLayer->getChildByID("end-text"))->setString("YAAAA");
				}
				if (randomnum == 6) {
				static_cast<cocos2d::CCLabelBMFont*>(WinLayer->getChildByID("end-text"))->setString("abcdefghijklmnop");
				}
				if (randomnum == 7) {
				static_cast<cocos2d::CCLabelBMFont*>(WinLayer->getChildByID("end-text"))->setString("123456789");
				}
				if (randomnum == 8) {
				static_cast<cocos2d::CCLabelBMFont*>(WinLayer->getChildByID("end-text"))->setString("W");
				}
				
			}
			WinLayer->getChildByID("background")->setPosition(-213,32);
			Buttons->getChildByID("retry-button")->setPosition(winSize.width-328,winSize.height-206);
			Buttons->getChildByID("exit-button")->setPosition(winSize.width-328,-133);
			if (WinLayer->getChildByID("edit-button")) { 	
				Buttons->getChildByID("edit-button")->setPosition(winSize.width-328,-1);
			}
			else {  
			if (WinLayer->getChildByID("leaderboard-button")) { 
			Buttons->getChildByID("leaderboard-button")->setPosition(winSize.width-328,-1);
			}
				else {
				if (Buttons->getChildByID("absolllute.megahack/practice-replay-button")) {
					Buttons->getChildByID("absolllute.megahack/practice-replay-button")->setPosition(winSize.width-328,-1);
				}
				else {
					Buttons->getChildByID("retry-button")->setPosition(winSize.width-328,winSize.height-250);
					Buttons->getChildByID("exit-button")->setPosition(winSize.width-328,-100);
				}
			     }
			}
			WinLayer->getChildByID("chain-right")->setVisible(false);
			WinLayer->getChildByID("chain-left")->setVisible(false);
		
				if(WinLayer->getChildByID("level-complete-text")) {
					WinLayer->getChildByID("level-complete-text")->setVisible(false);
				}
				else {
					WinLayer->getChildByID("practice-complete-text")->setVisible(false);
				}
			
				
		//WinLayer->setPosition(winSize.width-number, winSize.height)
		// And… behold! My famous Shrek’s warty penis skin quesadillas with Pinocchio’s squeezed testicles and a side of Lord Farquaad’s cum
	}
};
