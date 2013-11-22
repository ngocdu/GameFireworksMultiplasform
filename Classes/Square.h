//
//  Square.h
//  GameFireworks
//
//  Created by NgocDu on 13/10/25.
//
//

#ifndef GameFireworks_Square_h
#define GameFireworks_Square_h
#include "cocos2d.h"
using namespace cocos2d;
class Square : public CCSprite
{
public:
    Square();
    Square(bool notContain, bool w, bool e, bool n, bool s, int row, int column,
           bool statPoint, bool destination);
    void changeRotation(int columnsTable);
    void addCombo();
private:
    CC_SYNTHESIZE(bool, _notContain, NotContain);
    CC_SYNTHESIZE(bool, _east, East);
    CC_SYNTHESIZE(bool, _west, West);
    CC_SYNTHESIZE(bool, _south, South);
    CC_SYNTHESIZE(bool, _north, North);
    CC_SYNTHESIZE(bool, _startPoint, StartPoint);
    CC_SYNTHESIZE(bool, _destination, Destination);
    CC_SYNTHESIZE(bool, _isMoveTouch, IsMoveTouch);
    CC_SYNTHESIZE(int, _row, Row);
    CC_SYNTHESIZE(int, _column, Column);
    CC_SYNTHESIZE(bool, _rotateAble, RotateAble);
    CC_SYNTHESIZE(int, _life, Life);
    CC_SYNTHESIZE(bool, _isRemove, IsRemove);
    CC_SYNTHESIZE(int, _combo, Combo);
    CC_SYNTHESIZE(int, _point, Point);
};
#endif
