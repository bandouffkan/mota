//
//  SwordHero.cpp
//  MoTa
//
//  Created by xcode31 on 16/7/4.
//
//

#include "SwordHero.hpp"
#include "Attribute.hpp"
#include "GameConstants.h"
#include "GameScene.h"
#include "Enemy.hpp"
#include "Audio.hpp"
bool SwordHero::init()
{
    if (!Node::init())
    {
        return false;
    }
    attackCount = 0;
    //根据向下行走动画的第一帧创建精灵spriteWithSpriteFrame
    heroTexture = TextureCache::sharedTextureCache()->addImage("hero.png");
    heroSprite = Sprite::createWithTexture(heroTexture,Rect(TITL_SIZE*0, TITL_SIZE*0, TITL_SIZE, TITL_SIZE));
    
    //设置锚点
    heroSprite->setAnchorPoint(Point::ZERO);
    
    //将用于显示的heroSprite加到自己的节点下
    this->addChild(heroSprite);
    
    HP = Attribute::getInstance()->getHP();
    attack = Attribute::getInstance()->getAttack();
    defense = Attribute::getInstance()->getDefense();
    agile = Attribute::getInstance()->getAgile();
    thump = Attribute::getInstance()->getThump();
    attackTime = Attribute::getInstance()->getAttackTime();
    isPoison = Attribute::getInstance()->getIsPoison();
    isDebuff = Attribute::getInstance()->getIsDebuff();
    
    if(Props::getInstance()->getPropByGid(e_wand3)>0)
        isYongZhe = true;
    else
        isYongZhe = false;
    baZheKill = false;
    baZheDefeAdd = false;
    
    return true;
}
void SwordHero::attackFoe(Node* foe)
{
    Enemy* enemy = static_cast<Enemy*>(foe);
    int foeInjure;  //怪物损血
    foeInjure = Attribute::getInstance()->getAttack() - enemy->defense; //勇士功减怪物防，怪物损害
    
    if(foeInjure <= 0 && foeInjure>-40)
    {
        foeInjure = 1;
    }
    else if(foeInjure <=-40)
        foeInjure = 0;
    //随机的情况影响伤害值
    bool isMiss = false;
    int vir_rand = random(1,100);
    int thum_rand = random(1,100);
    if(vir_rand <= enemy->agile)  //躲避了
    {
        log("躲避");
        foeInjure = 0;
        isMiss = true;
    }
    if(thum_rand <= thump)  //重击了
    {
        log("重击");
        foeInjure *= 2;
    }
    
    //勇者3级加伤
    if(Props::getInstance()->getPropByGid(e_wand3)==3)
    {
        int rand = random(1,100);
        if(defense < enemy->attack && rand<=20)
        {
            foeInjure += defense/4;
        }
        
    }
    
    //声音
    if(isMiss)
        PlaySound(Audio::miss_e);
    else
    {
        if(isYongZhe)
            PlaySound(Audio::daoji_e);
        else if(baZheKill)
            PlaySound(Audio::bigDaji_e);
        else
            PlaySound(Audio::daji_e);
    }
    
    //霸者秒杀
    if(baZheKill)
    {
        foeInjure = enemy->HP;
        //战斗动画
        GameScene::controlLayer->sword->showSwordAnimate(10,false);
    }
    else
    {
        //战斗动画
        if(isYongZhe)
            GameScene::controlLayer->sword->showSwordAnimate(3,false);
        else
            GameScene::controlLayer->sword->showSwordAnimate(1,false);
    }
    if(isMiss==false)
    {
        //掉血动作
        GameScene::controlLayer->sword->showLossBlood(foeInjure,false);
    }
    else
    {
        GameScene::controlLayer->sword->showMiss(false);
    }
    enemy->HP = enemy->HP - foeInjure;
    if(enemy->HP<=0)
    {
        enemy->HP = 0;
        //怪物死亡，战斗结束
        GameScene::controlLayer->addGold(enemy->gold);
        GameScene::controlLayer->addExp(enemy->exp);
        GameScene::controlLayer->gameLayer->removeEnemy(GameScene::controlLayer->gameLayer->heroTarTilePos);
        if(enemy->id==57)    //有几个不死族死了会出怪
        {
            GameScene::controlLayer->gameLayer->enemy_layer->setTileGID(29, GameScene::controlLayer->gameLayer->heroTarTilePos);
            Archive::getInstance()->setStairEnemy_map(GameScene::controlLayer->gameLayer->heroTarTilePos,29,GameScene::controlLayer->stairNum);
        }
        else if(enemy->id==60)
        {
            GameScene::controlLayer->gameLayer->enemy_layer->setTileGID(241, GameScene::controlLayer->gameLayer->heroTarTilePos);
            Archive::getInstance()->setStairEnemy_map(GameScene::controlLayer->gameLayer->heroTarTilePos,241,GameScene::controlLayer->stairNum);
        }
        if(enemy->id == 61 || enemy->id==62 || enemy->id==63)   //大怪物
        {
            GameScene::controlLayer->gameLayer->tmx->removeChildByName("monst");
        }
        GameScene::controlLayer->sword->nodePos->getChildByName<Label*>("foeHP")->setString(StringUtils::format("%d",enemy->HP));
        GameScene::controlLayer->sword->swordOver();
        return;
    }
    else
    {
        GameScene::controlLayer->sword->nodePos->getChildByName<Label*>("foeHP")->setString(StringUtils::format("%d",enemy->HP));
        attackCount++;
        if(attackCount==attackTime)
        {
            baZheDefeAdd = false;
            baZheKill = false;
            GameScene::controlLayer->sword->isHeroAtta = false;
            attackCount = 0;
        }
    }
}