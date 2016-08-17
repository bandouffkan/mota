//
//  StairFlight.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/27.
//
//

#include "StairFlight.hpp"
#include "GameScene.h"
#include "Attribute.hpp"
#include "GameScene.h"
bool StairFlight::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    upOrDown = 0;//0表示没点按钮，1表示点了上，-1表示点了下
    timingSucc = false;
    
    //黑底layout，大小与屏幕一样大
    stairFlight_lay = Layout::create();
    stairFlight_lay->setContentSize(Size(VISIBSIZE.width,VISIBSIZE.height));
    addChild(stairFlight_lay);
    stairFlight_lay->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    stairFlight_lay->setColor(Color3B::BLACK);
    stairFlight_lay->setBackGroundColorOpacity(100);
    stairFlight_lay->setPosition(Vec2(0,0));
    stairFlight_lay->setTouchEnabled(true);
    stairFlight_lay->addClickEventListener(CC_CALLBACK_1(StairFlight::onClickBlack_lay, this));
    auto lay_size = stairFlight_lay->getContentSize();
    
    Vec2 tmx_pos = GameScene::controlLayer->gamePos;
    auto box_sp = Sprite::create("stair/box.png");
    stairFlight_lay->addChild(box_sp);
    box_sp->setScale(3.3);
    box_sp->setPosition(tmx_pos);
    
    auto up_but = Button::create("stair/but.png");
    stairFlight_lay->addChild(up_but);
    up_but->setZoomScale(-0.1);
    up_but->setScale(1.2);
    up_but->setPosition(box_sp->getPosition()+Vec2(0,200));
    auto but_size = up_but->getContentSize();
    auto up_lab = Label::createWithSystemFont("上", "", 50);
    up_lab->setColor(Color3B(110,213,247));
    up_but->addChild(up_lab);
    up_lab->setPosition(but_size.width/2,but_size.height/2);
    
    auto down_but = Button::create("stair/but.png");
    stairFlight_lay->addChild(down_but);
    down_but->setZoomScale(-0.1);
    down_but->setScale(1.3);
    down_but->setPosition(box_sp->getPosition()+Vec2(0,-200));
    auto down_lab = Label::createWithSystemFont("下", "", 50);
    down_lab->setColor(Color3B(110,213,247));
    down_but->addChild(down_lab);
    down_lab->setPosition(but_size.width/2,but_size.height/2);
    
    up_but->addTouchEventListener(CC_CALLBACK_2(StairFlight::touchUp_but,this));
    down_but->addTouchEventListener(CC_CALLBACK_2(StairFlight::touchDown_but,this));
    
    stairNum = GameScene::controlLayer->stairNum;
    stair_lab = Label::createWithSystemFont(StringUtils::format("%d",stairNum), "MarkerFelt-Thin", 60);
    stair_lab->setColor(Color3B::BLACK);
    stairFlight_lay->addChild(stair_lab);
    stair_lab->setPosition(box_sp->getPosition());
    
    //进入楼层的按钮
    auto enter_but = Button::create("stair/but.png");
    stairFlight_lay->addChild(enter_but);
    enter_but->setPosition(box_sp->getPosition()+Vec2(240,-300));
    enter_but->addClickEventListener(CC_CALLBACK_1(StairFlight::clickEnter_but,this));
    auto que_lab = Label::createWithSystemFont("确定", "", 40);
    que_lab->setColor(Color3B(110,213,247));
    enter_but->addChild(que_lab);
    que_lab->setPosition(but_size.width/2,but_size.height/2);
    
    return true;
}
void StairFlight::show()
{
    stairNum = GameScene::controlLayer->stairNum;
    stair_lab->setString(StringUtils::format("%d",stairNum));
    this->setVisible(true);
//    int topfloor = Attribute::getInstance()->getTopFloor();    //得到已到达的最高楼层值
//    //int topfloor = 20;
//    for(int i=1;i<=topfloor;i++)
//    {
//    }
}
void StairFlight::touchUp_but(Ref* p,Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            upOrDown = 1;
            this->schedule(CC_SCHEDULE_SELECTOR(StairFlight::updateTiming),1);
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::ENDED:
            if(timingSucc==false)
            {
                upOrDown = 1;
                updateStairNumChange(0);
            }
            this->unschedule(CC_SCHEDULE_SELECTOR(StairFlight::updateTiming));
            this->unschedule(CC_SCHEDULE_SELECTOR(StairFlight::updateStairNumChange));
            timingSucc = false;
            upOrDown = 0;
            break;
        case Widget::TouchEventType::CANCELED:
            this->unschedule(CC_SCHEDULE_SELECTOR(StairFlight::updateTiming));
            this->unschedule(CC_SCHEDULE_SELECTOR(StairFlight::updateStairNumChange));
            timingSucc = false;
            upOrDown = 0;
            break;
        default:
            break;
    }
}
void StairFlight::touchDown_but(Ref* p,Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            upOrDown = -1;
            this->schedule(CC_SCHEDULE_SELECTOR(StairFlight::updateTiming),1.2);
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::ENDED:
            if(timingSucc==false)
            {
                upOrDown = -1;
                updateStairNumChange(0);
            }
            this->unschedule(CC_SCHEDULE_SELECTOR(StairFlight::updateTiming));
            this->unschedule(CC_SCHEDULE_SELECTOR(StairFlight::updateStairNumChange));
            timingSucc = false;
            upOrDown = 0;
            break;
        case Widget::TouchEventType::CANCELED:
            this->unschedule(CC_SCHEDULE_SELECTOR(StairFlight::updateTiming));
            this->unschedule(CC_SCHEDULE_SELECTOR(StairFlight::updateStairNumChange));
            timingSucc = false;
            upOrDown = 0;
            break;
        default:
            break;
    }
}
void StairFlight::updateStairNumChange(float dt)
{
    int topStair = Attribute::getInstance()->getTopFloor();
    int minStair = Attribute::getInstance()->getMinFloor();
    if(upOrDown==-1)//下
    {
        
        if((stairNum-1)<minStair)
            return;
        else
        {
            stairNum--;
            stair_lab->setString(StringUtils::format("%d",stairNum));
        }
    }
    else if(upOrDown==1)//上
    {
        
        if((stairNum+1)>topStair)
            return;
        else
        {
            stairNum++;
            stair_lab->setString(StringUtils::format("%d",stairNum));
        }
    }
}
void StairFlight::updateTiming(float dt)
{
    if(timingSucc==false)
    {
        timingSucc = true;
        this->schedule(CC_SCHEDULE_SELECTOR(StairFlight::updateStairNumChange),0.15,kRepeatForever,0.01);
    }
}
void StairFlight::clickEnter_but(Ref* p)
{
    GameScene::controlLayer->switchStair(stairNum);
}
void StairFlight::onClickBlack_lay(Ref* p)
{
    this->setVisible(false);
}