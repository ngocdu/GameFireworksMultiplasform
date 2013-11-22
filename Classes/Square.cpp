//
//  Square.cpp
//  GameFireworks
//
//  Created by NgocDu on 13/10/25.
//
//

#include "Square.h"
Square::Square()
{
    
}
Square::Square(bool notContain, bool w, bool e, bool n, bool s, int row, int column,
               bool statPoint, bool destination) {
    this->setNotContain(notContain);
    this->setWest(w);
    this->setEast(e);
    this->setNorth(n);
    this->setSouth(s);
    this->setRow(row);
    this->setColumn(column);
    this->setStartPoint(statPoint);
    this->setDestination(destination);
    this->setIsMoveTouch(false);
    this->setIsRemove(false);
    this->setRotateAble(true);
    this->setPoint(1);
    this->setCombo(0);
}
void Square::changeRotation(int columns) {
    this->setIsMoveTouch(true);
    bool w = this->getWest();
    bool n = this->getNorth();
    bool e = this->getEast();
    bool s = this->getSouth();
    this->setNorth(w);
    this->setEast(n);
    this->setSouth(e);
    this->setWest(s);

    if (this->getTag() == 1 + columns * (this->getRow() - 1) && this->getWest() == true) {
        this->setStartPoint(true);
        this->setColor(ccc3(255, 0, 0));
    } else this->setStartPoint(false);

    if (this->getTag() == this->getRow() * columns && this->getEast() == true) {
        this->setDestination(true);
    } else this->setDestination(false);
    
    CCRotateTo * rotate = CCRotateTo::create(0.0f, this->getRotation() + 90);
    this->runAction(rotate);
}
void Square::addCombo() {
    //time
    if (this->getCombo() == 4) {
        CCSprite * item = CCSprite::create("gold_bell.png");
        item->setPosition(CCPoint(this->getContentSize().width/2,
                                  this->getContentSize().height/2));
        item->setTag(10);
        this->addChild(item);
    }else if(this->getCombo() == 5) { // score
        CCSprite * item = CCSprite::create("gift01.png");
         item->setPosition(CCPoint(this->getContentSize().width/2,
                                   this->getContentSize().height/2));
        item->setTag(20);
        this->addChild(item);
    }else if(this->getCombo() == 6) { // score
        CCSprite * item = CCSprite::create("gift02.png");
        item->setPosition(CCPoint(this->getContentSize().width/2,
                                  this->getContentSize().height/2));
        item->setTag(30);
        this->addChild(item);
    }
}