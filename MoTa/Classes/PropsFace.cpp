//
//  PropsFace.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/24.
//
//

#include "PropsFace.hpp"
#include "GameScene.h"

bool PropsFace::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto bg_sp = Sprite::create("props/propBg.png");
    addChild(bg_sp);
    bg_sp->setAnchorPoint(Vec2(0,1));
    bg_sp->setPosition(0,0);
    face_size = bg_sp->getContentSize();
    
    props = Props::getInstance();
    
    //钥匙前的图标
    auto key1_sp = Sprite::create("props/key1.png");
    auto key2_sp = Sprite::create("props/key2.png");
    auto key3_sp = Sprite::create("props/key3.png");
    addChild(key1_sp);
    addChild(key2_sp);
    addChild(key3_sp);
    key1_sp->setScale(2.7);
    key2_sp->setScale(2.7);
    key3_sp->setScale(2.7);
    key1_sp->setPosition(63,-55);
    key2_sp->setPosition(63,-145);
    key3_sp->setPosition(63,-232);
    //钥匙数量
    key1Num_lab = Label::createWithSystemFont("","Verdana-BoldItalic",60);
    key2Num_lab = Label::createWithSystemFont("","Verdana-BoldItalic",60);
    key3Num_lab = Label::createWithSystemFont("","Verdana-BoldItalic",60);
    key1Num_lab->setPosition(200,key1_sp->getPositionY());
    key2Num_lab->setPosition(200,key2_sp->getPositionY());
    key3Num_lab->setPosition(200,key3_sp->getPositionY());
//    key1Num_lab->setString(Value(props->getKey1Num()).asString());
//    key2Num_lab->setString(Value(props->getKey2Num()).asString());
//    key3Num_lab->setString(Value(props->getKey3Num()).asString());
    addChild(key1Num_lab);
    addChild(key2Num_lab);
    addChild(key3Num_lab);
    
    //有4种使用道具
    but_foeData = Button::create("foeBook.png");
    but_flight = Button::create("props/flight.png");
    addChild(but_foeData);
    addChild(but_flight);
    but_foeData->setScale(3);
    but_flight->setScale(3);
    but_foeData->setPosition(Vec2(70,-400));
    but_flight->setPosition(Vec2(230,-400));
    but_foeData->addClickEventListener(CC_CALLBACK_1(ControlLayer::onClickBut_foeData,(ControlLayer*)GameScene::controlLayer));
    but_flight->addClickEventListener(CC_CALLBACK_1(ControlLayer::onClickBut_flight,(ControlLayer*)GameScene::controlLayer));
    
    speDoor_but = Button::create("speDoor.png");
    addChild(speDoor_but);
    speDoor_but->setScale(3);
    speDoor_but->setPosition(Vec2(70,-570));
    speDoor_but->addClickEventListener(CC_CALLBACK_1(ControlLayer::onClickBut_speDoor,(ControlLayer*)GameScene::controlLayer));
    
    //神圣之证
    holy_but = Button::create("dagger.png");
    addChild(holy_but);
    holy_but->setScale(3);
    holy_but->setPosition(Vec2(230,-570));
    holy_but->addClickEventListener(CC_CALLBACK_1(ControlLayer::onClickBut_holy,(ControlLayer*)GameScene::controlLayer));
    
    updateByMap();
    
    return true;
}
void PropsFace::updateByMap()
{
    key1Num_lab->setString(Value(props->getKey1Num()).asString());
    key2Num_lab->setString(Value(props->getKey2Num()).asString());
    key3Num_lab->setString(Value(props->getKey3Num()).asString());
    
    if(props->getPropByGid(e_manual) >= 1)
        but_foeData->setVisible(true);
    else
        but_foeData->setVisible(false);
    if(props->getPropByGid(e_flightDown) >= 1)
        but_flight->setVisible(true);
    else
        but_flight->setVisible(false);
    if(props->getPropByGid(e_speDoor) >= 1)
        speDoor_but->setVisible(true);
    else
        speDoor_but->setVisible(false);
    if(props->getPropByGid(e_dagger) >= 1)
        holy_but->setVisible(true);
    else
        holy_but->setVisible(false);
}
void PropsFace::redOneKeyNumByVar(E_Door doorVar)
{
    props->redOneKeyNumByVar(doorVar);
    switch (doorVar) {
        case e_door1:
            key1Num_lab->setString(Value(props->getKey1Num()).asString());
            break;
        case e_door2:
            key2Num_lab->setString(Value(props->getKey2Num()).asString());
            break;
        case e_door3:
            key3Num_lab->setString(Value(props->getKey3Num()).asString());
            break;
        default:
            break;
    }
}
void PropsFace::addHeroKey1(int num)
{
    props->props_map["key1Num"] = props->props_map["key1Num"].asInt() + num;
    key1Num_lab->setString(StringUtils::format("%d",props->getKey1Num()));
}
void PropsFace::addHeroKey2(int num)
{
    props->props_map["key2Num"] = props->props_map["key2Num"].asInt() + num;
    key2Num_lab->setString(StringUtils::format("%d",props->getKey2Num()));
}
void PropsFace::addHeroKey3(int num)
{
    props->props_map["key3Num"] = props->props_map["key3Num"].asInt() + num;
    key3Num_lab->setString(StringUtils::format("%d",props->getKey3Num()));
}
void PropsFace::getSpDoor()
{
    speDoor_but->setVisible(true);
    props->setPropByGid(e_speDoor,5);
}
void PropsFace::getHoly()
{
    holy_but->setVisible(true);
    props->setPropByGid(e_dagger, 5);
}
void PropsFace::onClickBut_foeData(Ref* p)   //手册，查看怪物信息的按钮点击
{
    //GameScene::controlLayer->showFoeData();
}
void PropsFace::onClickBut_flight(Ref* p)     //楼层飞行器
{
}