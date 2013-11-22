//
//  GamePlayScene.cpp
//  GameFireworks
//
//  Created by NgocDu on 13/10/25.
//
//

#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "Square.h"
#include "BeginScene.h"
#include "GameManager.h"
#include "LevelScene.h"
#include <stdio.h>
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GamePlayScene::scene() {
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GamePlayScene *layer = GamePlayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool GamePlayScene::init() {
//    srandom(time(NULL));
    
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() ) {
        return false;
    }
    if (GameManager::sharedGameManager()->getBGM()) {
        this->playBGM();
    }
    this->setTouchEnabled(true);
    size = CCDirector::sharedDirector()->getWinSize();
    SIZE_RATIO = (size.width + size.height) / (640 + 960);
    SIZE_RATIO_X = size.width / 768;
    SIZE_RATIO_Y = size.height / 1024;
    _arraySquare = new CCArray();
    _arrayRemove = new CCArray();
    _numberPath = 0;
    _level = GameManager::sharedGameManager()->getLevel();
    _time =  120 ;
    _numberSqNotRotate = 0;
    checkTableFirst = false;
    _isPause = false;
    _isWin = false;
    char str_time[20] = {0};
    sprintf(str_time, "%i", _time);
    _lbTime = CCLabelTTF::create(str_time, "", 40);
    _lbTime->setPosition(ccp(size.width / 9, size.height - size.height/20));
    _lbTime->setScaleY(SIZE_RATIO_Y);
    _lbTime->setScaleX(SIZE_RATIO_X);
    this->addChild(_lbTime, 10);
    this->resetArrayTow(arrayPath);
    
    this->addTableGame(9, 6);
    this->addCandles();
    this->addFire();
    this->addMissiles();
    this->loadMatrix();
    this->checkTableGame();
    _touchAble = true;
    
    CCSprite * spriteTime = CCSprite::create("TimerBG.png");
    spriteTime->setPosition(ccp(size.width / 9, size.height - size.height/20));
    spriteTime->setScaleX(SIZE_RATIO_X);
    spriteTime->setScaleY(SIZE_RATIO_Y);
    this->addChild(spriteTime, 9);
    
    _layerEndGame = CCLayer::create();
    _layerEndGame->setScaleY(SIZE_RATIO_Y);
    _layerEndGame->setScaleX(SIZE_RATIO_X);
    _layerEndGame->setPosition(CCPoint(0, 0));
    CCSprite *bgEnd = CCSprite::create("EndGameBG.png");
    bgEnd->setPosition(CCPoint(size.width/2, size.height/2));
    _layerEndGame->addChild(bgEnd);
    
    CCSprite * imageLevel = CCSprite::create("table_lever.png");
    imageLevel->setPosition(CCPoint(size.width/10, size.height/20));
    imageLevel->setScale(SIZE_RATIO);
    this->addChild(imageLevel, 10);
    
    char strLev[10];
    sprintf(strLev, "Level %i", _level);
    CCLabelTTF *lbLevel = CCLabelTTF::create(strLev,"", 20);
    lbLevel->setPosition(CCPoint(imageLevel->getPosition().x,
            imageLevel->getPosition().y + imageLevel->getContentSize().height/4 * imageLevel->getScaleY()));
    lbLevel->setColor(ccc3(255, 100, 100));
    lbLevel->setScale(SIZE_RATIO);
    this->addChild(lbLevel, 12);
    
    CCSprite * imagePause = CCSprite::create("table_pause.png");
    imagePause->setPosition(CCPoint(size.width - size.width/10, size.height/20));
    imagePause->setScale(SIZE_RATIO);
    this->addChild(imagePause, 10);

    CCMenuItemImage * pause =
    CCMenuItemImage::create("pause.png", "pause_hover.png",this,
                            menu_selector(GamePlayScene::clickPauseButton));
    pause->setPosition(ccp(250, 450));
    pause->setScale(SIZE_RATIO);
    pause->setPosition(CCPoint(size.width - size.width/10, size.height/20));
    
    CCMenu * menuPause = CCMenu::create(pause, NULL);
    menuPause->setPosition(CCPoint(0, 0));
    this->addChild(menuPause , 10);
    
    
    CCMenuItemImage * playItem =
    CCMenuItemImage::create("Continue.png", "ContinueButtonOnClicked.png",this,
                            menu_selector(GamePlayScene::clickContinueButton));
    playItem->setPosition(ccp(250 * SIZE_RATIO_X, 450 * SIZE_RATIO_Y));
    playItem->setScale(3/4.0f);
    
    CCMenuItemImage * restart =
    CCMenuItemImage::create("RestartButton.png", "RestartButtonOnClicked.png",this,
                            menu_selector(GamePlayScene::clickResetButton));
    restart->setPosition(ccp(350 * SIZE_RATIO_X, 390 * SIZE_RATIO_Y));
    restart->setScale(3/4.0f);

    CCMenuItemImage * back =
    CCMenuItemImage::create("BackButton.png", "BackButtonOnClicked.png", this,
                            menu_selector(GamePlayScene::clickBackButton));
    back->setPosition(ccp(500 * SIZE_RATIO_X, 450 * SIZE_RATIO_Y));
    back->setScale(3/4.0f);
    
//    CCMenuItemImage * resume =
//    CCMenuItemImage::create("BackButton.png", "BackButtonOnClicked.png", this,
//                            menu_selector(GamePlayScene::clickBackButton));
//    resume->setPosition(ccp(500, 450));
    
    menu = CCMenu::create(playItem, back,restart, NULL);
    menu->setPosition(CCPoint(0, 0));
    _layerEndGame->addChild(menu);
    
    _imageLose = CCSprite::create("YouLose.png");
    _imageLose->setPosition(ccp(350 * SIZE_RATIO_X, 580 * SIZE_RATIO_Y));
    _layerEndGame->addChild(_imageLose);
    
    _imageWin = CCSprite::create("YouWin.png");
    _imageWin->setPosition(ccp(350 * SIZE_RATIO_X, 580 * SIZE_RATIO_Y));
    _layerEndGame->addChild(_imageWin);
    
    _layerEndGame->setVisible(false);
    this->addChild(_layerEndGame, 20);
    
    CCSprite * bground = CCSprite::create("bg.png");
    bground->setPosition(CCPoint(size.width/2, size.height/2));
    bground->setScaleX(SIZE_RATIO_X);
    bground->setScaleY(SIZE_RATIO_Y);
    this->addChild(bground);
    
    
    this->schedule(schedule_selector(GamePlayScene::downSquare), 0.1);
    this->schedule(schedule_selector(GamePlayScene::updateTime), 1);
    return true;
}
void GamePlayScene::addTableGame(int rows, int columns) {
    CCPoint pOrigin = CCPoint(57 * SIZE_RATIO_X , 40 * SIZE_RATIO_Y);
//    float WithTable = size.width * 5 / 7;
//    float HeightTable = size.height * 5 / 6;
    float WithTable = 490 * SIZE_RATIO_X;
    float HeightTable = 700 * SIZE_RATIO_Y;
    tableGame = new TableGame(rows, columns, pOrigin, WithTable, HeightTable);
    this->createArraySquareNotRotate();
    float with = tableGame->getWidth() / tableGame->getColumns() * 1.0f;
    float height = tableGame->getHeight() / tableGame->getRows() * 1.0f;
    int dem = 0;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {
            dem++;
            int arCategory[10] = {0, 0, 1, 1, 1, 0, 0, 2, 2, 3};
            int category = arCategory[rand() % 10];
            char tileName[7][20];
            strcpy(tileName[0], "square_blue01.png");
            strcpy(tileName[1], "square_blue07.png");
            strcpy(tileName[2], "square_blue08.png");
            strcpy(tileName[3], "square_blue05.png");
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
                    w = false;
                    e = true;
                    n = true;
                    s = false;
                    break;
                case 2:
                    w = true;
                    e = true;
                    n = false;
                    s = true;
                    break;
                case 3:
                    w = true;
                    e = true;
                    n = true;
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
            float sx = with * 1.0f / sq->getContentSize().width;
            float sy = height * 1.0f / sq->getContentSize().height;
            sq->setScaleX(sx);
            sq->setScaleY(sy);
            CCPoint p =
            ccp(pOrigin.x + (j + 0.5f) * sq->getContentSize().width * sx,
                pOrigin.y + (i + 0.5f) * sq->getContentSize().height * (sy));
            sq->setPosition(p);
            _arraySquare->addObject(sq);
            this->addChild(sq, 1, dem);
            sq->setTag(dem);
            
//            char strTime[20] = {0};
//            sprintf(strTime, "%i, %i , %i", i, j, dem);
//            CCLabelTTF *lable = CCLabelTTF::create(strTime, "Time New Roman", 13);
//            lable->setPosition(p);
//            this->addChild(lable, 10);
        }
    }
}
void GamePlayScene::addFire() {
    for (int i = 1; i <= tableGame->getRows(); i++) {
        Square * sq = (Square*)this->getChildByTag(1 + tableGame->getColumns() * (i - 1));
        CCPoint p = CCPoint(sq->getPosition().x - sq->getContentSize().width *2/3 * sq->getScaleX(),
                            sq->getPosition().y);
        CCParticleSun *m_emitter = CCParticleSun::create();
        m_emitter->retain();
        this->addChild(m_emitter, 10);
        m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("fire.png"));
        m_emitter->setPosition( p );
        m_emitter->setPositionType( kCCPositionTypeGrouped );
        m_emitter->setTotalParticles(10);
        m_emitter->setScaleX(SIZE_RATIO_X);
        m_emitter->setScaleY(SIZE_RATIO_Y);
    }
    
    CCSprite * ball_light = CCSprite::create("light.png");
    ball_light->setScaleY(SIZE_RATIO_Y);
    ball_light->setScaleX(SIZE_RATIO_X);
    CCAnimation *anim=CCAnimation::create();
    anim->addSpriteFrameWithFileName("light.png");
    anim->addSpriteFrameWithFileName("light_glow.png");
//    anim->addSpriteFrameWithFileName("light02_glow.png");
//    anim->addSpriteFrameWithFileName("light02.png");
    anim->setDelayPerUnit(2.8f / 9.0f);
    anim->setRestoreOriginalFrame(true);
    CCAnimate * animet=CCAnimate::create(anim);
    CCRepeatForever *re = CCRepeatForever::create(animet);
    ball_light->runAction(re);
    ball_light->setPosition(CCPoint(size.width/2, size.height - size.height/8));
    this->addChild(ball_light, 3);
}
void GamePlayScene::addCandles() {
    for (int i = 1; i <= tableGame->getRows(); i++) {
        Square * sq =
        (Square*)this->getChildByTag(1 + tableGame->getColumns() * (i - 1));
        CCSprite *candle = new CCSprite();
        candle->initWithFile("nen.png");
        candle->setScaleX(SIZE_RATIO_X);
        candle->setScaleY(SIZE_RATIO_Y);
        CCPoint p =
        CCPoint(sq->getPosition().x - sq->getContentSize().width *2/3 * sq->getScaleX(),
                sq->getPosition().y - sq->getContentSize().height *1/3 * sq->getScaleY());
        candle->setPosition(p);
        this->addChild(candle, 10);
    }
}
void GamePlayScene::addCoin(int row, float speed, int path[], int numberPoint) {
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
    this->runActionCoin(coin);
    
    CCParticleSun *m_emitter = CCParticleSun::create();
    m_emitter->retain();
    coin->addChild(m_emitter, 10);
    m_emitter->setScale((2.0f));
    m_emitter->setTexture(CCTextureCache::
                          sharedTextureCache()->addImage("fire.png"));
    m_emitter->setPosition(ccp(50,50));
    //                    m_emitter->setLife(2);
    m_emitter->setPositionType(kCCPositionTypeGrouped);
    //                    m_emitter->setTotalParticles(15);
}
void GamePlayScene::addMissiles() {
    for (int i = 1; i <= tableGame->getRows(); i++) {
        Missile *missile = new Missile();
        missile->initWithFile("phao02.png");
        missile->setScale(SIZE_RATIO);
//        missile->setColor(ccc3(255, 0, 0));
        Square * sq = (Square*)this->getChildByTag(tableGame->getColumns() * i);
        CCPoint p =
        CCPoint(sq->getPosition().x + sq->getContentSize().width * sq->getScaleX(),
                sq->getPosition().y);
        missile->setPosition(p);
        missile->setTag(500 + i);
        missile->setRow(i);
        missile->setScaleY(SIZE_RATIO_Y);
        missile->setScaleX(SIZE_RATIO_X);
        this->addChild(missile, 10);
        
        CCSprite *tat = CCSprite::create("tat.png");
        tat->setPosition(p);
        tat->setScaleY(SIZE_RATIO_Y);
        tat->setScaleX(SIZE_RATIO_X);
        this->addChild(tat, 9);
    }
}
void GamePlayScene::updateTime(float dt) {
    
    if (_time > 0) {
        _time --;
    }else if(_time <= 0 ) {
        CCDirector::sharedDirector()->replaceScene(BeginScene::scene());
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        _layerEndGame->setVisible(true);
        _imageLose->setVisible(true);
        this->unscheduleAllSelectors();
        _imageWin->setVisible(false);
        this->unschedule(schedule_selector(GamePlayScene::updateTime));
    }
    if (_numberSqNotRotate <= 0 && checkTableFirst == true) {
        _isWin = true;
        this->setTouchEnabled(false);
        int level = CCUserDefault::sharedUserDefault()->getIntegerForKey("level");
        if (_level == level) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("level", level + 1);
        }
        
        char stri[4];
        sprintf(stri, "high_score%i", _level);
        int score = CCUserDefault::sharedUserDefault()->getIntegerForKey(stri);
        
        if (_time > score) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey(stri, _time);
        }
        this->unschedule(schedule_selector(GamePlayScene::updateTime));
        _layerEndGame->setVisible(true);
        _imageWin->setVisible(true);
        _imageLose->setVisible(false);
        
        CCParticleFlower *m_emitter = CCParticleFlower::create();
        m_emitter->retain();
        _layerEndGame->addChild(m_emitter, 10);
        m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("fire.png"));
        m_emitter->setPosition( CCPoint(0, size.height * 2/4 + size.height/20));
//        m_emitter->setPositionType( kCCPositionTypeGrouped );
//        m_emitter->setScale(2);
//        m_emitter->setTotalParticles(100);
        CCMoveTo * move = CCMoveTo::create(3, CCPoint(size.width, size.height * 2/4 + size.height/20));
        CCMoveTo * moveback = CCMoveTo::create(3, CCPoint(0, size.height * 2/4 + size.height/20));
        CCSequence * sque = CCSequence::create(move, moveback, NULL);
        CCRepeatForever * re = CCRepeatForever::create(sque);
        m_emitter->runAction(re);
        
        CCParticleFlower *m_emitter1 = CCParticleFlower::create();
        m_emitter1->retain();
        _layerEndGame->addChild(m_emitter1, 10);
        m_emitter1->setTexture( CCTextureCache::sharedTextureCache()->addImage("fire.png"));
        m_emitter1->setPosition( CCPoint(size.width, size.height * 2/4 + size.height/20));
        //        m_emitter->setPositionType( kCCPositionTypeGrouped );
//        m_emitter1->setScale(2);
//        m_emitter1->setTotalParticles(100);
        CCMoveTo * move1 = CCMoveTo::create(3, CCPoint(size.width, size.height * 2/4 + size.height/20));
        CCMoveTo * moveback1 = CCMoveTo::create(3, CCPoint(0, size.height * 2/4 + size.height/20));
        CCSequence * sque1 = CCSequence::create(moveback1, move1, NULL);
        CCRepeatForever * re1 = CCRepeatForever::create(sque1);
        m_emitter1->runAction(re1);
    }
    char str_time[20] = {0};
    sprintf(str_time, "%i", _time);
    _lbTime->setString(str_time);
}
void GamePlayScene::ccTouchesBegan(cocos2d::CCSet * touch,cocos2d::CCEvent* event) {
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
void GamePlayScene::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event) {
    if (_touchAble)
    {
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
void GamePlayScene::ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event)
{
    if (_touchAble) {
        CCObject * i;
        CCARRAY_FOREACH(_arraySquare, i) {
            Square * sq = (Square*)i;
            sq->setIsMoveTouch(false);
        }
        this->loadMatrix();
        if (_numberPath == 0) {
            this->checkTableGame();
        }
    }
}
void GamePlayScene::checkTableGame() {
    _touchAble = false;
    for (int i = 1; i <= tableGame->getRows(); i ++) {
        int k = 1 + (i - 1) * tableGame->getColumns() ;
        Square * sq;
        if (this->getChildByTag(k)) {
            sq = (Square*)this->getChildByTag(k);
            if (sq->getStartPoint() == true)
            {
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
    if (_numberPath > 0 && checkTableFirst == false) {
        //
    }else if (_numberPath == 0 && checkTableFirst == false){
        checkTableFirst = true;
        this->setArraySquareNotRotate();
    }
}
void GamePlayScene::backTracking(int i) {
    int n = tableGame->getRows() * tableGame->getColumns();
    for(int j=2; j<=n; j++)
        if(daxet[j] != 1 && matran[pa[i-1]][j] == 1) {
            pa[i] = j;
            daxet[j] = 1;
            c += matran[pa[i-1]][j];
            Square * sq = (Square*)this->getChildByTag(j);
            if(sq->getDestination() == true) {
                _numberPath ++;
                this->addArrayInArray(arrayPath, pa, _numberPath, i);
            } else backTracking(i+1);

            daxet[j] = 0;
            c -= matran[pa[i-1]][j];
        }
}
void GamePlayScene::backTrackingNew(int i, Square * sqTaget) {
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
                this->addCoin(sq->getRow() , 1.0f / i, pa, i);
                this->addArrayInArray(arrayPath, pa, _numberPath, i);
                for (int k = 1; k <= i; k++) {
                    Square *sq = (Square *)this->getChildByTag(pa[k]);
                    _arrayRemove->addObject(sq);
                }
            } else backTrackingNew(i+1, sqTaget);
            
            daxet[j] = 0;
            c -= matran[pa[i-1]][j];
        }
}
void GamePlayScene::loadStartPointAndDestination() {
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
void GamePlayScene::loadMatrix() {
    if (_arraySquare->count() >= tableGame->getColumns() * (tableGame->getRows() )) {
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
void GamePlayScene::changeMatrix(Square *sq) {
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
void GamePlayScene::printMatrix(int (*matran)[max], int row, int column) {
    for (int i = 1; i <= row ; i++) {
        for (int j = 1; j <= column ; j++) {
            printf("%i  ", matran[i][j]);
        }
        printf("\n");
    }
}
void GamePlayScene::InPa() {
    CCLOG("kjnkjkjkjkjkjkkjjjjjj");
}
void GamePlayScene::resetArray(int a[]) {
    for (int i = 0; i < max; i++) {
        a[i] = 0;
    }
}
void GamePlayScene::resetArrayTow(int (*a)[max]) {
    for (int i = 0; i < 90; i ++) {
        for (int j = 0; j < 90; j++) {
            a[i][j] = 0;
        }
    }
}
void GamePlayScene::addArrayInArray(int (*arrayPaths)[max], int *arrayPath,
                                    int row, int sizeArray) {
    for (int i = 1; i <= sizeArray; i ++) {
        arrayPaths[row][i] = arrayPath[i];
    }
}
void GamePlayScene::runActionCoin(Coin *coin) {
    int *path = coin->getPath();
    CCArray * arPath = new CCArray();
    int dem = 0;
    for (int i = 1; i <= coin->getNumberPoint(); i++) {
        SimpleAudioEngine::sharedEngine()->playEffect("before.m4a", false);
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
                }else {
                    Square *sq = (Square*)this->getChildByTag(path[i]);
                    CCMoveTo * move =
                    CCMoveTo::create(coin->getSpeed(), sq->getPosition());
                    arPath->addObject(move); 
                }
            }else dem ++;
        }else {
            if (this->getChildByTag(path[coin->getNumberPoint()])) {
                Square *sq = (Square*)this->getChildByTag(path[i]);
                CCMoveTo * move =
                CCMoveTo::create(coin->getSpeed(), sq->getPosition());
                arPath->addObject(move);
            }else dem ++;
        }
    }
    if (dem == 0) {
        CCCallFuncN *remove =
        CCCallFuncN::create(this, callfuncN_selector(GamePlayScene::removeCoin));
        arPath->addObject(remove);
        CCSequence * squen = CCSequence::create(arPath);
        coin->runAction(squen);
    } 
}
void GamePlayScene::removeSquare() {
//    if (_numberPath == 0)
    {
        CCObject * ob;
        CCARRAY_FOREACH(_arrayRemove, ob) {
            Square * sq = (Square *) ob;
            if (sq->getRotateAble() == false && sq->getIsRemove() == false && checkTableFirst == true) {
                _numberSqNotRotate --;
                sq->setIsRemove(true);
            }
            _arraySquare->removeObject(ob);
            this->removeChild(sq, true);
        }
        _arrayRemove->removeAllObjects();
        this->resetArray(daxet);
        
    }
}
void GamePlayScene::downSquare() {
    CCObject * ob;
    CCPoint pOrigin = tableGame->getPointOrigin();
    int tableRow = tableGame->getRows();
    int tableColumn = tableGame->getColumns();
    float with = tableGame->getWidth() / tableColumn * 1.0f;
    float height = tableGame->getHeight() / tableRow * 1.0f;
    int index = tableColumn * tableRow;
    int dem = 0;
    CCARRAY_FOREACH(_arraySquare, ob) {
        Square * sq = (Square *) ob;
        if (sq->getTag() >= tableColumn + 1 &&
            !this->getChildByTag(sq->getTag() - tableColumn)) {
            float mv = sq->getContentSize().height * sq->getScaleY();
            CCMoveBy * mb = CCMoveBy::create(0.1, ccp(0, -mv));
            sq->runAction(mb);
            sq->setTag(sq->getTag() - tableColumn);
            sq->setRow(sq->getRow() - 1);
            dem ++;
        }
        if (sq->getTag() <= index ) {
            sq->setVisible(true);
        }
    }
    if (_arraySquare->count() < (tableRow + 1) * tableColumn) {
        _touchAble = false;
        for (int k = index + 1; k <= index + tableColumn; k++) {
            if (!this->getChildByTag(k)) {
                int arCategory[10] = {0, 0, 1, 1, 1, 0, 0, 2, 2, 3};
                int category = arCategory[rand() % 10];
                char tileName[7][20];
                strcpy(tileName[0], "square_blue01.png");
                strcpy(tileName[1], "square_blue07.png");
                strcpy(tileName[2], "square_blue08.png");
                strcpy(tileName[3], "square_blue05.png");
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
                        w = false;
                        e = true;
                        n = true;
                        s = false;
                        break;
                    case 2:
                        w = true;
                        e = true;
                        n = false;
                        s = true;
                        break;
                    case 3:
                        w = true;
                        e = true;
                        n = true;
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
                sq->initWithFile(spriteName);
                sq->setRotateAble(true);
                float sx = with * 1.0f / sq->getContentSize().width;
                float sy = height * 1.0f / sq->getContentSize().height;
                sq->setScaleX(sx);
                sq->setScaleY(sy);
                CCPoint p = ccp(pOrigin.x + ((k - index) + 0.5f) *
                                sq->getContentSize().width * sx,
                                pOrigin.y + (tableRow + 1 + 0.5f) *
                                sq->getContentSize().height * (sy));
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
void GamePlayScene::removeCoin(cocos2d::CCNode *node) {
    node->removeAllChildren();
    this->removeChild(node, true);
    _numberPath --;
    if (_numberPath <= 0) {
        for (int i = 1; i <= tableGame->getRows(); i++) {
            Missile *mi = (Missile*)this->getChildByTag(500 + i);
            if (mi->getLaunched()) {
                CCMoveTo * move = CCMoveTo::create(1, ccp(size.width + 100,
                                                    mi->getPosition().y + 500));
                CCCallFuncN *remove = CCCallFuncN::create(this,
                            callfuncN_selector(GamePlayScene::removeMissile));
                CCSequence *sq = CCSequence::create(move, remove, NULL);
                mi->runAction(sq);
                SimpleAudioEngine::sharedEngine()->playEffect("firework.m4a", false);
//                for (int d = 1; d <= mi->getNumberPath() / _level + 1; d++)
                {
                    CCParticleSun *m_emitter = CCParticleSun::create();
                    m_emitter->retain();
                    mi->addChild(m_emitter, 10);
                    m_emitter->setScale((1.0f));
                    m_emitter->setTexture(CCTextureCache::
                                          sharedTextureCache()->addImage("fire.png"));
                    m_emitter->setPosition(ccp(45,50));
//                    m_emitter->setLife(2);
                    m_emitter->setPositionType(kCCPositionTypeFree);
//                    m_emitter->setTotalParticles(15);
                }
            }
        }
        this->removeSquare();
    }
}
void GamePlayScene::runCheckTable(cocos2d::CCNode *node) {
    if (_numberPath <= 0) {
        this->checkTableGame();
    }
}
void GamePlayScene::removeMissile(cocos2d::CCNode *node) {
    Missile * mi = (Missile*)node;
    Missile *missile = new Missile();
    missile->initWithFile("phao02.png");
    missile->setScale(SIZE_RATIO);
//    missile->setColor(ccc3(255, 0, 0));
//    if (this->getChildByTag(mi->getRow() * tableGame->getColumns()))
    {
        Square * sq =
        (Square*)this->getChildByTag(mi->getRow() * tableGame->getColumns());
        CCPoint p =
        CCPoint(sq->getPosition().x + sq->getContentSize().width * sq->getScaleX(),
                sq->getPosition().y);
        missile->setPosition(CCPoint(size.width + 200, p.y));
        missile->setTag(mi->getTag());
        missile->setRow(mi->getRow());
        this->addChild(missile, 100);
        CCMoveTo * move = CCMoveTo::create(0.5f, p);
        CCCallFuncN *checktable =
        CCCallFuncN::create(this, callfuncN_selector(GamePlayScene::runCheckTable));
        CCSequence * seque = CCSequence::create(move, checktable, NULL);
        missile->runAction(seque);
        mi->removeAllChildren();
        this->removeChild(mi, true);
    }
    if (checkTableFirst == false) {
        this->setArraySquareNotRotate();
        checkTableFirst = true;
    }
}
void GamePlayScene::setLevel(int level) {
    this->_level = level;
}
bool GamePlayScene::findInArray(int x, int *array) {
//    int lenght = sizeof(array) / sizeof(array[0]);
    int lenght = 20;
    for (int i = 0; i < lenght; i ++) {
        if (x == array[i]) {
            return true;
        }
    }
    return false;
}
void GamePlayScene::createArraySquareNotRotate() {
    if (_level < 10) {
        _numberSqNotRotate = _level * 2;
    }else _numberSqNotRotate = 20;
    
    for (int i = 0; i < _numberSqNotRotate; i ++) {
        array_square_not_rotate[i] = (tableGame->getRows() * tableGame->getColumns() /  _numberSqNotRotate * i) +
                   rand() % ((tableGame->getRows() * tableGame->getColumns() /  _numberSqNotRotate)) + 1 ;
    }
}
void GamePlayScene::setArraySquareNotRotate() {
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
void GamePlayScene::playBGM() {
    int level = GameManager::sharedGameManager()->getLevel();
    switch (level) {
        case 1:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv1.mp3");
            break;
        case 2:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv2.mp3");
            break;
        case 3:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv3.mp3");
            break;
        case 4:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv4.mp3");
            break;
        case 5:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv5.mp3");
            break;
        case 6:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv6.mp3");
            break;
        case 7:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv7.mp3");
            break;
        case 8:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv8.mp3");
            break;
        case 9:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv9.mp3");
            break;
        case 10:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv10.mp3");
            break;
        case 11:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv11.mp3");
            break;
        case 12:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("lv12.mp3");
            break;
        default:
            break;
    }
}
void GamePlayScene::clickBackButton(CCObject *pSender) {
    if (_isPause) {
        CCDirector::sharedDirector()->resume();
    }
    CCDirector::sharedDirector()->replaceScene(LevelScene::scene());
}
void GamePlayScene::clickResetButton(CCObject *pSender) {
    if (_isPause) {
        CCDirector::sharedDirector()->resume();
        _isPause = false;
        _layerEndGame->setVisible(false);
    }else {
        GameManager::sharedGameManager()->setLevel(_level);
        CCDirector::sharedDirector()->replaceScene(GamePlayScene::scene());
    } 
}
void GamePlayScene::clickContinueButton(CCObject *pSender) {
    if (_isPause) {
        CCDirector::sharedDirector()->resume();
    }
    GameManager::sharedGameManager()->setLevel(_level + 1);
    CCDirector::sharedDirector()->replaceScene(GamePlayScene::scene());
}
void GamePlayScene::clickPauseButton(CCObject *pSender) {
    if (_isPause == false && _isWin == false) {
        _isPause = true;
        CCDirector::sharedDirector()->pause();
        _layerEndGame->setVisible(true);
        _imageWin->setVisible(false);
        _imageLose->setVisible(false);
    }
}