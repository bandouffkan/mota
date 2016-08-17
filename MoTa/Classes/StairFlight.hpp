//
//  StairFlight.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/27.
//
//

#ifndef StairFlight_hpp
#define StairFlight_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

class StairFlight : public Node
{
public:
    bool init();
    CREATE_FUNC(StairFlight);
    void show();
    void onClickBlack_lay(Ref* p);
    void touchUp_but(Ref* p,Widget::TouchEventType type);
    void touchDown_but(Ref* p,Widget::TouchEventType type);
    void clickEnter_but(Ref* p);
    void updateStairNumChange(float dt);
    void updateTiming(float dt);//计时
    
    Layout* stairFlight_lay;
    int stairNum;
    Label* stair_lab;
    short upOrDown;//0表示没点按钮，1表示点了上，-1表示点了下
    bool timingSucc;//按键计时成功
};

#endif /* StairFlight_hpp */
