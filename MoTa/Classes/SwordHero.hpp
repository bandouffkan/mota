//
//  SwordHero.hpp
//  MoTa
//
//  Created by xcode31 on 16/7/4.
//
//

#ifndef SwordHero_hpp
#define SwordHero_hpp

#include "cocos2d.h"
#include "GameConstants.h"

USING_NS_CC;

class SwordHero : public Node
{
public:
    //初始化方法
    bool init();
    CREATE_FUNC(SwordHero);
    void attackFoe(Node* foe);
    
    //用于显示勇士形象的精灵
    Texture2D *heroTexture; //英雄的图片缓存
    Sprite* heroSprite;    //显示英雄的精灵
    
    int HP;
    int attack;
    int defense;
    short agile;    //敏捷
    short thump;    //重击
    short attackTime;   //攻击次数
    bool isPoison;  //是否中毒
    bool isDebuff;  //是否衰弱
    
    int attackCount;    //攻击次数计数
    
    bool isYongZhe; //是不是勇者
    
    bool baZheKill; //霸者秒杀
    bool baZheDefeAdd;//霸者防御增加
};

#endif /* SwordHero_hpp */
