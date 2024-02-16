/**
	Including the headers.
*/
#include <unordered_map>
#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/loader/Loader.hpp>
using namespace geode::prelude;
/**
	Hooks to the EndLevel Layer
*/
bool DONOTCRASH = false;
int i = 0;
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
		auto Buttons = getChildOfType<CCMenu>(WinLayer, 1);

		if (Loader::get()->isModLoaded("absolllute.megahack")) {
			if(auto MEGAHACK_INFO = Buttons->getChildByID("absolllute.megahack/cheat-indicator-info"))
			{
			MEGAHACK_INFO->setPosition(-138, 120);
			}
			else
			{
			if(auto MEGAHACK_INFO = getChildBySpriteFrameName(Buttons, "GJ_infoIcon_001.png")) {
		        	MEGAHACK_INFO->setPosition(-138, 120);
			}
			}
			if(auto MEGAHACK_PRACTICEBTN = Buttons->getChildByID("absolllute.megahack/practice-replay-button"))
			{
			DONOTCRASH = true;
			MEGAHACK_PRACTICEBTN->setPosition(winSize.width-328,-66);	
			}
			else {
			if(auto MEGAHACK_PRACTICEBTN = getChildBySpriteFrameName(Buttons, "GJ_practiceBtn_001.png")) {
				DONOTCRASH = true;
				MEGAHACK_PRACTICEBTN->setPosition(winSize.width-328,-66);	
			}
			
		}
		auto textField = getChildOfType<TextArea>(WinLayer, 0)  
  	  		textField->setPosition(73 ,winSize.height -211);
			textField->setScale(0.5);
		
		if (auto gdlist = getChildOfType<GJListLayer>(WinLayer, 0)) {
        		gdlist->setPosition(-213,32);
    		}
		i = 0;
		  for (auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
       			 if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
          		  if(std::string_view(bmFont->getString()).starts_with("Time:")) {
              		 	 bmFont->setPosition(73,winSize.height -173);
				  i+=1;
           		 }
           		 if(std::string_view(bmFont->getString()).starts_with("Jumps:")) {
            		    bmFont->setPosition(73,winSize.height -149);
				  i+=1;
           		 }
           		 if(std::string_view(bmFont->getString()).starts_with("Attempts:")) {
            		    bmFont->setPosition(73,winSize.height -125);
				   i+=1;
           		 }
			if (i > 2) {
			break;
			}
        }
    }
		
 		if (auto Retry = getChildBySpriteFrameName(Buttons,"GJ_replayBtn_001.png")) {
 			Retry->setPosition(winSize.width-328,winSize.height-206);
		 }
		  if (auto MenuButton = getChildBySpriteFrameName(Buttons,"GJ_menuBtn_001.png")) {
			MenuButton->setPosition(winSize.width-328,-133);
		 }
		 if (auto EditButton = getChildBySpriteFrameName(Buttons,"GJ_editBtn_001.png")) {
			EditButton->setPosition(winSize.width-328,-1);
		 }
		if (auto Chain_Right = getChildOfType<CCSprite>(WinLayer, 1)) {
			Chain_Right->setVisible(false);
		}
			
		if (auto Chain_Left = getChildOfType<CCSprite>(WinLayer, 0)) {
			Chain_Left->setVisible(false);
		}
			if (!DONOTCRASH) {
				if(auto LevelComplete = getChildBySpriteFrameName(WinLayer, "GJ_levelComplete_001.png")) {
				LevelComplete->setVisible(false);
				}
			}
			else {
				//WinLayer->getChildByID("Level-Complete")->setPosition(winSize.width*20,winSize.height*2);	
			};	
		//WinLayer->setPosition(winSize.width-number, winSize.height)
	}
	}
};
