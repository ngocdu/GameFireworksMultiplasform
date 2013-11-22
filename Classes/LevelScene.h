//
//  LevelScene.h
//  GameFireworks
//
//  Created by macbook_016 on 2013/10/31.
//
//

#ifndef __GameFireworks__LevelScene__
#define __GameFireworks__LevelScene__

#include <iostream>
#include "cocos2d.h"
#include "GamePlayScene.h"
class LevelScene : public cocos2d::CCLayer {
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

    CREATE_FUNC(LevelScene);
};

#endif /* defined(__GameFireworks__LevelScene__) */
