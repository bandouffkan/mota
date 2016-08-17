//
//  HomeLayer.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/29.
//
//

#include "HomeScene.hpp"
#include "GameConstants.h"
#include "GameScene.h"
#include "ArchiveFace.hpp"
#include "Audio.hpp"
#import "GameCenterTools.h"
#include "ReadPlist.hpp"
#include "AnimationManager.hpp"
Scene* HomeScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HomeScene::create();
    
    scene->addChild(layer);

    return scene;
}

bool HomeScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto bg_sp = Sprite::create("HomeScene/bg.png");
    addChild(bg_sp);
    bg_sp->setPosition(VISIBSIZE.width/2,VISIBSIZE.height/2);
    
    auto title_sp = Sprite::create("HomeScene/title.png");
    addChild(title_sp);
    title_sp->setPosition(VISIBSIZE.width*0.5,VISIBSIZE.height*0.85);
    
    auto begin_but = Button::create("HomeScene/but1.png","HomeScene/but1_2.png");
    auto read_but = Button::create("HomeScene/but2.png","HomeScene/but2_2.png");
    auto set_but = Button::create("HomeScene/but1.png","HomeScene/but1_2.png");
    auto about_but = Button::create("HomeScene/but2.png","HomeScene/but2_2.png");
//    begin_but->setZoomScale(-0.1);
//    read_but->setZoomScale(-0.1);
//    set_but->setZoomScale(-0.1);
//    about_but->setZoomScale(-0.1);
    addChild(begin_but);
    addChild(read_but);
    addChild(set_but);
    addChild(about_but);
    begin_but->setPosition(Vec2(VISIBSIZE.width*0.28,VISIBSIZE.height*0.55));
    read_but->setPosition(Vec2(VISIBSIZE.width*0.72,VISIBSIZE.height*0.55));
    set_but->setPosition(Vec2(VISIBSIZE.width*0.28,VISIBSIZE.height*0.3));
    about_but->setPosition(Vec2(VISIBSIZE.width*0.72,VISIBSIZE.height*0.3));
    begin_but->addClickEventListener(CC_CALLBACK_1(HomeScene::onClickBut_begin,this));
    read_but->addClickEventListener(CC_CALLBACK_1(HomeScene::onClickBut_read,this));
    set_but->addClickEventListener(CC_CALLBACK_1(HomeScene::onClickBut_set,this));
    about_but->addClickEventListener(CC_CALLBACK_1(HomeScene::onClickBut_about,this));
    
    //按钮的文字
    auto begin_sp = Sprite::create("HomeScene/begin.png");
    auto read_sp = Sprite::create("HomeScene/read.png");
    auto set_sp = Sprite::create("HomeScene/set.png");
    auto about_sp = Sprite::create("HomeScene/rank.png");
    addChild(begin_sp);
    addChild(read_sp);
    addChild(set_sp);
    addChild(about_sp);
    begin_sp->setPosition(begin_but->getPosition());
    read_sp->setPosition(read_but->getPosition());
    set_sp->setPosition(set_but->getPosition());
    about_sp->setPosition(about_but->getPosition());
    
    
    //声音的界面
    voiceBg_lay = Layout::create();
    voiceBg_lay->setBackGroundImage("HomeScene/yinxiao.png");
    addChild(voiceBg_lay,2);
    auto voice_size = voiceBg_lay->getBackGroundImageTextureSize();
    voiceBg_lay->setContentSize(voice_size);
    voiceBg_lay->setAnchorPoint(Vec2(0.5,0.5));
    voiceBg_lay->setPosition(Vec2(VISIBSIZE.width/2,VISIBSIZE.height/2));
    voiceBg_lay->setVisible(false);
    
    auto kaiSound_but = Button::create("HomeScene/kai.png");
    auto guanSound_but = Button::create("HomeScene/guan.png");
    voiceBg_lay->addChild(kaiSound_but);
    voiceBg_lay->addChild(guanSound_but);
    kaiSound_but->setPosition(Vec2(178,326));
    guanSound_but->setPosition(Vec2(708,326));
    kaiSound_but->setTag(1);
    guanSound_but->setTag(2);
    kaiSound_but->addClickEventListener(CC_CALLBACK_1(HomeScene::onClickBut_setSound,this));
    guanSound_but->addClickEventListener(CC_CALLBACK_1(HomeScene::onClickBut_setSound,this));
    
    auto kaiBgm_but = Button::create("HomeScene/kai.png");
    auto guanBgm_but = Button::create("HomeScene/guan.png");
    voiceBg_lay->addChild(kaiBgm_but);
    voiceBg_lay->addChild(guanBgm_but);
    kaiBgm_but->setPosition(Vec2(178,115));
    guanBgm_but->setPosition(Vec2(708,115));
    kaiBgm_but->setTag(1);
    guanBgm_but->setTag(2);
    kaiBgm_but->addClickEventListener(CC_CALLBACK_1(HomeScene::onClickBut_setBGM,this));
    guanBgm_but->addClickEventListener(CC_CALLBACK_1(HomeScene::onClickBut_setBGM,this));
    
    gouSound = Sprite::create("HomeScene/gou.png");
    gouBGM = Sprite::create("HomeScene/gou.png");
    voiceBg_lay->addChild(gouSound);
    voiceBg_lay->addChild(gouBGM);
    if(Audio::getInstance()->isOpenSound())
    {
        gouSound->setPosition(kaiSound_but->getPosition());
        isSoundOpen = true;
    }
    else
    {
        gouSound->setPosition(guanSound_but->getPosition());
        isSoundOpen = false;
    }
    if(Audio::getInstance()->isOpenBGM())
    {
        gouBGM->setPosition(kaiBgm_but->getPosition());
        isBGMOpen = true;
    }
    else
    {
        gouBGM->setPosition(guanBgm_but->getPosition());
        isBGMOpen = false;
    }
    //设置音效
    Audio::getInstance()->setSoundType(isSoundOpen);
    Audio::getInstance()->setBGMType(isBGMOpen);
    
    ReadPlist::getInstance();
    AnimationManager::getInstance();
    
    [[GameCenterTools sharedGameKitHelper] authenticateLocalUser];
    
    return true;
}
void HomeScene::onClickBut_begin(Ref* p)
{
    Archive::getInstance()->release();   //重新开始，要消除记录
    Props::getInstance()->release();
    Attribute::getInstance()->release();
    GameScene::controlLayer = NULL;
    Director::getInstance()->replaceScene(GameScene::createScene());
}
void HomeScene::onClickBut_read(Ref* p)
{
    auto readFace = ArchiveFace::create(ArchiveFace::e_read);
    addChild(readFace);
    readFace->setPosition(VISIBSIZE.width/2,VISIBSIZE.height/2);
    auto scale = ScaleTo::create(0.2, 1);
    auto easeInOut = EaseBackOut::create(scale);
    readFace->setScale(0.65);
    readFace->runAction(easeInOut);
}
void HomeScene::onClickBut_set(Ref* p)
{
    auto black_lay = Layout::create();
    black_lay->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    black_lay->setBackGroundColor(Color3B::BLACK);
    black_lay->setBackGroundColorOpacity(100);//255
    addChild(black_lay);
    black_lay->setContentSize(VISIBSIZE);
    black_lay->setPosition(Vec2(0,0));
    black_lay->setTouchEnabled(true);
    
    voiceBg_lay->setVisible(true);
    voiceBg_lay->setScale(0.65);
    auto scale = ScaleTo::create(0.2, 1);
    auto easeInOut = EaseBackOut::create(scale);
    voiceBg_lay->runAction(easeInOut);
    
    black_lay->addClickEventListener([=](Ref* p){
        voiceBg_lay->setVisible(false);
        black_lay->removeFromParent();
    });
    
    //设置点击界面不会消失
    voiceBg_lay->setTouchEnabled(true);
    voiceBg_lay->addClickEventListener([=](Ref* p){
        
    });
}
void HomeScene::onClickBut_about(Ref* p)
{
    [[GameCenterTools sharedGameKitHelper] authenticateLocalUser];
    [[GameCenterTools sharedGameKitHelper] showLeaderboard];
}
void HomeScene::onClickBut_setSound(Ref* p)
{
    Button* but = (Button*)(p);
    gouSound->setPosition(but->getPosition());
    gouSound->setScale(0.1);
    auto scale = ScaleTo::create(0.4, 1);
    auto easeInOut = EaseElasticOut::create(scale);
    easeInOut->setTag(1);
    gouSound->runAction(easeInOut);
    if(but->getTag()==1)
        Audio::getInstance()->setSoundType(true);
    else if(but->getTag()==2)
        Audio::getInstance()->setSoundType(false);
}
void HomeScene::onClickBut_setBGM(Ref* p)
{
    Button* but = (Button*)(p);
    gouBGM->setPosition(but->getPosition());
    gouBGM->setScale(0.1);
    auto scale = ScaleTo::create(0.4, 1);
    auto easeInOut = EaseElasticOut::create(scale);
    easeInOut->setTag(1);
    gouBGM->runAction(easeInOut);
    if(but->getTag()==1)
        Audio::getInstance()->setBGMType(true);
    else if(but->getTag()==2)
        Audio::getInstance()->setBGMType(false);
}
