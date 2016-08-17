//
//  Enemy.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "cocos2d.h"

USING_NS_CC;

class Enemy:public Node
{
public:
    bool init(int foeNum);
    static Enemy* create(int foeNum);
    void attackHero(Node* foe);
    void runAnimation();
    
    static Texture2D *foeTexture; //英雄的图片缓存
    Sprite* foeSprite;    //显示怪物的精灵
    
    //怪物的属性
    std::string name;
    int id;
    int HP;
    int attack;
    int defense;
    short agile;
    short thump;
    short attackTime;
    short virulence;
    short debuff;
    int gold;
    int exp;
    short attackTag;
    
    bool isWizard;//是否是魔法师，法师无事敌人的防御力
    
    int attackCount;    //攻击次数计数
};

#endif /* Enemy_hpp */
