//
//  NPC.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/28.
//
//

#include "NPC.hpp"

bool NPC::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    npcTexture = NULL;
    npcSprite = NULL;
    
    return true;
}
void NPC::initById(int id)
{
    npcId = id;
    //根据向下行走动画的第一帧创建精灵spriteWithSpriteFrame
    npcTexture = TextureCache::sharedTextureCache()->addImage("npc.png");
    npcSprite = Sprite::createWithTexture(npcTexture,Rect(32*1, 32*(npcId-1), 32, 32));
    
    //设置锚点
    npcSprite->setAnchorPoint(Point::ZERO);
    addChild(npcSprite);
    npcSprite->setPosition(0,0);
    
    runAnimation();
}
void NPC::runAnimation()
{
    SpriteFrame *frame0;
    SpriteFrame *frame1;
    if(npcId!=6 && npcId!=7)
    {
        frame0 = SpriteFrame::createWithTexture(npcTexture, Rect(32*0, 32*(npcId-1), 32, 32));
        frame1 = SpriteFrame::createWithTexture(npcTexture, Rect(32*2, 32*(npcId-1), 32, 32));
    }
    else
    {
        frame0 = SpriteFrame::createWithTexture(npcTexture, Rect(32*1, 32*(npcId-1), 32, 32));
        frame1 = SpriteFrame::createWithTexture(npcTexture, Rect(32*3, 32*(npcId-1), 32, 32));
    }
    
    Vector<SpriteFrame*> foeFrames;
    
    foeFrames.pushBack(frame0);
    foeFrames.pushBack(frame1);
    
    Animation* animation = Animation::createWithSpriteFrames(foeFrames, 0.2f);
    auto fore = RepeatForever::create(Animate::create(animation));
    npcSprite->runAction(fore);
}