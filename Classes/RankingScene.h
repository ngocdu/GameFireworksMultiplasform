//
//  RankingScene.h
//  GameFireworks
//
//  Created by NgocDu on 13/11/04.
//
//

#ifndef GameFireworks_RankingScene_h
#define GameFireworks_RankingScene_h

#include "cocos2d.h"
#include "GamePlayScene.h"
class RankingScene : public cocos2d::CCLayer {
private:
    CCSize size;
    int levelmax;
    float width, height, SIZE_RATIO, SIZE_RATIO_X, SIZE_RATIO_Y;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    void itemMethod(CCObject *pSender);
    void clickBackMenu(CCObject *pSender);
    
    CREATE_FUNC(RankingScene);
};


#endif
