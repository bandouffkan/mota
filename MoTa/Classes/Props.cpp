//
//  Props.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#include "Props.hpp"
Props* Props::instance = NULL;
Props* Props::getInstance()   //得到类实例
{
    if(instance == NULL)
    {
        instance = new Props();
        instance->init();
    }
    return instance;
}

void Props::release()
{
    if(instance != NULL)
    {
        delete instance;
        instance = NULL;
    }
}

bool Props::init()
{
    props_map["key1Num"] = 1;   //原来是5
    props_map["key2Num"] = 1;
    props_map["key3Num"] = 1;
    props_map["key5"] = 0;  //铁门的钥匙
    //物品栏的道具
    props_map["manual"] = 0;    //怪物手册
    props_map["flight"] = 0;    //飞行器
    props_map["draft"] = 0;     //稿
    props_map["draft2"] = 0;     //星稿
    props_map["potion2"] = 0;  //药水
    props_map["iceMagic"] = 0; //冰魔法
    props_map["cross"] = 0;    //十字架
    props_map["speDoor"] = 0;  //特殊门
    props_map["dagger"] = 0;   //神圣之证
    props_map["magicRune"] = 0; //魔法神符
    props_map["wand2"] = 0;   //勇者
    props_map["wand3"] = 0;   //霸者

    return true;
}

int Props::getKeyNum(E_Door door_e)   //根据门属性，返回对应的钥匙数量
{
    switch (door_e) {
        case e_door1:
            return props_map["key1Num"].asInt();
            break;
        case e_door2:
            return props_map["key2Num"].asInt();
            break;
        case e_door3:
            return props_map["key3Num"].asInt();
            break;
        default:
            return 0;
            break;
    }
}

void Props::redOneKeyNumByVar(E_Door door_e)
{
    switch (door_e) {
        case e_door1:
            props_map["key1Num"] = props_map["key1Num"].asInt()-1;
            break;
        case e_door2:
            props_map["key2Num"] = props_map["key2Num"].asInt()-1;
            break;
        case e_door3:
            props_map["key3Num"] = props_map["key3Num"].asInt()-1;
            break;
        case e_door5:
            props_map["key5"] = props_map["key5"].asInt()-1;
            break;
        default:
            break;
    }
}
int Props::getPropByGid(int gid)
{
    switch (gid) {
        case e_key5:
            return props_map["key5"].asInt();
            break;
        case e_manual:
            return props_map["manual"].asInt();
            break;
        case e_draft:
            return props_map["draft"].asInt();
            break;
        case e_draft2:
            return props_map["draft2"].asInt();
            break;
        case e_iceMagic:
            return props_map["iceMagic"].asInt();
            break;
        case e_flightDown:
            return props_map["flight"].asInt();
            break;
        case e_cross:
            return props_map["cross"].asInt();
            break;
        case e_speDoor:
            return props_map["speDoor"].asInt();
            break;
        case e_dagger:
            return props_map["dagger"].asInt(); //神圣之证
            break;
        case e_magicRune:
            return props_map["e_magicRune"].asInt();
            break;
        case e_wand2:
            return props_map["wand2"].asInt();
            break;
        case e_wand3:
            return props_map["wand3"].asInt();
            break;
        default:
            return 0;
            break;
    }
}
void Props::setPropByGid(int gid,int num)
{
    switch (gid) {
        case e_key5:
            props_map["key5"] = num;
            break;
        case e_draft:
            props_map["draft"] = num;
            break;
        case e_draft2:
            props_map["draft2"] = num;
            break;
        case e_iceMagic:
            props_map["iceMagic"] = num;
            break;
        case e_cross:
            props_map["cross"] = num;
            break;
        case e_speDoor:
            props_map["speDoor"] = num;
            break;
        case e_dagger:
            props_map["dagger"] = num; //神圣之证
            break;
        case e_magicRune:
            props_map["e_magicRune"] = num;
            break;
        case e_wand2:
            props_map["wand2"] = num;
            break;
        case e_wand3:
            props_map["wand3"] = num;
            break;
        default:
            return;
            break;
    }
}
void Props::addOnePropByGid(int gid,int num)
{
    switch (gid) {
        case e_key5:
            props_map["key5"] = props_map["key5"].asInt() + num;
            break;
        case e_draft:
            props_map["draft"] = props_map["draft"].asInt()+ num;
            break;
        case e_draft2:
            props_map["draft2"] = props_map["draft2"].asInt()+num;
            break;
        case e_iceMagic:
            props_map["iceMagic"] = props_map["iceMagic"].asInt()+num;
            break;
        case e_cross:
            props_map["cross"] = props_map["draft2"].asInt()+num;
            break;
        case e_speDoor:
            props_map["speDoor"] = props_map["speDoor"].asInt()+num;
            break;
        case e_dagger:
            props_map["dagger"] = props_map["dagger"].asInt()+num; //神圣之证
            break;
        case e_wand2:
            props_map["wand2"] = props_map["wand2"].asInt()+num;
            break;
        case e_wand3:
            props_map["wand3"] = props_map["wand3"].asInt()+num;
            break;
        default:
            return;
            break;
    }
}
//得到钥匙的状态
int Props::getKey1Num()
{
    return props_map["key1Num"].asInt();
}
int Props::getKey2Num()
{
    return props_map["key2Num"].asInt();
}
int Props::getKey3Num()
{
    return props_map["key3Num"].asInt();
}