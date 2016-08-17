//
//  AttributeFace.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/24.
//
//

#include "AttributeFace.hpp"
#import "GameCenterTools.h"
#include "GameScene.h"
#include "Props.hpp"
//这个界面node的原点坐标设置在左上角
bool AttributeFace::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto bg_sp = Sprite::create("attribute/attri2.png");
    addChild(bg_sp);
    bg_sp->setAnchorPoint(Vec2(0,1));
    bg_sp->setPosition(0,0);
    face_size = bg_sp->getContentSize();
    attri = Attribute::getInstance();
    
    int font_size = 40;
    hero_sp = Sprite::create("hero.png",cocos2d::Rect(0,0,32,32));
    addChild(hero_sp);
    hero_sp->setScale(2.7);
    hero_sp->setPosition(60,-60);
    auto state_sp = Label::createWithSystemFont("状态:","",font_size);
    state_sp->setAnchorPoint(Vec2(0,0.5));
    addChild(state_sp);
    state_sp->setPosition(150,-40);
    state_lab = Label::createWithSystemFont("正常","",font_size);
    state_lab->setAnchorPoint(Vec2(0,0.5));
    addChild(state_lab);
    state_lab->setPosition(state_sp->getPositionX()+95,state_sp->getPositionY());
    //属性图标
//    auto hp_sp = Sprite::create("attribute/a.png");
//    auto atta_sp = Sprite::create("attribute/a.png");
//    auto defen_sp = Sprite::create("attribute/a.png");
//    auto agile_sp = Sprite::create("attribute/a.png");
//    auto gold_sp = Sprite::create("attribute/a.png");
//    auto exp_sp = Sprite::create("attribute/a.png");
//    auto grade_sp = Sprite::create("attribute/a.png");
//    auto stair_sp = Sprite::create("attribute/a.png");
    auto grade_sp = Label::createWithSystemFont("等级：","",font_size);
    auto hp_sp = Label::createWithSystemFont("血量","",font_size);
    auto atta_sp = Label::createWithSystemFont("攻击力","",font_size);
    auto defen_sp = Label::createWithSystemFont("防御力","",font_size);
    auto agile_sp = Label::createWithSystemFont("敏捷值","",font_size);
    auto gold_sp = Label::createWithSystemFont("金币","",font_size);
    auto exp_sp = Label::createWithSystemFont("经验","",font_size);

    addChild(hp_sp);
    addChild(atta_sp);
    addChild(defen_sp);
    addChild(agile_sp);
    addChild(gold_sp);
    addChild(exp_sp);
    addChild(grade_sp);

    hp_sp->setAnchorPoint(Vec2(0,0.5));
    atta_sp->setAnchorPoint(Vec2(0,0.5));
    defen_sp->setAnchorPoint(Vec2(0,0.5));
    agile_sp->setAnchorPoint(Vec2(0,0.5));
    gold_sp->setAnchorPoint(Vec2(0,0.5));
    exp_sp->setAnchorPoint(Vec2(0,0.5));
    grade_sp->setAnchorPoint(Vec2(0,0.5));

    int val = -70;
    int fPosY = -145;//开始的y位置
    int fPosX = 30;//开始的x位置
    grade_sp->setPosition(150,-90); //等级特别放置
    hp_sp->setPosition(fPosX,fPosY);
    atta_sp->setPosition(fPosX,fPosY+val);
    defen_sp->setPosition(fPosX,fPosY+val*2);
    agile_sp->setPosition(fPosX,fPosY+val*3);
    gold_sp->setPosition(fPosX,fPosY+val*4);
    exp_sp->setPosition(fPosX,fPosY+val*5);

    
    //属性值
    std::string font_str = "Arial-BoldItalicMT";
    HP_lab = Label::createWithSystemFont("",font_str,40);
    attack_lab = Label::createWithSystemFont("",font_str,40);
    defense_lab = Label::createWithSystemFont("",font_str,40);
    agile_lab = Label::createWithSystemFont("",font_str,40);
    gold_lab = Label::createWithSystemFont("",font_str,40);
    exp_lab = Label::createWithSystemFont("",font_str,40);
    grade_lab = Label::createWithSystemFont("",font_str,50);

    
    HP_lab->setAnchorPoint(Vec2(0,0.5));
    attack_lab->setAnchorPoint(Vec2(0,0.5));
    defense_lab->setAnchorPoint(Vec2(0,0.5));
    agile_lab->setAnchorPoint(Vec2(0,0.5));
    gold_lab->setAnchorPoint(Vec2(0,0.5));
    exp_lab->setAnchorPoint(Vec2(0,0.5));
    grade_lab->setAnchorPoint(Vec2(0,0.5));

    int valX = 180;
    HP_lab->setPosition(hp_sp->getPositionX()+valX,hp_sp->getPositionY());
    attack_lab->setPosition(atta_sp->getPositionX()+valX,atta_sp->getPositionY());
    defense_lab->setPosition(defen_sp->getPositionX()+valX,defen_sp->getPositionY());
    agile_lab->setPosition(agile_sp->getPositionX()+valX,agile_sp->getPositionY());
    gold_lab->setPosition(gold_sp->getPositionX()+valX,gold_sp->getPositionY());
    exp_lab->setPosition(exp_sp->getPositionX()+valX,exp_sp->getPositionY());
    grade_lab->setPosition(grade_sp->getPositionX()+110,grade_sp->getPositionY());

    HP_lab->setString(StringUtils::format("%d",attri->getHP()));
    attack_lab->setString(StringUtils::format("%d",attri->getAttack()));
    defense_lab->setString(StringUtils::format("%d",attri->getDefense()));
    agile_lab->setString(StringUtils::format("%d",attri->getAgile()));
    gold_lab->setString(StringUtils::format("%d",attri->getGold()));
    exp_lab->setString(StringUtils::format("%d",attri->getExp()));
    grade_lab->setString(StringUtils::format("%d",attri->getGrade()));

    addChild(HP_lab);
    addChild(attack_lab);
    addChild(defense_lab);
    addChild(agile_lab);
    addChild(gold_lab);
    addChild(exp_lab);
    addChild(grade_lab);
    
    return true;
}
void AttributeFace::updateByMap()
{
    HP_lab->setString(Value(attri->getHP()).asString());
    attack_lab->setString(Value(attri->getAttack()).asString());
    defense_lab->setString(Value(attri->getDefense()).asString());
    gold_lab->setString(Value(attri->getGold()).asString());
    exp_lab->setString(Value(attri->getExp()).asString());
    grade_lab->setString(Value(attri->getGrade()).asString());
    agile_lab->setString(StringUtils::format("%d",attri->getAgile()));
    
    int wand2 = Props::getInstance()->getPropByGid(e_wand2);
    int wand3 = Props::getInstance()->getPropByGid(e_wand3);
    if(wand2>0)
    {
        state_lab->setString(StringUtils::format("霸者%d级",wand2));
        hero_sp->setTexture("hero2.png");
        hero_sp->setTextureRect(cocos2d::Rect(0,0,32,32));
    }
    if(wand3>0)
    {
        state_lab->setString(StringUtils::format("勇者%d级",wand3));
        hero_sp->setTexture("hero3.png");
        hero_sp->setTextureRect(cocos2d::Rect(0,0,32,32));
    }
}
void AttributeFace::addLevel(int num)
{
    attri->addGrade(num);
    grade_lab->setString(StringUtils::format("%d",attri->getGrade()));
    addHP(400);
    addAttack(5);
    addDefen(5);
}
//增加和减少属性
void AttributeFace::addAttack(int num)
{
    attri->addAttack(num);
    attack_lab->setString(Value(attri->getAttack()).asString());
}
void AttributeFace::addDefen(int num)
{
    attri->addDefen(num);
    defense_lab->setString(Value(attri->getDefense()).asString());
}
void AttributeFace::addAgile(int num)
{
    attri->addAgile(num);
    agile_lab->setString(Value(attri->getAgile()).asString());
}
void AttributeFace::addHP(int num)
{
    attri->addHP(num);
    HP_lab->setString(Value(attri->getHP()).asString());
}
//设置属性
void AttributeFace::setAttack(int num)
{
    if(num<0)
        num = 0;
    attri->setAttack(num);
    attack_lab->setString(StringUtils::format("%d",num));
}
void AttributeFace::setDefen(int num)
{
    if(num<0)
        num = 0;
    attri->setDefense(num);
    defense_lab->setString(StringUtils::format("%d",num));
}
void AttributeFace::setHP(int num)
{
    if(num<0)
        num = 0;
    attri->setHP(num);
    HP_lab->setString(StringUtils::format("%d",num));
}
//使用或增加金币
bool AttributeFace::useGold(int num)
{
    if(attri->getGold() < num)
        return false;   //钱不够就返回false
    else
    {
        attri->addGold(-num);
    }
    gold_lab->setString(StringUtils::format("%d",attri->getGold()));
    return true;
}
void AttributeFace::addGold(int num)
{
    attri->addGold(num);
    gold_lab->setString(StringUtils::format("%d",attri->getGold()));
    return;
}
bool AttributeFace::useExp(int num)
{
    if(attri->getExp() < num)
        return false;   //钱不够就返回false
    else
    {
        attri->addExp(-num);
    }
    exp_lab->setString(StringUtils::format("%d",attri->getExp()));
    return true;
}
void AttributeFace::addExp(int num)
{
    attri->addExp(num);
    exp_lab->setString(StringUtils::format("%d",attri->getExp()));
    return;
}
void AttributeFace::uploadScore()
{
    int score;
    int hp = attri->getHP();
    int atta = attri->getAttack();
    int defen = attri->getDefense();
    int topStair = attri->getTopFloor();
    int minStair = attri->getMinFloor();
    score = atta*7 + defen*5 + hp*2;   //分数计算
    score += topStair * 5000;
    score += abs(minStair) * 10000;
    if(GameScene::controlLayer->stairNum==108)
    {
        score += 200000;
    }
    [[GameCenterTools sharedGameKitHelper] authenticateLocalUser];
    [[GameCenterTools sharedGameKitHelper] reportScore: score forCategory: @"com.cdbandou.fang_top"];
}