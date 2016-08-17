//
//  GameLayer.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/12.
//
//

#include "GameLayer.hpp"
#include "GameConstants.h"
#include "Props.hpp"
#include "AnimationManager.hpp"
#include "Archive.hpp"
#include "GameScene.h"
#include "ReadPlist.hpp"
#include "ControlLayer.hpp"
#include "StairInfo.hpp"
#include "Audio.hpp"
GameLayer::GameLayer()
{
    doorOpening = false;
    isFirstEnStair = false;
    stairIsWorking = false;
}
GameLayer::~GameLayer()
{}
GameLayer* GameLayer::create(int stairNum,Vec2 heroPos)
{
    GameLayer *pRet = new(std::nothrow) GameLayer();
    if (pRet && pRet->init(stairNum,heroPos))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
//坐标类型是node在地图中间的
bool GameLayer::init(int stairNum,Vec2 heroPos)
{
    if (!Node::init())
    {
        return false;
    }

    this->stairNum = stairNum;

    tmx = TMXTiledMap::create( StringUtils::format("map%d.tmx",stairNum) );
    tmx->setAnchorPoint(Vec2(0.5,0.5));
    addChild(tmx);

    tmx->setScale(getTmxScaleByScreen());
    //tmx->setPosition(getTmxPosByScreen());
    tmx->setPosition(0,0);
    tmxSize = tmx->getBoundingBox().size;
    
    tileSize = tmx->getLayer("floor")->getLayerSize();//存下地图的瓦片尺寸
    
    //地图层指针存储
    floor_layer = tmx->getLayer("floor");
    wall_layer = tmx->getLayer("wall");
    darkWall_layer = tmx->getLayer("darkWall");
    door_layer = tmx->getLayer("door");
    enemy_layer = tmx->getLayer("enemy");
    NPC_layer = tmx->getLayer("NPC");
    prop_layer = tmx->getLayer("prop");
    special_layer = tmx->getLayer("special");
    
    initStair(heroPos);
    initHero(heroPos);
    
    //楼层数值的显示
    if(GameScene::controlLayer!=NULL)
    {
        std::string str = GameScene::controlLayer->getStairStr(stairNum);
        GameScene::controlLayer->stair_lab->setString(str);
    }
    
    hint_sp = Sprite::create("hint.png");
    addChild(hint_sp,15);
    hint_sp->setPosition(0,tmxSize.height*0.4);
    hint_sp->setVisible(false);
    
    return true;
}
bool GameLayer::init()  //读取存档时用
{
    if (!Node::init())
    {
        return false;
    }
    
    stairNum = Attribute::getInstance()->getHeroStair();
    Vec2 pos = Attribute::getInstance()->getHeroPos();
    
    tmx = TMXTiledMap::create( StringUtils::format("map%d.tmx",stairNum) );
    tmx->setAnchorPoint(Vec2(0.5,0.5));
    addChild(tmx);

    tmx->setScale(getTmxScaleByScreen());
    tmx->setPosition(0,0);
    tmxSize = tmx->getBoundingBox().size;
    
    tileSize = tmx->getLayer("floor")->getLayerSize();//存下地图的瓦片尺寸

    //地图层指针存储
    floor_layer = tmx->getLayer("floor");
    wall_layer = tmx->getLayer("wall");
    darkWall_layer = tmx->getLayer("darkWall");
    door_layer = tmx->getLayer("door");
    enemy_layer = tmx->getLayer("enemy");
    NPC_layer = tmx->getLayer("NPC");
    prop_layer = tmx->getLayer("prop");
    special_layer = tmx->getLayer("special");
    
    initStair(pos);
    initHero(pos);
    
    //楼层数值的显示
    if(GameScene::controlLayer!=NULL)
    {
        GameScene::controlLayer->stairNum = stairNum;
        std::string str = GameScene::controlLayer->getStairStr(stairNum);
        GameScene::controlLayer->stair_lab->setString(str);
    }
    
    hint_sp = Sprite::create("hint.png");
    addChild(hint_sp,15);
    hint_sp->setPosition(0,tmxSize.height*0.4);
    hint_sp->setVisible(false);
    
    if(stairNum==0)
         Audio::getInstance()->playBGM(Audio::bgm0);
    else
        Audio::getInstance()->playBGM(Audio::bgm1);
        
    return true;
}
GameLayer* GameLayer::create()
{
    GameLayer *pRet = new(std::nothrow) GameLayer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
void GameLayer::initStair(Vec2 heroPos)
{
    if(Archive::getInstance()->stairInfoIsNull(stairNum))   //表示第一次来本层
    {
        StairInfo stairInfo;
        stairInfo.setUpPos(heroPos);
        Archive::getInstance()->setStairInfo_map(stairInfo.getStoreyValueMap(),stairNum);
        if(stairNum>=0 && stairNum<=20)
        {
            if(stairNum > Attribute::getInstance()->getTopFloor())//设置到达的最高楼层
                Attribute::getInstance()->setTopFloor(stairNum);
        }
        else if(stairNum>=-25 && stairNum<0)
        {
            if(stairNum < Attribute::getInstance()->getMinFloor())//设置到达的最高楼层
                Attribute::getInstance()->setMinFloor(stairNum);
        }
        isFirstEnStair = true;
    }
    else
    {
        isFirstEnStair = false;
    }
    initWall();
    initDarkWall();
    initEnemy();
    initDoor();
    initNPC();
    initProp();
    initSpecial();
    
    if(isFirstEnStair==true)
    {
        if(stairNum != 0)
            GameScene::controlLayer->attriFace->uploadScore();
    }
}
void GameLayer::initWall()
{
    if(wall_layer==NULL)
        return;
    if(!isFirstEnStair)
    {
        ValueMap* wallMap = &Archive::getInstance()->getStairWall_map(stairNum);
        for(auto it:*wallMap)
        {
            if(it.second.asInt()==1)
            {
                //Vec2 t = StringToVec2(it.first);
                wall_layer->removeTileAt(StringToVec2(it.first));
            }
        }
    }
    if(stairNum==105)  //拿章那里特殊
    {
        if(Props::getInstance()->getPropByGid(e_wand2)==0)
        {
            wall_layer->removeTileAt(Vec2(10,3));
        }
        if(Props::getInstance()->getPropByGid(e_wand3)==0)
        {
            wall_layer->removeTileAt(Vec2(5,3));
        }
    }
    this->schedule(schedule_selector(GameLayer::updateTerrain), 0.3f);
}
void GameLayer::initDarkWall()
{
    if(darkWall_layer==NULL)
        return;
    if(!isFirstEnStair)
    {
        ValueMap* darkWallMap = &Archive::getInstance()->getStairDarkWall_map(stairNum);
        for(auto it:*darkWallMap)
        {
            if(it.second.asInt()==1)
            {
                darkWall_layer->removeTileAt(StringToVec2(it.first));
            }
            else if(it.second.asInt()==e_door1)
            {
                Vec2 t = StringToVec2(it.first);
                darkWall_layer->removeTileAt(t);
                door_layer->setTileGID(e_door1,t);
            }
        }
    }
}
void GameLayer::initEnemy()
{
    if(enemy_layer==NULL)
        return;
    if(!isFirstEnStair)
    {
        ValueMap* foeMap = &Archive::getInstance()->getStairEnemy_map(stairNum);
        for(auto it:*foeMap)
        {
            if(it.second.asInt()==1)
            {
                enemy_layer->removeTileAt(StringToVec2(it.first));
            }
            else if(it.second.asInt()==29)
            {
                enemy_layer->setTileGID(29, StringToVec2(it.first));
            }
            else if(it.second.asInt()==241)
            {
                enemy_layer->setTileGID(241, StringToVec2(it.first));
            }
        }
    }
    if(stairNum==20)
    {
        if(Archive::getInstance()->getStairNpc_state(Vec2(5,0),20)==1 && Attribute::getInstance()->attr_map["20GZIsDie"].asBool()==false)
        {
            enemy_layer->setTileGID(121, Vec2(5,0));
            wall_layer->setTileGID(3, Vec2(5,3));
        }
    }
    this->schedule(schedule_selector(GameLayer::updateEnemyAnimation), 0.3f);
}
void GameLayer::initDoor()
{
    if(door_layer==NULL)
        return;
    if(!isFirstEnStair)
    {
        ValueMap* doorMap = &Archive::getInstance()->getStairDoor_map(stairNum);
        for(auto it:*doorMap)
        {
            if(it.second.asInt()==1)
            {
                //Vec2 t = StringToVec2(it.first);
                door_layer->removeTileAt(StringToVec2(it.first));
            }
        }
    }
    if(stairNum==-2)    //-2层的楼梯是否显示
    {
        if(Archive::getInstance()->getStairNpc_state(Vec2(5,5),-2)!=5)
        {
            door_layer->removeTileAt(Vec2(0,0));
        }
    }
    else if(stairNum==0)
    {
        if(Attribute::getInstance()->attr_map["downIsOpen"].asBool() == true)
        {
            door_layer->setTileGID(e_doorDown, Vec2(1,1));
        }
    }
}
void GameLayer::initProp()
{
    if(prop_layer==NULL)
        return;
    if(!isFirstEnStair)
    {
        ValueMap* propMap = &Archive::getInstance()->getStairProp_map(stairNum);
        for(auto it:*propMap)
        {
            if(it.second.asInt()==1)
            {
                //Vec2 t = StringToVec2(it.first);
                prop_layer->removeTileAt(StringToVec2(it.first));
            }
        }
    }
    if(stairNum==20)//20层特殊
    {
        if(Attribute::getInstance()->attr_map["20GZIsDie"].asBool()==true && NPC_layer->getTileGIDAt(Vec2(5,0))==0)
        {
            prop_layer = tmx->getLayer("prop2");
            prop_layer->setVisible(true);
            ValueMap* propMap = &Archive::getInstance()->getStairProp_map(stairNum);
            for(auto it:*propMap)
            {
                if(it.second.asInt()==1)
                {
                    //Vec2 t = StringToVec2(it.first);
                    prop_layer->removeTileAt(StringToVec2(it.first));
                }
            }
        }
        else
        {
            door_layer->setTileGID(0, Vec2(4,10));
            door_layer->setTileGID(0, Vec2(6,10));
            tmx->getLayer("prop2")->setVisible(false);
        }
    }
    else if(stairNum==-13)
    {
        if(Props::getInstance()->getPropByGid(e_wand2)>=1)
        {
            prop_layer->setTileGID(e_wand2,Vec2(2,2));
        }
        else if(Props::getInstance()->getPropByGid(e_wand3)>=1)
        {
            prop_layer->setTileGID(e_wand3,Vec2(2,2));
        }
        else
        {
            prop_layer->setTileGID(e_sword5,Vec2(2,2));
        }
    }
}
void GameLayer::initNPC()
{
    if(NPC_layer==NULL)
        return;
    if(!isFirstEnStair)
    {
        ValueMap* npcMap = &Archive::getInstance()->getStairNpc_map(stairNum);
        for(auto it:*npcMap)
        {
            if(it.second.asInt()==1)
            {
                //Vec2 t = StringToVec2(it.first);
                NPC_layer->removeTileAt(StringToVec2(it.first));
            }
        }
    }
    if(stairNum==0)
    {
        if(Attribute::getInstance()->attr_map["downIsOpen"].asBool() == true)
        {
            log("??x");
            NPC_layer->setTileGID(e_NPC2, Vec2(2,1));
        }
    }
    this->schedule(schedule_selector(GameLayer::updateNPCAnimation), 0.3f);
}
void GameLayer::initSpecial()//特殊层
{
    if(!isFirstEnStair)
    {
    }
    std::string monstr1;
    std::string monstr2;
    Vec2 pos;
    bool haveMons = false;
    if(stairNum == 15)
    {
        int gid = enemy_layer->getTileGIDAt(Vec2(5,3));
        if(gid != 0)
        {
            monstr1 = "octopus1.png";
            monstr2 = "octopus2.png";
            pos.set(4, 3);
            haveMons = true;
            enemy_layer->getTileAt(Vec2(5,3))->setVisible(false);
        }
    }
    else if(stairNum == -10)
    {
        if(enemy_layer->getTileGIDAt(Vec2(5,8)) != 0)
        {
            monstr1 = "dragon1.png";
            monstr2 = "dragon2.png";
            pos.set(4, 8);
            haveMons = true;
            enemy_layer->getTileAt(Vec2(5,8))->setVisible(false);
        }
    }
    else if(stairNum == 109)
    {
        if(enemy_layer->getTileGIDAt(Vec2(5,5)) != 0)
        {
            monstr1 = "ddragon1.png";
            monstr2 = "ddragon2.png";
            pos.set(4, 5);
            haveMons = true;
            enemy_layer->getTileAt(Vec2(5,5))->setVisible(false);
        }
    }
    if(haveMons)
    {
        auto octopus_Sp = Sprite::create(monstr1);
        octopus_Sp->setAnchorPoint(Vec2(0,0));
        tmx->addChild(octopus_Sp,10,"monst");
        octopus_Sp->setPosition(enemy_layer->getPositionAt(pos));
        //章鱼动画
        SpriteFrame *frame0 = SpriteFrame::create(monstr1,cocos2d::Rect(0,0,octopus_Sp->getContentSize().width,octopus_Sp->getContentSize().height));
        SpriteFrame *frame1 = SpriteFrame::create(monstr2,cocos2d::Rect(0,0,octopus_Sp->getContentSize().width,octopus_Sp->getContentSize().height));
        Vector<SpriteFrame*> octFrames;
        
        octFrames.pushBack(frame0);
        octFrames.pushBack(frame1);
        auto animate = Animate::create(Animation::createWithSpriteFrames(octFrames, 0.35f));
        auto rep = RepeatForever::create(animate);
        octopus_Sp->runAction(rep);
    }
}
void GameLayer::initHero(Vec2 pos)
{
    hero = Hero::create();
    hero->setPosition( floor_layer->getPositionAt(pos) );
    tmx->addChild(hero,10);
    heroNowTilePos = pos;
    //设置英雄的方向
    if(wall_layer->getTileGIDAt(pos+Vec2(-1,0))==0)
        hero->setHeroDir(e_left);
    else if(wall_layer->getTileGIDAt(pos+Vec2(0,-1))==0)
        hero->setHeroDir(e_up);
    else if(wall_layer->getTileGIDAt(pos+Vec2(1,0))==0)
        hero->setHeroDir(e_right);
    else
        hero->setHeroDir(e_down);
}
float GameLayer::getTmxScaleByScreen()
{
    if(VISIBSIZE.width > VISIBSIZE.height)//横屏
    {
        auto tmxSize = tmx->getContentSize();
        float ratio = VISIBSIZE.height/tmxSize.width;
        ratio = ratio>TMX_MAXSCALE?TMX_MAXSCALE:ratio;
        if(GETADS_NO==false)
            return ratio * 0.85;
        else
            return ratio;
    }
    else if(VISIBSIZE.width <= VISIBSIZE.height)//竖屏
    {
        auto tmxSize = tmx->getContentSize();
        float ratio = VISIBSIZE.width/tmxSize.width;
        ratio = ratio>TMX_MAXSCALE?TMX_MAXSCALE:ratio;
        return ratio;
    }
    return TMX_MAXSCALE;
}
Vec2 GameLayer::getTmxPosByScreen()
{
    if(VISIBSIZE.width > VISIBSIZE.height)//横屏
    {
        float x = (VISIBSIZE.width-VISIBSIZE.height)/5*3;
        float y = 0;
        return Vec2(x,y);
    }
    else if(VISIBSIZE.width <= VISIBSIZE.height)//竖屏
    {
        float y = (VISIBSIZE.height-VISIBSIZE.width)/5*3;
        float x = VISIBSIZE.width/2-540;
        return Vec2(x,y);
    }
    return Vec2(VISIBSIZE.width/2-540,585);
}
void GameLayer::updateTerrain(float dt) //更新地形
{
    for(short x=0;x<tileSize.width;x++)
    {
        for(short y=0;y<tileSize.height;y++)
        {
            int gid = wall_layer->getTileGIDAt(Vec2(x, y));
            if(gid!=0)
            {
                switch (gid) {
                    case e_floorMagma1:
                        gid = e_floorMagma2;
                        break;
                    case e_floorMagma2:
                        gid = e_floorMagma1;
                        break;
                    case e_floorFire1:
                        gid = e_floorFire2;
                        break;
                    case e_floorFire2:
                        gid = e_floorFire1;
                        break;
                    case e_floorStar1:
                        gid = e_floorStar2;
                        break;
                    case e_floorStar2:
                        gid = e_floorStar1;
                        break;
                    default:
                        break;
                }
            }
            wall_layer->setTileGID(gid, Vec2(x, y));
        }
    }
}
void GameLayer::updateEnemyAnimation(float dt)    //更新怪物们的动态图
{
    for(short x=0;x<tileSize.width;x++)
    {
        for(short y=0;y<tileSize.height;y++)
        {
            int gid = enemy_layer->getTileGIDAt(Vec2(x, y));
            if(gid != 0)
            {
                int startGID = getEnemyStartIdByGid(gid);
                gid+=2;
                if (gid - startGID > 3)
                {
                    gid = startGID;
                }
                //给怪物设置新的图块
                enemy_layer->setTileGID(gid, Vec2(x, y));
            }
        }
    }
}
void GameLayer::updateNPCAnimation(float dt)
{
    for(short x=0;x<tileSize.width;x++)
    {
        for(short y=0;y<tileSize.height;y++)
        {
            int gid = NPC_layer->getTileGIDAt(Vec2(x, y));
            if(gid != 0)
            {
                gid = updateNPCGid(gid);
                NPC_layer->setTileGID(gid, Vec2(x, y));
            }
        }
    }
}
int GameLayer::updateNPCGid(int gid)
{
    switch (gid) {
        case e_NPC1:
            return e_NPC1+2;
            break;
        case e_NPC1+2:
            return e_NPC1;
            break;
        case e_NPC2:
            return e_NPC2+2;
            break;
        case e_NPC2+2:
            return e_NPC2;
            break;
        case e_NPC3:
            return e_NPC3+2;
            break;
        case e_NPC3+2:
            return e_NPC3;
            break;
        case e_NPC4:
            return e_NPC4+2;
            break;
        case e_NPC4+2:
            return e_NPC4;
            break;
        case e_NPC5:
            return e_NPC5+2;
            break;
        case e_NPC5+2:
            return e_NPC5;
            break;
        case e_NPCStore1:
            return e_NPCStore1+2;
            break;
        case e_NPCStore1+2:
            return e_NPCStore1;
            break;
        case e_NPCStore2:
            return e_NPCStore2+2;
            break;
        case e_NPCStore2+2:
            return e_NPCStore2;
            break;
        default:
            break;
    }
    return gid;
}
void GameLayer::heroMove(E_HeroDir dir)
{
    if (hero->isMoving || hero->isFighting || hero->isDialog)//一些情况下，英雄不能移动
        return;
    //设置勇士的方向和目标点
    hero->setHeroDir(dir);
    
    heroTarTilePos = heroNowTilePos+getMoveVec(dir);//设置目标位置
    if(heroMoveDet(dir)==false)
    {
        return;
    }
    //取消移动动画，改设置帧加延时
//    auto delay1 = DelayTime::create(AnimationManager::getInstance()->heroStepTime*0.1);
//    auto delay2 = DelayTime::create(AnimationManager::getInstance()->heroStepTime*0.6);
//    auto funcM1 = CallFunc::create([=](){
//        hero->addMoveFrameNum();
//    });
//    auto funcM2 = CallFunc::create([=](){
//        hero->addMoveFrameNum();
//    });
//    auto seq1 = Sequence::create(delay1,funcM1,delay2,funcM2,NULL);
    Animation* moveAnima = AnimationManager::getInstance()->getHeroAnimationByDir(dir,hero->skin); //根据方向得到动画
    Vec2 tarPos = floor_layer->getPositionAt(heroTarTilePos);
    auto move = MoveTo::create(AnimationManager::getInstance()->heroStepTime,tarPos); //本来0.2
    //移动结束的处理函数
    auto func = CallFunc::create([=](){
        heroNowTilePos = heroTarTilePos;
        heroTarTilePos = heroNowTilePos+getMoveVec(dir);
        hero->isMoving = false;
        heroArriveDet(heroNowTilePos);
    });
    auto seq2 = Sequence::create(move,func, NULL);
    auto animate = Animate::create(moveAnima);
    hero->isMoving = true;
    hero->runAction(seq2);
    hero->heroSprite->runAction(animate);
}
bool GameLayer::heroMoveDet(E_HeroDir dir)
{
    if(heroMove_OverstepDet(dir) == false)  //是否出范围检测
        return false;
    if(heroMove_WallDet(dir)==false)    //墙的检测
        return false;
    if(heroMove_darkWallDet(dir)==false)   //暗墙的检测
        return false;
    if(heroMove_DoorDet(dir)==false)    //门的检测
        return false;
    if( heroMove_NPCDet(dir) == false )   //NPC的检测
        return false;
    if(heroMove_MonsterDet(dir)==false)   //怪物的检测
        return false;
    if(heroMove_SpecialDet(dir) == false)
        return false;
    return true;
}
bool GameLayer::heroArriveDet(Vec2 pos)//检测道具和上下楼梯
{
    if(heroArriveStair())
        return true;
    if(heroMove_PropDet())
        return true;
    int now_gid = wall_layer->getTileGIDAt(heroNowTilePos);
    if(now_gid==e_floorFire1 || now_gid==e_floorFire2)  //碰到炎路损血
    {
        if(Props::getInstance()->getPropByGid(e_iceMagic)==0)
        {
            GameScene::controlLayer->attriFace->addHP(-50);
        }
    }
    if(GameScene::controlLayer->scenarioDet(stairNum,pos))
        return true;
    if(GameScene::controlLayer->handle->touchDir==e_stand)
    {
        hero->setHeroDir(hero->heroDir);
        return false;
    }
    if(GameScene::controlLayer->handle->touchDir!=e_stand)
    {
        heroMove(GameScene::controlLayer->handle->touchDir);
    }
    return false;
}
bool GameLayer::heroArriveStair()//到达楼梯
{
    int gid = door_layer->getTileGIDAt(heroNowTilePos);
    if(gid == e_doorUp)
    {
        GameScene::controlLayer->upOrDownstairs(stairNum+1,heroNowTilePos);
        return true;
    }
    else if(gid == e_doorDown)
    {
        GameScene::controlLayer->upOrDownstairs(stairNum-1,heroNowTilePos);
        return true;
    }
    else if(gid == e_doorUp2 || gid==e_doorDown2)
    {
        GameScene::controlLayer->upOrDownSpeStair(stairNum,gid);
        return true;
    }
    return false;
}
bool GameLayer::heroMove_OverstepDet(E_HeroDir dir)  //移动前的越界检测函数
{
    if(heroTarTilePos.x<0 || heroTarTilePos.x>=TILE_MAPSIZE)
        return false;
    if(heroTarTilePos.y<0 || heroTarTilePos.y>=TILE_MAPSIZE)
        return false;
    return true;
}
bool GameLayer::heroMove_WallDet(E_HeroDir dir)    //移动前wall层的墙的检测函数
{
    if(wall_layer==NULL)
        return true;
    int gid = wall_layer->getTileGIDAt(heroTarTilePos);
    if(gid!=0)
    {
        if(gid==e_floorFire1 || gid==e_floorFire2)
            return true;
        return false;
    }
    else
        return true;
}
bool GameLayer::heroMove_darkWallDet(E_HeroDir dir)    //移动前暗墙层的检测函数
{
    if(darkWall_layer==NULL)
        return true;
    int gid = darkWall_layer->getTileGIDAt(heroTarTilePos);
    if(gid!=0)
    {
//        if(wallIsRemove==false)
//        {
//            removeDarkWallBlock(tarTilePos);
//        }
//        else
//        {
//            if(wallIsRemove==false)
//                removeDarkWallBlock(tarTilePos);
//        }
        return false;
    }
    return true;
}
bool GameLayer::heroMove_DoorDet(E_HeroDir dir)   //移动前门的检测
{
    if(door_layer==NULL)
        return true;
    int gid = door_layer->getTileGIDAt(heroTarTilePos);
    if(gid!=0)  //如果不为0，表示有门
    {
        if(doorOpening==true)   //如果门开动画在放，就不响应开门了
            return false;
        if(gid<e_door4) //这表示是门
        {
            if(Props::getInstance()->getKeyNum((E_Door)gid)<1)  //如果钥匙数量小于1
            {
                return false;
            }
            else    //开门
            {
                PlaySound(Audio::door_e);
                Animation* doorAnimat = AnimationManager::getInstance()->getDoorAnimationByDir((E_Door)gid);   //得到门开动画
                auto animate = Animate::create(doorAnimat); //门开动画动作
                auto func = CallFunc::create([=](){
                    door_layer->removeTileAt(heroTarTilePos); //移除门
                    doorOpening = false;    //表示动画放完了
                    //更改为valuemap来存储信息
                    Archive::getInstance()->setStairDoor_map(heroTarTilePos,1,stairNum);
                    if(GameScene::controlLayer->handle->touchDir!=e_stand)  //门开后继续移动
                        heroMove(GameScene::controlLayer->handle->touchDir);
                });
                auto seq = Sequence::create(animate,func, NULL);
                Sprite* doorSp = door_layer->getTileAt(heroTarTilePos);
                doorOpening = true;     //动作执行前，表动画开始执行
                //AUD_OPENDOOR;
                doorSp->runAction(seq);
                GameScene::controlLayer->redOneKeyNumByVar((E_Door)gid);  //让钥匙数量减少
                return false;
            }
        }
        else if (gid==e_steelDoor)   //遇到铁门
        {
            removeDoor(heroTarTilePos);
            return false;
        }
        else if(gid==e_door5)   //封堵的铁门，需要钥匙
        {
            if(Props::getInstance()->getPropByGid(e_key5)>0)
            {
                Props::getInstance()->redOneKeyNumByVar(e_door5);
                removeDoor(heroTarTilePos);
                return false;
            }
            else
            {
                showHint(108);
                return false;
            }
        }
        else if(gid==e_door4)   //逻辑门
        {
            GameScene::controlLayer->logicDoorDet(heroTarTilePos);
            return false;
        }
        else if(gid==e_doorUp || gid==e_doorDown || gid==e_doorUp2 || gid==e_doorDown2 )
        {
            return true;
        }
        else
            return false;
    }
    else
        return true;
}
bool GameLayer::heroMove_MonsterDet(E_HeroDir dir)   //移动前怪物的检测
{
    if(enemy_layer == NULL)
        return true;
    int gid = enemy_layer->getTileGIDAt(heroTarTilePos);
    if(gid!=0)
    {
//        int id = getEnemyIdInFile(gid);
//        ValueMap* enemy_map = ReadPlist::getInstance()->getEnemyMap();
//        ValueMap enemyAttr_map = (*enemy_map)[StringUtils::format("%d",id)].asValueMap();
        //计算下能否打败
        //if(GameScene::controlLayer->sword->swordCalcIsWin(gid))
        //{
        hero->isFighting = true;
        GameScene::controlLayer->sword->beginSword(gid);
        return false;
        //}
        //else
            //return false;
    }
    else
        return true;
}
bool GameLayer::heroMove_PropDet()    //道具的检测,当前位子的
{
    if(prop_layer==NULL)
        return false;
    int gid = prop_layer->getTileGIDAt(heroNowTilePos);
    if(gid!=0)
    {
        PlaySound(Audio::chiProp_e);
        GameScene::controlLayer->getPropDeal(gid);
        removeProp(heroNowTilePos);
        //显示提示精灵
        if(stairNum==-13 && heroNowTilePos==Vec2(2,2))  //13层有个道具特殊
            return true;
        int hintId = getPropIdByGid(gid);
        showHint(hintId);
        return true;
    }
    return false;
}
bool GameLayer::heroMove_NPCDet(E_HeroDir dir)    //NPC的检测
{
    if(NPC_layer==NULL)
        return true;
    int gid = NPC_layer->getTileGIDAt(heroTarTilePos);
    if(gid!=0)
    {
        log("nnGid:%d",gid);
        int npcId = getNPCIdByGid(gid);
        log("npcid:%d",npcId);
        GameScene::controlLayer->meetNPC(npcId,heroTarTilePos);
        return false;
    }
    return true;
}
bool GameLayer::heroMove_SpecialDet(E_HeroDir dir)   //特殊层的检测，必须特殊层的使用变量为ture在能使用
{
    
    return true;
}
bool GameLayer::swordCountIsWin(int gid)//计算战斗是否会赢
{
    int id = getEnemyIdInFile(gid);
    ValueMap* enemy_map = ReadPlist::getInstance()->getEnemyMap();
    ValueMap enemyAttr_map = (*enemy_map)[StringUtils::format("%d",id)].asValueMap();
    int foeHP = enemyAttr_map["HP"].asInt();
    int foeAttack = enemyAttr_map["attackNum"].asInt();
    int foeDefense = enemyAttr_map["defenseNum"].asInt();
    int heroAttack = Attribute::getInstance()->getAttack();
    if(heroAttack<= foeDefense)
        return false;
    else
    {
        int loss = (ceil( (float)foeHP/(heroAttack-foeDefense) )-1) * ((foeAttack-Attribute::getInstance()->getDefense())>0?(foeAttack-Attribute::getInstance()->getDefense()):0);
        fightNum = (ceil( (float)foeHP/(heroAttack-foeDefense) ));
        if(loss >= Attribute::getInstance()->getHP())
        {
            return false;
        }
    }
    return true;
}

void GameLayer::removeEnemy(Vec2 pos)
{
    enemy_layer->removeTileAt(pos); //地图层中移除怪物
    Archive::getInstance()->setStairEnemy_map(pos,1,stairNum);
}
void GameLayer::removeProp(Vec2 pos)
{
    if(prop_layer==NULL)
        return ;
    prop_layer->removeTileAt(heroNowTilePos); //地图上的物品要消除
    //存储信息~
    Archive::getInstance()->setStairProp_map(heroNowTilePos,1,stairNum);
}
void GameLayer::removeNPC(Vec2 tarTilePos,bool IsfadeOut)
{
    if(NPC_layer==NULL)
        return;
    if(IsfadeOut)
    {
        auto npcSp = NPC_layer->getTileAt(tarTilePos);
        if(npcSp==NULL)
            return;
        auto npc_Sp = Sprite::createWithSpriteFrame(npcSp->getSpriteFrame());
        npc_Sp->setAnchorPoint(npcSp->getAnchorPoint());
        npc_Sp->setPosition(npcSp->getPosition());
        tmx->addChild(npc_Sp);
        auto fadeOut = FadeOut::create(1);
        auto func = CallFunc::create([=](){
            npc_Sp->removeFromParent();
        });
        auto seq = Sequence::create(fadeOut,func, NULL);
        npc_Sp->runAction(seq);
    }
    NPC_layer->removeTileAt(tarTilePos); //移除这个npc
    Archive::getInstance()->setStairNpc_map(tarTilePos,1,stairNum);  //移除此npc，记录改为1
}
void GameLayer::removeSteelDoor(Vec2 tarTilePos)   //根据坐标移除一个铁门
{
    if(door_layer==NULL)
        return;
    if(door_layer->getTileGIDAt(tarTilePos)==e_steelDoor)
    {
        auto sDoorSp = door_layer->getTileAt(tarTilePos);
        auto animate = Animate::create(AnimationManager::getInstance()->getDoorAnimationByDir(e_steelDoor));
        if(animate==NULL)
            return;
        auto func = CallFunc::create([=](){
            door_layer->removeTileAt(tarTilePos); //移除门
            Archive::getInstance()->setStairDoor_map(tarTilePos,1,stairNum);//更改为valuemap来存储信息
        });
        auto seq = Sequence::create(animate,func, NULL);
        sDoorSp->runAction(seq);
    }
}
void GameLayer::removeDoor(Vec2 tarTilePos)
{
    if(door_layer==NULL)
        return;
    int gid = door_layer->getTileGIDAt(tarTilePos);
    auto sDoorSp = door_layer->getTileAt(tarTilePos);
    if(sDoorSp==NULL)
        return;
    auto animate = Animate::create(AnimationManager::getInstance()->getDoorAnimationByDir(E_Door(gid)));
    if(animate==NULL)
        return;
    auto func = CallFunc::create([=](){
        door_layer->removeTileAt(tarTilePos); //移除门
        doorOpening = false;
        Archive::getInstance()->setStairDoor_map(tarTilePos,1,stairNum);//更改为valuemap来存储信息
        stairIsWorking = false;
    });
    auto seq = Sequence::create(animate,func, NULL);
    stairIsWorking = true;
    doorOpening = true;
    sDoorSp->runAction(seq);
}
void GameLayer::removeWallBlock(Vec2 tarTilePos)
{
    if(wall_layer==NULL)
        return;
    Sprite* wall_sp =  wall_layer->getTileAt(tarTilePos);
    if(wall_sp==NULL)
        return;
    auto darkWall_sp = Sprite::createWithSpriteFrame(wall_sp->getSpriteFrame());
    tmx->addChild(darkWall_sp,12);
    darkWall_sp->setAnchorPoint(Vec2::ZERO);
    darkWall_sp->setPosition(wall_layer->getPositionAt(tarTilePos));
    wall_sp->setVisible(false);
    auto animate = Animate::create(AnimationManager::getInstance()->getRetWallAnimation());
    auto func = CallFunc::create([=](){
        stairIsWorking = false;
        wall_layer->removeTileAt(tarTilePos);
        tmx->removeChild(darkWall_sp);
        Archive::getInstance()->setStairWall_map(tarTilePos,1,stairNum);
    });
    auto seq = Sequence::create(animate,func, NULL);
    //AUD_OPENDOOR;
    stairIsWorking = true;
    darkWall_sp->runAction(seq);
}
void GameLayer::removeDarkWall(Vec2 pos)
{
    auto darkWall = tmx->getLayer("darkWall");
    if(darkWall==NULL)
        return;
    darkWall->removeTileAt(pos);
    Archive::getInstance()->setStairDarkWall_map(pos,1,stairNum);
}
void GameLayer::changeEnemyToSLM()
{
    if(stairNum!=-25)
    {
        enemy_layer->setTileGID(49, heroTarTilePos);
        Archive::getInstance()->setStairEnemy_map(heroTarTilePos,1,stairNum);
        Props::getInstance()->addOnePropByGid(e_dagger,-1);
    }
    else if(stairNum==-25)
    {
        removeNPC(heroTarTilePos,false);
        enemy_layer->setTileGID(49, heroTarTilePos);
        Archive::getInstance()->setStairNpc_map(heroTarTilePos,1,stairNum);
        Props::getInstance()->addOnePropByGid(e_dagger,-1);
    }
}
void GameLayer::changeWallToDoor()
{
    if(stairNum == -9 && heroTarTilePos==Vec2(4,0))  //-9层有个特殊的
    {
        Props::getInstance()->addOnePropByGid(e_speDoor,-1);
        removeDarkWall(Vec2(4,0));
    }
    else if(stairNum == -25)
    {
        Props::getInstance()->addOnePropByGid(e_speDoor,-1);
        removeDarkWall(Vec2(5,10));
    }
    else
    {
        int speDoor = Props::getInstance()->getPropByGid(e_speDoor);
        Props::getInstance()->setPropByGid(e_speDoor,speDoor-1);
        door_layer->setTileGID(e_door1,heroTarTilePos);
        removeDarkWall(heroTarTilePos);
        Archive::getInstance()->setStairDarkWall_map(heroTarTilePos,e_door1,stairNum);
    }
}
void GameLayer::showHint(int id,int gold,int exp)
{
    ValueMap* hint_map = ReadPlist::getInstance()->getHintInfoMap();
    hint_sp->stopAllActions();
    hint_sp->removeChildByName("lab");
    hint_sp->setVisible(false);
    Label* hint_lab = NULL;
    if(id==1||id==2)
    {
        std::string labStr = (*hint_map)[StringUtils::format("%d",id).c_str()].asString();
        std::string numStr = StringUtils::format("%d",2);
        labStr = labStr.append(numStr);
        hint_lab = Label::createWithSystemFont(labStr,"",40);
    }
    else if(id==100)
    {
        std::string hintStr = (*hint_map)[StringUtils::format("%d",id).c_str()].asString();
        std::string labStr = StringUtils::format(hintStr.c_str(),gold,exp);
        hint_lab = Label::createWithSystemFont(labStr,"",40);
    }
    else if(id==5||id==6)
    {
        std::string labStr = (*hint_map)[StringUtils::format("%d",id).c_str()].asString();
        int num;
        if(id==5)
            num = 150;
        else if(id==6)
            num = 400;
        std::string numStr = StringUtils::format("%d",num);
        labStr = labStr.append(numStr);
        hint_lab = Label::createWithSystemFont(labStr,"",40);
    }
    else if(id==16)
    {
        std::string labStr = (*hint_map)[StringUtils::format("%d",id).c_str()].asString();
        std::string numStr = StringUtils::format("%d",Attribute::getInstance()->getHP()/2);
        labStr = labStr.append(numStr);
        hint_lab = Label::createWithSystemFont(labStr,"",40);
    }
    else
    {
        hint_lab = Label::createWithSystemFont((*hint_map)[StringUtils::format("%d",id).c_str()].asString(),"",40);
    }
    //提示的动作
    hint_sp->addChild(hint_lab,0,"lab");
    hint_lab->setPosition(hint_sp->getContentSize().width/2,hint_sp->getContentSize().height/2);
    hint_sp->setScale(0.5);
    auto scaleTo = ScaleTo::create(0.1, 1);
    auto ease = EaseElasticOut::create(scaleTo);
    auto delay = DelayTime::create(0.8);
    auto func = CallFunc::create([=](){
        hint_sp->removeChildByName("lab");
        hint_sp->setVisible(false);
    });
    auto seq = Sequence::create(ease,delay,func, NULL);
    hint_sp->setVisible(true);
    hint_sp->runAction(seq);
}