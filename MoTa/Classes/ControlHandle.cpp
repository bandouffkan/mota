//
//  ControlHandle.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/23.
//
//

#include "ControlHandle.hpp"
#include "cocostudio/CocoStudio.h"
#include "GameScene.h"
#include "ControlLayer.hpp"
bool ControlHandle::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    touchDir = e_stand;
    
    auto cotrolNode_csb = CSLoader::createNode("Control/ControlHandle.csb");
    addChild(cotrolNode_csb);
    control_Sp = cotrolNode_csb->getChildByName<Sprite*>("control");
    up_but = control_Sp->getChildByName<Button*>("up_But");
    down_but = control_Sp->getChildByName<Button*>("down_But");
    left_but = control_Sp->getChildByName<Button*>("left_But");
    right_but = control_Sp->getChildByName<Button*>("right_But");
    
    up_but->setTag(e_up);
    down_but->setTag(e_down);
    left_but->setTag(e_left);
    right_but->setTag(e_right);
    up_but->addTouchEventListener(CC_CALLBACK_2(ControlHandle::onTouchButMove, this));
    down_but->addTouchEventListener(CC_CALLBACK_2(ControlHandle::onTouchButMove, this));
    left_but->addTouchEventListener(CC_CALLBACK_2(ControlHandle::onTouchButMove, this));
    right_but->addTouchEventListener(CC_CALLBACK_2(ControlHandle::onTouchButMove, this));
    
    return true;
}

void ControlHandle::onTouchButMove(Ref *pSender, ui::Widget::TouchEventType type)
{
    if(GameScene::controlLayer->heroIsDie)
        return;
    Node *but = static_cast<Node*>(pSender);
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            if(touchDir != e_stand)  //防止多按键
                return;
            touchDir = (E_HeroDir)but->getTag();
            changeControlPic((E_HeroDir)but->getTag());
            GameScene::controlLayer->gameLayer->heroMove( (E_HeroDir)but->getTag() );
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::ENDED:
            touchDir = e_stand;
            changeControlPic(e_stand);
            break;
        case Widget::TouchEventType::CANCELED:
            touchDir = e_stand;
            changeControlPic(e_stand);
            break;
        default:
            touchDir = e_stand;
            break;
    }
}
void ControlHandle::changeControlPic(E_HeroDir dir)
{
    switch (dir)
    {
        case e_down:
            control_Sp->setTexture("Control/down_Cont.png");
            break;
        case e_left:
            control_Sp->setTexture("Control/left_Cont.png");
            break;
        case e_right:
            control_Sp->setTexture("Control/right_Cont.png");
            break;
        case e_up:
            control_Sp->setTexture("Control/up_Cont.png");
            break;
        case e_stand:
            control_Sp->setTexture("Control/normal_Cont.png");
            break;
        default:
            control_Sp->setTexture("Control/normal_Cont.png");
            break;
    }
}