//
//  GameLayer.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/12.
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include "cocos2d.h"
#include "Hero.hpp"
USING_NS_CC;
typedef enum
{
    e_stairUp = 361,
    e_stairDown = 363,
} E_HeroPosStair;   //代表英雄进入塔层的初始位置类型

class GameLayer : public Node
{
public:
    GameLayer();
    ~GameLayer();
    bool init(int stairNum,Vec2 heroPos);
    static GameLayer* create(int stairNum,Vec2 heroPos);
    bool init();
    static GameLayer* create();    //这个是用来载入存档时使用的
    void initStair(Vec2 heroPos);   //对本楼层的初始化
    void initWall();    //对本层强的初始化，有些墙可能消失、
    void initDarkWall();   //对本层暗墙的初始化
    void initEnemy();   //本层怪物的初始化
    void initDoor();    //本层门的初始化
    void initProp();    //本层道具的初始化
    void initNPC();     //本层npc层的初始化
    void initSpecial();    //特殊层的初始化
    void initHero(Vec2 pos);
    //帧更新函数
    void updateTerrain(float dt);   //对地形的更新
    void updateEnemyAnimation(float dt);    //更新怪物们的动态图
    void updateNPCAnimation(float dt);//更新npc们的动态图
    int updateNPCGid(int gid);      //参数是npc的gid，返回更新后的gid
    
    float getTmxScaleByScreen();//根据屏幕得到
    Vec2 getTmxPosByScreen();//根据屏幕得到位置
    //勇士移动
    void heroMove(E_HeroDir dir);
    bool heroMoveDet(E_HeroDir dir);//英雄移动前的检测,false表不能前进
    bool heroArriveDet(Vec2 pos);//英雄到达的检测
    bool heroMove_OverstepDet(E_HeroDir dir);  //移动前的越界检测函数
    bool heroMove_WallDet(E_HeroDir dir);    //移动前wall层的墙的检测函数
    bool heroMove_darkWallDet(E_HeroDir dir);    //移动前暗墙层的检测函数
    bool heroMove_DoorDet(E_HeroDir dir);   //移动前门的检测
    bool heroMove_MonsterDet(E_HeroDir dir);   //移动前怪物的检测
    bool heroMove_PropDet();    //道具的检测,当前位子的
    bool heroMove_NPCDet(E_HeroDir dir);    //NPC的检测
    bool heroMove_SpecialDet(E_HeroDir dir);   //特殊层的检测，必须特殊层的使用变量为ture在能使用
    bool heroArriveStair();//到达楼梯的检测
    
    void showHint(int id,int gold = 0,int exp = 0);
    
    bool swordCountIsWin(int gid);//计算战斗是否可以赢
    void sword(int id);
    void InitFoeAttrBox(int id);
    
    void removeEnemy(Vec2 pos);//移除目标位置的怪物
    void removeProp(Vec2 pos);//移除目标位置的物品
    void removeNPC(Vec2 tarTilePos,bool IsfadeOut = true);//移除NPC
    void removeSteelDoor(Vec2 tarTilePos);   //特意的根据坐标移除一个铁门
    void removeDoor(Vec2 tarTilePos);  //根据坐标移除门
    void removeWallBlock(Vec2 wallPos);  //移除一个墙块
    void removeDarkWall(Vec2 pos);  //移除一个暗墙块
    void changeEnemyToSLM();   //变一个怪物为史莱姆
    void changeWallToDoor();   //变墙为门
    //战斗的
    std::string foeName;
    int foeGid;
    int foeHP;
    int foeAttack;
    int foeDefense;
    int foeGold;
    int fightNum;//战斗次数
    
    Vec2 heroTarTilePos;//勇士移动目标位置
    Hero* hero;
    Vec2 heroNowTilePos;//勇士现在的瓦片位置
    
    TMXTiledMap* tmx;//地图
    cocos2d::Size tmxSize;
    //地图的层
    TMXLayer* floor_layer;
    TMXLayer* wall_layer;
    TMXLayer* darkWall_layer;
    TMXLayer* door_layer;
    TMXLayer* enemy_layer;
    TMXLayer* NPC_layer;
    TMXLayer* prop_layer;
    TMXLayer* special_layer;
private:
    
    cocos2d::Size tileSize;//地图瓦片尺寸
    
    int stairNum;//楼层值
    
    bool isFirstEnStair;    //是否是第一次来本层
    bool doorOpening;
    bool stairIsWorking;    //本层正在干什么事，会使得勇士不能移动
    
    Sprite* hint_sp;    //提示的精灵
};

#endif /* GameLayer_hpp */
