//
//  AnimationManager.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#ifndef AnimationManager_hpp
#define AnimationManager_hpp

#include "cocos2d.h"
#include "GameConstants.h"
USING_NS_CC;
class AnimationManager
{
public:
    static AnimationManager* instance;
    static AnimationManager * getInstance();
    //释放类的唯一实例
    void release();
    bool init();    //初始化
    
    void createHeroAnimation(); //创建英雄的行走动画
    void createDoorAnimation(); //创建门的动画
    //void createSwordAnimation(); //创建战斗的效果动画
    void createRetWallAnimation(); //创建暗墙的动画
    
    Animation* getHeroAnimationByDir(E_HeroDir dir_e,int skin);  //根据方向得到英雄动画
    Animation* getDoorAnimationByDir(E_Door door_e);  //根据门种类得到门动画
    Animation* getDoor4ShowAnimation(); //得到4号没出现的动画
    //Animation* getSwordAnimation(int id); //等到战斗动画
    Animation* getRetWallAnimation();    //得到墙的动画
    
    float heroStepTime;//勇士一步的时间
private:
    //动画的创建
    Animation* createHeroAnimationByDir(E_HeroDir dir_e,int skin);   //根据方向创建英雄的移动动画
    Animation* createDoorAnimationByVar(E_Door door_e);
    Animation* createDoor4ShowAnimation();  //这是门4的关门动画
    //Animation* createSwordAnimationByID(int id);   //设计了4中战斗一次的动画，id从0到3
    Animation* createSteelDoorAnimation();
    Animation* createWallAnimation();
};

#endif /* AnimationManager_hpp */
