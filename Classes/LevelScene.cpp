//
//  LevelScene.cpp
//  GameFireworks
//
//  Created by macbook_016 on 2013/10/31.
//
//

#include "LevelScene.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "BeginScene.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene * LevelScene::scene() {
    CCScene * scene = CCScene::create();
    LevelScene * layer = LevelScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    levelmax = CCUserDefault::sharedUserDefault()->getIntegerForKey("level");
    size = CCDirector::sharedDirector()->getWinSize();
    width = size.width;
    height = size.height;
    SIZE_RATIO = (width + height) / (640 + 960);
    SIZE_RATIO_X = width / 640;
    SIZE_RATIO_Y = height / 960;
    //background
    CCSprite * background = CCSprite::create("bg.png");
    background->setAnchorPoint(ccp(0.5, 0.5));
    background->setPosition(ccp(width / 2, height / 2));
    background->setScale(SIZE_RATIO);
    this->addChild(background);
    CCMenu *pMenu = CCMenu::create(NULL);
    pMenu->setPosition(ccp(0, 0));
    int dem = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            CCMenuItemImage * item =
            CCMenuItemImage::create("unlock.png", "unlock.png", this,
                                    menu_selector(LevelScene::itemMethod));
            dem ++;
            item->setTag(dem);
            item->setPosition(ccp((50 + 150 * (j + 1)) * SIZE_RATIO_X,
                                  (50 + 200 * (4 - i)) * SIZE_RATIO_Y));
            item->setScale(0.5 * SIZE_RATIO);
            pMenu->addChild(item);
            char spriteName[4];
            sprintf(spriteName, "%i", dem);
            CCLabelTTF * label = CCLabelTTF::create(spriteName, "Time new Roman", 40);
            label->setAnchorPoint(ccp(0.5f, 0.5f));
            label->setColor(ccc3(200, 50, 150));
            this->addChild(label, 100);
            if (dem > levelmax) {
                item->setVisible(false);
                CCSprite * sp = CCSprite::create("lock.png");
                sp->setPosition(ccp((50 + 150 * (j + 1)) * SIZE_RATIO_X,
                                    (50 + 200 * (4 - i)) * SIZE_RATIO_Y));
                sp->setScale(0.5 * SIZE_RATIO);
                label->setPosition(ccp((50 + 150 * (j + 1)) * SIZE_RATIO_X,
                                       (30 + 200 * (4 - i)) * SIZE_RATIO_Y));
                this->addChild(sp);
            } else label->setPosition(ccp((30 + 150 * (j + 1)) * SIZE_RATIO_X,
                                          (30 + 200 * (4 - i)) * SIZE_RATIO_Y));
        }
    }
    CCMenuItemImage * item =
    CCMenuItemImage::create("button_large.png", "button_large.png", this,
                            menu_selector(LevelScene::clickBackMenu));
    item->setPosition(CCPoint(size.width / 2, size.height / 14));
//    item->setScale(0.25 * SIZE_RATIO);
    pMenu->addChild(item);
    
    this->addChild(pMenu);
    return true;
}

void LevelScene::itemMethod(CCObject *pSender) {
    CCMenuItemImage * item = (CCMenuItemImage*)pSender;
    GameManager::sharedGameManager()->setLevel(item->getTag());
    CCDirector::sharedDirector()->replaceScene(GamePlayScene::scene());
}
void LevelScene::clickBackMenu(cocos2d::CCObject *pSender) {
    CCDirector::sharedDirector()->replaceScene(BeginScene::scene());
}
