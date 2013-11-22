//
//  BeginScene.h
//  GameFireworks
//
//  Created by macbook_016 on 2013/10/29.
//
//

#ifndef __GameFireworks__BeginScene__
#define __GameFireworks__BeginScene__

#include <iostream>
#include "cocos2d.h"
#include "GamePlayScene.h"
#include "LevelScene.h"
#include "EziSocialDelegate.h"
#include "EziFacebookUser.h"
class BeginScene : public cocos2d::CCLayer,
public EziFacebookDelegate,
public EziEmailDelegate,
public EziTwitterDelegate {
private:
    CCSize size;
    CCSprite * bgm_off;

    float width, height, SIZE_RATIO, SIZE_RATIO_X, SIZE_RATIO_Y;
    
    //-------------------------------
    const char* profileID;
    
    float SCREEN_WIDTH;
    float SCREEN_HEIGHT;
    
    float SCALE_FACTOR;
    float GAP;
    
    
    cocos2d::CCLabelTTF* pendingRequestCount;
    
    cocos2d::CCArray* _highScores;
    cocos2d::CCArray* _highScorePlayerNames;
    
    cocos2d::CCLayerColor* _previousLayer;
    cocos2d::CCLayerColor* _currentLayer;
    
    cocos2d::CCLayerColor* _loginLayer;
    cocos2d::CCLayerColor* _userDetailsLayer;
    cocos2d::CCLayerColor* _facebookActionLayer;
    cocos2d::CCLayerColor* _highScoreLayer;
    
    cocos2d::CCLabelTTF* mName;
    cocos2d::CCLabelTTF* mUsername;
    cocos2d::CCLabelTTF* mGender;
    cocos2d::CCLabelTTF* mHometown;
    cocos2d::CCLabelTTF* mPresentLocation;
    cocos2d::CCLabelTTF* mProfileID;
    cocos2d::CCLabelTTF* mFirstName;
    cocos2d::CCLabelTTF* mLastName;
    cocos2d::CCLabelTTF* mAccessToken;
    
    cocos2d::CCMenu* mFBActionMenu;
    
    cocos2d::CCSprite *mBallSprite;
    
    EziFacebookUser* mCurrentFacebookUser;
    
    
    // Preparing Pages
    void prepareLoginPage();
    void prepareUserDetailPage();
    void prepareFacebookActionPage();
    void prepareHighScorePage();
    void prepareScene();
    
    // Showing Pages
    void showLayer(cocos2d::CCLayerColor* layerToShow);
    void showLoginPage();
    void showUserDetailPage();
    void showFacebookActionPage();
    void showTwitterActionPage();
    void showHighScorePage(cocos2d::CCArray* highScoreList);
//    void showRequestList();
    
    // Facebook Action Items
    void loginViaFacebook();
    void logoutFromFacebook();
    void postMessageOnFacebookWall();
    void autoPostMessageOnFacebookWall();
//    void getListOfFriendsUsingThisApp();
    void checkIfUserLikeMyFacebookPage();
    void fetchFBUserDetails();
    void postScore();
    void getHighScores();
    void openFacebookPage();
//    void getUserPhoto();
    
    void postPhoto();
    
    // Facebook Requests
//    void sendGiftsToFriends();
//    void challengeFriends();
//    void inviteFriends();
    
    void checkSessionStatus();
    
    // Twitter Action Items
    void loginViaTwitter();
    void tweetMessage();
    void logoutFromTwitter();
    void checkIfUserFollowingMyTwitterID();
    
    // Sending Email
    void sendEmail();
    
    // Network Status
    void checkNetworkStatus();
    
    // Helper Methods
    void placeLabelInRow(cocos2d::CCLabelTTF* topLabel,
                         cocos2d::CCLabelTTF* labelToPlace);
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void menuPlay(CCObject* pSender);
    void menuOtion(CCObject * pSender);
    void menuHelp(CCObject * pSender);
    void menuHighScore(CCObject * pSender);
    void menuQuit(CCObject * pSender);
    void menuBGM(CCObject * pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(BeginScene);
    
    //--------------------------------------------
    // Facebook Delegate Methods
    virtual void fbSessionCallback(int responseCode, const char* responseMessage);
    virtual void fbUserDetailCallback(int responseCode, const char* responseMessage, EziFacebookUser *fbUser);
    virtual void fbMessageCallback(int responseCode, const char* responseMessage);
    virtual void fbPageLikeCallback(int responseCode, const char* responseMessage);
    
    virtual void fbUserPhotoCallback(const char *userPhotoPath);
    
    virtual void fbSendRequestCallback(int responseCode, const char* responseMessage, cocos2d::CCArray* friendsGotRequests);
    virtual void fbPostPhotoCallback(int responseCode, const char* responseMessage);
    
    virtual void fbIncomingRequestCallback(int responseCode, const char* responseMessage, int totalIncomingRequests);
    
    // EMail Delegate
    virtual void mailCallback(int responseCode);
    
    // Twitter Callback
    virtual void twitterCallback(int responseCode);
};

#endif /* defined(__GameFireworks__BeginScene__) */
