//
//  StairInfo.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#include "StairInfo.hpp"
#include "GameConstants.h"
ValueMap& StairInfo::getStoreyValueMap()
{
    stairInfo_map["wall"] = wallInfo_map;
    stairInfo_map["darkWall"] = darkWallInfo_map;
    stairInfo_map["enemy"] = enemyInfo_map;
    stairInfo_map["door"] = doorInfo_map;
    stairInfo_map["prop"] = propInfo_map;
    stairInfo_map["npc"] = npcInfo_map;
    stairInfo_map["special"] = specialInfo_map;
    if(stairInfo_map["upPos"]==Value::Null)
        stairInfo_map["upPos"] = "";
    return stairInfo_map;
}
void StairInfo::setUpPos(Vec2 pos)
{
    stairInfo_map["upPos"] = Vec2ToString(pos);
}