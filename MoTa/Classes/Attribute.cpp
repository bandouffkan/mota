//
//  Attribute.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#include "Attribute.hpp"
#include "GameConstants.h"

Attribute* Attribute::instance = NULL;
Attribute* Attribute::getInstance()
{
    if(instance == NULL)
    {
        instance = new Attribute();
        instance->init();
    }
    return instance;
}
void Attribute::release()
{
    if(instance != NULL)
    {
        delete instance;
        instance = NULL;
    }
}
bool Attribute::init()
{
    //改为valuemap后的初始化~
    attr_map["HP"] = 1000;      //血量
    attr_map["attack"] = 15;     //攻击力,原来是10
    attr_map["defense"] = 15;     //防御力，原来是5
    attr_map["agile"] = 2;  //敏捷
    attr_map["thump"] = 5;  //重击
    attr_map["attackTime"] = 1; //攻击次数
    attr_map["isPoison"] = false;   //中毒
    attr_map["isDebuff"] = false;   //虚弱
    attr_map["gold"] = 0;        //金币
    attr_map["exp"] = 0;
    attr_map["grade"] = 1;  //等级
    attr_map["stair"] = 0;       //楼梯值
    attr_map["position"] = "0,0";   //位置，用字符串表示
    attr_map["topFloor"] = 0;   //这储存着最高的楼层
    attr_map["minFloor"] = 0;
    attr_map["store1Price"] = 20;  //商店的卖价
    attr_map["useStore2"] = false;   //地下5层的商店是否使用
    
    //情景数据
    attr_map["firstGame"] = true;  //刚进游戏
    attr_map["downIsOpen"] = false;//地下层开启了，稿交给小偷了
    attr_map["20GZIsDie"] = false;//20层的假公主死了
    
    return true;
}

int Attribute::getHP()      //获得血
{
    return attr_map["HP"].asInt();
}
int Attribute::getAttack()   //获得攻击力
{
    return attr_map["attack"].asInt();
}
int Attribute::getDefense()  //获得防御力
{
    return attr_map["defense"].asInt();
}
short Attribute::getAgile()
{
    return attr_map["agile"].asInt();
}
short Attribute::getThump()
{
    return attr_map["thump"].asInt();
}
short Attribute::getAttackTime()
{
    return attr_map["attackTime"].asInt();
}
bool Attribute::getIsPoison()
{
    return attr_map["isPoison"].asBool();
}
bool Attribute::getIsDebuff()
{
    return attr_map["isDebuff"].asBool();
}
int Attribute::getGold()     //获得金币
{
    return attr_map["gold"].asInt();
}
int Attribute::getExp()    //得到经验值
{
    return attr_map["exp"].asInt();
}
int Attribute::getGrade()
{
    return attr_map["grade"].asInt();
}
int Attribute::getHeroStair() //获取勇士的楼层值
{
    return attr_map["stair"].asInt();
}
Vec2 Attribute::getHeroPos()  //获取勇士的位置
{
    std::string posStr = attr_map["position"].asString();
    return StringToVec2(posStr);
}
int Attribute::getTopFloor()  //得到到达楼层的最高值
{
    return attr_map["topFloor"].asInt();
}
int Attribute::getMinFloor()
{
    return attr_map["minFloor"].asInt();
}
int Attribute::getStore1Price()
{
    return attr_map["store1Price"].asInt();
}
bool Attribute::getIsUseStore2()
{
    return attr_map["useStore2"].asBool();
}
//增加属性
void Attribute::addAttack(int num)
{
    attr_map["attack"] = attr_map["attack"].asInt() + num;
}
void Attribute::addDefen(int num)
{
    attr_map["defense"] = attr_map["defense"].asInt() + num;
}
void Attribute::addAgile(int num)
{
    attr_map["agile"] = attr_map["agile"].asInt() + num;
}
void Attribute::addHP(int num)
{
    attr_map["HP"] = attr_map["HP"].asInt() + num;
}
void Attribute::addGold(int num)
{
    attr_map["gold"] = attr_map["gold"].asInt() + num;
}
void Attribute::addExp(int num)
{
    attr_map["exp"] = attr_map["exp"].asInt() + num;
}
void Attribute::addGrade(int num)
{
    attr_map["grade"] = attr_map["grade"].asInt() + num;
}
void Attribute::addStore1Price(int num)
{
    attr_map["store1Price"] = attr_map["store1Price"].asInt() + num;
}
//每种属性，有一个设置函数
void Attribute::setHP(int hp)
{
    attr_map["HP"] = hp;
}
void Attribute::setAttack(int atta)
{
    attr_map["attack"] = atta;
}
void Attribute::setDefense(int defen)
{
    attr_map["defense"] = defen;
}
void Attribute::setGold(int gold)
{
    attr_map["gold"] = gold;
}
void Attribute::setHeroStair(int stair) //设置勇士的楼层值
{
    attr_map["stair"] = stair;
}
void Attribute::setHeroPos(Vec2 pos)  //设置勇士的位置
{
    std::string strPos = Vec2ToString(pos);
    attr_map["position"] = strPos;
}
void Attribute::setTopFloor(int num)  //设置到达楼层的最高值
{
    attr_map["topFloor"] = num;
}
void Attribute::setMinFloor(int num)
{
    attr_map["minFloor"] = num;
}
void Attribute::setExp(int num)
{
    attr_map["exp"] = num;
}
void Attribute::setGrade(int num)
{
    attr_map["grade"] = num;
}
void Attribute::setIsUseStore2(bool bo)
{
    attr_map["useStore2"] = bo;
}
void Attribute::setStore1Price(int num)
{
    attr_map["store1Price"] = num;
}