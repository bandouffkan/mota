//
//  Sword.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/15.
//
//

#ifndef Sword_hpp
#define Sword_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Enemy.hpp"
#include "SwordHero.hpp"
USING_NS_CC;
using namespace ui;
class Sword : public Node
{
public:
    bool init();
    CREATE_FUNC(Sword);
    void updateSword(float dt);
    void updateSword1(float dt);
    void beginSword(int gid);
    void swordShow();
    void InitDataAndImage(int id);
    bool swordCalcIsWin(int gid);
    void swordOver();
    void swordOverHeroDie();
    void showSwordAnimate(int ID,bool isHeroPos);  //显示打击动画
    void showLossBlood(int loss, bool isHeroPos); //显示损血数字
    void showMiss(bool isHeroPos);  //显示miss
    
    void onClickBut_exit(Ref* p);
    Animation* getSwordAnimationByID(int ID);
    Animation* createSwordAnimationByID(int ID);
    
    Layout* fight_lay;
    Label* foeHP_lab;
    Label* foeAtta_lab;
    Label* foeDefe_lab;
    Label* foeAgile_lab;
    
    Label* heroHP_lab;
    Label* heroAtta_lab;
    Label* heroDefe_lab;
    Label* heroAgile_lab;
    
    Node* nodePos;
    Sprite* win_sp;
    Sprite* foePos_sp;
    Sprite* heroPos_sp;
    
    Enemy* enemy;
    SwordHero* hero;
    
    bool isHeroAtta;    //记录回合的变量
    
    //怪物的属性
    std::string foeName;
    int foeID;
    int foeHP;
    int foeAttack;
    int foeDefense;
    int foeGold;
    int fightNum;//战斗次数
};

#endif /* Sword_hpp */
