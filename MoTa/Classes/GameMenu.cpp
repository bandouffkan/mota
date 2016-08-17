//
//  GameMenu.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/24.
//
//

#include "GameMenu.hpp"
#include "GameScene.h"
#include "HomeScene.hpp"
#include "ShopFace.hpp"
bool GameMenu::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto bg_sp = Sprite::create("menu/menuBg.png");
    addChild(bg_sp);
    bg_sp->setPosition(0,0);
    
    continue_but = Button::create("menu/close.png");
    save_but = Button::create("menu/menuOp.png");
    read_but = Button::create("menu/menuOp.png");
    retHome_but = Button::create("menu/menuOp.png");
    shop_but = Button::create("menu/menuOp.png");
    addChild(continue_but);
    addChild(save_but);
    addChild(read_but);
    addChild(retHome_but);
    addChild(shop_but);
    continue_but->setPosition(Vec2(395,270));
    save_but->setPosition(Vec2(-265,160));
    read_but->setPosition(Vec2(190,160));
    retHome_but->setPosition(Vec2(-265,-160));
    shop_but->setPosition(Vec2(190,-160));
    
    continue_but->addClickEventListener(CC_CALLBACK_1(GameMenu::onClickBut_continue,this));
    save_but->addClickEventListener(CC_CALLBACK_1(GameMenu::onClickBut_save,this));
    read_but->addClickEventListener(CC_CALLBACK_1(GameMenu::onClickBut_read,this));
    retHome_but->addClickEventListener(CC_CALLBACK_1(GameMenu::onClickBut_retHome,this));
    shop_but->addClickEventListener(CC_CALLBACK_1(GameMenu::onClickBut_shop,this));
    
    //显示的lab
    auto save_lab = Label::createWithSystemFont("保存游戏","" , 40);
    auto read_lab = Label::createWithSystemFont("读取游戏","" , 40);
    auto retHome_lab = Label::createWithSystemFont("返回主页","" , 40);
    auto shop_lab = Label::createWithSystemFont("商店","" , 40);
    auto but_size = save_but->getContentSize();
    save_but->addChild(save_lab);
    read_but->addChild(read_lab);
    retHome_but->addChild(retHome_lab);
    shop_but->addChild(shop_lab);
    save_lab->setColor(Color3B(188,252,195));
    read_lab->setColor(Color3B(188,252,195));
    retHome_lab->setColor(Color3B(188,252,195));
    shop_lab->setColor(Color3B(188,252,195));
    save_lab->setPosition(but_size.width/2,but_size.height/2);
    read_lab->setPosition(but_size.width/2,but_size.height/2);
    retHome_lab->setPosition(but_size.width/2,but_size.height/2);
    shop_lab->setPosition(but_size.width/2,but_size.height/2);
    
    return true;
}
void GameMenu::onClickBut_continue(Ref* p)
{
    this->setVisible(false);
}
void GameMenu::onClickBut_save(Ref* p)
{
    GameScene::controlLayer->arcSaveFace->setVisible(true);
    this->setVisible(false);
    auto scale = ScaleTo::create(0.2, 1);
    auto easeInOut = EaseBackOut::create(scale);
    GameScene::controlLayer->arcSaveFace->setScale(0.65);
    GameScene::controlLayer->arcSaveFace->runAction(easeInOut);
}
void GameMenu::onClickBut_read(Ref* p)
{
    GameScene::controlLayer->arcReadFace->setVisible(true);
    this->setVisible(false);
    auto scale = ScaleTo::create(0.2, 1);
    auto easeInOut = EaseBackOut::create(scale);
    GameScene::controlLayer->arcReadFace->setScale(0.65);
    GameScene::controlLayer->arcReadFace->runAction(easeInOut);
}
void GameMenu::onClickBut_retHome(Ref* p)
{
    Director::getInstance()->replaceScene(HomeScene::createScene());
}
void GameMenu::onClickBut_shop(Ref* p)
{
    if(!GameScene::controlLayer->shopFace->isVisible())
    {
        GameScene::controlLayer->menu->setVisible(false);
        GameScene::controlLayer->shopFace->setVisible(true);
    }
    else
        GameScene::controlLayer->shopFace->setVisible(false);
}