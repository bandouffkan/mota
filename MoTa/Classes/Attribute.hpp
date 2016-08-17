//
//  Attribute.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#ifndef Attribute_hpp
#define Attribute_hpp

#include "cocos2d.h"
USING_NS_CC;

class Attribute
{
public:
    static Attribute* instance;
    static Attribute* getInstance();
    void release();
    bool init();
    ValueMap attr_map;
    
    //每种属性，有一个获取函数
    int getHP();
    int getAttack();
    int getDefense();
    short getAgile();
    short getThump();
    short getAttackTime();
    bool getIsPoison();
    bool getIsDebuff();
    int getGold();
    int getExp();    //得到经验值
    int getGrade();     //得到等级
    int getHeroStair(); //获取勇士的楼层值
    Vec2 getHeroPos();  //获取勇士的位置
    int getTopFloor();  //得到到达楼层的最高值
    int getMinFloor(); //得到到达的最低楼层
    int getStore1Price();    //得到商店价格
    bool getIsUseStore2();
    
    void addAttack(int num);   //增加攻击
    void addDefen(int num);    //增加防御
    void addAgile(int num);
    void addHP(int num);    //增加血量
    void addGold(int num);
    void addExp(int num);
    void addGrade(int num);
    void addStore1Price(int num);
    
    //每种属性，有一个设置函数
    void setHP(int hp);
    void setAttack(int atta);
    void setDefense(int defen);
    void setGold(int gold);
    void setExp(int num);
    void setGrade(int num);
    void setHeroStair(int stairNum); //设置勇士的楼层值
    void setHeroPos(Vec2 pos);  //设置勇士的位置
    void setTopFloor(int num);  //设置到达楼层的最高值
    void setMinFloor(int num);
    void setIsUseStore2(bool bo);
    void setStore1Price(int num);
};

#endif /* Attribute_hpp */
