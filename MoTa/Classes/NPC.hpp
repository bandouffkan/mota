//
//  NPC.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/28.
//
//

#ifndef NPC_hpp
#define NPC_hpp

#include "cocos2d.h"
USING_NS_CC;

class NPC : public Node
{
public:
    bool init();
    CREATE_FUNC(NPC);
    void initById(int id);
    void runAnimation();
    
    Texture2D* npcTexture; //英雄的图片缓存
    Sprite* npcSprite;    //显示怪物的精灵
    int npcId;
};

#endif /* NPC_hpp */
