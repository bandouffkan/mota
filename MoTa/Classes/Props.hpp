//
//  Props.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#ifndef Props_hpp
#define Props_hpp

#include "cocos2d.h"
#include "GameConstants.h"
USING_NS_CC;

class Props
{
public:
    static Props* instance;
    static Props * getInstance();
    void release();
    bool init();
    
    //得到对应的钥匙道具数量
    int getKey1Num();
    int getKey2Num();
    int getKey3Num();
    int getKeyNum(E_Door door_e);
    void redOneKeyNumByVar(E_Door door_e);    //减少钥匙
    int getPropByGid(int gid);
    void setPropByGid(int gid,int num);
    void addOnePropByGid(int gid,int num = 1);
    //得到物品的状态
    
    ValueMap props_map;
    
};

#endif /* Props_hpp */
