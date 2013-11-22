//
//  GamePlaySceneNew.cpp
//  GameFireworks
//
//  Created by NgocDu on 13/11/11.
//
//

#include "GamePlaySceneNew.h"
#include "SimpleAudioEngine.h"
#include "Square.h"
#include "BeginScene.h"
#include "GameManager.h"
#include "LevelScene.h"
#include <stdio.h>
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GamePlaySceneNew::scene() {
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GamePlaySceneNew *layer = GamePlaySceneNew::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool GamePlaySceneNew::init() {
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setTouchEnabled(true);
    if (GameManager::sharedGameManager()->getBGM()) {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("soundBackground.wav", true);
    }
    SimpleAudioEngine::sharedEngine()->preloadEffect("phonglen.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("bum.m4a");
    SimpleAudioEngine::sharedEngine()->preloadEffect("soundClick.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("soundCombo.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("before.m4a");
    SimpleAudioEngine::sharedEngine()->preloadEffect("ok.mp3");

    size = CCDirector::sharedDirector()->getWinSize();
    width = size.width * 1.0f;
    height = size.height * 1.0f;
    SIZE_RATIO = (width + height) * 1.0f / (768 + 1024);
    SIZE_RATIO_X = width / 768.0f;
    SIZE_RATIO_Y = height / 1024.0f;
    _arraySquare = new CCArray();
    _arrayRemove = new CCArray();
    _numberPath = 0;
    _sumNumberPath = 0;
    _numberPathScore = 0;
    _sumNumberSquareRemove = 0;
    _time =  120 ;
    _numberSqNotRotate = 0;
    checkTableFirst = false;
    _isPause = false;
    _isWin = false;
    _isSoundCoin = true;
    char str_time[20] = {'0'};
    sprintf(str_time, "%i", _time);
    if (GameManager::sharedGameManager()->getPlatform() == 1) {
        _lbTime = CCLabelTTF::create(str_time, "UTM American Sans", 40);
    }else if(GameManager::sharedGameManager()->getPlatform() == 2) {
        _lbTime = CCLabelTTF::create(str_time, "UTM American Sans.ttf", 40);
    }
    this->resetArrayChar(str_time, 20);
    _lbTime->setPosition(ccp(width / 10, height * 17.3f / 20));
    _lbTime->setScaleY(SIZE_RATIO_Y);
    _lbTime->setScaleX(SIZE_RATIO_X);
    _lbTime->setColor(ccc3(210, 105, 30));
    this->addChild(_lbTime, 10);

    char str_score[20] = {'0'};
    sprintf(str_score, "%i", _score);    
    if (GameManager::sharedGameManager()->getPlatform() == 1) {
        _lbScore = CCLabelTTF::create(str_score, "UTM American Sans", 40);
    }else if(GameManager::sharedGameManager()->getPlatform() == 2) {
        _lbScore = CCLabelTTF::create(str_score, "UTM American Sans.ttf", 40);
    }
     this->resetArrayChar(str_score, 20);
    _lbScore->setPosition(ccp(width / 2, height - height/40));
    _lbScore->setScaleY(SIZE_RATIO_Y);
    _lbScore->setScaleX(SIZE_RATIO_X);
    _lbScore->setColor(ccc3(210, 105, 30));
    this->addChild(_lbScore, 10);
    this->addTextureCache();
//    this->resetArrayTow(arrayPath);
    this->addTableGame(10, 7);
    this->addCandles();
    this->addFire();
    this->addMissiles();
    this->loadMatrix();
    this->checkTableGame();
    _touchAble = true;

    CCSprite * spriteTime = CCSprite::create("frame_timer.png");
    spriteTime->setPosition(ccp(width / 10, height * 17.3f / 20));
    spriteTime->setScaleX(SIZE_RATIO_X);
    spriteTime->setScaleY(SIZE_RATIO_Y);
    this->addChild(spriteTime, 9);

    _layerEndGame = CCLayer::create();
    _layerEndGame->setScaleY(SIZE_RATIO_Y);
    _layerEndGame->setScaleX(SIZE_RATIO_X);
    _layerEndGame->setPosition(CCPoint(0, 0));
    CCSprite *bgEnd = CCSprite::create("frame_dialog.png");
    bgEnd->setPosition(CCPoint(width / 2, height / 2));
    _layerEndGame->addChild(bgEnd);

    //BGM
    CCMenuItemImage * BGMItem =
    CCMenuItemImage::create("BgmOn.png", "BgmOn.png", this,
                            menu_selector(GamePlaySceneNew::menuBGM));
    BGMItem->setPosition(ccp(width / 10, height / 20));
    BGMItem->setScale(SIZE_RATIO);

    _bgm_off = CCSprite::create("BgmOff.png");
    _bgm_off->setScaleX(SIZE_RATIO_X);
    _bgm_off->setScaleY(SIZE_RATIO_Y);
    _bgm_off->setPosition(BGMItem->getPosition());
    _bgm_off->setVisible(!GameManager::sharedGameManager()->getBGM());
    this->addChild(_bgm_off, 12);

    CCSprite * imagePause = CCSprite::create("table_pause.png");
    imagePause->setPosition(CCPoint(width * 9 / 10, height / 20));
    imagePause->setScale(SIZE_RATIO);
    this->addChild(imagePause, 10);

    CCMenuItemImage * pause =
    CCMenuItemImage::create("pause.png", "pause_hover.png",this,
                            menu_selector(GamePlaySceneNew::clickPauseButton));
    pause->setPosition(ccp(250, 450));
    pause->setScale(SIZE_RATIO);
    pause->setPosition(CCPoint(width * 9 / 10, height / 20));

    CCMenu * menuPause = CCMenu::create(pause, BGMItem, NULL);
    menuPause->setPosition(CCPoint(0, 0));
    this->addChild(menuPause , 10);

    playItem =
    CCMenuItemImage::create("resume.png", "resume_hover.png",this,
                            menu_selector(GamePlaySceneNew::clickContinueButton));
    playItem->setPosition(ccp(370 * SIZE_RATIO_X, 590 * SIZE_RATIO_Y));

    CCMenuItemImage * restart =
    CCMenuItemImage::create("Restart.png", "Restart_Hover.png",this,
                            menu_selector(GamePlaySceneNew::clickResetButton));
    restart->
    setPosition(ccp(370 * SIZE_RATIO_X,
                    (570 - playItem->getContentSize().height * 0.9 ) * SIZE_RATIO_Y));
    CCMenuItemImage * back =
    CCMenuItemImage::create("quit.png", "quit_hover.png", this,
                            menu_selector(GamePlaySceneNew::clickBackButton));

    back->
    setPosition(ccp(370 * SIZE_RATIO_X,
                    (570 - playItem->getContentSize().height * 2) * SIZE_RATIO_Y));
    menu = CCMenu::create(playItem, back,restart, NULL);
    menu->setPosition(CCPoint(0, 0));
    _layerEndGame->addChild(menu);

    _layerEndGame->setVisible(false);
    this->addChild(_layerEndGame, 20);

    CCSprite * bground = CCSprite::create("bg.png");
    bground->setPosition(CCPoint(width / 2, height / 2));    
    bground->setScaleX(SIZE_RATIO_X);
    bground->setScaleY(SIZE_RATIO_Y);
    this->addChild(bground);

    CCParticleSnow * m_emitter = CCParticleSnow::create();
    m_emitter->retain();
    bground->addChild(m_emitter, 10);

    CCPoint p = m_emitter->getPosition();
    m_emitter->setPosition(ccp( p.x , p.y ));
    m_emitter->setLife(9);
    m_emitter->setLifeVar(9);
    m_emitter->setTotalParticles(500);
    m_emitter->setScaleX(490 / width);
    m_emitter->setGravity(ccp(0,-10));

    // speed of particles
    m_emitter->setSpeed(30);
    m_emitter->setSpeedVar(30);

    ccColor4F startColor = m_emitter->getStartColor();
    startColor.r = 0.9f;
    startColor.g = 0.9f;
    startColor.b = 0.9f;
    m_emitter->setStartColor(startColor);
    startColor.r = NULL;
    startColor.g = NULL;
    startColor.b = NULL;

    ccColor4F startColorVar = m_emitter->getStartColorVar();
    startColorVar.b = 0.1f;
    m_emitter->setStartColorVar(startColorVar);

    startColorVar.r = NULL;
    startColorVar.g = NULL;
    startColorVar.b = NULL;
    m_emitter->setEmissionRate(m_emitter->getTotalParticles() / m_emitter->getLife());

    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("fire.png"));

    this->schedule(schedule_selector(GamePlaySceneNew::downSquare), 0.1f);
    this->schedule(schedule_selector(GamePlaySceneNew::updateTime), 1);
    return true;
}
void GamePlaySceneNew::addTextureCache() {
    CCTextureCache::sharedTextureCache()->addImage("1.png");
    CCTextureCache::sharedTextureCache()->addImage("2.png");
    CCTextureCache::sharedTextureCache()->addImage("3.png");
    CCTextureCache::sharedTextureCache()->addImage("4.png");
    
    CCTextureCache::sharedTextureCache()->addImage("red1.png");
    CCTextureCache::sharedTextureCache()->addImage("red2.png");
    CCTextureCache::sharedTextureCache()->addImage("red3.png");
    CCTextureCache::sharedTextureCache()->addImage("red4.png");
    
    CCTextureCache::sharedTextureCache()->addImage("yellow1.png");
    CCTextureCache::sharedTextureCache()->addImage("yellow2.png");
    CCTextureCache::sharedTextureCache()->addImage("yellow3.png");
    CCTextureCache::sharedTextureCache()->addImage("yellow4.png");
    
    CCTextureCache::sharedTextureCache()->addImage("fire.png");
    
    CCTextureCache::sharedTextureCache()->addImage("Icon.png");
    
    CCTextureCache::sharedTextureCache()->addImage("phao01.png");
    CCTextureCache::sharedTextureCache()->addImage("phao02.png");
    CCTextureCache::sharedTextureCache()->addImage("phao03.png");
    CCTextureCache::sharedTextureCache()->addImage("phao04.png");
    CCTextureCache::sharedTextureCache()->addImage("phao05.png");
    CCTextureCache::sharedTextureCache()->addImage("phao06.png");
    CCTextureCache::sharedTextureCache()->addImage("phao07.png");
    CCTextureCache::sharedTextureCache()->addImage("phao08.png");
    CCTextureCache::sharedTextureCache()->addImage("phao09.png");
}
void GamePlaySceneNew::addEffectTime(CCSprite *item) {
    this->addChild(item, 30);
    item->setTag(5);
    CCParticleGalaxy *m_emitter = CCParticleGalaxy::create();
    m_emitter->
      setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
    m_emitter->setPositionType( kCCPositionTypeFree );
    m_emitter->setPosition(item->getPosition());
    CCMoveTo * moveM = CCMoveTo::create(1, _lbTime->getPosition());
    CCCallFuncN *removeM =
    CCCallFuncN::create(this,
                        callfuncN_selector(GamePlaySceneNew::removePratice));
    CCSequence * squenM = CCSequence::create(moveM, removeM, NULL);
    m_emitter->runAction(squenM);
    this->addChild(m_emitter, 30);
    if (_time > 0) {
        CCMoveTo * move = CCMoveTo::create(1, _lbTime->getPosition());
        CCCallFuncN *remove =
        CCCallFuncN::create(this,
                            callfuncN_selector(GamePlaySceneNew::removeEffectTime));
        CCSequence * squen = CCSequence::create(move, remove, NULL);
        item->runAction(squen);
    }else {
        CCMoveTo * move = CCMoveTo::create(1, _lbScore->getPosition());
        CCCallFuncN *remove =
        CCCallFuncN::create(this,
                            callfuncN_selector(GamePlaySceneNew::removeEffectScore));
        CCSequence * squen = CCSequence::create(move, remove, NULL);
        item->runAction(squen);
    }
    
}
void GamePlaySceneNew::addEffectScore(CCSprite *item) {
    this->addChild(item, 30);
    CCParticleFlower *m_emitter = CCParticleFlower::create();
    m_emitter->
    setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
    m_emitter->setPositionType( kCCPositionTypeFree );
    m_emitter->setPosition(item->getPosition());
    CCMoveTo * moveM = CCMoveTo::create(1, _lbScore->getPosition());
    CCCallFuncN *removeM =
    CCCallFuncN::create(this,
                        callfuncN_selector(GamePlaySceneNew::removePratice));
    CCSequence * squenM = CCSequence::create(moveM, removeM, NULL);
    m_emitter->runAction(squenM);
    this->addChild(m_emitter, 30);
    
    CCMoveTo * move = CCMoveTo::create(1, _lbScore->getPosition());
    CCCallFuncN *remove =
    CCCallFuncN::create(this,
                        callfuncN_selector(GamePlaySceneNew::removeEffectScore));
    CCSequence * squen = CCSequence::create(move, remove, NULL);
    item->runAction(squen);
}
void GamePlaySceneNew::addTableGame(int rows, int columns) {
    CCPoint pOrigin;
    if (SIZE_RATIO_X >= 1) {
        pOrigin = CCPoint(70 * SIZE_RATIO_X , 47 * SIZE_RATIO_Y);
    } else pOrigin = CCPoint(70 * SIZE_RATIO_X , 90 * SIZE_RATIO_Y);
    float WithTable = 490 * SIZE_RATIO_X;
    float HeightTable = 700 * SIZE_RATIO_X;
    tableGame = new TableGame(rows, columns, pOrigin, WithTable, HeightTable);
    int dem = 0;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {
            dem++;
            int arCategory[10] = {2, 0, 3, 0, 3 , 2, 0, 1, 2, 3};
            int category = arCategory[rand() % 10];
            char tileName[7][20];
            strcpy(tileName[0], "1.png");
            strcpy(tileName[1], "2.png");
            strcpy(tileName[2], "3.png");
            strcpy(tileName[3], "4.png");
            char spriteName[100];
            sprintf(spriteName, "%s", tileName[category]);
            bool notContain = false;
            bool w = true;
            bool e = true;
            bool n = true;
            bool s = true;
            bool statPoint = true;
            bool destination = true;
            switch (category) {
                case 0:
                    w = true;
                    e = true;
                    n = false;
                    s = false;
                    break;
                case 1:
                    w = true;
                    e = true;
                    n = true;
                    s = true;
                    break;
                case 2:
                    w = true;
                    e = true;
                    n = true;
                    s = false;
                    break;
                case 3:
                    w = true;
                    e = false;
                    n = false;
                    s = true;
                    break;
                default:
                    break;
            }

            if (dem == 1 + columns * (i - 1) && w == true) {
                statPoint = true;
            } else statPoint = false;

            if (dem == i * columns && e == true) {
                destination = true;
            } else destination = false;
            Square *sq =
            new  Square(notContain, w, e, n, s, i, j, statPoint, destination );
            sq->initWithFile(spriteName);
            sq->setScaleX(SIZE_RATIO_X);
            sq->setScaleY(SIZE_RATIO_X);
            CCPoint p =
            ccp(pOrigin.x + (j + 0.5f) * sq->getContentSize().width * SIZE_RATIO_X,
                pOrigin.y + (i + 0.5f) * sq->getContentSize().height * SIZE_RATIO_X);
            sq->setPosition(p);
            _arraySquare->addObject(sq);
            this->addChild(sq, 1, dem);
            sq->setTag(dem);
        }
    }
    
    pOrigin.x = NULL;
    pOrigin.y = NULL;
    WithTable = NULL;
    HeightTable = NULL;
    dem = NULL;
}
void GamePlaySceneNew::addFire() {
    for (int i = 1; i <= tableGame->getRows(); i++) {
        Square * sq =
        (Square*)this->getChildByTag(1 + tableGame->getColumns() * (i - 1));
        CCPoint p =
        CCPoint(sq->getPosition().x -
                sq->getContentSize().width * 3 / 2 * sq->getScaleX(),
                sq->getPosition().y);
        CCParticleSun *m_emitter = CCParticleSun::create();
        m_emitter->retain();
        this->addChild(m_emitter, 10);
        m_emitter->
        setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
        m_emitter->setPosition( p );
        m_emitter->setPositionType( kCCPositionTypeGrouped );
        m_emitter->setTotalParticles(10);
        m_emitter->setScaleX(SIZE_RATIO_X);
        m_emitter->setScaleY(SIZE_RATIO_Y);
        sq = NULL;
    }

    CCSprite * ball_light = CCSprite::create("light.png");
    ball_light->setScaleY(SIZE_RATIO_Y);
    ball_light->setScaleX(SIZE_RATIO_X);
    CCAnimation *anim=CCAnimation::create();
    anim->addSpriteFrameWithFileName("light.png");
    anim->addSpriteFrameWithFileName("light_glow.png");
    anim->setDelayPerUnit(2.8f / 9.0f);
    anim->setRestoreOriginalFrame(true);
    CCAnimate * animet=CCAnimate::create(anim);
    CCRepeatForever *re = CCRepeatForever::create(animet);
    ball_light->runAction(re);
    ball_light->setPosition(CCPoint(width / 2, height * 7 / 8));
    this->addChild(ball_light, 3);
}
void GamePlaySceneNew::addCandles() {
    for (int i = 1; i <= tableGame->getRows(); i++) {
        Square * sq =
        (Square*)this->getChildByTag(1 + tableGame->getColumns() * (i - 1));
        CCSprite *candle = new CCSprite();
        candle->initWithFile("nen.png");
        candle->setScaleX(SIZE_RATIO_X);
        candle->setScaleY(SIZE_RATIO_Y);
        CCPoint p =
        CCPoint(sq->getPosition().x -
                sq->getContentSize().width * 3 / 2 * sq->getScaleX(),
                sq->getPosition().y - sq->getContentSize().height * 1 / 3 *
                sq->getScaleY());
        candle->setPosition(p);
        this->addChild(candle, 10);
        sq = NULL;
    }
}
void GamePlaySceneNew::addCoin(int row, float speed, int path[], int numberPoint) {
    Coin *coin = new Coin();
    coin->initWithFile("Icon.png");
    coin->setScale(0.30f);
    coin->setSpeed(speed);
    coin->setPath(path);
    coin->setNumberPoint(numberPoint);
    Square * sq =
    (Square*)this->getChildByTag(1 + tableGame->getColumns() * (row - 1));
    CCPoint p =
    CCPoint(sq->getPosition().x - sq->getContentSize().width * sq->getScaleX(),
            sq->getPosition().y);
    coin->setPosition(p);
    coin->setRow(row);
    coin->setTag(100 + row);
    this->addChild(coin, 10);
    if (GameManager::sharedGameManager()->getBGM() && _isSoundCoin == true) {
        _isSoundCoin = false;
        SimpleAudioEngine::sharedEngine()->playEffect("ok.mp3", false);
    }
    this->runActionCoin(coin);
}
void GamePlaySceneNew::addMissiles() {
    for (int i = 1; i <= tableGame->getRows(); i++) {
        Missile *missile = new Missile();
        char strName[20];
        sprintf(strName, "phao0%i.png",
                GameManager::sharedGameManager()->getNumberRocket());
        missile->initWithFile(strName);
        this->resetArrayChar(strName, 20);
        missile->setScale(SIZE_RATIO);
        Square * sq = (Square*)this->getChildByTag(tableGame->getColumns() * i);
        CCPoint p =
        CCPoint(sq->getPosition().x + sq->getContentSize().width * sq->getScaleX(),
                sq->getPosition().y);
        missile->setPosition(p);
        missile->setOriginPoint(p);
        missile->setTag(500 + i);
        missile->setRow(i);
        missile->setScaleY(SIZE_RATIO_Y);
        missile->setScaleX(SIZE_RATIO_X);
        this->addChild(missile, 20);

        CCSprite *tat = CCSprite::create("tat.png");
        tat->setPosition(CCPoint(p.x + tat->getContentSize().width/7 * SIZE_RATIO_X,
                                 p.y + tat->getContentSize().width/7 * SIZE_RATIO_X));
        tat->setScaleY(SIZE_RATIO_Y);
        tat->setScaleX(SIZE_RATIO_X);
        this->addChild(tat, 19);
    }
}
void GamePlaySceneNew::addPraticle(cocos2d::CCPoint p , int k) {
    switch (k) {
        case 2:
        {
            CCParticleFlower *m_emitter = CCParticleFlower::create();
            this->addChild(m_emitter, 10);
            m_emitter->
            setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
            m_emitter->setPosition(p);
            m_emitter->setPositionType( kCCPositionTypeRelative );
            m_emitter->setTotalParticles(15);
            m_emitter->setScaleX(SIZE_RATIO_X);
            m_emitter->setScaleY(SIZE_RATIO_Y);
            CCMoveTo * move = CCMoveTo::create(0.50f, p);
            CCCallFuncN *remove =
            CCCallFuncN::create(this,
                                callfuncN_selector(GamePlaySceneNew::removePratice));
            CCSequence * squen = CCSequence::create(move, remove, NULL);
            m_emitter->runAction(squen);
        }
            break;
        case 3:
        {
            CCParticleGalaxy *m_emitter = CCParticleGalaxy::create();
//            m_emitter->retain();
            this->addChild(m_emitter, 10);
            m_emitter->
            setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
            m_emitter->setPosition(p);
            m_emitter->setPositionType( kCCPositionTypeRelative );
            m_emitter->setTotalParticles(15);
            m_emitter->setScaleX(SIZE_RATIO_X);
            m_emitter->setScaleY(SIZE_RATIO_Y);
            CCMoveTo * move = CCMoveTo::create(0.50f, p);
            CCCallFuncN *remove =
            CCCallFuncN::create(this,
                                callfuncN_selector(GamePlaySceneNew::removePratice));
            CCSequence * squen = CCSequence::create(move, remove, NULL);
            m_emitter->runAction(squen);
        }
            break;
        case 1:
        {
            CCParticleFire *m_emitter = CCParticleFire::create();
//            m_emitter->retain();
            this->addChild(m_emitter, 10);
            m_emitter->
            setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
            m_emitter->setPosition(p);
            m_emitter->setPositionType( kCCPositionTypeGrouped );
            m_emitter->setTotalParticles(15);
            m_emitter->setScaleX(SIZE_RATIO_X);
            m_emitter->setScaleY(SIZE_RATIO_Y);
            CCMoveTo * move = CCMoveTo::create(0.50f, p);
            CCCallFuncN *remove =
            CCCallFuncN::create(this,
                                callfuncN_selector(GamePlaySceneNew::removePratice));
            CCSequence * squen = CCSequence::create(move, remove, NULL);
            m_emitter->runAction(squen);
        }
            break;
        default:
            break;
    }
}
void GamePlaySceneNew::addSquareToArrayRemove(Square *sq) {
    int k = 0;
    CCObject *i;
    CCARRAY_FOREACH(_arrayRemove, i) {
        Square * sq1 = (Square*)i;
        if (sq->getTag() == sq1->getTag()) {
            k ++;
            break;
        }
    }
    if (k == 0) {
        if (sq->getRotateAble() == false && sq->getCombo() != 0) {
            if (GameManager::sharedGameManager()->getBGM()) {
                SimpleAudioEngine::sharedEngine()->playEffect("phonglen.mp3",
                                                              false);
            }
        }
        _arrayRemove->addObject(sq);
    }
}
void GamePlaySceneNew::updateTime(float dt) {
    if (_time > 0) {
        _time --;
    }else if(_time <= 0 ) {
        if (_numberPath <= 0) {
            _layerEndGame->setVisible(true);
            playItem->setVisible(false);
        }        
        this->setTouchEnabled(false);
    }
    char str_time[20] = {0};
    sprintf(str_time, "%i", _time);
    _lbTime->setString(str_time);
    this->resetArrayChar(str_time, 20);
}
void GamePlaySceneNew::ccTouchesBegan(CCSet * touch, CCEvent* event) {
    if ( _touchAble) {
        CCTouch *touch1 = (CCTouch*)(touch->anyObject());
        CCPoint p2 = touch1->getLocationInView();
        touchLocation=CCDirector::sharedDirector()->convertToGL(p2); 
        Square * sq1 = (Square*)_arraySquare->lastObject();
        if (touchLocation.x >= tableGame->getPointOrigin().x +
            sq1->getContentSize().width / 2 &&
            touchLocation.x <= tableGame->getPointOrigin().x +
            tableGame->getWidth() + sq1->getContentSize().width &&
            touchLocation.y >= tableGame->getPointOrigin().y +
            sq1->getContentSize().height / 2 &&
            touchLocation.y <= tableGame->getPointOrigin().y +
            tableGame->getHeight()  + sq1->getContentSize().height) {
            int H = (int)(tableGame->getHeight() / tableGame->getRows());
            int W = (int)(tableGame->getWidth() / tableGame->getColumns());
            int px = (int)(tableGame->getPointOrigin().x +
                           sq1->getContentSize().width * sq1->getScaleX());
            int py = (int)(tableGame->getPointOrigin().y +
                           sq1->getContentSize().height * sq1->getScaleY());
            int col = (int)((touchLocation.x - px) / W ) + 1;
            int row = (int)((touchLocation.y - py) / H ) + 1;
            int tag = (row - 1) * tableGame->getColumns() + col;  
            if (this->getChildByTag(tag) != NULL) {
                Square * sqSelected1 = (Square*)this->getChildByTag(tag);
                sqSelected1->setIsMoveTouch(true);
                if (sqSelected1->getRotateAble()) {
                if (sqSelected1->getPosition().x + sqSelected1->getContentSize().width >
                    touchLocation.x) {
                    if (GameManager::sharedGameManager()->getBGM()) {
                        SimpleAudioEngine::sharedEngine()->playEffect("soundClick.mp3", false);
                    }
                    if (sqSelected1->getRotateAble()) {
                        bool w = sqSelected1->getWest();
                        bool n = sqSelected1->getNorth();
                        bool e = sqSelected1->getEast();
                        bool s = sqSelected1->getSouth();
                        sqSelected1->setNorth(w);
                        sqSelected1->setEast(n);
                        sqSelected1->setSouth(e);
                        sqSelected1->setWest(s);
                        
                        if (sqSelected1->getTag() == 1 + tableGame->getColumns() *
                            (sqSelected1->getRow() - 1) &&
                            sqSelected1->getWest() == true) {
                            sqSelected1->setStartPoint(true);
                        } else sqSelected1->setStartPoint(false);
                        
                        if (sqSelected1->getTag() == sqSelected1->getRow() *
                            tableGame->getColumns() && sqSelected1->getEast() == true) {
                            sqSelected1->setDestination(true);
                        } else sqSelected1->setDestination(false);
                        
                        CCRotateTo * rotate =
                        CCRotateTo::create(0.0f, sqSelected1->getRotation() + 90);
                        sqSelected1->runAction(rotate);
                        this->changeMatrix(sqSelected1);
                    }
                }
            }
        }
    }
}
}
void GamePlaySceneNew::ccTouchesMoved(CCSet* touches, CCEvent* event) {
    if (_touchAble) {
        CCTouch *touch = (CCTouch*)touches->anyObject();
        CCPoint p2 = touch->getLocationInView();

        CCPoint touchpoint = CCDirector::sharedDirector()->convertToGL(p2); 

        Square * sq1 = (Square*)_arraySquare->objectAtIndex(1);
        if (touchpoint.x >= tableGame->getPointOrigin().x +
            sq1->getContentSize().width / 2 &&
            touchpoint.x <= tableGame->getPointOrigin().x +
            tableGame->getWidth() + sq1->getContentSize().width &&
            touchpoint.y >= tableGame->getPointOrigin().y +
            sq1->getContentSize().height / 2 &&
            touchpoint.y <= tableGame->getPointOrigin().y +
            tableGame->getHeight()  + sq1->getContentSize().height) {
            int H = (int)(tableGame->getHeight() / tableGame->getRows());
            int W = (int)(tableGame->getWidth() / tableGame->getColumns());
            int px = (int)(tableGame->getPointOrigin().x +
                           sq1->getContentSize().width * sq1->getScaleX());
            int py = (int)(tableGame->getPointOrigin().y +
                           sq1->getContentSize().height * sq1->getScaleY());
            int col = (int)((touchpoint.x - px) / W ) + 1;
            int row = (int)((touchpoint.y - py) / H ) + 1;
            int tag = (row - 1) * tableGame->getColumns() + col;
            if (this->getChildByTag(tag) != NULL) {
                Square * sqSelected1 = (Square*)this->getChildByTag(tag);
                if (!sqSelected1->getIsMoveTouch()) {
                if (sqSelected1->getPosition().x + sqSelected1->getContentSize().width >
                    touchLocation.x) {
                    if (GameManager::sharedGameManager()->getBGM()) {
                        SimpleAudioEngine::sharedEngine()->playEffect("soundClick.mp3", false);
                    }
                    if (!sqSelected1->getIsMoveTouch()) {
                        sqSelected1->setIsMoveTouch(true);
                        if (sqSelected1->getRotateAble()) {
                            bool w = sqSelected1->getWest();
                            bool n = sqSelected1->getNorth();
                            bool e = sqSelected1->getEast();
                            bool s = sqSelected1->getSouth();
                            sqSelected1->setNorth(w);
                            sqSelected1->setEast(n);
                            sqSelected1->setSouth(e);
                            sqSelected1->setWest(s);
                            
                            if (sqSelected1->getTag() == 1 + tableGame->getColumns() *
                                (sqSelected1->getRow() - 1) &&
                                sqSelected1->getWest() == true) {
                                sqSelected1->setStartPoint(true);
                            } else sqSelected1->setStartPoint(false);
                            
                            if (sqSelected1->getTag() == sqSelected1->getRow() *
                                tableGame->getColumns() && sqSelected1->getEast() == true) {
                                sqSelected1->setDestination(true);
                            } else sqSelected1->setDestination(false);
                            
                            CCRotateTo * rotate =
                            CCRotateTo::create(0.0f, sqSelected1->getRotation() + 90);
                            sqSelected1->runAction(rotate);
                            this->changeMatrix(sqSelected1); 
                        }
                    }
                }
            }
        }
    }
}
}
void GamePlaySceneNew::ccTouchesEnded(CCSet* touches, CCEvent* event) {
    if (_touchAble) {
        CCObject * i;
        CCARRAY_FOREACH(_arraySquare, i) {
            Square * sq = (Square*)i;
            sq->setIsMoveTouch(false);
        }
        this->loadMatrix();
        if (_numberPath == 0 && _touchAble &&
            _arraySquare->count() == (tableGame->getRows() + 1) *
                tableGame->getColumns()) {
            this->checkTableGame();
        }
    }
}
void GamePlaySceneNew::checkTableGame() {
    _touchAble = false;
    for (int i = 1; i <= tableGame->getRows(); i ++) {
        int k = 1 + (i - 1) * tableGame->getColumns() ;
        Square * sq;
        if (this->getChildByTag(k)) {
            sq = (Square*)this->getChildByTag(k);
            if (sq->getStartPoint() == true && sq->getIsRemove() == false) {
                pa[1] = k;
                daxet[pa[1]] = 1;
                c = 0;
                for (int j = 1; j <= tableGame->getRows(); j ++) {
                    if (this->getChildByTag(j * tableGame->getColumns())) {
                        Square * sqTaget =
                        (Square*)this->getChildByTag(j * tableGame->getColumns());
                        if (sqTaget->getDestination()) {
                            this->backTrackingNew(2, sqTaget);
                            this->resetArray(daxet);
                        }
                    }
                }
            }
        }
    }
}
void GamePlaySceneNew::backTracking(int i) {
    int n = tableGame->getRows() * tableGame->getColumns();
    for(int j=2; j<=n; j++)
        if(daxet[j] != 1 && matran[pa[i-1]][j] == 1) {
            pa[i] = j;
            daxet[j] = 1;
            c += matran[pa[i-1]][j];
            Square * sq = (Square*)this->getChildByTag(j);
            if(sq->getDestination() == true) {
                _numberPath ++;
//                this->addArrayInArray(arrayPath, pa, _numberPath, i);
            } else backTracking(i+1);

            daxet[j] = 0;
            c -= matran[pa[i-1]][j];
        }
}
void GamePlaySceneNew::backTrackingNew(int i, Square * sqTaget) {
    int n = tableGame->getRows() * tableGame->getColumns();
    for(int j = 1; j <= n; j++)
        if(daxet[j] != 1 && matran[pa[i-1]][j] == 1) {
            pa[i] = j;
            daxet[j] = 1;
            c += matran[pa[i-1]][j];
            if(sqTaget->getTag() == j) {
                Square * sq = (Square*)this->getChildByTag(pa[1]);
                Missile *missile =
                (Missile*)this->getChildByTag(sqTaget->getRow() + 500);
                missile->setLaunched(true);
                missile->setNumberPath(missile->getNumberPath() + 1);
                _numberPath ++;
//                if (_numberPath < 20)
                {
                    _numberPathScore++;
                    _sumNumberPath ++;
                    this->addCoin(sq->getRow() , 1.0f / i, pa, i);
                    for (int k = 1; k <= i; k++) {
                        Square *sq = (Square *)this->getChildByTag(pa[k]);
                        this->addSquareToArrayRemove(sq);
                        sq->setIsRemove(true);
                        if (sq->getRotateAble() == false) {
                            //                        if (checkTableFirst)
                            {
                                if (sq->getWest()) {
                                    this->addPraticle(sq->getPosition(), sq->getCombo());
                                    CCPoint pointaget1;
                                    for (int i = 1; i < sq->getColumn(); i ++) {
                                        if (this->getChildByTag((sq->getRow() - 1) *
                                                                tableGame->getColumns()  + i)) {
                                            Square *sqw =
                                            (Square *)this->
                                            getChildByTag((sq->getRow() - 1) *
                                                          tableGame->getColumns() + i);
                                            _arrayRemove->addObject(sqw);
                                            pointaget1 =
                                            CCPoint(sqw->getPosition().x,
                                                    sqw->getPosition().y);
                                            this->addPraticle(sqw->getPosition(),
                                                              sq->getCombo());
                                        }
                                    }
                                }
                                if (sq->getEast()) {
                                    this->addPraticle(sq->getPosition(), sq->getCombo());
                                    CCPoint pointaget2;
                                    for (int i = sq->getTag() + 1; i <= (sq->getRow()) *
                                         tableGame->getColumns() ; i ++) {
                                        if (this->getChildByTag(i)) {
                                            Square *sqw =
                                            (Square *)this->getChildByTag(i);
                                            _arrayRemove->addObject(sqw);
                                            sqw->setPoint(sq->getPoint());
                                            pointaget2 =
                                            CCPoint(sqw->getPosition().x,
                                                    sqw->getPosition().y);
                                            this->addPraticle(sqw->getPosition(),
                                                              sq->getCombo());
                                            pointaget2 =
                                            CCPoint(sqw->getPosition().x,
                                                    sqw->getPosition().y);
                                            this->addPraticle(sqw->getPosition(),
                                                              sq->getCombo());
                                        }
                                    }
                                }
                                if (sq->getNorth()) {
                                    this->addPraticle(sq->getPosition(), sq->getCombo());
                                    CCPoint pointaget3;
                                    for (int i = 1;
                                         i <= tableGame->getRows() - sq->getRow();
                                         i ++) {
                                        if (this->
                                            getChildByTag(sq->getTag() + i *
                                                          tableGame->getColumns())) {
                                                Square *sqw =
                                                (Square *)this->
                                                getChildByTag(sq->getTag() + i *
                                                              tableGame->getColumns());
                                                _arrayRemove->addObject(sqw);
                                                pointaget3 =
                                                CCPoint(sqw->getPosition().x,
                                                        sqw->getPosition().y);
                                                this->addPraticle(sqw->getPosition(),
                                                                  sq->getCombo());
                                            }
                                    }
                                }
                                if (sq->getSouth()) {
                                    this->addPraticle(sq->getPosition(), sq->getCombo());
                                    CCPoint pointaget4;
                                    for (int i = sq->getRow() - 1; i > 0; i --) {
                                        if (this->
                                            getChildByTag(sq->getTag() - i *
                                                          tableGame->getColumns())) {
                                                Square *sqw =
                                                (Square *)this->
                                                getChildByTag(sq->getTag() - i *
                                                              tableGame->getColumns());
                                                _arrayRemove->addObject(sqw);
                                                pointaget4 =
                                                CCPoint(sqw->getPosition().x,
                                                        sqw->getPosition().y);
                                                this->addPraticle(sqw->getPosition(),
                                                                  sq->getCombo());
                                            }
                                    }
                                }
                            }
                        } else {
                            CCTintTo * tinto = CCTintTo::create(0.2f, 255, 0, 0);
                            CCTintTo * tinto2 = CCTintTo::create(0.2f, 0, 0, 255);
                            CCTintTo * tinto3 = CCTintTo::create(0.2f, 0, 255, 0);
                            CCSequence * squen =
                            CCSequence::create(tinto, tinto2, tinto3, NULL);
                            CCRepeatForever *repeat = CCRepeatForever::create(squen);
                            sq->runAction(repeat);
                        }
                        sq = NULL;
                    }
                }
            } else backTrackingNew(i+1, sqTaget);

            daxet[j] = 0;
            c -= matran[pa[i-1]][j];
        }
}
void GamePlaySceneNew::loadStartPointAndDestination() {
    int dS = 0;
    int dD = 0;
    CCObject *i;
    CCARRAY_FOREACH(_arraySquare, i) {
        Square * sq = (Square*)i;
        if (sq->getStartPoint()) {
            dS ++ ;
            arrayStart[dS] = sq->getTag();
        }
        if (sq->getDestination()) {
            dD ++;
            arrarDestination[dD] = sq->getTag();
        }
    }
}
void GamePlaySceneNew::loadMatrix() {
    if (_arraySquare->count() >= tableGame->getColumns() * (tableGame->getRows())) {
        for (int i = 1; i <= tableGame->getColumns() * tableGame->getRows(); i++) {
            if (this->getChildByTag(i) ) {
                Square *sq = (Square*)this->getChildByTag(i);
                // i + 1
                if (i + 1 <= tableGame->getColumns() * tableGame->getRows() &&
                    sq->getColumn() != tableGame->getColumns()) {
                    if (this->getChildByTag(i + 1) ) {
                        Square *sq1 = (Square*)this->getChildByTag(i + 1);
                        if (sq->getEast() && sq1->getWest()) {
                            matran[i][i+1] = 1;
                            matran[i+1][i] = 1;
                        } else matran[i][i+1] = 0;
                    }
                }
                // i - 1
                if (i - 1 > 0 && sq->getColumn() != 1) {
                    if (this->getChildByTag(i - 1) ) {
                        Square *sq1 = (Square*)this->getChildByTag(i - 1);
                        if (sq1->getEast() && sq->getWest()) {
                            matran[i][i-1] = 1;
                            matran[i-1][i] = 1;
                        }else matran[i][i-1] = 0;
                    }
                }
                // i + columns
                if (i + tableGame->getColumns() <= tableGame->getColumns() *
                    tableGame->getRows() && sq->getRow() != tableGame->getRows()) {
                    if (this->getChildByTag(i + tableGame->getColumns()) ) {
                        Square *sq1 =
                        (Square*)this->getChildByTag(i + tableGame->getColumns());
                        if (sq1->getSouth() && sq->getNorth()) {
                            matran[i][i + tableGame->getColumns()] = 1;
                            matran[i + tableGame->getColumns()][i] = 1;
                        }else matran[i][i + tableGame->getColumns()] = 0;
                    }
                }
                // i - columns
                if (i - tableGame->getColumns() > 0 && sq->getRow() != 1) {
                    if (this->getChildByTag(i - tableGame->getColumns()) ) {
                        Square *sq1 =
                        (Square*)this->getChildByTag(i - tableGame->getColumns());
                        if (sq->getSouth() && sq1->getNorth()) {
                            matran[i][i - tableGame->getColumns()] = 1;
                            matran[i - tableGame->getColumns()][i] = 1;
                        }else matran[i][i - tableGame->getColumns()] = 0;
                    }
                }
            }
        }
    }
}
void GamePlaySceneNew::changeMatrix(Square *sq) {
    int i = sq->getTag();
    // i + 1
    if (i + 1 <= tableGame->getColumns() * tableGame->getRows() &&
        sq->getColumn() != tableGame->getColumns()) {
        if (this->getChildByTag(i + 1)) {
            Square *sq1 = (Square*)this->getChildByTag(i + 1);
            if (sq->getEast() && sq1->getWest()) {
                matran[i][i+1] = 1;
                matran[i+1][i] = 1;
            } else {
                matran[i][i+1] = 0;
                matran[i+1][i] = 0;
            }
        }
    }
    // i - 1
    if (i - 1 > 0 && sq->getColumn() != 1) {
        if (this->getChildByTag(i - 1)) {
            Square *sq1 = (Square*)this->getChildByTag(i - 1);
            if (sq1->getEast() && sq->getWest()) {
                matran[i][i-1] = 1;
                matran[i-1][i] = 1;
            }else {
                matran[i-1][i] = 0;
                matran[i][i-1] = 0;
            }
        }
    }
    // i + columns
    if (i + tableGame->getColumns() <= tableGame->getColumns() * tableGame->getRows() &&
        sq->getRow() != tableGame->getRows()) {
        if (this->getChildByTag(i + tableGame->getColumns()) != NULL) {
            Square *sq1 = (Square*)this->getChildByTag(i + tableGame->getColumns());
            if (sq1->getSouth() && sq->getNorth()) {
                matran[i][i + tableGame->getColumns()] = 1;
                matran[i + tableGame->getColumns()][i] = 1;
            } else {
                matran[i][i + tableGame->getColumns()] = 0;
                matran[i + tableGame->getColumns()][i] = 0;
            }
        }
    }
    // i - columns
    if (i - tableGame->getColumns() > 0 && sq->getRow() != 1) {
        if (this->getChildByTag(i - tableGame->getColumns()) != NULL) {
            Square *sq1 = (Square*)this->getChildByTag(i - tableGame->getColumns());
            if (sq->getSouth() && sq1->getNorth()) {
                matran[i][i - tableGame->getColumns()] = 1;
                matran[i- tableGame->getColumns()][i] = 1;
            }else {
                matran[i][i - tableGame->getColumns()] = 0;
                matran[i- tableGame->getColumns()][i] = 0;
            }
        }
    }
}
void GamePlaySceneNew::printMatrix(int (*matran)[max], int row, int column) {
    for (int i = 1; i <= row ; i++) {
        for (int j = 1; j <= column ; j++) {
            printf("%i  ", matran[i][j]);
        }
        printf("\n");
    }
}
void GamePlaySceneNew::InPa() {
    CCLOG("kjnkjkjkjkjkjkkjjjjjj");
}
void GamePlaySceneNew::resetArray(int a[]) {
    for (int i = 0; i < max; i++) {
        a[i] = NULL;
    }
}
void GamePlaySceneNew::resetArrayTow(int (*a)[max]) {
    for (int i = 0; i < max; i ++) {
        for (int j = 0; j < max; j++) {
            a[i][j] = NULL;
        }
    }
}
void GamePlaySceneNew::addArrayInArray(int (*arrayPaths)[max], int *arrayPath,
                                    int row, int sizeArray) {
    for (int i = 1; i <= sizeArray; i ++) {
        arrayPaths[row][i] = arrayPath[i];
    }
}
void GamePlaySceneNew::runActionCoin(Coin *coin) {
    int *path = coin->getPath();
    CCArray * arPath = new CCArray();
    int dem = 0;
    for (int i = 1; i <= coin->getNumberPoint(); i++) {
        if (i == coin->getNumberPoint()) {
            if (this->getChildByTag(path[coin->getNumberPoint()])) {
                Square *sq =
                (Square*)this->getChildByTag(path[coin->getNumberPoint()]);
                int tag = 500 + sq->getRow();
                if (this->getChildByTag(tag)){
                    Missile *missile = (Missile*)this->getChildByTag(tag);
                    CCMoveTo * move =
                    CCMoveTo::create(coin->getSpeed(), missile->getPosition());
                    arPath->addObject(move);
                    move = NULL;
                }else {
                    if (this->getChildByTag(path[i])) {
                        Square *sq = (Square*)this->getChildByTag(path[i]);
                        CCMoveTo * move =
                        CCMoveTo::create(coin->getSpeed(), sq->getPosition());
                        arPath->addObject(move);
                        move = NULL;
                    }
                }
            }else dem ++;
        }else {
            if (this->getChildByTag(path[coin->getNumberPoint()])) {
                Square *sq = (Square*)this->getChildByTag(path[i]);
                CCMoveTo * move =
                CCMoveTo::create(coin->getSpeed(), sq->getPosition());
                arPath->addObject(move);
                move = NULL;
            }else dem ++;
        }
    }
    if (dem == 0) {
        CCCallFuncN *remove =
        CCCallFuncN::create(this,
                            callfuncN_selector(GamePlaySceneNew::removeCoin));
        arPath->addObject(remove);
        CCSequence * squen = CCSequence::create(arPath);
        coin->runAction(squen);
        remove = NULL;
        squen = NULL;
    }
}
void GamePlaySceneNew::removeSquare() {
        CCObject * ob;
        CCARRAY_FOREACH(_arrayRemove, ob) {
            Square * sq = (Square *) ob;
            if (sq->getRotateAble() == false && sq->getIsRemove() == false &&
                checkTableFirst == true) {
                _numberSqNotRotate --;
            }
            if (sq->getRotateAble() == false) {
                SimpleAudioEngine::sharedEngine()->playEffect("soundCombo.mp3",
                                                              false);
                if (sq->getCombo() == 4) {
                    CCSprite * item = (CCSprite*)sq->getChildByTag(10);
                    item->setVisible(false);
                    CCSprite * itemnew = CCSprite::create("gold_bell.png");
                    itemnew->setPosition(sq->getPosition());
                    this->addEffectTime(itemnew);
                }else if (sq->getCombo() == 5) {
                    CCSprite * item = (CCSprite*)sq->getChildByTag(20);
                    item->setVisible(false);
                    CCSprite * itemnew = CCSprite::create("gift01.png");
                    itemnew->setPosition(sq->getPosition());
                    itemnew->setTag(5);
                    this->addEffectScore(itemnew);
                }else if (sq->getCombo() == 6) {
                    CCSprite * item = (CCSprite*)sq->getChildByTag(30);
                    item->setVisible(false);
                    CCSprite * itemnew = CCSprite::create("gift02.png");
                    itemnew->setPosition(sq->getPosition());
                    itemnew->setTag(6);
                    this->addEffectScore(itemnew);
                }
            }
            _score = _score + sq->getPoint();
            char str_score[20] = {0};
            sprintf(str_score, "%i", _score);
            _lbScore->setString(str_score);
            this->resetArrayChar(str_score, 20);
            _sumNumberSquareRemove ++ ;
            CCRotateTo * rotate = CCRotateTo::create(0.2f, 180);
            CCMoveTo * move =
            CCMoveTo::create(0.3f, CCPoint(sq->getPosition().x,
                                           sq->getPosition().y - 10));
            CCCallFuncN *remove =
            CCCallFuncN::create(this,
                                callfuncN_selector(GamePlaySceneNew::removeOneSquare));
            CCSequence * squen = CCSequence::create(move, remove, NULL);
            sq->runAction(squen);
            sq->runAction(rotate);
            move = NULL;
            remove = NULL;
            squen = NULL;
        }
        _arrayRemove->removeAllObjects();
        this->resetArray(daxet);
}
void GamePlaySceneNew::downSquare() {
    CCObject * ob;
    CCPoint pOrigin = tableGame->getPointOrigin();
    int tableRow = tableGame->getRows();
    int tableColumn = tableGame->getColumns();
    int index = tableColumn * tableRow;
    int dem = 0;
    CCARRAY_FOREACH(_arraySquare, ob) {
        Square * sq = (Square *) ob;
        if (sq->getTag() >= tableColumn + 1 &&
            !this->getChildByTag(sq->getTag() - tableColumn)) {
            float mv = sq->getContentSize().height * sq->getScaleY();
            CCMoveTo * mb = CCMoveTo::create(0.1f, ccp(sq->getPosition().x,
                                                       sq->getPosition().y - mv));
            sq->runAction(mb);
            sq->setTag(sq->getTag() - tableColumn);
            sq->setRow(sq->getRow() - 1);
            dem ++;
            mb = NULL;
            mv = NULL;
        }
        if (sq->getTag() <= index ) {
            sq->setVisible(true);
        }
    }
    if (_arraySquare->count() < (tableRow + 1) * tableColumn) {
        _touchAble = false;
        int random = index + 1 + (rand() % (tableColumn) + 1);
        for (int k = index + 1; k <= index + tableColumn; k++) {
            if (!this->getChildByTag(k)) {
                int arCategory[10] = {2, 1, 3, 0, 0, 2, 0, 1, 2, 3};
                int category = arCategory[rand() % 10];
                char tileName[7][20];
                strcpy(tileName[0], "1.png");
                strcpy(tileName[1], "2.png");
                strcpy(tileName[2], "3.png");
                strcpy(tileName[3], "4.png");
                char spriteName[20];
                sprintf(spriteName, "%s", tileName[category]);
                bool notContain = false;
                bool w = true;
                bool e = true;
                bool n = true;
                bool s = true;
                bool statPoint = true;
                bool destination = true;
                switch (category) {
                    case 0:
                        w = true;
                        e = true;
                        n = false;
                        s = false;
                        break;
                    case 1:
                        w = true;
                        e = true;
                        n = true;
                        s = true;
                        break;
                    case 2:
                        w = true;
                        e = true;
                        n = true;
                        s = false;
                        break;
                    case 3:
                        w = true;
                        e = false;
                        n = false;
                        s = true;
                        break;
                    default:
                        break;
                }
                if (k == index + 1 && w == true) {
                    statPoint = true;
                } else statPoint = false;

                if (k == index + tableColumn && e == true) {
                    destination = true;
                } else destination = false;
                Square *sq =
                new  Square(notContain, w, e, n, s, tableGame->getRows() + 1,
                            k - index, statPoint, destination );
                if (k == random) {
                    if (_numberPathScore == 2) {
                        sq->setRotateAble(false);
                        sq->setCombo(1);
                        sq->setPoint(2);
                        char spriteName1[20];
                        sprintf(spriteName1, "red%i.png", category + 1);
                        sq->initWithFile(spriteName1);
                        this->resetArrayChar(spriteName1, 20);
                        _numberSqNotRotate ++;
                        _numberPathScore = 0;
                    }else if (_numberPathScore == 3) {
                        sq->setRotateAble(false);
                        sq->setCombo(2);
                        sq->setPoint(3);
                        char spriteName1[20];
                        sprintf(spriteName1, "yellow%i.png", category + 1);
                        sq->initWithFile(spriteName1);
                        this->resetArrayChar(spriteName1, 20);
                        _numberSqNotRotate ++;
                        _numberPathScore = 0;
                    } else if (_numberPathScore == 4) {
                        sq->setRotateAble(false);
                        sq->setCombo(3);
                        sq->setPoint(4);
                        sq->initWithFile(spriteName);
                        sq->setColor(ccc3(0, 0, 255));
                        _numberSqNotRotate ++;
                        _numberPathScore = 0;
                        sq->addCombo();
                    }else if (_numberPathScore == 5) {
                        sq->setRotateAble(false);
                        sq->setCombo(4);
                        sq->setPoint(2);
                        sq->initWithFile(spriteName);
                        sq->setColor(ccc3(10, 50, 255));
                        _numberSqNotRotate ++;
                        _numberPathScore = 0;
                        sq->addCombo();
                    }else if (_numberPathScore == 6) {
                        sq->setRotateAble(false);
                        sq->setCombo(5);
                        sq->setPoint(5);
                        sq->initWithFile(spriteName);
                        sq->setColor(ccc3(10, 50, 255));
                        _numberSqNotRotate ++;
                        _numberPathScore = 0;
                        sq->addCombo();
                    }else if (_numberPathScore > 6) {
                        sq->setRotateAble(false);
                        sq->setCombo(6);
                        sq->setPoint(5);
                        sq->initWithFile(spriteName);
                        sq->setColor(ccc3(10, 50, 255));
                        _numberSqNotRotate ++;
                        _numberPathScore = 0;
                        sq->addCombo();
                    }
                    else {
                        sq->setRotateAble(true);
                        sq->initWithFile(spriteName);
                    }
                }else {
                    sq->setRotateAble(true);
                    sq->initWithFile(spriteName);
                }
                sq->setScale(SIZE_RATIO_X);
                CCPoint p = ccp(pOrigin.x + ((k - index) + 0.5f) *
                                sq->getContentSize().width * SIZE_RATIO_X,
                                pOrigin.y + (tableRow + 1 + 0.5f) *
                                sq->getContentSize().height * SIZE_RATIO_X);
                sq->setPosition(p);
                _arraySquare->addObject(sq);
                this->addChild(sq, 1, k);
                sq->setTag(k);
                sq->setVisible(false);
            }
        }
    } else {
        this->loadMatrix();
    }
    if (dem == 0 && _numberPath == 0 && _arraySquare->count() >=
        (tableRow + 1) * tableColumn) {
        _touchAble = true;
    }
}
void GamePlaySceneNew::removeOneSquare(CCNode *node) {
    Square * sq = (Square*)node;
    sq->stopAllActions();
    sq->removeAllChildren();
    _arraySquare->removeObject(sq);
    this->removeChild(sq, true);
}
void GamePlaySceneNew::removePratice(CCNode *node) {
    node->stopAllActions();
    this->removeChild(node, true);
}
void GamePlaySceneNew::removeCoin(CCNode *node) {
    node->stopAllActions();
    node->removeAllChildren();
    this->removeChild(node, true);
    _numberPath --;
    if (_numberPath <= 0) {
        for (int i = 1; i <= tableGame->getRows(); i++) {
            Missile *mi = (Missile*)this->getChildByTag(500 + i);
            if (mi->getLaunched()) {
                CCMoveTo * move =
                CCMoveTo::create(1, ccp(width + 100, mi->getPosition().y + 500));
                CCCallFuncN *remove =
                CCCallFuncN::create(this, callfuncN_selector(GamePlaySceneNew::
                                                             removeMissile));
                CCSequence *sq = CCSequence::create(move, remove, NULL);
                mi->runAction(sq);
                if (GameManager::sharedGameManager()->getBGM()) {
                    SimpleAudioEngine::sharedEngine()->playEffect("phonglen.mp3",
                                                                  false);
                }
                CCParticleSun *m_emitter = CCParticleSun::create();
                m_emitter->retain();
                mi->addChild(m_emitter, 10);
                m_emitter->setScale((1.0f));
                m_emitter->
                setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
                if (GameManager::sharedGameManager()->getNumberRocket() == 1 ||
                    GameManager::sharedGameManager()->getNumberRocket() == 2) {
                    m_emitter->setPosition(ccp(45,50));
                } else  m_emitter->setPosition(ccp(65,40));
                m_emitter->setPositionType(kCCPositionTypeFree);
            }
        }
        this->removeSquare();
    }
}
void GamePlaySceneNew::runCheckTable(CCNode *node) {
    if (_numberPath <= 0 && _arraySquare->count() == (tableGame->getRows() + 1) *
        tableGame->getColumns()) {
        this->checkTableGame();
        checkTableFirst = true;
    }
}
void GamePlaySceneNew::removeMissile(CCNode *node) {
    if (GameManager::sharedGameManager()->getBGM()) {
        SimpleAudioEngine::sharedEngine()->playEffect("bum.m4a", false);
    }
    Missile * mi = (Missile*)node;
    Missile *missile = new Missile();
    char strName[20];
    sprintf(strName, "phao0%i.png",
            GameManager::sharedGameManager()->getNumberRocket());
    missile->initWithFile(strName);
    this->resetArrayChar(strName, 20);
    missile->setScale(SIZE_RATIO);
    if (this->getChildByTag(mi->getRow() * tableGame->getColumns())) {
        Square * sq =
        (Square*)this->getChildByTag(mi->getRow() * tableGame->getColumns());
        CCPoint p =
        CCPoint(sq->getPosition().x + sq->getContentSize().width * sq->getScaleX(),
                sq->getPosition().y);
        missile->setPosition(CCPoint(width + 200, p.y));
        missile->setTag(mi->getTag());
        missile->setRow(mi->getRow());
        missile->setOriginPoint(mi->getOriginPoint());
        this->addChild(missile, 100);
        CCMoveTo * move = CCMoveTo::create(0.5f, mi->getOriginPoint());
        CCCallFuncN *checktable =
        CCCallFuncN::create(this,
                            callfuncN_selector(GamePlaySceneNew::runCheckTable));
        CCSequence * seque = CCSequence::create(move, checktable, NULL);
        missile->runAction(seque);
        mi->stopAllActions();
        mi->removeAllChildren();
        this->removeChild(mi, true);
        _isSoundCoin = true;
    }
}
void GamePlaySceneNew::removeEffectTime(cocos2d::CCNode *node) {
    node->removeAllChildren();
    node->stopAllActions();
    this->removeChild(node, true);
    _time = _time + 10;
    char str_time[20] = {0};
    sprintf(str_time, "%i", _time);
    _lbTime->setString(str_time);
    this->resetArrayChar(str_time, 20);
}
void GamePlaySceneNew::removeEffectScore(cocos2d::CCNode *node) {
    node->removeAllChildren();
    node->stopAllActions();
    this->removeChild(node, true);
    if (node->getTag() == 5) {
        _score = _score + 500;
    }else if (node->getTag() == 6) _score = _score + 1000;
    char str_score[20] = {0};
    sprintf(str_score, "%i", _score);
    _lbScore->setString(str_score);
    this->resetArrayChar(str_score, 20);
}
void GamePlaySceneNew::setLevel(int level) {
    this->_level = level;
}
bool GamePlaySceneNew::findInArray(int x, int *array) {
    int lenght = 20;
    for (int i = 0; i < lenght; i ++) {
        if (x == array[i]) {
            return true;
        }
    }
    return false;
}
void GamePlaySceneNew::createArraySquareNotRotate() {
    if (_level < 10) {
        _numberSqNotRotate = _level * 2;
    }else _numberSqNotRotate = 20;
    
    for (int i = 0; i < _numberSqNotRotate; i ++) {
        array_square_not_rotate[i] =
        (tableGame->getRows() * tableGame->getColumns() /  _numberSqNotRotate * i) +
        rand() % ((tableGame->getRows() * tableGame->getColumns() /
                   _numberSqNotRotate)) + 1;
    }
}
void GamePlaySceneNew::setArraySquareNotRotate() {
    CCObject *i;
    CCARRAY_FOREACH(_arraySquare, i) {
        Square *sq = (Square*)i;
        if (this->findInArray(sq->getTag(), array_square_not_rotate)) {
            sq->setRotateAble(false);
            sq->setColor(ccc3(255, 0, 0));
        }else {
            sq->setRotateAble(true);
        }
    }
}
void GamePlaySceneNew::clickBackButton(CCObject *pSender) {
    if (_isPause) {
        CCDirector::sharedDirector()->resume();
    }
    this->resetArrayInt(arrayStart, max/5);
    this->resetArrayInt(daxet, max);
    this->resetArrayInt(pa, max);
    this->resetArrayInt(arrarDestination, max/5);
    this->resetArrayTow(matran);
    CCDirector::sharedDirector()->replaceScene(BeginScene::scene());
    saveScore();
}
void GamePlaySceneNew::clickResetButton(CCObject *pSender) {
    if (_isPause) {
        CCDirector::sharedDirector()->resume();
    }
    this->resetArrayInt(arrayStart, max/5);
    this->resetArrayInt(daxet, max);
    this->resetArrayInt(pa, max);
    this->resetArrayInt(arrarDestination, max/5);
    this->resetArrayTow(matran);
    GameManager::sharedGameManager()->setLevel(_level + 1);
    CCDirector::sharedDirector()->replaceScene(GamePlaySceneNew::scene());
    saveScore();
}
void GamePlaySceneNew::clickContinueButton(CCObject *pSender) {
    if (_isPause) {
        CCDirector::sharedDirector()->resume();
        _isPause = false;
        _layerEndGame->setVisible(false);
    }else {
        this->resetArrayInt(arrayStart, max/5);
        this->resetArrayInt(daxet, max);
        this->resetArrayInt(pa, max);
        this->resetArrayInt(arrarDestination, max/5);
        this->resetArrayTow(matran);
        GameManager::sharedGameManager()->setLevel(_level);
        CCDirector::sharedDirector()->replaceScene(GamePlaySceneNew::scene());
    }
}
void GamePlaySceneNew::clickPauseButton(CCObject *pSender) {
    if (_isPause == false && _isWin == false) {
        _isPause = true;
        CCDirector::sharedDirector()->pause();
        _layerEndGame->setVisible(true);
    }
}
void GamePlaySceneNew::saveScore() {
    int score10 =
    CCUserDefault::sharedUserDefault()->getIntegerForKey("high_score10");
    if (_score > score10) {
        int scorelist[10];
        for (int i = 0; i < 10; i++) {
            char scoreBuf[15] = {0};
            sprintf(scoreBuf, "high_score%d", i+1);
            scorelist[i] =
            CCUserDefault::sharedUserDefault()->getIntegerForKey(scoreBuf);
            this->resetArrayChar(scoreBuf, 15);
        }
        for (int i = 0; i < 10; i++) {
            if (scorelist[i] < _score) {
                for (int j = 9; j > i; j--) {
                    scorelist[j] = scorelist[j - 1];
                }
                scorelist[i] = _score;
                break;
            }
        }
        for (int i = 0; i < 10; i++) {
            char scoreBuf[15] = {0};
            sprintf(scoreBuf, "high_score%d", i+1);
            CCUserDefault::sharedUserDefault()->setIntegerForKey(scoreBuf,
                                                                 scorelist[i]);
            this->resetArrayChar(scoreBuf, 15);
        }
    }
}
void GamePlaySceneNew::menuBGM() {
    GameManager * game = GameManager::sharedGameManager();
    game->setBGM(!game->getBGM());
    _bgm_off->setVisible(!game->getBGM());
    if (game->getBGM()) {
        SimpleAudioEngine::sharedEngine()->resumeAllEffects();
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }else {
        SimpleAudioEngine::sharedEngine()->pauseAllEffects();
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
}
void GamePlaySceneNew::resetArrayInt(int *ar, int l) {
    for (int i = 0; i < l; i++) {
        ar[i] = NULL;
    }
}
void GamePlaySceneNew::resetArrayChar(char *ar, int lenght) {
    for (int i = 0; i < lenght; i++) {
        ar[i] = NULL;
    }
}