//
//  RankingScene.cpp
//  GameFireworks
//
//  Created by NgocDu on 13/11/04.
//
//

#include "RankingScene.h"
#include "GameManager.h"
#include "BeginScene.h"
using namespace cocos2d;

CCScene * RankingScene::scene() {
    CCScene * scene = CCScene::create();
    RankingScene * layer = RankingScene::create();
    scene->addChild(layer);
    return scene;
}

bool RankingScene::init() {
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
    background->setScaleX(SIZE_RATIO_X);
    background->setScaleY(SIZE_RATIO_Y);
    this->addChild(background);

    CCLabelTTF * lbRanking = CCLabelTTF::create("Ranking", "", 60 * SIZE_RATIO);
    lbRanking->setPosition(CCPoint(width / 2, height * 10 / 11));
    lbRanking->setColor(ccBLUE);
    this->addChild(lbRanking, 1);

    CCMenu *pMenu = CCMenu::create(NULL);
    pMenu->setPosition(ccp(0, 0));
    for (int i = 1; i <= 10; i++) {
        char strLevel[10];
        sprintf(strLevel, "Rank %i", i);
        CCLabelTTF * lbLevel = CCLabelTTF::create(strLevel, "", 35 * SIZE_RATIO);
        lbLevel->setAnchorPoint(ccp(0, 0.5));
        lbLevel->setPosition(ccp(width / 4,
                                 (64 * (13 - i) - 30) * SIZE_RATIO_Y));
        this->addChild(lbLevel, 1);

        char stri[20];
        sprintf(stri, "high_score%i", i);
        int score = CCUserDefault::sharedUserDefault()->getIntegerForKey(stri);

        char strScore[14];
        sprintf(strScore, "%i", score);

        CCLabelTTF * lbScore = CCLabelTTF::create(strScore, "", 35 * SIZE_RATIO);
        lbScore->setAnchorPoint(ccp(1, 0.5));
        lbScore->setPosition(ccp(width * 3 / 4, lbLevel->getPositionY()));
        this->addChild(lbScore, 1);
    }
    CCMenuItemImage * item =
    CCMenuItemImage::create("back.png", "back_hover.png", this,
                            menu_selector(RankingScene::clickBackMenu));
    item->setPosition(CCPoint(item->getContentSize().width / 2,
                              item->getContentSize().height / 2));
    pMenu->addChild(item);

    this->addChild(pMenu);
    return true;
}

void RankingScene::itemMethod(CCObject *pSender) {
    CCMenuItemImage * item = (CCMenuItemImage*)pSender;
    GameManager::sharedGameManager()->setLevel(item->getTag());
    CCDirector::sharedDirector()->replaceScene(GamePlayScene::scene());
}
void RankingScene::clickBackMenu(cocos2d::CCObject *pSender) {
    CCDirector::sharedDirector()->replaceScene(BeginScene::scene());
}
