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
using NodeIdTable = std::unordered_map<std::string, cocos2d::CCNode*>;
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
static SetupIDS(CCLayer* WinLayer) {
        NodeIdTable nodeIds;

        nodeIds["WinLayer"] = WinLayer;

        if (auto LevelComplete = getChildBySpriteFrameName(WinLayer, "GJ_levelComplete_001.png")) {
            nodeIds["LevelComplete"] = LevelComplete;
        }

        for (auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
            if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
                if (std::string_view(bmFont->getString()).starts_with("Time:")) {
                    nodeIds["Time-label"] = bmFont;
                    break;
                }
            }
        }

        for (auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
            if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
                if (std::string_view(bmFont->getString()).starts_with("Jumps:")) {
                    bmFont->setID("Jump-label");
                    nodeIds["Jump-label"] = bmFont;
                    break;
                }
            }
        }

        for (auto child : CCArrayExt<CCNode*>(WinLayer->getChildren())) {
            if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
                if (std::string_view(bmFont->getString()).starts_with("Attempts:")) {
                    nodeIds["Attempts-label"] = bmFont;
                    break;
                }
            }
        }

        if (auto CCSprite0 = getChildOfType<CCSprite>(WinLayer, 0)) {
            nodeIds["Chain_Left"] = CCSprite0;
        }

        if (auto CCSprite1 = getChildOfType<CCSprite>(WinLayer, 1)) {
            nodeIds["Chain_Right"] = CCSprite1;
        }

        if (auto CCMENU0 = getChildOfType<CCMenu>(WinLayer, 0)) {
            nodeIds["Top_Menu"] = CCMENU0;
        }

        if (auto CCMENU1 = getChildOfType<CCMenu>(WinLayer, 1)) {
            nodeIds["Buttons_Layer"] = CCMENU1;

            if (auto CCMENUITEMS0 = getChildBySpriteFrameName(CCMENU1,"GJ_replayBtn_001.png")) {
                nodeIds["Retry"] = CCMENUITEMS0;
            }

            if (auto MenuButton = getChildBySpriteFrameName(CCMENU1,"GJ_menuBtn_001.png")) {
                nodeIds["MenuButton"] = MenuButton;
            }

            if (auto EditButton = getChildBySpriteFrameName(CCMENU1,"GJ_editBtn_001.png")) {
                nodeIds["EditButton"] = EditButton;
            }

            if (Loader::get()->isModLoaded("absolllute.megahack")) {
                if (auto MEGAHACK_INFO = getChildBySpriteFrameName(CCMENU1, "GJ_infoIcon_001.png")) {
                    nodeIds["MEGAHACK_INFO"] = MEGAHACK_INFO;
                }
                if (auto MEGAHACK_ARROW = getChildBySpriteFrameName(CCMENU1, "GJ_arrow_02_001.png")) {
                    nodeIds["MEGAHACK_ARROW"] = MEGAHACK_ARROW;
                }
                if (auto GJ_practiceBtn_001 = getChildBySpriteFrameName(CCMENU1, "GJ_practiceBtn_001.png")) {
                    nodeIds["MEGAHACK_PRACTICEBTN"] = GJ_practiceBtn_001;
                }
            }
        }

        if (auto textField = getChildOfType<TextArea>(WinLayer, 0)) {
            nodeIds["LevelVerified_TextField"] = textField;
        }

        if (auto gdlist = getChildOfType<GJListLayer>(WinLayer, 0)) {
            nodeIds["Background_Textures"] = gdlist;
        }

        return nodeIds;
    }

	void customSetup() {
		EndLevelLayer::customSetup();
		auto WinLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0)); // CCLAYER REAL
		auto nodeIds = SetupIDS(WinLayer);
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
		auto Buttons = nodeIds["Buttons_Layer"];
		if (Loader::get()->isModLoaded("absolllute.megahack")) {
			if (nodeIds["MEGAHACK_PRACTICEBTN"]) {
				DONOTCRASH = true;
				nodeIds["MEGAHACK_PRACTICEBTN"]->setPosition(winSize.width-328,-66);	
			}
			if (nodeIds["MEGAHACK_INFO"]) {
		        	nodeIds["MEGAHACK_INFO"]->setPosition(-138, 120);
			}
		}
			nodeIds["LevelVerified_TextField"]->setPosition(73,winSize.height -211);
			nodeIds["LevelVerified_TextField"]->setScale(0.5);
			nodeIds["Attempts-label"]->setPosition(73,winSize.height -125);
			nodeIds["Jump-label"]->setPosition(73,winSize.height -149);
			nodeIds["Background_Textures"]->setPosition(-213,32);
			nodeIds["Time-label"]->setPosition(73,winSize.height -173);
			nodeIds["Retry"]->setPosition(winSize.width-328,winSize.height-206);
			nodeIds["MenuButton"]->setPosition(winSize.width-328,-133);
			nodeIds["EditButton"]->setPosition(winSize.width-328,-1);	
			nodeIds["Chain_Right"]->setVisible(false);
			nodeIds["Chain_Left"]->setVisible(false);
			if (!DONOTCRASH) {
				nodeIds["Level-Complete"]->setVisible(false);
			}
			else {
				//WinLayer->getChildByID("Level-Complete")->setPosition(winSize.width*20,winSize.height*2);	
			};	
		//WinLayer->setPosition(winSize.width-number, winSize.height)
	}
};
