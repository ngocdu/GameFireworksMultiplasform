//
//  HelpScene.h
//  GameFireworks
//
//  Created by NgocDu on 13/11/14.
//
//

#ifndef GameFireworks_HelpScene_h
#define GameFireworks_HelpScene_h

#include "cocos2d.h"

class HelpScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelpScene);
};


#endif
