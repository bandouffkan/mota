//
//  ControlHandle.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/23.
//
//

#ifndef ControlHandle_hpp
#define ControlHandle_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameConstants.h"
USING_NS_CC;
using namespace ui;

class ControlHandle : public Node
{
public:
    bool init();
    CREATE_FUNC(ControlHandle);
    void onTouchButMove(Ref *pSender, ui::Widget::TouchEventType type);    //移动按键的点击事件
    void changeControlPic(E_HeroDir dir);//改变控制器的图片
    
    E_HeroDir touchDir;//方向按键的属性
    
    Sprite* control_Sp; //显示控制图的精灵
    Button* up_but;
    Button* down_but;
    Button* left_but;
    Button* right_but;
};

#endif /* ControlHandle_hpp */
