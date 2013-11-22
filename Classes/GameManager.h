#ifndef _GameManager_H_
#define _GameManager_H_

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class GameManager : public cocos2d::CCObject {
private:
    //Constructor
    GameManager();

    //Instance of the singleton
    static GameManager* m_mySingleton;
    
    CC_SYNTHESIZE(float, _SCALE_N_X, SCALE_N_X);
    CC_SYNTHESIZE(float, _SCALE_N_Y, SCALE_N_Y);
    CC_SYNTHESIZE(int, _level, Level);
    CC_SYNTHESIZE(bool, _BGM, BGM);
    CC_SYNTHESIZE(int, _numberRocket, NumberRocket);
    CC_SYNTHESIZE(float, _SIZE_RATIO, SIZE_RATIO);
    CC_SYNTHESIZE(float, _SIZE_RATIO_X, SIZE_RATIO_X);
    CC_SYNTHESIZE(float, _SIZE_RATIO_Y, SIZE_RATIO_Y);
    CC_SYNTHESIZE(int, _platform, Platform);
public:
    //Get instance of singleton
    static GameManager* sharedGameManager();
};

#endif