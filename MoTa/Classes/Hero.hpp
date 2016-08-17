//
//  Hero.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/13.
//
//

#ifndef Hero_hpp
#define Hero_hpp

#include "cocos2d.h"
#include "GameConstants.h"
USING_NS_CC;

class Hero : public Node
{
public:
    //初始化方法
    bool init();
    CREATE_FUNC(Hero);
    void setHeroDir(E_HeroDir dir);//设置勇士的朝向和目标点
    void addMoveFrameNum();
    void changeSkin(int skin);  //改变皮肤
    
    //用于显示勇士形象的精灵
    Texture2D *heroTexture; //英雄的图片缓存
    Sprite* heroSprite;    //显示英雄的精灵
    int skin;
    
    E_HeroDir heroDir;
    
    short moveFrameNum;//移动时的帧计数，0到3
    bool isMoving;  //在移动
    bool isFighting;    //在战斗
    bool isDialog;  //在对话中
};

#endif /* Hero_hpp */
