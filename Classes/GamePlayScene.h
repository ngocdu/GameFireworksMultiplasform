//
//  GamePlayScene.h
//  GameFireworks
//
//  Created by NgocDu on 13/10/25.
//
//

#ifndef GameFireworks_GamePlayScene_h
#define GameFireworks_GamePlayScene_h
#include "cocos2d.h"
#include "TableGame.h"
#include "Square.h"
#include "Coin.h"
#include "Missile.h"
#define max 100
using namespace cocos2d;
class GamePlayScene : public CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GamePlayScene);
    virtual void ccTouchesBegan(cocos2d::CCSet * touch,cocos2d::CCEvent* event);
	virtual void ccTouchesMoved(cocos2d::CCSet* touch,cocos2d::CCEvent* event);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event);
    
    void addTableGame(int rows, int columns);
    void addCandles();
    void addCoin(int row, float speed, int path[], int numberPoint);
    void addMissiles();
    void addFire();
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
    void removeCoin(CCNode * node);
    void removeMissile(CCNode * node);
    void runCheckTable(CCNode * node);
    void setLevel(int level);
    bool findInArray(int x, int array[]);
    void createArraySquareNotRotate();
    void setArraySquareNotRotate();
    void playBGM();
    
    void clickContinueButton(CCObject* pSender);
    void clickResetButton(CCObject* pSender);
    void clickBackButton(CCObject* pSender);
    void clickPauseButton(CCObject* pSender);
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
    int arrayPath[max][max];
    int daxet[max];
    int pa[max];
    int chiphi;
    int c;//chi phí tạm thời
    int array_square_not_rotate[max/5];
    int _numberPath;
    int _numberSqNotRotate;
    int _score;
    int _time;
    int _level;
    bool checkTableFirst;
    CCLabelTTF *_lbTime;
    CCLayer * _layerEndGame;
    CCMenu * menu;
    CCSprite * _imageWin;
    CCSprite * _imageLose;
    float width, height, SIZE_RATIO, SIZE_RATIO_X, SIZE_RATIO_Y;
    bool _isPause;
    bool _isWin;
};
#endif
