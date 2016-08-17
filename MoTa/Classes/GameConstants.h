//
//  GameConstants.h
//  MoTa
//
//  Created by xcode31 on 16/6/13.
//
//

#ifndef GameConstants_h
#define GameConstants_h
#include "cocos2d.h"
USING_NS_CC;

#define VISIBSIZE Director::getInstance()->getVisibleSize()
#define GETADS_NO UserDefault::getInstance()->getBoolForKey("adsNo",false)
#define TMX_MAXSCALE 3.068
#define TITL_SIZE 32
#define TILE_MAPSIZE 11
#define ENEMY_PICNUM 4   //怪物的动画数
typedef enum
{
    e_down =  0,//向下方向
    e_left = 1,//向左方向
    e_right= 2,//向右方向
    e_up = 3,//向上方向
    e_stand = 4,
} E_HeroDir;//勇士方向

enum E_terrain
{
    e_floor1 = 1,
    e_floorMagma1 = 5,
    e_floorMagma2 = 6,
    e_floorFire1 = 7,
    e_floorFire2 = 8,
    e_floorStar1 = 9,
    e_floorStar2 = 10,
    e_floor2 = 13,
};

typedef enum
{
    e_door1 = 273,   //以前的259
    e_door2 = 274,
    e_door3 = 275,
    e_door4 = 276,
    e_doorUp = 289,
    e_doorDown = 290,
    e_door5 = 291,  //封堵的铁门，要钥匙才能打开
    e_steelDoor = 293,   //可以开的铁门
    e_doorUp2 = 297,
    e_doorDown2 = 298,
} E_Door;

typedef enum    //道具的枚举值，包含所有道具
{
    //291是道具第一个,后变成297第一个
    e_attGem = 305,
    e_defGem = 306,
    e_agile = 307,
    e_HPBot1 = 309,
    e_HPBot2 = 310,
    e_potion1 = 313,
    e_potion2 = 314,
    e_potion = 320, //药剂
    e_key1 = 321,
    e_key2 ,
    e_key3 ,
    e_key5 ,
    e_bigKey1 = 327, //大黄钥匙
    e_manual = 333,  //怪物手册
    e_notebook = 334,    //笔记
    e_coin = 336,  //钱币
    e_draft = 337,   //稿
    e_draft2 = 338,   //星光神锒
    e_iceMagic = 339,    //冰魔法道具
    e_flight = 341,  //小飞羽
    e_flightDown = 342,   //楼层飞行器下
    e_flightBig = 343, //大飞羽
    e_cross = 344,   //十字架
    e_bombFoe = 345,    //墙炸弹
    e_speDoor = 346, //任意门
    e_dagger = 347,  //神剑之证
    e_teleport = 349,  //相位移动
    e_magicRune = 351, //魔法神符
    e_sword1 = 353,  //剑1
    e_sword2 = 354,  //剑2
    e_sword3 = 355,  //剑3
    e_sword4 = 356,  //剑4
    e_sword5 = 357,  //剑5
    e_shield1 = 361, //盾1
    e_shield2 = 362,  //盾2
    e_shield3 = 363,  //盾3
    e_shield4 = 364,  //盾4
    e_shield5 =365,  //盾5
    e_wand1 = 366,   //灵杖1
    e_wand2 = 367,   //霸者
    e_wand3 = 368,   //勇者
} E_Prop;

typedef enum    //NPC的枚举值，包含所有NPC
{
    e_NPC1 = 369,    //371
    e_NPC2 = 373,
    e_NPC3 = 377,
    e_NPC4 = 381,
    e_NPC5 = 385,
    e_NPCStore1 = 390,
    e_NPCStore2 = 394,
} E_NPC;

static Vec2 getMoveVec(E_HeroDir dir)
{
    Vec2 moveVec(0,0);
    switch (dir)
    {
        case e_down:
            moveVec = Vec2(0,1);
            break;
        case e_left:
            moveVec = Vec2(-1,0);
            break;
        case e_right:
            moveVec = Vec2(1,0);
            break;
        case e_up:
            moveVec = Vec2(0,-1);
            break;
        default:
            break;
    }
    return moveVec;
}
static cocos2d::Size getAdsVisibleSize() //得到可视区域
{
    if(UserDefault::getInstance()->getBoolForKey("adsNo",false)==false)
    {
        cocos2d::Size vis_size;
        vis_size.width = Director::getInstance()->getVisibleSize().width;
        vis_size.height = Director::getInstance()->getVisibleSize().height + 164;
        return vis_size;
    }
    else
    {
        return Director::getInstance()->getVisibleSize();
    }
}
static Vec2 StringToVec2(std::string str) //string转vec2
{
    if(str == "")
        return Vec2(5,5);
    auto i = str.find_first_of(',');
    auto l = str.length();
    char num1[3] = {'\0' ,'\0','\0'};
    char num2[3] = { '\0' , '\0' ,'\0'};
    str.copy(num1, i, 0);
    str.copy(num2,l-i-1,i+1);
    float x = Value(num1).asFloat();
    float y = Value(num2).asFloat();
    return Vec2(x,y);
}
static std::string Vec2ToString(Vec2 vec) //vec2转string
{
    int x = vec.x;
    int y = vec.y;
    return Value(x).asString() + "," + Value(y).asString();
}
static int getEnemyIdInFile(int gid)
{
    return (gid-16)/ENEMY_PICNUM+1;
}
static int getPropIdByGid(int gid)//根据gid得到物品id
{
    return gid-e_attGem+1;
}
static int getEnemyStartIdByGid(int gid)  //根据gid得到startId值
{
    return ((int)(ceil((float)gid/ENEMY_PICNUM)) - 1) * ENEMY_PICNUM+1;
}
static int getNPCIdByGid(int gid) //根据gid得到npc的id，从1开始
{
    int id = gid - e_NPC1;
    id = int(id/4) + 1;
    return id;
}
#endif /* GameConstants_h */
