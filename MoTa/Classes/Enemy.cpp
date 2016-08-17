//
//  Enemy.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#include "Enemy.hpp"
#include "SwordHero.hpp"
#include "ReadPlist.hpp"
#include "GameScene.h"
#include "Audio.hpp"
Texture2D* Enemy::foeTexture = NULL;
Enemy* Enemy::create(int foeNum)
{
    Enemy *pRet = new(std::nothrow) Enemy();
    if (pRet && pRet->init(foeNum))
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
bool Enemy::init(int foeNum)
{
    if (!Node::init())
    {
        return false;
    }
    attackCount = 0;
    //根据向下行走动画的第一帧创建精灵spriteWithSpriteFrame
    foeSprite = Sprite::createWithTexture(foeTexture,Rect(32*0, 32*(foeNum-1), 32, 32));
    
    //设置锚点
    foeSprite->setAnchorPoint(Point::ZERO);
    
    //将用于显示的heroSprite加到自己的节点下
    this->addChild(foeSprite);
    
    id = foeNum;
    //属性
    if(foeNum>0)
    {
        ValueMap* enemy_map = ReadPlist::getInstance()->getEnemyMap();
        ValueMap enemyAttr_map = (*enemy_map)[StringUtils::format("%d",id)].asValueMap();
        name = enemyAttr_map["name"].asString();
        id = foeNum;
        HP = enemyAttr_map["HP"].asInt();
        attack = enemyAttr_map["attack"].asInt();
        defense = enemyAttr_map["defense"].asInt();
        agile = enemyAttr_map["agile"].asInt();
        thump = enemyAttr_map["thump"].asInt();
        attackTime = enemyAttr_map["attackTime"].asInt();
        virulence = enemyAttr_map["virulence"].asInt();
        debuff = enemyAttr_map["debuff"].asInt();
        gold = enemyAttr_map["gold"].asInt();
        exp = enemyAttr_map["exp"].asInt();
        attackTag = enemyAttr_map["attackTag"].asInt();
        if(attackTime==0)
            attackTime = 1;
        if((foeNum>=13 && foeNum<=16) || foeNum==47 || foeNum==49 ||foeNum==54)  //是否是法师的判断，法师是无视防御力的
        {
            isWizard = true;
        }
        else
        {
            isWizard = false;
        }
    }
    
    runAnimation();
    
    return true;
}
void Enemy::attackHero(Node* foe)
{
    SwordHero* hero = static_cast<SwordHero*>(foe);
    int heroInjure; //勇士损血量
    if(isWizard)    //是巫师，无视勇士防御
    {
        heroInjure = this->attack;
    }
    else //普通计算
    {
        if(hero->baZheDefeAdd)
            heroInjure = this->attack - hero->defense*2;
        else
            heroInjure = this->attack - hero->defense;  //怪物功减勇士防，勇士损耗
    }
    if(heroInjure<=0 && heroInjure>-30) //最少伤害为1
        heroInjure = 1;
    else if(heroInjure <= -30)
        heroInjure = 0;
    //随机的情况影响伤害值
    bool isMiss = false;
    int vir_rand = random(1,100);
    int thum_rand = random(1,100);
    if(vir_rand <= hero->agile)  //躲避了
    {
        heroInjure = 0;
    }
    if(thum_rand <= thump)  //重击了
    {
        heroInjure *= 2;
    }
    
    //***************霸者的判断
    int wand2 = Props::getInstance()->getPropByGid(e_wand2);
    if(!isWizard && wand2==1)  //霸者1
    {
        int hurt = this->attack;
        int rand = random(1,100);
        if(rand<=10)//%6的几率
        {
            if(hurt/2 >= HP)//条件达成，怪物会死亡
            {
                hero->baZheKill = true;
                attackCount = attackTime;
            }
            else
            {
                HP -= hurt/2;
                GameScene::controlLayer->sword->nodePos->getChildByName<Label*>("foeHP")->setString(StringUtils::format("%d",HP));
                GameScene::controlLayer->sword->showLossBlood(hurt/2,true);
            }
        }
    }
    else if(!isWizard && wand2==2)  //霸者2
    {
        int hurt = this->attack;
        int rand = random(1,100);
        if(rand<=15)//%11的几率
        {
            if(hurt >= HP)//条件达成，怪物会死亡
            {
                hero->baZheKill = true;
                attackCount = attackTime;
            }
            else
            {
                heroInjure = hurt/2;
                HP -= hurt;
                GameScene::controlLayer->sword->nodePos->getChildByName<Label*>("foeHP")->setString(StringUtils::format("%d",HP));
                GameScene::controlLayer->sword->showLossBlood(hurt,true);
            }
        }
        else if(rand>=89)
        {
            hero->baZheDefeAdd = true;
        }
    }
    else if(!isWizard && wand2==3)  //霸者3
    {
        int rand = random(1,100);
        if(rand<=20)//%16的几率
        {
            int hurt = this->attack;
            if(hurt/2 >= HP)//条件达成，怪物会死亡
            {
                hero->baZheKill = true;
                attackCount = attackTime;
            }
            else
            {
                heroInjure = heroInjure/3;
                HP -= hurt/3;
                GameScene::controlLayer->sword->nodePos->getChildByName<Label*>("foeHP")->setString(StringUtils::format("%d",HP));
                GameScene::controlLayer->sword->showLossBlood(hurt,true);
            }
        }
        else if(rand>=84)
        {
            hero->baZheDefeAdd = true;
        }
    }
    
    //***************
    //声音
    if(isMiss)
        PlaySound(Audio::miss_e);
    else if(heroInjure==0)
        PlaySound(Audio::daji0_e);
    else
    {
        if(attackTag==3)
            PlaySound(Audio::daoji_e);
        else if(attackTag==9 || attackTag==10)
            PlaySound(Audio::bigDaji_e);
        else if(attackTag==11)
            PlaySound(Audio::hongji_e);
        else
            PlaySound(Audio::daji_e);
    }
    //攻击动画
    GameScene::controlLayer->sword->showSwordAnimate(attackTag,true);
    if(isMiss==false)
    {
        //见血动作
        GameScene::controlLayer->sword->showLossBlood(heroInjure,true);
    }
    else
    {
        GameScene::controlLayer->sword->showMiss(true);
    }
    
    //勇士血量的减少
    hero->HP = hero->HP - heroInjure;
    GameScene::controlLayer->sword->nodePos->getChildByName<Label*>("heroHP")->setString(StringUtils::format("%d",hero->HP));
    if(hero->HP <= 0)   //勇士死亡
    {
        GameScene::controlLayer->setHP(0);
        GameScene::controlLayer->sword->swordOverHeroDie();
        GameScene::controlLayer->HeroDie();
    }
    else
    {
        GameScene::controlLayer->setHP(hero->HP);
        attackCount++;  //攻击次数加1
        if(attackCount>=attackTime)
        {
            GameScene::controlLayer->sword->isHeroAtta = true;
            attackCount = 0;
        }
    }
}
void Enemy::runAnimation()
{
    SpriteFrame *frame0;
    SpriteFrame *frame1;

    if(id==61 || id==62 || id==63)
    {
        frame0 = SpriteFrame::createWithTexture(foeTexture, Rect(32*0, 32*(id-1), 32, 32));
        frame1 = SpriteFrame::createWithTexture(foeTexture, Rect(32*1, 32*(id-1), 32, 32));
    }
    else
    {
        frame0 = SpriteFrame::createWithTexture(foeTexture, Rect(32*1, 32*(id-1), 32, 32));
        frame1 = SpriteFrame::createWithTexture(foeTexture, Rect(32*3, 32*(id-1), 32, 32));
    }
        
    Vector<SpriteFrame*> foeFrames;
    
    foeFrames.pushBack(frame0);
    foeFrames.pushBack(frame1);
    
    Animation* animation = Animation::createWithSpriteFrames(foeFrames, 0.2f);
    auto fore = RepeatForever::create(Animate::create(animation));
    foeSprite->runAction(fore);
}