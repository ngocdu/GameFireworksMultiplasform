//
//  GamePlaySceneNew.h
//  GameFireworks
//
//  Created by NgocDu on 13/11/11.
//
//
#ifndef GameFireworks_GamePlaySceneNew_h
#define GameFireworks_GamePlaySceneNew_h
#include "cocos2d.h"
#include "TableGame.h"
#include "Square.h"
#include "Coin.h"
#include "Missile.h"
#define max 100
using namespace cocos2d;
class GamePlaySceneNew : public CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GamePlaySceneNew);
    virtual void ccTouchesBegan(cocos2d::CCSet * touch,cocos2d::CCEvent* event);
	virtual void ccTouchesMoved(cocos2d::CCSet* touch,cocos2d::CCEvent* event);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event);
    
    void addEffectTime(CCSprite *item);
    void addEffectScore(CCSprite *item);
    void addTextureCache();
    void addTableGame(int rows, int columns);
    void addCandles();
    void addCoin(int row, float speed, int path[], int numberPoint);
    void addMissiles();
    void addFire();
    void addPraticle(CCPoint position, int category);
    void addSquareToArrayRemove(Square *sq);
    void loadMatrix();
    void changeMatrix(Square *sq);
    void printMatrix(int matrix[max][max], int row, int column);
    void backTracking(int i);
    void backTrackingNew(int i, Square * taget);
    void loadStartPointAndDestination();
    void InPa();
    void resetArray(int a[]);
    void checkTableGame();
    void addArrayInArray(int arrayPaths[max/5][max], int arrayPath[], int row, int sizeArray);
    void resetArrayTow(int a[max][max]);
    void runActionCoin(Coin * coin);
    void removeSquare();
    void downSquare();
    void updateTime(float dt);
    void removeOneSquare(CCNode * node);
    void removeCoin(CCNode * node);
    void removeMissile(CCNode * node);
    void removePratice(CCNode * node);
    void runCheckTable(CCNode * node);
    void removeEffectTime(CCNode * node);
    void removeEffectScore(CCNode * node);
    void setLevel(int level);
    bool findInArray(int x, int array[]);
    void createArraySquareNotRotate();
    void setArraySquareNotRotate();
    void clickContinueButton(CCObject* pSender);
    void clickResetButton(CCObject* pSender);
    void clickBackButton(CCObject* pSender);
    void clickPauseButton(CCObject* pSender);
    void saveScore();
    void menuBGM();
    void resetArrayInt(int ar[], int lenght);
    void resetArrayChar(char ar[], int lenght);
private:
    CCSize  size;
    TableGame * tableGame;
    CCArray * _arraySquare;
    CCArray * _arrayRemove;
    CCPoint touchLocation;
    bool _touchAble;
    int arrarDestination[max/5];
    int arrayStart[max/5];
    int matran[max][max];
//    int arrayPath[max][max];
    int daxet[max];
    int pa[max];
    int chiphi;
    int c;//chi phí tạm thời
    int array_square_not_rotate[max/5];
    int _numberPathScore;
    int _numberPath;
    int _sumNumberPath;
    int _sumNumberSquareRemove;
    int _numberSqNotRotate;
    int _score;
    int _time;
    int _level;
    bool checkTableFirst;
    CCLabelTTF *_lbTime;
    CCLabelTTF *_lbScore;
    CCLayer * _layerEndGame;
    CCMenu * menu;
    CCSprite * _bgm_off;
    CCMenuItemImage * playItem;
    float width, height, SIZE_RATIO, SIZE_RATIO_X, SIZE_RATIO_Y;
    bool _isPause;
    bool _isWin;
    bool _isSoundCoin;
};
#endif