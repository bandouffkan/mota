//
//  FoeData.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/27.
//
//

#include "FoeData.hpp"
#include "GameScene.h"
#include "ReadPlist.hpp"
#include "Attribute.hpp"
bool FoeData::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    foeData_list = ListView::create();
    foeData_list->setContentSize(GameScene::controlLayer->gameLayer->tmxSize);
    addChild(foeData_list);
    foeData_list->setBackGroundColorType(ui::HBox::BackGroundColorType::SOLID);
    foeData_list->setPosition(Vec2(0,0));
    foeData_list->setTouchEnabled(true);
    foeData_list->setColor(Color3B(100,100,100));
    foeData_list->setBackGroundColorOpacity(204);
    
    return true;
}
void FoeData::foeDataShow()
{
    TMXLayer* enemy_layer = GameScene::controlLayer->gameLayer->enemy_layer;
    if(enemy_layer == NULL)
        return;
    
    Texture2D* foeTexture = Director::getInstance()->getTextureCache()->addImage("enemy.png");
    Size s = enemy_layer->getLayerSize();
    int foeNum = 0;    //怪物数量
    std::vector<int> foeCount;
    for(short x=0;x<s.width;x++)
    {
        for(short y=0;y<s.height;y++)
        {
            int gid = enemy_layer->getTileGIDAt(Point(x, y));
            if(gid != 0)
            {
                int id = getEnemyIdInFile(gid);
                foeCount.push_back(id);
            }
        }
    }
    
    //这两句是对vector中的数据的排序，和删除重复的元素
    sort(foeCount.begin(),foeCount.end());
    foeCount.erase(unique(foeCount.begin(),foeCount.end()),foeCount.end());
    
    ValueMap* enemy_map = ReadPlist::getInstance()->getEnemyMap();
    //遍历vector,显示数据
    for(int foeinfo:foeCount)
    {
        ValueMap enemyAttr_map = (*enemy_map)[StringUtils::format("%d",foeinfo)].asValueMap();
        std::string foeName = enemyAttr_map["name"].asString();
        int foeHP = enemyAttr_map["HP"].asInt();
        int foeAttack = enemyAttr_map["attack"].asInt();
        int foeDefense = enemyAttr_map["defense"].asInt();
        int foeGold = enemyAttr_map["gold"].asInt();
        int foeExp = enemyAttr_map["exp"].asInt();
        Label* foeName_Lab = Label::createWithSystemFont(foeName,"",35);
        Label* foeHP_Lab = Label::createWithSystemFont(StringUtils::format("%d",foeHP),"",45);
        Label* foeAttack_Lab = Label::createWithSystemFont (StringUtils::format("%d",foeAttack),"",45);
        Label* foeDefen_Lab = Label::createWithSystemFont (StringUtils::format("%d",foeDefense),"",45);
        Label* foeGold_Lab = Label::createWithSystemFont (StringUtils::format("%d",foeGold),"",45);
        Label* foeExp_Lab = Label::createWithSystemFont (StringUtils::format("%d",foeExp),"",45);
        Label* lossHP_Lab = NULL;
        if(Attribute::getInstance()->getAttack() <= foeDefense)
        {
            lossHP_Lab = Label::createWithSystemFont ("???","",45);
        }
        else
        {
            int loss = (ceil((float)foeHP/(Attribute::getInstance()->getAttack()-foeDefense))-1) * ((foeAttack-Attribute::getInstance()->getDefense())>0?(foeAttack-Attribute::getInstance()->getDefense()):0);
            
            //int ci = ceil((float)foeHP/(attribute->getAttackNum()-foeDefense))-1;
            lossHP_Lab = Label::createWithSystemFont (StringUtils::format("%d",loss),"",45);
            //atta_Lab = Label::createWithSystemFont(StringUtils::format("%d",ci),"",45);
        }
        
        //创建一个UI控件加入到ListView里
        Widget* foeInfo = Widget::create();
        foeInfo->setSize(Size(140,140));
        foeData_list->pushBackCustomItem(foeInfo);
        //foeData_list->addChild(foeInfo);
        //设置表示怪物样子的图片精灵
        auto foeSprite = Sprite::createWithTexture(foeTexture,Rect(0,(foeinfo-1)*32,32,32));
        foeSprite->setScale(2.4);
        foeInfo->addChild(foeSprite);
        int interval = 150; //间隔
        int fiCd = 100; //初始位子间隔
        foeSprite->setPosition(interval*0+fiCd,0);
        //把表示数据意义的图片做成精灵
        auto foeHP_Sp = Sprite::create("Attribute/HP.png");
        auto foeAtta_Sp = Sprite::create("Attribute/atta.png");
        auto foeDefen_Sp = Sprite::create("Attribute/defen.png");
        auto foeGold_Sp = Sprite::create("Attribute/gold.png");
        auto foeExp_Sp = Sprite::create("Attribute/exp.png");
        auto damage_Sp = Sprite::create("Attribute/hai.png");
        foeInfo->addChild(foeHP_Sp);
        foeInfo->addChild(foeAtta_Sp);
        foeInfo->addChild(foeDefen_Sp);
        foeInfo->addChild(foeGold_Sp);
        foeInfo->addChild(foeExp_Sp);
        foeInfo->addChild(damage_Sp);
        foeHP_Sp->setScale(2);
        foeAtta_Sp->setScale(1.6);
        foeDefen_Sp->setScale(1.6);
        foeGold_Sp->setScale(1.6);
        foeExp_Sp->setScale(2.2);
        damage_Sp->setScale(2.2);
        foeAtta_Sp->setPosition(foeSprite->getPositionX() + interval,20);
        foeDefen_Sp->setPosition(foeSprite->getPositionX() + interval,-50);
        foeHP_Sp->setPosition(foeSprite->getPositionX() + fiCd*4,20);
        foeGold_Sp->setPosition(foeSprite->getPositionX() + fiCd*4,-50);
        foeExp_Sp->setPosition(750,20);
        damage_Sp->setPosition(900,20);
        //把Label都加入到UI控件里
        foeHP_Lab->setAnchorPoint(Vec2(0,0.5));
        foeAttack_Lab->setAnchorPoint(Vec2(0,0.5));
        foeDefen_Lab->setAnchorPoint(Vec2(0,0.5));
        foeGold_Lab->setAnchorPoint(Vec2(0,0.5));
        lossHP_Lab->setAnchorPoint(Vec2(0,0.5));
        foeInfo->addChild(foeName_Lab);
        foeInfo->addChild(foeHP_Lab);
        foeInfo->addChild(foeAttack_Lab);
        foeInfo->addChild(foeDefen_Lab);
        foeInfo->addChild(foeGold_Lab);
        foeInfo->addChild(lossHP_Lab);
        foeInfo->addChild(foeExp_Lab);
        //设置label的位子
        foeName_Lab->setPosition(foeSprite->getPositionX(),foeSprite->getPositionY()-65);
        foeHP_Lab->setPosition(foeHP_Sp->getPositionX()+45,foeHP_Sp->getPositionY());
        foeAttack_Lab->setPosition(foeAtta_Sp->getPositionX()+45,foeAtta_Sp->getPositionY());
        foeDefen_Lab->setPosition(foeDefen_Sp->getPositionX()+45,foeDefen_Sp->getPositionY());
        foeGold_Lab->setPosition(foeGold_Sp->getPositionX()+45,foeGold_Sp->getPositionY());
        lossHP_Lab->setPosition(900,-30);
        foeExp_Lab->setPosition(750,-30);
        foeNum++;
    }
    Widget* foeInfo = Widget::create();
    foeInfo->setSize(Size(140,140));
    foeData_list->pushBackCustomItem(foeInfo);
    this->setVisible(true);
}
void FoeData::foeDataNoShow()
{
    foeData_list->removeAllItems();
    foeData_list->setVisible(false);
}