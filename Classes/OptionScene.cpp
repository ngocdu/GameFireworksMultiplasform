//
//  OptionScene.cpp
//  GameFireworks
//
//  Created by NgocDu on 13/11/15.
//
//

#include "OptionScene.h"
#include "cocos2d.h"
#include "HelpScene.h"
#include "BeginScene.h"
#include "GameManager.h"
#include "GamePlaySceneNew.h"
using namespace cocos2d;

CCScene* OptionScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    OptionScene *layer = OptionScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OptionScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem =
    CCMenuItemImage::create("back.png", "back_hover.png", this,
                            menu_selector(OptionScene::menuCloseCallback) );
    pCloseItem->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    pCloseItem->
    setPosition(ccp(pCloseItem->getContentSize().width * pCloseItem->getScaleX()/2,
                    pCloseItem->getContentSize().height* pCloseItem->getScaleY()/2));
    CCMenuItemImage *imageLevel =
    CCMenuItemImage::create("table_lever.png", "table_lever.png", this,
                            menu_selector(OptionScene::btClickPlay) );
    imageLevel->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    imageLevel->
    setPosition(CCPoint(size.width - imageLevel->getContentSize().width *
                        imageLevel->getScaleX() / 2,
                        imageLevel->getContentSize().height* imageLevel->getScaleY() / 2));

    CCLabelTTF *lbLevel = CCLabelTTF::create("PLAY", "UTM American Sans", 20);
    lbLevel->
    setPosition(CCPoint(imageLevel->getPosition().x, imageLevel->getPosition().y +
                        imageLevel->getContentSize().height / 4 *
                        imageLevel->getScaleY()));
    lbLevel->setColor(ccc3(255, 100, 100));
    lbLevel->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    this->addChild(lbLevel, 12);

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, imageLevel, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    // add "BeginScene" splash screen"
    CCSprite* pSprite = CCSprite::create("bg_option_ipad.png");
    pSprite->setScaleX(GameManager::sharedGameManager()->getSIZE_RATIO_X());
    pSprite->setScaleY(GameManager::sharedGameManager()->getSIZE_RATIO_Y());
    // position the sprite on the center of the screen
    pSprite->setPosition(CCPoint(size.width/2, size.height/2));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    this->addBackground();
    return true;
}
void OptionScene::addBackground() {
    CCMenuItemImage *pCloseItem1 =
    CCMenuItemImage::create("frame_rocket01.png", "frame_rocket01.png", this,
                            menu_selector(OptionScene::btClick));
    pCloseItem1->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    pCloseItem1->
    setPosition(ccp(155 * GameManager::sharedGameManager()->getSIZE_RATIO_X() +
                    pCloseItem1->getContentSize().width * pCloseItem1->getScaleX()/2,
                    162 * GameManager::sharedGameManager()->getSIZE_RATIO_Y() +
                    pCloseItem1->getContentSize().height * pCloseItem1->getScaleY()/2));
    pCloseItem1->setTag(1);
    CCMenuItemImage *pCloseItem2 =
    CCMenuItemImage::create("frame_rocket02.png", "frame_rocket02.png", this,
                            menu_selector(OptionScene::btClick));
    pCloseItem2->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    pCloseItem2->
    setPosition(ccp(155 * GameManager::sharedGameManager()->getSIZE_RATIO_X() +
                    pCloseItem2->getContentSize().width * pCloseItem2->getScaleX() * 3 / 2,
                    162 * GameManager::sharedGameManager()->getSIZE_RATIO_Y() +
                    pCloseItem2->getContentSize().height * pCloseItem2->getScaleY() / 2));
    pCloseItem2->setTag(2);

    CCMenuItemImage *pCloseItem3 =
    CCMenuItemImage::create("frame_rocket03.png", "frame_rocket03.png", this,
                            menu_selector(OptionScene::btClick));
    pCloseItem3->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    pCloseItem3->
    setPosition(ccp(155 * GameManager::sharedGameManager()->getSIZE_RATIO_X() +
                    pCloseItem2->getContentSize().width * pCloseItem2->getScaleX() * 5 / 2,
                    162 * GameManager::sharedGameManager()->getSIZE_RATIO_Y() +
                    pCloseItem2->getContentSize().height * pCloseItem2->getScaleY() / 2));
    pCloseItem3->setTag(3);

    CCMenuItemImage *pCloseItem4 =
    CCMenuItemImage::create("frame_rocket04.png", "frame_rocket04.png", this,
                            menu_selector(OptionScene::btClick));
    pCloseItem4->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    pCloseItem4->
    setPosition(ccp(155 * GameManager::sharedGameManager()->getSIZE_RATIO_X() +
                    pCloseItem2->getContentSize().width * pCloseItem2->getScaleX() / 2,
                    162 * GameManager::sharedGameManager()->getSIZE_RATIO_Y() +
                    pCloseItem2->getContentSize().height * pCloseItem2->getScaleY() * 3 / 2));
    pCloseItem4->setTag(4);

    CCMenuItemImage *pCloseItem5 =
    CCMenuItemImage::create("frame_rocket05.png", "frame_rocket05.png", this,
                            menu_selector(OptionScene::btClick));
    pCloseItem5->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    pCloseItem5->
    setPosition(ccp(155 * GameManager::sharedGameManager()->getSIZE_RATIO_X() +
                    pCloseItem2->getContentSize().width * pCloseItem2->getScaleX() * 3 / 2,
                    162 * GameManager::sharedGameManager()->getSIZE_RATIO_Y() +
                    pCloseItem2->getContentSize().height * pCloseItem2->getScaleY() * 3 / 2));
    pCloseItem5->setTag(5);

    CCMenuItemImage *pCloseItem6 =
    CCMenuItemImage::create("frame_rocket06.png", "frame_rocket06.png", this,
                            menu_selector(OptionScene::btClick));
    pCloseItem6->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    pCloseItem6->
    setPosition(ccp(155 * GameManager::sharedGameManager()->getSIZE_RATIO_X() +
                    pCloseItem2->getContentSize().width * pCloseItem2->getScaleX() * 5 / 2,
                    162 * GameManager::sharedGameManager()->getSIZE_RATIO_Y() +
                    pCloseItem2->getContentSize().height * pCloseItem2->getScaleY() * 3 / 2));
    pCloseItem6->setTag(6);

    CCMenuItemImage *pCloseItem7 =
    CCMenuItemImage::create("frame_rocket07.png", "frame_rocket07.png", this,
                            menu_selector(OptionScene::btClick));
    pCloseItem7->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    pCloseItem7->
    setPosition(ccp(155 * GameManager::sharedGameManager()->getSIZE_RATIO_X() +
                    pCloseItem2->getContentSize().width * pCloseItem2->getScaleX() / 2,
                    162 * GameManager::sharedGameManager()->getSIZE_RATIO_Y() +
                    pCloseItem2->getContentSize().height * pCloseItem2->getScaleY() * 5 / 2));
    pCloseItem7->setTag(7);

    CCMenuItemImage *pCloseItem8 =
    CCMenuItemImage::create("frame_rocket08.png", "frame_rocket08.png", this,
                            menu_selector(OptionScene::btClick));
    pCloseItem8->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    pCloseItem8->
    setPosition(ccp(155 * GameManager::sharedGameManager()->getSIZE_RATIO_X() +
                    pCloseItem2->getContentSize().width * pCloseItem2->getScaleX() * 3 / 2,
                    162 * GameManager::sharedGameManager()->getSIZE_RATIO_Y() +
                    pCloseItem2->getContentSize().height * pCloseItem2->getScaleY() * 5 / 2));
    pCloseItem8->setTag(8);

    CCMenuItemImage *pCloseItem9 =
    CCMenuItemImage::create("frame_rocket09.png", "frame_rocket09.png", this,
                            menu_selector(OptionScene::btClick));
    pCloseItem9->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    pCloseItem9->
    setPosition(ccp(155 * GameManager::sharedGameManager()->getSIZE_RATIO_X() +
                    pCloseItem2->getContentSize().width * pCloseItem2->getScaleX() * 5 / 2,
                    162 * GameManager::sharedGameManager()->getSIZE_RATIO_Y() +
                    pCloseItem2->getContentSize().height * pCloseItem2->getScaleY() * 5 / 2));
    pCloseItem9->setTag(9);

    // create menu, it's an autorelease object
    pMenu = CCMenu::create(pCloseItem1, pCloseItem2, pCloseItem3, pCloseItem4,
                           pCloseItem5, pCloseItem6, pCloseItem7, pCloseItem8,
                           pCloseItem9, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

}
void OptionScene::btClick(CCObject* pSender) {
    for (int i = 1; i <= 9; i++) {
         CCMenuItemImage * item = (CCMenuItemImage*)pMenu->getChildByTag(i);
        item->setOpacity(255);
    }
    CCMenuItemImage * item = (CCMenuItemImage*)pSender;
    int tag = item->getTag();
    item->setOpacity(50);
    GameManager::sharedGameManager()->setNumberRocket(tag);
}
void OptionScene::btClickPlay(CCObject* pSender) {
    CCDirector::sharedDirector()->replaceScene(GamePlaySceneNew::scene());
}
void OptionScene::menuCloseCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->replaceScene(BeginScene::scene());
}