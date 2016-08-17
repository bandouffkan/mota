//
//  AnimationManager.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#include "AnimationManager.hpp"
AnimationManager* AnimationManager::instance = NULL;
AnimationManager* AnimationManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new AnimationManager();
        instance->init();
    }
    return instance;
}
void AnimationManager::release()
{
    if(instance != NULL)
    {
        delete instance;
        instance = NULL;
    }
}
bool AnimationManager::init()
{
    heroStepTime = 0.12;
    createRetWallAnimation();
    createHeroAnimation();
    createDoorAnimation();
    return true;
}
void AnimationManager::createHeroAnimation()    //创建英雄动画
{
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_down,0), "down");
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_left,0), "left");
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_right,0), "right");
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_up,0), "up");
    
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_down,2), "down2");
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_left,2), "left2");
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_right,2), "right2");
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_up,2), "up2");
    
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_down,3), "down3");
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_left,3), "left3");
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_right,3), "right3");
    AnimationCache::getInstance()->addAnimation(createHeroAnimationByDir(e_up,3), "up3");
}
void AnimationManager::createDoorAnimation()  //创建门的动画
{
    AnimationCache::getInstance()->addAnimation(createDoorAnimationByVar(e_door1), "door1");
    AnimationCache::getInstance()->addAnimation(createDoorAnimationByVar(e_door2), "door2");
    AnimationCache::getInstance()->addAnimation(createDoorAnimationByVar(e_door3), "door3");
    AnimationCache::getInstance()->addAnimation(createDoorAnimationByVar(e_door4), "door4");
    AnimationCache::getInstance()->addAnimation(createDoor4ShowAnimation(), "door4Show");
    AnimationCache::getInstance()->addAnimation(createSteelDoorAnimation(), "steelDoor");
}
void AnimationManager::createRetWallAnimation() //创建暗墙的动画
{
    AnimationCache::getInstance()->addAnimation(createWallAnimation(),"retWall");
}
//***********
Animation* AnimationManager::createWallAnimation()
{
    Texture2D *retWallTexture = Director::getInstance()->getTextureCache()->addImage("RetWall.png");
    SpriteFrame *frame0 = SpriteFrame::createWithTexture(retWallTexture, Rect(0, 0, 32, 32));
    SpriteFrame *frame1 = SpriteFrame::createWithTexture(retWallTexture, Rect(0, 32, 32, 32));
    SpriteFrame *frame2 = SpriteFrame::createWithTexture(retWallTexture, Rect(0, 64, 32, 32));
    SpriteFrame *frame3 = SpriteFrame::createWithTexture(retWallTexture, Rect(0, 96, 32, 32));
    SpriteFrame *frame4 = SpriteFrame::createWithTexture(retWallTexture, Rect(0, 128, 32, 32));
    
    Vector<SpriteFrame*> retWallFrames;
    
    retWallFrames.pushBack(frame0);
    retWallFrames.pushBack(frame1);
    retWallFrames.pushBack(frame2);
    retWallFrames.pushBack(frame3);
    retWallFrames.pushBack(frame4);
    
    Animation* animation = Animation::createWithSpriteFrames(retWallFrames, 0.1f);
    return animation;
}
Animation* AnimationManager::createHeroAnimationByDir(E_HeroDir dir_e,int skin)   //根据方向创建英雄的移动动画
{
    //创建英雄的动画
    Texture2D *heroTexture;
    if(skin==0)
        heroTexture = Director::getInstance()->getTextureCache()->addImage("hero.png");
    else if(skin==2)
        heroTexture = Director::getInstance()->getTextureCache()->addImage("hero2.png");
    else if(skin==3)
        heroTexture = Director::getInstance()->getTextureCache()->addImage("hero3.png");
    //第二个参数表示显示区域的x, y, width, height，根据direction来确定显示的y坐标
    SpriteFrame *frame0 = SpriteFrame::createWithTexture(heroTexture, Rect(32*0, 32*dir_e, 32, 32));
    SpriteFrame *frame1 = SpriteFrame::createWithTexture(heroTexture, Rect(32*1, 32*dir_e, 32, 32));
    SpriteFrame *frame2 = SpriteFrame::createWithTexture(heroTexture, Rect(32*2, 32*dir_e, 32, 32));
    SpriteFrame *frame3 = SpriteFrame::createWithTexture(heroTexture, Rect(32*3, 32*dir_e, 32, 32));
    
    Vector<SpriteFrame*> heroFrames;
    
    heroFrames.pushBack(frame0);
    heroFrames.pushBack(frame1);
    heroFrames.pushBack(frame2);
    heroFrames.pushBack(frame3);
    
    Animation* animation = Animation::createWithSpriteFrames(heroFrames, heroStepTime/4);//4变2
    
    return animation;
}
Animation* AnimationManager::createDoorAnimationByVar(E_Door door_e)
{
    int var;
    switch (door_e) {
        case e_door1:
            var = 0;
            break;
        case e_door2:
            var = 1;
            break;
        case e_door3:
            var = 2;
            break;
        case e_door4:
            var = 3;
            break;
        default:
            var = 4;
            break;
    }
    
    Texture2D *doorTexture = Director::getInstance()->getTextureCache()->addImage("door.png");
    SpriteFrame *frame0 = SpriteFrame::createWithTexture(doorTexture, Rect(32*var, 32*0, 32, 32));
    SpriteFrame *frame1 = SpriteFrame::createWithTexture(doorTexture, Rect(32*var, 32*1, 32, 32));
    SpriteFrame *frame2 = SpriteFrame::createWithTexture(doorTexture, Rect(32*var, 32*2, 32, 32));
    SpriteFrame *frame3 = SpriteFrame::createWithTexture(doorTexture, Rect(32*var, 32*3, 32, 32));
    SpriteFrame *frame4 = SpriteFrame::createWithTexture(doorTexture, Rect(32 * 0, 32*7, 32, 32));
    Vector<SpriteFrame*> doorFrames;
    
    doorFrames.pushBack(frame0);
    doorFrames.pushBack(frame1);
    doorFrames.pushBack(frame2);
    doorFrames.pushBack(frame3);
    doorFrames.pushBack(frame4);
    
    Animation* animation = Animation::createWithSpriteFrames(doorFrames, 0.1f);
    
    return animation;
}
Animation* AnimationManager::createDoor4ShowAnimation()
{
    Texture2D *doorTexture = Director::getInstance()->getTextureCache()->addImage("door.png");
    SpriteFrame *frame0 = SpriteFrame::createWithTexture(doorTexture, Rect(32*3, 32*3, 32, 32));
    SpriteFrame *frame1 = SpriteFrame::createWithTexture(doorTexture, Rect(32*3, 32*2, 32, 32));
    SpriteFrame *frame2 = SpriteFrame::createWithTexture(doorTexture, Rect(32*3, 32*1, 32, 32));
    SpriteFrame *frame3 = SpriteFrame::createWithTexture(doorTexture, Rect(32*3, 32*0, 32, 32));
    Vector<SpriteFrame*> doorFrames;
    
    doorFrames.pushBack(frame0);
    doorFrames.pushBack(frame1);
    doorFrames.pushBack(frame2);
    doorFrames.pushBack(frame3);
    
    Animation* animation = Animation::createWithSpriteFrames(doorFrames, 0.1f);
    
    return animation;
}
Animation* AnimationManager::createSteelDoorAnimation()
{
    Texture2D *doorTexture = Director::getInstance()->getTextureCache()->addImage("door.png");
    SpriteFrame *frame0 = SpriteFrame::createWithTexture(doorTexture, Rect(32*0, 32*5, 32, 32));
    SpriteFrame *frame1 = SpriteFrame::createWithTexture(doorTexture, Rect(32*1, 32*5, 32, 32));
    SpriteFrame *frame2 = SpriteFrame::createWithTexture(doorTexture, Rect(32*2, 32*5, 32, 32));
    SpriteFrame *frame3 = SpriteFrame::createWithTexture(doorTexture, Rect(32*3, 32*5, 32, 32));
    SpriteFrame *frame4 = SpriteFrame::createWithTexture(doorTexture, Rect(32*0, 32*7, 32, 32));
    Vector<SpriteFrame*> doorFrames;
    
    doorFrames.pushBack(frame0);
    doorFrames.pushBack(frame1);
    doorFrames.pushBack(frame2);
    doorFrames.pushBack(frame3);
    doorFrames.pushBack(frame4);
    
    Animation* animation = Animation::createWithSpriteFrames(doorFrames, 0.1f);
    
    return animation;
}
//*******
Animation* AnimationManager::getHeroAnimationByDir(E_HeroDir dir_e,int skin)  //根据方向得到英雄动画
{
    if(skin==0)
    {
        switch (dir_e) {
            case e_down:
                return AnimationCache::getInstance()->getAnimation("down");
                break;
            case e_left:
                return AnimationCache::getInstance()->getAnimation("left");
                break;
            case e_right:
                return AnimationCache::getInstance()->getAnimation("right");
                break;
            case e_up:
                return AnimationCache::getInstance()->getAnimation("up");
                break;
            default:
                return NULL;
                break;
        }
    }
    else if(skin==2)
    {
        switch (dir_e) {
            case e_down:
                return AnimationCache::getInstance()->getAnimation("down2");
                break;
            case e_left:
                return AnimationCache::getInstance()->getAnimation("left2");
                break;
            case e_right:
                return AnimationCache::getInstance()->getAnimation("right2");
                break;
            case e_up:
                return AnimationCache::getInstance()->getAnimation("up2");
                break;
            default:
                return NULL;
                break;
        }
    }
    else if(skin==3)
    {
        switch (dir_e) {
            case e_down:
                return AnimationCache::getInstance()->getAnimation("down3");
                break;
            case e_left:
                return AnimationCache::getInstance()->getAnimation("left3");
                break;
            case e_right:
                return AnimationCache::getInstance()->getAnimation("right3");
                break;
            case e_up:
                return AnimationCache::getInstance()->getAnimation("up3");
                break;
            default:
                return NULL;
                break;
        }
    }
}
Animation* AnimationManager::getDoorAnimationByDir(E_Door door_e)  //根据门种类得到门动画
{
    switch (door_e) {
        case e_door1:
            return AnimationCache::getInstance()->getAnimation("door1");
            break;
        case e_door2:
            return AnimationCache::getInstance()->getAnimation("door2");
            break;
        case e_door3:
            return AnimationCache::getInstance()->getAnimation("door3");
            break;
        case e_door4:
            return AnimationCache::getInstance()->getAnimation("door4");
            break;
        case e_steelDoor:
            return AnimationCache::getInstance()->getAnimation("steelDoor");
            break;
        case e_door5:
            return AnimationCache::getInstance()->getAnimation("steelDoor");
            break;
        default:
            return NULL;
            break;
    }
}
Animation* AnimationManager::getDoor4ShowAnimation()
{
    return AnimationCache::getInstance()->getAnimation("door4Show");
}
Animation* AnimationManager::getRetWallAnimation()    //得到墙的动画
{
    return AnimationCache::getInstance()->getAnimation("retWall");
}
