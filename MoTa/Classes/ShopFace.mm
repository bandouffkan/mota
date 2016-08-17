//
//  ShopFace.cpp
//  MoTa
//
//  Created by xcode31 on 16/8/5.
//
//

#include "ShopFace.hpp"
#include "GameScene.h"
#import "InAppRageIAPHelper.h"
bool ShopFace::isResulted = false;
int ShopFace::buyResults = 0;
bool ShopFace::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    //黑底layout，大小与屏幕一样大
    auto black_lay = Layout::create();
    addChild(black_lay);
    cocos2d::Size black_size = GameScene::controlLayer->gameLayer->tmxSize;
    black_lay->setContentSize(black_size);
    black_lay->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    black_lay->setColor(Color3B::BLACK);
    black_lay->setBackGroundColorOpacity(100);
    //Vec2 pos = GameScene::controlLayer->gameLayer->getPosition();
    black_lay->setPosition(Vec2(0-black_size.width/2,0-black_size.height/2));
    black_lay->setTouchEnabled(true);
    black_lay->addClickEventListener(CC_CALLBACK_1(ShopFace::onClickBlack_lay, this));
    auto lay_size = black_lay->getContentSize();
    
    auto bg_sp = ImageView::create("shop/bg.png");
    addChild(bg_sp);
    bg_sp->setTouchEnabled(true);
    bg_sp->setPosition(Vec2(0,0));
    auto bg_size = bg_sp->getContentSize();
    
    //商品1
    auto goods1_sp = Sprite::create("shop/goods.png");
    bg_sp->addChild(goods1_sp);
    goods1_sp->setPosition(bg_size.width*0.2,bg_size.height*0.75);
    auto sp_size = goods1_sp->getContentSize();
    
    auto goods1_lab = Label::createWithSystemFont("金币1200", "", 40);
    goods1_sp->addChild(goods1_lab);
    goods1_lab->setColor(Color3B(213,237,9));
    goods1_lab->setPosition(sp_size.width/2,sp_size.height/2);
    
    //商品2
    auto goods2_sp = Sprite::create("shop/goods.png");
    bg_sp->addChild(goods2_sp);
    goods2_sp->setPosition(bg_size.width*0.2,bg_size.height*0.25);
    
    auto goods2_lab = Label::createWithSystemFont("消除广告", "", 40);
    goods2_sp->addChild(goods2_lab);
    goods2_lab->setColor(Color3B(213,237,9));
    goods2_lab->setPosition(sp_size.width/2,sp_size.height/2);
    
    //购买1
    auto buy1_but = Button::create("shop/but.png");
    bg_sp->addChild(buy1_but);
    buy1_but->setPosition(Vec2(bg_size.width*0.7,bg_size.height*0.75));
    auto but_size = buy1_but->getContentSize();
    auto but1_lab = Label::createWithSystemFont("购买", "", 40);
    but1_lab->setColor(Color3B(213,237,9));
    buy1_but->addChild(but1_lab);
    but1_lab->setPosition(but_size.width/2,but_size.height/2);
    buy1_but->addClickEventListener(CC_CALLBACK_1(ShopFace::onClickBut_buy1,this));
    
    //购买2
    auto buy2_but = Button::create("shop/but.png");
    bg_sp->addChild(buy2_but);
    buy2_but->setPosition(Vec2(bg_size.width*0.7,bg_size.height*0.25));
    auto but2_lab = Label::createWithSystemFont("购买", "", 40);
    but2_lab->setColor(Color3B(213,237,9));
    buy2_but->addChild(but2_lab);
    but2_lab->setPosition(but_size.width/2,but_size.height/2);
    buy2_but->addClickEventListener(CC_CALLBACK_1(ShopFace::onClickBut_buy2,this));
    if(UserDefault::getInstance()->getBoolForKey("adsNo",false)==false)
    {
        buy2_but->setVisible(false);
    }
        
    return true;
}
void ShopFace::onClickBlack_lay(Ref* p)
{
    this->setVisible(false);
}
void ShopFace::onClickBut_buy1(Ref* p)
{
    NSArray* array = [[InAppRageIAPHelper sharedHelper] productIdentifiers];
    [[InAppRageIAPHelper sharedHelper] buyProductIdentifier:[array objectAtIndex:0]];
    schedule(CC_SCHEDULE_SELECTOR(ShopFace::judgeResponseFromBuy1));
}
void ShopFace::onClickBut_buy2(Ref* p)
{
    if(UserDefault::getInstance()->getBoolForKey("adsNo",false)==false)
    {
        NSArray* array = [[InAppRageIAPHelper sharedHelper] productIdentifiers];
        [[InAppRageIAPHelper sharedHelper] buyProductIdentifier:[array objectAtIndex:1]];
        schedule(CC_SCHEDULE_SELECTOR(ShopFace::judgeResponseFromBuy1));
    }
}
void ShopFace::judgeResponseFromBuy1(float dt)
{
    if(isResulted)
    {
        unschedule(CC_SCHEDULE_SELECTOR(ShopFace::judgeResponseFromBuy1));
        isResulted = false;
        switch (buyResults)
        {
            case 0:
                break;
            case 1:
                break;
            case 2:
            {
                GameScene::controlLayer->addGold(1200);
            }
                break;
            default:
                break;
        }
        buyResults = 0;
    }
}
void ShopFace::judgeResponseFromBuy2(float dt)
{
    if(isResulted)
    {
        unschedule(CC_SCHEDULE_SELECTOR(ShopFace::judgeResponseFromBuy1));
        isResulted = false;
        switch (buyResults)
        {
            case 0:
                break;
            case 1:
                break;
            case 2:
            {
                UserDefault::getInstance()->setBoolForKey("adsNo",true); //广告
                UserDefault::getInstance()->flush();
            }
                break;
            default:
                break;
        }
        buyResults = 0;
    }
}