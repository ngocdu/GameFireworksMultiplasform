//
//  HelpScene.cpp
//  GameFireworks
//
//  Created by NgocDu on 13/11/14.
//
//
#include "cocos2d.h"
#include "HelpScene.h"
#include "BeginScene.h"
#include "GameManager.h"
using namespace cocos2d;

CCScene* HelpScene::scene() {
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelpScene *layer = HelpScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelpScene::init() {
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem =
    CCMenuItemImage::create("back.png", "back_hover.png", this,
                            menu_selector(HelpScene::menuCloseCallback));
    pCloseItem->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    pCloseItem->
    setPosition(ccp(pCloseItem->getContentSize().width * pCloseItem->getScaleX()/2,
                    pCloseItem->getContentSize().height * pCloseItem->getScaleY()/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    std::string str = "you tap the box to rotate it so that made ​​up \n \
    a pipe connecting the two sides.\ntime for each table is two minutes. \n \
    you must create as many pipelines as\n possible to record multiple points.";
    CCLabelTTF* pLabel = CCLabelTTF::create(str.c_str(), "",
                        30 * GameManager::sharedGameManager()->getSIZE_RATIO());
    pLabel->setScale(GameManager::sharedGameManager()->getSIZE_RATIO());
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height * 2/ 3) );
    pLabel->setColor(ccc3(255, 0, 200));
    // add the label as a child to this layer
    this->addChild(pLabel, 10);
    
    // add "BeginScene" splash screen"
    CCSprite* pSprite = CCSprite::create("bg_option_ipad.png");
    pSprite->setScaleX(GameManager::sharedGameManager()->getSIZE_RATIO_X());
    pSprite->setScaleY(GameManager::sharedGameManager()->getSIZE_RATIO_Y());
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    return true;
}

void HelpScene::menuCloseCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->replaceScene(BeginScene::scene());
}
