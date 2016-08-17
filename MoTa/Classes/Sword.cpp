//
//  Sword.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/15.
//
//

#include "Sword.hpp"
#include "GameConstants.h"
#include "ReadPlist.hpp"
#include "Enemy.hpp"
#include "Hero.hpp"
#include "Attribute.hpp"
#include "GameScene.h"
#include "Audio.hpp"
bool Sword::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    isHeroAtta = true;
    
    fight_lay = Layout::create();
    fight_lay->setBackGroundImage("sword/flightBg.png");
    fight_lay->setTouchEnabled(true);
    fight_lay->setContentSize(Sprite::create("sword/flightBg.png")->getContentSize());
    addChild(fight_lay);
    fight_lay->setAnchorPoint(Vec2(0.5,0.5));
    fight_lay->setPosition(Vec2(0,0));
    
    foeHP_lab = Label::createWithSystemFont("生命值", "", 33);
    foeAtta_lab = Label::createWithSystemFont("攻击力", "", 33);
    foeDefe_lab = Label::createWithSystemFont("防御力", "", 33);
    foeAgile_lab = Label::createWithSystemFont("敏捷", "", 33);
    
    heroHP_lab = Label::createWithSystemFont("生命值", "", 33);
    heroAtta_lab = Label::createWithSystemFont("攻击力", "", 33);
    heroDefe_lab = Label::createWithSystemFont("防御力", "", 33);
    heroAgile_lab = Label::createWithSystemFont("敏捷", "", 33);
    
    fight_lay->addChild(foeHP_lab);
    fight_lay->addChild(foeAtta_lab);
    fight_lay->addChild(foeDefe_lab);
    fight_lay->addChild(foeAgile_lab);
    
    fight_lay->addChild(heroHP_lab);
    fight_lay->addChild(heroAtta_lab);
    fight_lay->addChild(heroDefe_lab);
    fight_lay->addChild(heroAgile_lab);
    
    foeHP_lab->setPosition(266,435);
    foeAtta_lab->setPosition(266,317.5);
    foeDefe_lab->setPosition(266,200);
    foeAgile_lab->setPosition(266,82.5);
    
    heroHP_lab->setPosition(684,435);
    heroAtta_lab->setPosition(684,317.5);
    heroDefe_lab->setPosition(684,200);
    heroAgile_lab->setPosition(684,82.5);
    
    nodePos = Node::create();
    win_sp = Sprite::create("sword/win.png");
    foePos_sp = Sprite::create("sword/looksBox.png");
    heroPos_sp = Sprite::create("sword/looksBox.png");
    fight_lay->addChild(nodePos);
    fight_lay->addChild(win_sp,2);
    fight_lay->addChild(foePos_sp,3);
    fight_lay->addChild(heroPos_sp,3);
    nodePos->setPosition(0,0);
    win_sp->setPosition(475,250);
    foePos_sp->setPosition(106,385);
    heroPos_sp->setPosition(839,385);
    
    //勇士的名字
    auto heroName_lab = Label::createWithSystemFont("勇士","", 40);
    fight_lay->addChild(heroName_lab);
    heroName_lab->setPosition(heroPos_sp->getPositionX(),heroPos_sp->getPositionY()-155);
    
    win_sp->setVisible(false);
    
    //战斗退出按钮
    auto exit_but = Button::create("sword/chetui.png");
    fight_lay->addChild(exit_but);
    exit_but->setPosition(Vec2(857,65));
    exit_but->addClickEventListener(CC_CALLBACK_1(Sword::onClickBut_exit,this));
    
    return true;
}
void Sword::beginSword(int gid)//开始战斗
{
    foeID = getEnemyIdInFile(gid);//得到怪物的id
    InitDataAndImage(foeID);
    swordShow();
    
    //计算每次攻击的时间
    float fightTime = 20.0/fightNum;
    if(fightTime>0.4)
        fightTime = 0.4;
    else if(fightTime<0.1)
        fightTime = 0.1;
    this->schedule(schedule_selector(Sword::updateSword),fightTime,kRepeatForever,0.01);
}
void Sword::swordShow()
{
    this->setVisible(true);
    //怪物属性显示
    auto foeHPNum_lab = Label::createWithSystemFont(StringUtils::format("%d",enemy->HP),"" ,35);
    auto foeAttaNum_lab = Label::createWithSystemFont(StringUtils::format("%d",enemy->attack),"" ,35);
    auto foeDefeNum_lab = Label::createWithSystemFont(StringUtils::format("%d",enemy->defense),"" ,35);
    auto foeName_lab = Label::createWithSystemFont(enemy->name,"" ,40);
    auto foeAgileNum_lab = Label::createWithSystemFont(StringUtils::format("%d",enemy->agile),"" ,40);
    nodePos->addChild(foeHPNum_lab,0,"foeHP");
    nodePos->addChild(foeAttaNum_lab);
    nodePos->addChild(foeDefeNum_lab);
    nodePos->addChild(foeName_lab);
    nodePos->addChild(foeAgileNum_lab);
    foeHPNum_lab->setPosition( foeHP_lab->getPositionX(), foeHP_lab->getPositionY()-50);
    foeAttaNum_lab->setPosition( foeAtta_lab->getPositionX(),foeAtta_lab->getPositionY()-50);
    foeDefeNum_lab->setPosition( foeDefe_lab->getPositionX(),foeDefe_lab->getPositionY()-50);
    foeName_lab->setPosition( foePos_sp->getPositionX(),foePos_sp->getPositionY()- 155);
    foeAgileNum_lab->setPosition( foeAgile_lab->getPositionX(),foeAgile_lab->getPositionY()- 50 );
    //怪物和英雄的精灵显示
//    auto foe_Sp = Enemy::create(foeID);
//    foePos_sp->addChild(foe_Sp);
//    foe_Sp->foeSprite->setAnchorPoint(Vec2(0.5,0.5));
//    foe_Sp->setPosition(70,70);
//    foe_Sp->setScale(3);
//    auto hero_Sp = Hero::create();
//    heroPos_sp->addChild(hero_Sp);
//    hero_Sp->heroSprite->setAnchorPoint(Vec2(0.5,0.5));
//    hero_Sp->setPosition(70,70);
//    hero_Sp->setScale(3);
    //英雄的属性显示
    auto heroHPNum_lay = Label::createWithSystemFont(StringUtils::format("%d",hero->HP),"" ,35);
    auto heroAttaNum_lay = Label::createWithSystemFont(StringUtils::format("%d",hero->attack),"" ,35);
    auto heroDefeNum_lay = Label::createWithSystemFont(StringUtils::format("%d",hero->defense),"" ,35);
    auto heroAgileNum_lay = Label::createWithSystemFont(StringUtils::format("%d",hero->agile),"" ,35);
    // auto heroName_lay = Label::createWithSystemFont("勇士","",40);
    nodePos->addChild(heroHPNum_lay,0,"heroHP");
    nodePos->addChild(heroAttaNum_lay,0,"heroAtta");
    nodePos->addChild(heroDefeNum_lay,0,"heroDefe");
    nodePos->addChild(heroAgileNum_lay);
    heroHPNum_lay->setPosition( heroHP_lab->getPositionX(), heroHP_lab->getPositionY()-50);
    heroAttaNum_lay->setPosition( heroAtta_lab->getPositionX(),heroAtta_lab->getPositionY()-50);
    heroDefeNum_lay->setPosition( heroDefe_lab->getPositionX(),heroDefe_lab->getPositionY()-50);
    heroAgileNum_lay->setPosition( heroAgile_lab->getPositionX(),heroAgile_lab->getPositionY()-50);
}
void Sword::InitDataAndImage(int id)
{
    if(id>0)
    {
        enemy = Enemy::create(id);
        foePos_sp->addChild(enemy);
        enemy->foeSprite->setAnchorPoint(Vec2(0.5,0.5));
        enemy->setPosition(70,70);
        enemy->setScale(3);
        hero = SwordHero::create();
        heroPos_sp->addChild(hero);
        hero->heroSprite->setAnchorPoint(Vec2(0.5,0.5));
        hero->setPosition(70,70);
        hero->setScale(3);
        
        //如果有魔法护符，法师敌人防御减弱
        if(enemy->isWizard)
        {
            if(Props::getInstance()->getPropByGid(e_magicRune) >= 1)
            {
                enemy->defense -= hero->defense / 3;
            }
        }
        else if(enemy->id == 39)//白银史莱姆
        {
            log("白银");
            enemy->attack = hero->defense + 250;
            enemy->defense = hero->attack;
            enemy->HP = 6;
        }
        else if(enemy->id == 40)//黄金史莱姆
        {
            log("黄金");
            enemy->attack = hero->defense + 500;
            enemy->defense = hero->attack;
            enemy->HP = 10;
        }
        else if(enemy->id == 44)    //铁块
        {
            enemy->defense = hero->attack;
            enemy->HP = 20;
        }
    }
    else
    {
        enemy = NULL;
        hero = NULL;
    }
//    if(id>0)
//    {
//        ValueMap* enemy_map = ReadPlist::getInstance()->getEnemyMap();
//        ValueMap enemyAttr_map = (*enemy_map)[StringUtils::format("%d",id)].asValueMap();
//        foeID = id;
//        foeName = enemyAttr_map["name"].asString();
//        foeHP = enemyAttr_map["HP"].asInt();
//        foeAttack = enemyAttr_map["attackNum"].asInt();
//        foeDefense = enemyAttr_map["defenseNum"].asInt();
//        foeGold = enemyAttr_map["goldNum"].asInt();
//    }
}
bool Sword::swordCalcIsWin(int gid)//战斗前的计算
{
    int id = getEnemyIdInFile(gid);
    ValueMap* enemy_map = ReadPlist::getInstance()->getEnemyMap();
    ValueMap enemyAttr_map = (*enemy_map)[StringUtils::format("%d",id)].asValueMap();
    int foeHP = enemyAttr_map["HP"].asInt();
    int foeAttack = enemyAttr_map["attack"].asInt();
    int foeDefense = enemyAttr_map["defense"].asInt();
    int heroAttack = Attribute::getInstance()->getAttack();
    if(heroAttack<= foeDefense)
        return false;
    else
    {
        int loss = (ceil( (float)foeHP/(heroAttack-foeDefense) )-1) * ((foeAttack-Attribute::getInstance()->getDefense())>0?(foeAttack-Attribute::getInstance()->getDefense()):0);
        fightNum = (ceil( (float)foeHP/(heroAttack-foeDefense) ));
        if(loss >= Attribute::getInstance()->getHP())
        {
            return false;
        }
    }
    return true;
}
void Sword::updateSword1(float dt)
{
    //勇士先打一次，怪物再打一次
    //攻击动画
    auto swordAnima1 = Sprite::create();
    foePos_sp->addChild(swordAnima1);
    swordAnima1->setPosition(enemy->getPosition());
    swordAnima1->setScale(2);
    auto animate = Animate::create(getSwordAnimationByID(enemy->attackTag));
    auto func = CallFunc::create([=](){
        swordAnima1->removeFromParent();
    });
    auto seq = Sequence::create(animate,func, NULL);
    swordAnima1->runAction(seq);

    int enemyInjure = Attribute::getInstance()->getAttack() - enemy->defense; //勇士功减怪物防，怪物损害
    if(enemyInjure<=0)
        enemyInjure = 1;
    enemy->HP = enemy->HP - enemyInjure;    //怪物的血减损害
    if(enemy->HP<=0)
    {
        enemy->HP = 0;
        //怪物死亡,战斗结束
        GameScene::controlLayer->addGold(enemy->gold); //增加相应的金币
        //GameScene::controlLayer->addExp(enemy->exp);
        GameScene::controlLayer->gameLayer->removeEnemy(GameScene::controlLayer->gameLayer->heroTarTilePos);
        nodePos->getChildByName<Label*>("foeHP")->setString(StringUtils::format("%d",enemy->HP));
        
        this->unschedule(schedule_selector(Sword::updateSword));  //取消这个update
        
        swordOver();
        
        return;
    }
    nodePos->getChildByName<Label*>("foeHP")->setString(StringUtils::format("%d",enemy->HP));
    
    //怪物打一次
    auto delay2 = DelayTime::create(0.1);
    auto func2 = CallFunc::create([=](){
        //攻击动画
        auto swordAnima = Sprite::create();
        heroPos_sp->addChild(swordAnima);
        swordAnima->setPosition(hero->getPosition());
        swordAnima->setScale(2);
        auto animate = Animate::create(getSwordAnimationByID(enemy->attackTag));
        auto func = CallFunc::create([=](){
            swordAnima->removeFromParent();
        });
        auto seq = Sequence::create(animate,func, NULL);
        swordAnima->runAction(seq);
        
        int heroInjure = enemy->attack - Attribute::getInstance()->getDefense();  //怪物功减勇士防，勇士损耗
        if(heroInjure<=0)
            heroInjure = 1;
        int heroHP = Attribute::getInstance()->getHP();
        heroHP = heroHP - heroInjure;   //勇士的血减损
        if(heroHP <= 0)
        {
            //勇士死亡,战斗结束
            heroHP = 1;
            //hero->swordSprite->stopActionByTag(1);
            Attribute::getInstance()->attr_map["HP"] = 1;
            GameScene::controlLayer->setHP(1);
            
            GameScene::controlLayer->addGold(enemy->gold); //增加相应的金币
            //GameScene::controlLayer->addExp(exp);
            GameScene::controlLayer->gameLayer->removeEnemy(GameScene::controlLayer->gameLayer->heroTarTilePos);
            
            nodePos->getChildByName<Label*>("foeHP")->setString(StringUtils::format("%d",enemy->HP));
            
            this->unschedule(schedule_selector(Sword::updateSword));  //取消这个update
            
            swordOver();
            
            return;
        }
        GameScene::controlLayer->setHP(heroHP);
        nodePos->getChildByName<Label*>("heroHP")->setString(StringUtils::format("%d",heroHP));
    });
    auto seq2 = Sequence::create(delay2,func2, NULL);
    this->runAction(seq2);
}
void Sword::updateSword(float dt)
{
    if(isHeroAtta)
    {
        //勇士先打次
        hero->attackFoe(enemy);
    }
    else
    {
        //怪物打次
        enemy->attackHero(hero);
    }
}
void Sword::swordOver()
{
    this->unschedule(schedule_selector(Sword::updateSword));
    win_sp->setVisible(true);
    auto delay = DelayTime::create(0.25);
    auto func = CallFunc::create([=](){
        this->setVisible(false);
        foePos_sp->removeAllChildrenWithCleanup(true);
        heroPos_sp->removeAllChildrenWithCleanup(true);
        nodePos->removeAllChildrenWithCleanup(true);
        win_sp->setVisible(false);
        GameScene::controlLayer->gameLayer->showHint(100,enemy->gold,enemy->exp);
        GameScene::controlLayer->logicFoeDet(GameScene::controlLayer->gameLayer->heroTarTilePos);  //特殊逻辑怪物的检测，一般用于开门
        GameScene::controlLayer->gameLayer->hero->isFighting = false;   //战斗结束
        if(GameScene::controlLayer->handle->touchDir!=e_stand)  //如果按键了的，继续移动
            GameScene::controlLayer->gameLayer->heroMove(GameScene::controlLayer->handle->touchDir);
    });
    auto seq = Sequence::create(delay,func, NULL);
    PlaySound(Audio::swordOver_e);
    this->runAction(seq);
}
void Sword::swordOverHeroDie()
{
    this->unschedule(schedule_selector(Sword::updateSword));
    this->setVisible(false);
    foePos_sp->removeAllChildrenWithCleanup(true);
    heroPos_sp->removeAllChildrenWithCleanup(true);
    nodePos->removeAllChildrenWithCleanup(true);

}
void Sword::onClickBut_exit(Ref* p)
{
    this->unschedule(schedule_selector(Sword::updateSword));
    this->setVisible(false);
    foePos_sp->removeAllChildrenWithCleanup(true);
    heroPos_sp->removeAllChildrenWithCleanup(true);
    nodePos->removeAllChildrenWithCleanup(true);
    GameScene::controlLayer->gameLayer->hero->isFighting = false;
}
Animation* Sword::getSwordAnimationByID(int ID)
{
    Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("sword%d",ID));
    if(animation==NULL)
    {
        AnimationCache::getInstance()->addAnimation(createSwordAnimationByID(ID),StringUtils::format("sword%d",ID));
    }
    return AnimationCache::getInstance()->getAnimation(StringUtils::format("sword%d",ID));
}
Animation* Sword::createSwordAnimationByID(int ID)
{
    //创建英雄的动画
    //Texture2D *heroTexture = Director::getInstance()->getTextureCache()->addImage("hero.png");
    int sub = 1;
//    auto size = Sprite::create(str)->getContentSize();
//    auto rect = Rect(Vec2(0,0),size);
    Vector<SpriteFrame*> swordFrames;
    while (1) {
        bool isHave = FileUtils::getInstance()->isFileExist(StringUtils::format("sword/atta%d_%d.png",ID,sub));
        if(isHave)
        {
            auto size = Sprite::create(StringUtils::format("sword/atta%d_%d.png",ID,sub))->getContentSize();
            auto rect = Rect(Vec2(0,0),size);
            SpriteFrame *frame = SpriteFrame::create(StringUtils::format("sword/atta%d_%d.png",ID,sub),rect);
            swordFrames.pushBack(frame);
            sub++;
        }
        else
        {
            Animation* animation = Animation::createWithSpriteFrames(swordFrames,0.025);
            return animation;
        }
    }
}
void Sword::showSwordAnimate(int ID,bool isHeroPos)   //显示打击动画
{
    auto swordAnima = Sprite::create();
    if(isHeroPos)
    {
        heroPos_sp->addChild(swordAnima);
        swordAnima->setPosition(hero->getPosition());
        swordAnima->setScale(2);
    }
    else
    {
        foePos_sp->addChild(swordAnima);
        swordAnima->setPosition(enemy->getPosition());
        swordAnima->setScale(2);
    }
    auto animate = Animate::create(getSwordAnimationByID(ID));
    auto func = CallFunc::create([=](){
        swordAnima->removeFromParent();
    });
    auto seq = Sequence::create(animate,func, NULL);
    swordAnima->runAction(seq);
}
void Sword::showLossBlood(int loss,bool isHeroPos)
{
    Label* loss_lab = Label::createWithSystemFont(StringUtils::format("%d",loss),"Verdana-Bold", 55);
    loss_lab->setColor(Color3B(220,20,60));
    if(isHeroPos)
    {
        heroPos_sp->addChild(loss_lab);
        loss_lab->setPosition(hero->getPosition());
    }
    else
    {
        foePos_sp->addChild(loss_lab);
        loss_lab->setPosition(enemy->getPosition());
    }
    auto jump = JumpBy::create(0.4, Vec2(80,-70), 100, 1);
    auto ease = EaseBounceOut::create(jump);
    auto dealy = DelayTime::create(0.1);
    auto func = CallFunc::create([=](){
        loss_lab->removeFromParent();
    });
    auto seq = Sequence::create(ease,dealy,func, NULL);
    loss_lab->runAction(seq);
}
void Sword::showMiss(bool isHeroPos)
{
    Label* miss_lab = Label::createWithSystemFont("MISS","Verdana-Bold",50);
    miss_lab->setColor(Color3B(220,20,60));
    if(isHeroPos)
    {
        heroPos_sp->addChild(miss_lab);
        miss_lab->setPosition(hero->getPosition());
    }
    else
    {
        foePos_sp->addChild(miss_lab);
        miss_lab->setPosition(enemy->getPosition());
    }
    auto move = MoveBy::create(0.3, Vec2(0,35));
    auto func = CallFunc::create([=](){
        miss_lab->removeFromParent();
    });
    auto seq = Sequence::create(move,func, NULL);
    miss_lab->runAction(seq);
}