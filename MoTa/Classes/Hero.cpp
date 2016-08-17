//
//  Hero.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/13.
//
//

#include "Hero.hpp"
#include "Props.hpp"
bool Hero::init()
{
    if (!Node::init())
    {
        return false;
    }
    moveFrameNum = 1;
    isMoving = false;
    isFighting = false;
    isDialog = false;
    heroDir = e_down;
    
    //根据向下行走动画的第一帧创建精灵spriteWithSpriteFrame
    if(Props::getInstance()->getPropByGid(e_wand2)>0)
    {
        heroTexture = TextureCache::sharedTextureCache()->addImage("hero2.png");
        skin = 2;
    }
    else if(Props::getInstance()->getPropByGid(e_wand3)>0)
    {
        heroTexture = TextureCache::sharedTextureCache()->addImage("hero3.png");
        skin = 3;
    }
    else
    {
        heroTexture = TextureCache::sharedTextureCache()->addImage("hero.png");
        skin = 0;
    }
    
    heroSprite = Sprite::createWithTexture(heroTexture,Rect(TITL_SIZE*0, TITL_SIZE*0, TITL_SIZE, TITL_SIZE));
    
    //设置锚点
    heroSprite->setAnchorPoint(Point::ZERO);
    
    //将用于显示的heroSprite加到自己的节点下
    this->addChild(heroSprite);    
    return true;
}
void Hero::setHeroDir(E_HeroDir dir)
{
    heroDir = dir;
    //getMoveVec(dir);
    heroSprite->setTextureRect(cocos2d::Rect(0, TITL_SIZE*dir, TITL_SIZE, TITL_SIZE));  //设置朝向
}
void Hero::addMoveFrameNum()
{
    moveFrameNum++;
    if(moveFrameNum>=3)
        moveFrameNum = 0;
    heroSprite->setTextureRect(cocos2d::Rect(TITL_SIZE*moveFrameNum, TITL_SIZE*heroDir, TITL_SIZE, TITL_SIZE));
}
void Hero::changeSkin(int skin)
{
    std::string str;
    if(skin==0)
    {
        str = "hero.png";
    }
    else if(skin==2)
    {
        str = "hero2.png";
    }
    else if(skin==3)
    {
        str = "hero3.png";
    }
    heroTexture = TextureCache::sharedTextureCache()->addImage(str);
    heroSprite->setTexture(heroTexture);
    this->skin = skin;
}