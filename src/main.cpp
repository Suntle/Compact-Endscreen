/**
	Including the headers.
*/
#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/loader/Loader.hpp>
#include <cstdlib>
#include <Geode/cocos/label_nodes/CCLabelBMFont.h>
using namespace geode::prelude;
int randomnum = 0;
int CoinCount = 0;
int t = 0;
/*
Geode as of writing this is adding node ids to the end level layer but 1, i did this before and just renaming the layers so when it comes out it doesn't break
*/
// This just Makes it so you can get the texture by Sprite and stuff 
bool isSpriteFrameName_1(CCNode* node, const char* name) {
    auto cache = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
    if (!cache) return false;

    auto* texture = cache->getTexture();
    auto rect = cache->getRect();

    if (auto* spr = typeinfo_cast<CCSprite*>(node)) {
        if (spr->getTexture() == texture && spr->getTextureRect() == rect) {
            return true;
        }
    } else if (auto* btn = typeinfo_cast<CCMenuItemSprite*>(node)) {
        auto* img = btn->getNormalImage();
        if (auto* spr = typeinfo_cast<CCSprite*>(img)) {
            if (spr->getTexture() == texture && spr->getTextureRect() == rect) {
                return true;
            }
        }
    }
    return false;
}
CCNode* getChildBySpriteFrameName_1(CCNode* parent, const char* name) {
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

		 if (auto CCMENU1 = getChildOfType<CCMenu>(WinLayer, 1)) {
        if (Loader::get()->isModLoaded("absolllute.megahack")) {
		if(auto MEGAHACK_INFO = getChildBySpriteFrameName_1(CCMENU1, "GJ_infoIcon_001.png")) {
        		MEGAHACK_INFO->setID("absolllute.megahack/cheat-indicator-info");
    		}
		if(auto MEGAHACK_ARROW = getChildBySpriteFrameName_1(CCMENU1, "GJ_arrow_02_001.png")) {
        		MEGAHACK_ARROW->setID("absolllute.megahack/hide-endscreen");
    		}
		if(auto GJ_practiceBtn_001 = getChildBySpriteFrameName_1(CCMENU1, "GJ_practiceBtn_001.png")) {
        		GJ_practiceBtn_001->setID("absolllute.megahack/practice-replay-button");
    		}
		  };
    };
int currentCoin = 1;
int coinstoplace = 0;
	CoinCount = 0;
    std::vector<CCPoint> coinPos;
    for (auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
        for (auto framename : {
            "secretCoin_b_01_001.png",
            "secretCoin_2_b_01_001.png"
        }) {
            if (isSpriteFrameName_1(child, framename)) {
				if (!Loader::get()->isModLoaded("geode.node-ids")) {
                child->setID(fmt::format("coin-{}-background", currentCoin));
                coinPos.push_back(child->getPosition());
				}
                currentCoin += 1;
		CoinCount += 1;
            }
        }
    }
	for (auto child : CCArrayExt<CCNode*>(m_coinsToAnimate)) {
        	for (int i = 1; i < currentCoin; i++) {
           		if (child->getID().empty() && child->getPosition() == coinPos[i - 1]) {
					  child->setVisible(false)
					  coinstoplace =+1
          		  }
        		}
   		}
		 for (auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
        for (int i = 1; i < currentCoin; i++) {
            if (child->getID().empty() && child->getPosition() == coinPos[i - 1]) {
               coinstoplace=+1
            }
        }
		 }

		
		if (Loader::get()->isModLoaded("geode.node-ids")) {
            return;
        };

		if(auto LevelComplete = getChildBySpriteFrameName_1(WinLayer, "GJ_levelComplete_001.png")) {
        		LevelComplete->setID("level-complete-text");
    		}
	else if (auto practiceTxt = getChildBySpriteFrameName_1(WinLayer, "GJ_practiceComplete_001.png")) {
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
                bmFont->setID("jumps-label");
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

	for (auto child : CCArrayExt<CCNode*>(m_coinsToAnimate)) {
        	for (int i = 1; i < currentCoin; i++) {
           		if (child->getID().empty() && child->getPosition() == coinPos[i - 1]) {
              		  child->setID(fmt::format("coin-{}-sprite", i));
          		  }
        		}
   		}
    for (auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
        for (int i = 1; i < currentCoin; i++) {
            if (child->getID().empty() && child->getPosition() == coinPos[i - 1]) {
                child->setID(fmt::format("coin-{}-sprite", i));
            }
        }
    }

}
void showLayer(bool p0) {
 	EndLevelLayer::showLayer(p0);
	auto WinLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0)); // CCLAYER REAL
	for (auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
            if (auto star = getChildBySpriteFrameName_1(child, "GJ_bigStar_001.png")) {
                child->setPosition(114.500,228);
		child->setScale(0.8);
            }
            else if (auto moon = getChildBySpriteFrameName_1(child, "GJ_bigMoon_001.png")) {
                child->setPosition(114.500,228);
		child->setScale(0.8);
            }
            else if (auto orb = getChildBySpriteFrameName_1(child, "currencyOrbIcon_001.png")) {
                child->setPosition(47.500,228);
		child->setScale(0.8);
            }
            else if (auto diamond = getChildBySpriteFrameName_1(child, "GJ_bigDiamond_001.png")) {
                child->setPosition(114.500,247);
		child->setScale(0.8);
            }
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
				WinLayer->getChildByID("complete-message")->setVisible(true);
			}
			if (WinLayer->getChildByID("attempts-label")) { WinLayer->getChildByID("attempts-label")->setPosition(73,winSize.height -125); }
			if (WinLayer->getChildByID("jumps-label")) { WinLayer->getChildByID("jumps-label")->setPosition(73,winSize.height -149); }
			if (WinLayer->getChildByID("points-label")) { WinLayer->getChildByID("points-label")->setPosition(73,winSize.height -149); }
			if (WinLayer->getChildByID("time-label")) { 	WinLayer->getChildByID("time-label")->setPosition(73,winSize.height -173); }
			if (WinLayer->getChildByID("end-text")) { 	
				WinLayer->getChildByID("end-text")->setPosition(73,95);
				WinLayer->getChildByID("end-text")->setScale(0.425);
				randomnum = rand() % 1000 + 1;
				static_cast<cocos2d::CCLabelBMFont*>(WinLayer->getChildByID("end-text"))->limitLabelWidth(35,0.425,0.1);
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
				if (randomnum == 9) {
				static_cast<cocos2d::CCLabelBMFont*>(WinLayer->getChildByID("end-text"))->setString("¿Cuándo sales alguna vez afuera?");
				}
				if (randomnum == 10) {
				static_cast<cocos2d::CCLabelBMFont*>(WinLayer->getChildByID("end-text"))->setString("Megahack Update When?");
				}
				
			}
		
		if (CoinCount > 0) {
			if (CoinCount == 3) {
			WinLayer->getChildByID("coin-1-background")->setPosition(167,216);
				WinLayer->getChildByID("coin-1-background")->setScale(0.5);
				if (WinLayer->getChildByID("coin-1-sprite")) { 
					WinLayer->getChildByID("coin-1-sprite")->setPosition(167,216);
					WinLayer->getChildByID("coin-1-sprite")->setScale(0.5);
				}
				WinLayer->getChildByID("coin-2-background")->setPosition(167,190);
				WinLayer->getChildByID("coin-2-background")->setScale(0.5);
				if (WinLayer->getChildByID("coin-2-sprite")) { 
					WinLayer->getChildByID("coin-2-sprite")->setPosition(167,190);
					WinLayer->getChildByID("coin-2-sprite")->setScale(0.5);
				}
				WinLayer->getChildByID("coin-3-background")->setPosition(167,164);
				WinLayer->getChildByID("coin-3-background")->setScale(0.5);
				if (WinLayer->getChildByID("coin-3-sprite")) { 
					WinLayer->getChildByID("coin-3-sprite")->setPosition(167,164);
					WinLayer->getChildByID("coin-3-sprite")->setScale(0.5);
				}
				// 167
				// 216
				// 190
				// 164
			}
			if (CoinCount == 2) {
				WinLayer->getChildByID("coin-1-background")->setPosition(167,190);
				WinLayer->getChildByID("coin-1-background")->setScale(0.5);
				if (WinLayer->getChildByID("coin-1-sprite")) { 
					WinLayer->getChildByID("coin-1-sprite")->setPosition(167,190);
					WinLayer->getChildByID("coin-1-sprite")->setScale(0.5);
				}
				WinLayer->getChildByID("coin-2-background")->setPosition(167,164);
				WinLayer->getChildByID("coin-2-background")->setScale(0.5);
				if (WinLayer->getChildByID("coin-2-sprite")) { 
					WinLayer->getChildByID("coin-2-sprite")->setPosition(167,164);
					WinLayer->getChildByID("coin-2-sprite")->setScale(0.5);
				}
			}
			if (CoinCount == 1) {
				WinLayer->getChildByID("coin-1-background")->setPosition(167,164);
				WinLayer->getChildByID("coin-1-background")->setScale(0.5);
				if (WinLayer->getChildByID("coin-1-sprite")) { 
					WinLayer->getChildByID("coin-1-sprite")->setPosition(167,164);
					WinLayer->getChildByID("coin-1-sprite")->setScale(0.5);
				}
			}
			
		}
		// 26
		// 165.500, 227 coins, 0.5 size
			WinLayer->getChildByID("background")->setPosition(-213,32);
			Buttons->getChildByID("retry-button")->setPosition(winSize.width-328,winSize.height-206);
			Buttons->getChildByID("exit-button")->setPosition(winSize.width-328,-133);
			bool moved = false; 
			if (Buttons->getChildByID("edit-button")) { 	
				Buttons->getChildByID("edit-button")->setPosition(winSize.width-328,-1);
				moved=true;
			}  
				if (Buttons->getChildByID("leaderboard-button")) { 
					if (!moved) {
						Buttons->getChildByID("leaderboard-button")->setPosition(winSize.width-328,-1);
						moved=true;
					}
				}  
				
					if (Buttons->getChildByID("absolllute-megahack-practice-replay-button")) {
						if (!moved) {
							Buttons->getChildByID("absolllute-megahack-practice-replay-button")->setPosition(winSize.width-328,-1);
							moved=true;
						}
				}  
		
				if (!moved) {
					if (!Buttons->getChildByID("absolllute-megahack-practice-replay-button")) {
						Buttons->getChildByID("retry-button")->setPosition(winSize.width-328,winSize.height-250);
						Buttons->getChildByID("exit-button")->setPosition(winSize.width-328,winSize.height-348);
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
	}
};
