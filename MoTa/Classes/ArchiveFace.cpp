//
//  ArchiveFace.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/24.
//
//

#include "ArchiveFace.hpp"
#include "Attribute.hpp"
#include "Archive.hpp"
#include "GameScene.h"
#include "GameConstants.h"
#include "Props.hpp"
ArchiveFace* ArchiveFace::create(E_Type type_e)
{
    ArchiveFace *pRet = new(std::nothrow) ArchiveFace();
    if (pRet && pRet->init(type_e))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool ArchiveFace::init(E_Type type_e)
{
    if(!Node::init())
    {
        return false;
    }
    
    archive = Archive::getInstance();
    
    if(type_e == e_save)
    {
        //保存存档的
        saveBg_lay = Layout::create();
        saveBg_lay->setBackGroundImage("menu/cundan1.png");
        saveBg_lay->setTouchEnabled(true);
        addChild(saveBg_lay);
        saveBg_lay->setContentSize(saveBg_lay->getBackGroundImageTextureSize());
        saveBg_lay->setAnchorPoint(Vec2(0.5,0.5));
        saveBg_lay->setPosition(Vec2(0,0));
        
        save1_but = Button::create("menu/savebu.png");
        save2_but = Button::create("menu/savebu.png");
        save3_but = Button::create("menu/savebu.png");
        save4_but = Button::create("menu/savebu.png");
        auto close_but = Button::create("menu/xx.png");
        
        saveBg_lay->addChild(save1_but);
        saveBg_lay->addChild(save2_but);
        saveBg_lay->addChild(save3_but);
        saveBg_lay->addChild(save4_but);
        saveBg_lay->addChild(close_but);
        
        auto bg_size = saveBg_lay->getContentSize();
        save1_but->setPosition(Vec2(bg_size.width*0.3,bg_size.height*0.3));
        save2_but->setPosition(Vec2(bg_size.width*0.7,bg_size.height*0.3));
        save3_but->setPosition(Vec2(bg_size.width*0.3,bg_size.height*0.7));
        save4_but->setPosition(Vec2(bg_size.width*0.7,bg_size.height*0.7));
        close_but->setPosition(Vec2(770,470));
        
        save1_but->setTag(1);
        save2_but->setTag(2);
        save3_but->setTag(3);
        save4_but->setTag(4);
        
        save1_but->addClickEventListener(CC_CALLBACK_1(ArchiveFace::onClickBut_saveGame,this));
        save2_but->addClickEventListener(CC_CALLBACK_1(ArchiveFace::onClickBut_saveGame,this));
        save3_but->addClickEventListener(CC_CALLBACK_1(ArchiveFace::onClickBut_saveGame,this));
        save4_but->addClickEventListener(CC_CALLBACK_1(ArchiveFace::onClickBut_saveGame,this));
        close_but->addClickEventListener([=](Ref* p){
            this->setVisible(false);
        });
        //存档的文字
        auto arc1_lab = Label::createWithSystemFont("保存存档3", "", 35);
        auto arc2_lab = Label::createWithSystemFont("保存存档4", "", 35);
        auto arc3_lab = Label::createWithSystemFont("保存存档1", "", 35);
        auto arc4_lab = Label::createWithSystemFont("保存存档2", "", 35);
        arc1_lab->setColor(Color3B(223,255,147));
        arc2_lab->setColor(Color3B(223,255,147));
        arc3_lab->setColor(Color3B(223,255,147));
        arc4_lab->setColor(Color3B(223,255,147));
        save1_but->addChild(arc1_lab);
        save2_but->addChild(arc2_lab);
        save3_but->addChild(arc3_lab);
        save4_but->addChild(arc4_lab);
        auto but_size = save1_but->getContentSize();
        arc1_lab->setPosition(but_size.width/2,but_size.height/2);
        arc2_lab->setPosition(but_size.width/2,but_size.height/2);
        arc3_lab->setPosition(but_size.width/2,but_size.height/2);
        arc4_lab->setPosition(but_size.width/2,but_size.height/2);
    }
    else if(type_e == e_read)
    {
        //读取存档的
        readBg_lay = Layout::create();
        readBg_lay->setBackGroundImage("menu/cundan1.png");
        readBg_lay->setTouchEnabled(true);
        addChild(readBg_lay);
        readBg_lay->setContentSize(readBg_lay->getBackGroundImageTextureSize());
        readBg_lay->setAnchorPoint(Vec2(0.5,0.5));
        readBg_lay->setPosition(Vec2(0,0));
        
        read1_but = Button::create("menu/savebu.png");
        read2_but = Button::create("menu/savebu.png");
        read3_but = Button::create("menu/savebu.png");
        read4_but = Button::create("menu/savebu.png");
        auto close_but = Button::create("menu/xx.png");
        
        readBg_lay->addChild(read1_but);
        readBg_lay->addChild(read2_but);
        readBg_lay->addChild(read3_but);
        readBg_lay->addChild(read4_but);
        readBg_lay->addChild(close_but);
        
        auto readBg_size = readBg_lay->getContentSize();
        read1_but->setPosition(Vec2(readBg_size.width*0.25,readBg_size.height*0.3));
        read2_but->setPosition(Vec2(readBg_size.width*0.75,readBg_size.height*0.3));
        read3_but->setPosition(Vec2(readBg_size.width*0.25,readBg_size.height*0.7));
        read4_but->setPosition(Vec2(readBg_size.width*0.75,readBg_size.height*0.7));
        close_but->setPosition(Vec2(770,470));
        
        read1_but->addClickEventListener(CC_CALLBACK_1(ArchiveFace::onClickBut_readGame,this));
        read2_but->addClickEventListener(CC_CALLBACK_1(ArchiveFace::onClickBut_readGame,this));
        read3_but->addClickEventListener(CC_CALLBACK_1(ArchiveFace::onClickBut_readGame,this));
        read4_but->addClickEventListener(CC_CALLBACK_1(ArchiveFace::onClickBut_readGame,this));
        close_but->addClickEventListener([=](Ref* p){
            this->setVisible(false);
        });
        
        read1_but->setTag(1);
        read2_but->setTag(2);
        read3_but->setTag(3);
        read4_but->setTag(4);
        //存档的文字
        auto arc1_lab = Label::createWithSystemFont("读取存档3", "", 35);
        auto arc2_lab = Label::createWithSystemFont("读取存档4", "", 35);
        auto arc3_lab = Label::createWithSystemFont("读取存档1", "", 35);
        auto arc4_lab = Label::createWithSystemFont("读取存档2", "", 35);
        arc1_lab->setColor(Color3B(223,255,147));
        arc2_lab->setColor(Color3B(223,255,147));
        arc3_lab->setColor(Color3B(223,255,147));
        arc4_lab->setColor(Color3B(223,255,147));
        read1_but->addChild(arc1_lab);
        read2_but->addChild(arc2_lab);
        read3_but->addChild(arc3_lab);
        read4_but->addChild(arc4_lab);
        auto but_size = read1_but->getContentSize();
        arc1_lab->setPosition(but_size.width/2,but_size.height/2);
        arc2_lab->setPosition(but_size.width/2,but_size.height/2);
        arc3_lab->setPosition(but_size.width/2,but_size.height/2);
        arc4_lab->setPosition(but_size.width/2,but_size.height/2);
    }
        
    return true;
}
void ArchiveFace::onClickBut_saveGame(Ref* p)   //保存存档
{
    if(GameScene::controlLayer->heroIsDie)
    {
        GameScene::controlLayer->gameLayer->showHint(105);
        return;
    }
    int tag = static_cast<Button*>(p)->getTag();
    Attribute::getInstance()->attr_map["stair"] = GameScene::controlLayer->stairNum;    //保存楼层值
    Attribute::getInstance()->attr_map["position"] = Vec2ToString(GameScene::controlLayer->gameLayer->heroNowTilePos); //保存英雄的位置
//    archive->attr_map = Attribute::getInstance()->attr_map;  //保存属性map
//    archive->props_map = Props::getInstance()->props_map;    //保存物品map到类中的map变量中
    Archive::getInstance()->archive_map["attr"] = Attribute::getInstance()->attr_map;
    Archive::getInstance()->archive_map["props"] = Props::getInstance()->props_map;
    Archive::getInstance()->saveArchive();   //保存到总map中

    std::string filePath = FileUtils::getInstance()->getWritablePath();
    std::string fullPath = filePath + StringUtils::format("archive%d.plist",tag);
    FileUtils::getInstance()->writeToFile(Archive::getInstance()->archive_map,fullPath.c_str());

    this->setVisible(false);
    GameScene::controlLayer->gameLayer->showHint(104);
}
void ArchiveFace::onClickBut_closeSave(Ref* p)  //关闭保存存档界面
{
    saveBg_lay->setVisible(false);
}
void ArchiveFace::onClickBut_readGame(Ref* p)   //读取存档
{
    Archive::getInstance()->release();   //重新开始，要消除记录
//    Props::getInstance()->release();
//    Attribute::getInstance()->release();
    GameScene::controlLayer = NULL;
    int tag = static_cast<Button*>(p)->getTag();
    Director::getInstance()->replaceScene(GameScene::createArcScene(tag));
    
    this->setVisible(false);
}
void ArchiveFace::onClickBut_closeRead(Ref* p)  //关闭读取存档界面
{
    readBg_lay->setVisible(false);
}
void ArchiveFace::saveFaceShow()
{
    saveBg_lay->setVisible(true);
    readBg_lay->setVisible(false);
}
void ArchiveFace::readFaceShow()
{
    saveBg_lay->setVisible(false);
    readBg_lay->setVisible(true);
}