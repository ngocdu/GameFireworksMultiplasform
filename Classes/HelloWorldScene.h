#ifndef __BeginScene_SCENE_H__
#define __BeginScene_SCENE_H__

#include "cocos2d.h"
#include "EziSocialDelegate.h"

class BeginScene : public cocos2d::CCLayer, public EziFacebookDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnterTransitionDidFinish();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(BeginScene);
    
    // Facebook Delegate Methods
    virtual void fbSessionCallback(int responseCode, const char* responseMessage);
    virtual void fbUserDetailCallback(int responseCode, const char* responseMessage, EziFacebookUser* fbUser);
};

#endif // __BeginScene_SCENE_H__
