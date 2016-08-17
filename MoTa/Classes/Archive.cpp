//
//  InfoStored.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#include "Archive.hpp"
#include "GameConstants.h"
#include "StairInfo.hpp"
Archive* Archive::instance = NULL;
Archive* Archive::getInstance()
{
    if(instance == NULL)
    {
        instance = new Archive();
        //instance->init();
    }
    return instance;
}
void Archive::release()
{
    if(instance != NULL)
    {
        delete instance;
        instance = NULL;
    }
}
void Archive::saveArchive() //储存到valuemap中
{
//    archive_map["attr"] = attr_map;
//    archive_map["props"] = props_map;
    archive_map["stairsInfo"] = stairsInfo_map;
    archive_map["scenario"] = scene_map;
}
bool Archive::stairInfoIsNull(int stairNum) //判断一层的信息是不是空的，表示第一次来本层
{
    if( stairsInfo_map[StringUtils::format("%d",stairNum).c_str()] == Value::Null )
        return true;
    else
        return false;
}
void Archive::setStairInfo_map(ValueMap& map,int stairNum)
{
    stairsInfo_map[StringUtils::format("%d",stairNum)] = map;
}
void Archive::setStairInfo_map(int stairNum)  //设置一层信息，只有楼层值，就是初始化而已
{
    StairInfo stairInfo;
    setStairInfo_map(stairInfo.getStoreyValueMap(),stairNum);
}
ValueMap& Archive::getStairWall_map(int stairNum)
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    return stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["wall"].asValueMap();
}
ValueMap& Archive::getStairDarkWall_map(int stairNum)
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    return stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["darkWall"].asValueMap();
}
ValueMap& Archive::getStairEnemy_map(int stairNum)   //楼层的enemy层信息map
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    return stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["enemy"].asValueMap();
}
ValueMap& Archive::getStairDoor_map(int stairNum)   //楼层的door层信息map
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    return stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["door"].asValueMap();
}
ValueMap& Archive::getStairProp_map(int stairNum)   //楼层的prop层信息map
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    return stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["prop"].asValueMap();
}
ValueMap& Archive::getStairNpc_map(int stairNum)   //楼层的npc层信息map
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    return stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["npc"].asValueMap();
}
ValueMap& Archive::getStairSpecial_map(int stairNum)
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    return stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["special"].asValueMap();
}
int Archive::getStairNpc_state(Vec2 pos,int stairNum)
{
    if(!stairInfoIsNull(stairNum))
    {
        return stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["npc"].asValueMap()[Vec2ToString(pos)].asInt();
    }
    return 0;
}
int Archive::getStairSpecialIsShow(int stairNum)    //得到楼层值特殊层是否显示
{
    if(!stairInfoIsNull(stairNum))
        return stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["special"].asValueMap()[Vec2ToString(Vec2(11,11))].asInt();
    return 0;
}
Vec2 Archive::getUpPos(int stairNum)    //得到上楼梯时的出现位置
{
    if(stairInfoIsNull(stairNum))
    {
        log("xx21");
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    std::string str = stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["upPos"].asString();
    log("str:%s",str.c_str());
    return StringToVec2(str);
}
Vec2 Archive::getDownPos(int stairNum)  //得到下楼梯时的出现位置
{
    if(stairNum>=0)
    {
        stairNum++;
    }
    else
    {
        stairNum--;
    }
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    std::string str = stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["upPos"].asString();
    return StringToVec2(str);
}
//设置楼层相关的map
void Archive::setStairWall_map(Vec2 pos,int stateNum,int stairNum)
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    std::string strPos = Vec2ToString(pos);
    stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["wall"].asValueMap()[strPos] = stateNum;
}
void Archive::setStairDarkWall_map(Vec2 pos,int stateNum,int stairNum)
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    std::string strPos = Vec2ToString(pos);
    stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["darkWall"].asValueMap()[strPos] = stateNum;
}
void Archive::setStairEnemy_map(Vec2 pos,int stateNum,int stairNum)
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    std::string strPos = Vec2ToString(pos);
    stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["enemy"].asValueMap()[strPos] = stateNum;
}
void Archive::setStairDoor_map(Vec2 pos,int stateNum,int stairNum)
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    std::string strPos = Vec2ToString(pos);
    stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["door"].asValueMap()[strPos] = stateNum;
}
void Archive::setStairProp_map(Vec2 pos,int stateNum,int stairNum)
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    std::string strPos = Vec2ToString(pos);
    stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["prop"].asValueMap()[strPos] = stateNum;
}
void Archive::setStairNpc_map(Vec2 pos,int stateNum,int stairNum)
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    std::string strPos = Vec2ToString(pos);
    stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["npc"].asValueMap()[strPos.c_str()] = stateNum;
}
void Archive::setStairSpecial_map(Vec2 pos,int stateNum,int stairNum)
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    std::string strPos = Vec2ToString(pos);
    stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["special"].asValueMap()[strPos.c_str()] = stateNum;
}
void Archive::setStairSpecialIsShow(int stateNum,int stairNum)   //设置特殊层是否显示，其实是用坐标11，11位置的值来代表是否显示，1表示显示，0表示不显示
{
    if(stairInfoIsNull(stairNum))
    {
        setStairInfo_map(stairNum); //初始化这层，存个没数据的ValueMap
    }
    stairsInfo_map[StringUtils::format("%d",stairNum)].asValueMap()["special"].asValueMap()[Vec2ToString(Vec2(11,11))] = 1;
}
