//
//  InfoStored.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#ifndef InfoStored_hpp
#define InfoStored_hpp

#include "cocos2d.h"
USING_NS_CC;
class Archive
{
public:
    static Archive* instance;
    static Archive * getInstance();
    void release();
    void saveArchive(); //储存到valuemap中
    
    ValueMap archive_map;//总存档
    ValueMap stairsInfo_map;     //楼层信息存储的map
    ValueMap attr_map;      //英雄信息存储的map
    ValueMap props_map;     //英雄会有道具，这是道具的存储map
    ValueMap scene_map;     //场景记忆存储
    
    bool stairInfoIsNull(int stairNum); //判断一层的信息是不是空的，表示第一次来本层
    
    void setStairInfo_map(ValueMap& map,int stairNum);  //设置一层的信息，存起来，参数有层号
    void setStairInfo_map(int stairNum); //设置一层信息，只有楼层值，用来初始化而已
    
    //得到楼层相关的map
    ValueMap& getStairWall_map(int stairNum);   //楼层的wall层信息map
    ValueMap& getStairDarkWall_map(int stairNum);  //暗墙楼层的信息map
    ValueMap& getStairEnemy_map(int stairNum);   //楼层的enemy层信息map
    ValueMap& getStairDoor_map(int stairNum);   //楼层的door层信息map
    ValueMap& getStairProp_map(int stairNum);   //楼层的prop层信息map
    ValueMap& getStairNpc_map(int stairNum);   //楼层的npc层信息map
    ValueMap& getStairSpecial_map(int stairNum);
    Vec2 getUpPos(int stairNum);    //得到上楼梯时的出现位置
    Vec2 getDownPos(int stairNum);  //得到下楼梯时的出现位置
    
    //设置楼层相关的map,参数是坐标，属性值，楼层值
    void setStairWall_map(Vec2 pos,int stateNum,int stairNum);  //设置楼层的wall层信息map
    void setStairDarkWall_map(Vec2 pos,int stateNum,int stairNum);  //设置暗墙楼层的wall层信息map
    void setStairEnemy_map(Vec2 pos,int stateNum,int stairNum); //设置楼层的enemy层信息map
    void setStairDoor_map(Vec2 pos,int stateNum,int stairNum);  //设置楼层的door层信息map
    void setStairProp_map(Vec2 pos,int stateNum,int stairNum);  //设置楼层的prop层信息map
    void setStairNpc_map(Vec2 pos,int stateNum,int stairNum);   //设置楼层的npc层信息map
    void setStairSpecial_map(Vec2 pos,int stateNum,int stairNum);   //设置特殊层信息map
    void setStairSpecialIsShow(int stateNum,int stairNum);   //设置特殊层是否显示，其实是用坐标11，11位置的值来代表是否显示，1表示显示，0表示不显示
    int getStairNpc_state(Vec2 pos,int stairNum);    //得到楼层npc层信息的值
    int getStairSpecialIsShow(int stairNum);    //得到楼层值特殊层是否显示
};

#endif /* InfoStored_hpp */
