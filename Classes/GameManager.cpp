#include "GameManager.h" 

GameManager* GameManager::m_mySingleton = NULL;

GameManager::GameManager() {
    this->_level = 0 ;
    this->_numberRocket = 0;
}
GameManager* GameManager::sharedGameManager() {
    if(NULL == m_mySingleton) {
        m_mySingleton = new GameManager();
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        m_mySingleton->sharedGameManager()->setSCALE_N_X(s.width / 1024.0f);
        m_mySingleton->sharedGameManager()->setSCALE_N_Y(s.height / 768.0f);
    }
    return m_mySingleton;
}
