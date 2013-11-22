//
//  OptionScene.h
//  GameFireworks
//
//  Created by NgocDu on 13/11/15.
//
//

#ifndef GameFireworks_OptionScene_h
#define GameFireworks_OptionScene_h

#include "cocos2d.h"

class OptionScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void btClick(CCObject* pSender);
    void btClickPlay(CCObject* pSender);
    void addBackground();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(OptionScene);
private:
    cocos2d::CCMenu* pMenu;
};


#endif
