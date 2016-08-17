//
//  StairInfo.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#ifndef StairInfo_hpp
#define StairInfo_hpp

#include "cocos2d.h"
USING_NS_CC;

class StairInfo    //层信息类
{
public:
    ValueMap& getStoreyValueMap();
    void setUpPos(Vec2 pos);    //存储上下楼时的位置
    ValueMap stairInfo_map; //塔层信息，valuemap，本类总的信息储存类
    //以下的各类信息map,对应地图的每种层
    ValueMap wallInfo_map;  //墙层
    ValueMap darkWallInfo_map;  //暗墙层
    ValueMap enemyInfo_map; //敌人层
    ValueMap doorInfo_map;  //门层
    ValueMap propInfo_map;  //物品层
    ValueMap npcInfo_map;   //npc层
    ValueMap specialInfo_map;  //特殊层
};

#endif /* StairInfo_hpp */
