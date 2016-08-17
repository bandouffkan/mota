//
//  ControlLayer.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/12.
//
//

#include "ControlLayer.hpp"
#include "GameScene.h"
#include "GameConstants.h"
#include "cocostudio/CocoStudio.h"
#include "Enemy.hpp"
#include "Archive.hpp"
#include "Dialog.hpp"
#include "Audio.hpp"
#include "HomeScene.hpp"
bool ControlLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    stairNum = 0;
    heroIsDie = false;
    
    cotroLayer_csb = CSLoader::createNodeWithVisibleSize("Control/ControlLayer.csb");
    addChild(cotroLayer_csb);
    
    //    //控制器
//    control_Sp = cotroLayer_csb->getChildByName<Sprite*>("control");
//    up_but = control_Sp->getChildByName<Button*>("up_But");
//    down_but = control_Sp->getChildByName<Button*>("down_But");
//    left_but = control_Sp->getChildByName<Button*>("left_But");
//    right_but = control_Sp->getChildByName<Button*>("right_But");
//    up_but->setTag(e_up);
//    down_but->setTag(e_down);
//    left_but->setTag(e_left);
//    right_but->setTag(e_right);
//    up_but->addTouchEventListener(CC_CALLBACK_2(ControlLayer::onTouchButMove, this));
//    down_but->addTouchEventListener(CC_CALLBACK_2(ControlLayer::onTouchButMove, this));
//    left_but->addTouchEventListener(CC_CALLBACK_2(ControlLayer::onTouchButMove, this));
//    right_but->addTouchEventListener(CC_CALLBACK_2(ControlLayer::onTouchButMove, this));

//    props = Props::getInstance();
//    key1Num_lab = Label::createWithSystemFont("","",40);
//    key2Num_lab = Label::createWithSystemFont("","",40);
//    key3Num_lab = Label::createWithSystemFont("","",40);
//    key1Num_lab->setPosition(100,750);
//    key2Num_lab->setPosition(100,700);
//    key3Num_lab->setPosition(100,650);
//    key1Num_lab->setString(Value(props->getKey1Num()).asString());
//    key2Num_lab->setString(Value(props->getKey2Num()).asString());
//    key3Num_lab->setString(Value(props->getKey3Num()).asString());
//    addChild(key1Num_lab);
//    addChild(key2Num_lab);
//    addChild(key3Num_lab);
    
    attriFace = AttributeFace::create();
    addChild(attriFace);
    attriFace->setPosition(VISIBSIZE.width*0.012,VISIBSIZE.height*0.995);
    if(GETADS_NO==false)
    {
        attriFace->setScale(0.9);
        attriFace->setPosition(VISIBSIZE.width*0.012,VISIBSIZE.height*0.998);
    }
        
    //楼梯的显示
    stair_sp = Sprite::create("stair/bg.png");
    addChild(stair_sp);
    //stair_sp->setScale(0.7);
    stair_sp->setAnchorPoint(Vec2(0,1));
    stair_sp->setPosition(VISIBSIZE.width*0.835,VISIBSIZE.height*0.99);
    stair_lab = Label::createWithSystemFont("", "", 45);
    stair_sp->addChild(stair_lab);
    stair_lab->setPosition(stair_sp->getContentSize().width/2,stair_sp->getContentSize().height/2);
    stair_lab->setColor(Color3B(181,219,238));
    
//    //英雄属性的字符显示
//    attri = Attribute::getInstance();
//    HP_lab = Label::createWithSystemFont("","",40);
//    attack_lab = Label::createWithSystemFont("","",40);
//    defense_lab = Label::createWithSystemFont("","",40);
//    gold_lab = Label::createWithSystemFont("","",40);
//    exp_lab = Label::createWithSystemFont("","",40);
//    grade_lab = Label::createWithSystemFont("","",50);
//    HP_lab->setPosition(100,1030);
//    attack_lab->setPosition(100,950);
//    defense_lab->setPosition(100,900);
//    gold_lab->setPosition(100,850);
//    exp_lab->setPosition(100,800);
//    grade_lab->setPosition(200,800);
//    
//    HP_lab->setString(StringUtils::format("%d",attri->getHP()));
//    attack_lab->setString(StringUtils::format("%d",attri->getAttack()));
//    defense_lab->setString(StringUtils::format("%d",attri->getDefense()));
//    gold_lab->setString(StringUtils::format("%d",attri->getGold()));
//    exp_lab->setString(StringUtils::format("%d",attri->getExp()));
//    grade_lab->setString(StringUtils::format("%d",attri->getGrade()));
//    addChild(HP_lab);
//    addChild(attack_lab);
//    addChild(defense_lab);
//    addChild(gold_lab);
//    addChild(exp_lab);
//    addChild(grade_lab);
    
    gameLayer = GameLayer::create(stairNum,Vec2(5,9));
    addChild(gameLayer);
    gamePos = getGamePosByScreen();
    gameLayer->setPosition(gamePos);
   // gameLayer->initHero(Vec2(5,9));
    
    //楼层数值的显示
    std::string str = GameScene::controlLayer->getStairStr(stairNum);
    stair_lab->setString(str);
    
    //菜单
    menu = GameMenu::create();
    addChild(menu,10);
    menu->setPosition(gameLayer->getPosition());
    menu->setVisible(false);
    
    //存档界面
    arcSaveFace = ArchiveFace::create(ArchiveFace::e_save);
    addChild(arcSaveFace,10);
    arcSaveFace->setPosition(gameLayer->getPosition());
    arcSaveFace->setVisible(false);
    
    //读取存档界面
    arcReadFace = ArchiveFace::create(ArchiveFace::e_read);
    addChild(arcReadFace,10);
    arcReadFace->setPosition(gameLayer->getPosition());
    arcReadFace->setVisible(false);
    
    //菜单按钮
    auto menu_but = Button::create("menu/menu3.png");
    addChild(menu_but);
    menu_but->setPosition(Vec2(VISIBSIZE.width*0.915,VISIBSIZE.height*0.8));
    menu_but->setZoomScale(-0.1);
    menu_but->addClickEventListener(CC_CALLBACK_1(ControlLayer::onClickBut_menu,this));
    if(GETADS_NO==false)
    {
        menu_but->setPosition(Vec2(VISIBSIZE.width*0.915,VISIBSIZE.height*0.83));
    }
    
    auto menu_lab = Label::createWithSystemFont("菜  单", "", 49);
    menu_but->addChild(menu_lab);
    auto but_size = menu_but->getContentSize();
    menu_lab->setPosition(but_size.width/2,but_size.height/2);
    menu_lab->setColor(Color3B(181,219,238));
    
    Enemy::foeTexture = TextureCache::sharedTextureCache()->addImage("enemy.png");
    
    sword = Sword::create();
    addChild(sword,10);
    sword->setPosition(gameLayer->getPosition()+Vec2(0,VISIBSIZE.height*0.1));
    sword->setVisible(false);
    
    handle = ControlHandle::create();
    addChild(handle,10);
    handle->setPosition(VISIBSIZE.width*0.13,VISIBSIZE.height*0.23);
    //handle->setPosition(245,268);
    if(GETADS_NO==false)
    {
        handle->setPosition(VISIBSIZE.width*0.13,VISIBSIZE.height*0.32);
    }
        
    return true;
}
void ControlLayer::readArchive(int num)
{
    std::string filePath = FileUtils::getInstance()->getWritablePath();
    std::string fullPath = filePath + StringUtils::format("archive%d.plist",num);
    bool isExist = FileUtils::getInstance()->isFileExist(fullPath);
    if(isExist)
    {
        Archive::getInstance()->release();
        Archive::getInstance()->archive_map = FileUtils::getInstance()->getValueMapFromFile(fullPath.c_str());
        Attribute::getInstance()->attr_map = Archive::getInstance()->archive_map["attr"].asValueMap();
        Props::getInstance()->props_map = Archive::getInstance()->archive_map["props"].asValueMap();
        Archive::getInstance()->stairsInfo_map = Archive::getInstance()->archive_map["stairsInfo"].asValueMap();
        Archive::getInstance()->scene_map = Archive::getInstance()->archive_map["scenario"].asValueMap();
        
        //更新属性和道具
        readAfterUpdate();
        loadStair();
    }
}
void ControlLayer::readAfterUpdate()    //读取存档更新显示的数据的函数
{
    attriFace->updateByMap();
    propsFace->updateByMap();
}
void ControlLayer::loadStair()
{
    if(gameLayer!=NULL)
    {
        gameLayer->removeFromParentAndCleanup(true);
        gameLayer = GameLayer::create();
        //gameLayer->initHero(Attribute::getInstance()->getHeroPos());
        addChild(gameLayer);
        gameLayer->setPosition(getGamePosByScreen());
    }
}
void ControlLayer::switchStair(int num)
{
    Vec2 pos;
    if(num>=0)//目标楼层是地上层
    {
        if(stairNum<=num)
        {
            pos = Archive::getInstance()->getUpPos(num);
        }
        else
        {
            pos = Archive::getInstance()->getDownPos(num);
        }
    }
    else //目标楼层是地下层
    {
        if(num>=stairNum)
        {
            pos = Archive::getInstance()->getDownPos(num);
        }
        else
        {
            pos = Archive::getInstance()->getUpPos(num);
        }
    }
    gameLayer->removeFromParentAndCleanup(true);
    gameLayer = GameLayer::create(num,pos);
    addChild(gameLayer);
    gameLayer->setPosition(getGamePosByScreen());
    //gameLayer->initHero(Vec2(5,8));
    stairNum = num;
}
void ControlLayer::HeroDie()
{
    PlaySound(Audio::die_e);
    
    auto black_lay = Layout::create();
    black_lay->setContentSize(gameLayer->tmxSize);
    addChild(black_lay);
    black_lay->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    black_lay->setColor(Color3B::BLACK);
    black_lay->setBackGroundColorOpacity(100);
    Vec2 pos = gameLayer->getPosition();
    black_lay->setPosition(Vec2(pos.x-gameLayer->tmxSize.width/2,pos.y-gameLayer->tmxSize.height/2));
    
    auto die_sp = Sprite::create("sword/die.png");
    addChild(die_sp,9);
    die_sp->setPosition(gameLayer->getPosition());
    auto move = MoveBy::create(1, Vec2(0,100));
    auto fin = FadeIn::create(0.5);
    auto spawn = Spawn::create(move,fin,NULL);
    die_sp->runAction(spawn);
    gameLayer->hero->removeFromParent();
    heroIsDie = true;
}
void ControlLayer::gameOver1()
{
    heroIsDie = true;
    Layout* endPre_lay = Layout::create();
    endPre_lay->setBackGroundColorType(cocos2d::ui::HBox::BackGroundColorType::SOLID);
    endPre_lay->setBackGroundColor(Color3B::BLACK);
    endPre_lay->setSwallowTouches(true);
    endPre_lay->setSize(cocos2d::Size(1080,1080));
    endPre_lay->setPosition(Vec2(gamePos.x-gameLayer->tmxSize.width/2,gamePos.y-gameLayer->tmxSize.height/2));
    endPre_lay->setTouchEnabled(true);
    Sprite* endPre_Sp = Sprite::create("Control/jieju1.png");
    endPre_Sp->setScale(2);
    endPre_Sp->setPosition(gamePos.x,-350);
    addChild(endPre_lay,5);
    addChild(endPre_Sp,6);
    auto move = MoveBy::create(10, Vec2(0,1200));
    auto func = CallFunc::create([=](){
        endPre_lay->addClickEventListener([=](Ref* p){
            SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            Director::getInstance()->replaceScene(HomeScene::createScene());
        });
    });
    auto seq = Sequence::create(move,func, NULL);
    endPre_Sp->runAction(seq);
    
    Audio::getInstance()->playBGM(Audio::bgmSucce);
}
void ControlLayer::gameOver2()
{
    heroIsDie = true;
    Layout* endPre_lay = Layout::create();
    endPre_lay->setBackGroundColorType(cocos2d::ui::HBox::BackGroundColorType::SOLID);
    endPre_lay->setBackGroundColor(Color3B::BLACK);
    endPre_lay->setSwallowTouches(true);
    endPre_lay->setSize(cocos2d::Size(1080,1080));
    endPre_lay->setPosition(Vec2(gamePos.x-gameLayer->tmxSize.width/2,gamePos.y-gameLayer->tmxSize.height/2));
    endPre_lay->setTouchEnabled(true);
    Sprite* endPre_Sp = Sprite::create("Control/jieju2.png");
    endPre_Sp->setScale(2);
    endPre_Sp->setPosition(gamePos.x,-350);
    addChild(endPre_lay,5);
    addChild(endPre_Sp,6);
    auto move = MoveBy::create(10, Vec2(0,1000));
    auto func = CallFunc::create([=](){
        endPre_lay->addClickEventListener([=](Ref* p){
            SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            Director::getInstance()->replaceScene(HomeScene::createScene());
        });
    });
    auto seq = Sequence::create(move,func, NULL);
    endPre_Sp->runAction(seq);
    
    Audio::getInstance()->playBGM(Audio::bgmSucce);
}
void ControlLayer::onClickBut_menu(Ref* p)
{
    if(menu->isVisible())
    {
        menu->setVisible(false);
    }
    else
    {
        auto scale = ScaleTo::create(0.2, 1);
        auto easeInOut = EaseBackOut::create(scale);
        menu->setVisible(true);
        menu->setScale(0.6);
        menu->runAction(easeInOut);
    }
}
void ControlLayer::onClickBut_foeData(Ref* p)
{
    if(heroIsDie)
        return;
    if(!foeData->isVisible())
    {
        foeData->setVisible(true);
        foeData->foeDataShow();
        GameScene::controlLayer->gameLayer->hero->isDialog = true;
    }
    else if(foeData->isVisible())
    {
        foeData->foeData_list->removeAllItems();
        foeData->setVisible(false);
        GameScene::controlLayer->gameLayer->hero->isDialog = false;
    }
}
void ControlLayer::onClickBut_flight(Ref* p)
{
    if(heroIsDie || gameLayer->hero->isFighting)
        return;
    bool isCanUse = true;   //debug
//    Vec2 h = GameScene::controlLayer->gameLayer->heroNowTilePos;
//    Vec2 hUp = h+Vec2(0,-1);
//    Vec2 hDown = h+Vec2(0,1);
//    Vec2 hLeft = h+Vec2(-1,0);
//    Vec2 hRight = h+Vec2(1,0);
//    TMXLayer* door_layer = gameLayer->door_layer;
//    if(hUp.x>=0 && hUp.x<TILE_MAPSIZE && hUp.y>=0 && hUp.y<TILE_MAPSIZE)
//    {
//        if(door_layer->getTileGIDAt(hUp)==e_doorUp || door_layer->getTileGIDAt(hUp)==e_doorDown)
//            isCanUse = true;
//    }
//    if(hDown.x>=0 && hDown.x<TILE_MAPSIZE && hDown.y>=0 && hDown.y<TILE_MAPSIZE)
//    {
//        if(door_layer->getTileGIDAt(hDown)==e_doorUp || door_layer->getTileGIDAt(hDown)==e_doorDown)
//            isCanUse = true;
//    }
//    if(hLeft.x>=0 && hLeft.x<TILE_MAPSIZE && hLeft.y>=0 && hLeft.y<TILE_MAPSIZE)
//    {
//        if(door_layer->getTileGIDAt(hLeft)==e_doorUp || door_layer->getTileGIDAt(hLeft)==e_doorDown)
//            isCanUse = true;
//    }
//    if(hRight.x>=0 && hRight.x<TILE_MAPSIZE && hRight.y>=0 && hRight.y<TILE_MAPSIZE)
//    {
//        if(door_layer->getTileGIDAt(hRight)==e_doorUp || door_layer
//           ->getTileGIDAt(hRight)==e_doorDown)
//            isCanUse = true;
//    }
    if(isCanUse==true && stairNum>=-25 && stairNum<=19)
    {
        stairFlight->show();
    }
    else
    {
        gameLayer->showHint(105);
    }
}
void ControlLayer::onClickBut_speDoor(Ref* p)
{
    if(heroIsDie || gameLayer->hero->isFighting)
        return;
    auto darkWall = gameLayer->tmx->getLayer("darkWall");
    if(darkWall==NULL)
    {
        gameLayer->showHint(105);
        return;
    }
    else
    {
        int gid = darkWall->getTileGIDAt(gameLayer->heroTarTilePos);
        if(gid!=0)
        {
            if(gameLayer->tmx->getChildByName("speDoor")==NULL)
            {
                auto dialog = Dialog::create();
                gameLayer->tmx->addChild(dialog,20,"speDoor");
                dialog->showDialogSpDoor();
                auto tmxSize = gameLayer->tmx->getContentSize();
                dialog->setPosition(tmxSize.width/2,tmxSize.height/2);
            }
        }
        else
        {
            gameLayer->showHint(105);
        }
    }
}
void ControlLayer::onClickBut_holy(Ref* p)
{
    if(heroIsDie || gameLayer->hero->isFighting)
        return;
    if(gameLayer->enemy_layer == NULL)
    {
        gameLayer->showHint(105);
        return;
    }
    if(stairNum==-25 && gameLayer->heroTarTilePos==Vec2(5,9))   //-25层的公主特别
    {
        if(gameLayer->NPC_layer->getTileGIDAt(Vec2(5,9))!=0)
        {
            if(gameLayer->tmx->getChildByName("holy")==NULL)
            {
                auto dialog = Dialog::create();
                gameLayer->tmx->addChild(dialog,20,"holy");
                dialog->showDialogHoly();
                auto tmxSize = gameLayer->tmx->getContentSize();
                dialog->setPosition(tmxSize.width/2,tmxSize.height*0.6);
            }
            return;
        }
    }
    auto enemy_layer = gameLayer->enemy_layer;
    int gid = enemy_layer->getTileGIDAt(gameLayer->heroTarTilePos);
    if(gid!=0)
    {
        int id = getEnemyIdInFile(gid);
        if(id==56 || id==41 || id==53 || id==8) //某些怪物不能使用
        {
            gameLayer->showHint(105);
            return;
        }
        else
        {
            if(gameLayer->tmx->getChildByName("holy")==NULL)
            {
                auto dialog = Dialog::create();
                gameLayer->tmx->addChild(dialog,20,"holy");
                dialog->showDialogHoly();
                auto tmxSize = gameLayer->tmx->getContentSize();
                dialog->setPosition(tmxSize.width/2,tmxSize.height*0.6);
            }
        }
    }
    else
    {
        gameLayer->showHint(105);
    }
}
//void ControlLayer::showFoeData()
//{
//    auto foeData =  FoeData::create();
//    addChild(foeData);
//    foeData->setPosition(gameLayer->tmx->getPosition());
//}
Vec2 ControlLayer::getGamePosByScreen()
{
    if(VISIBSIZE.width > VISIBSIZE.height)//横屏
    {
        float x = (VISIBSIZE.width-VISIBSIZE.height)/5*2.95 + VISIBSIZE.height/2;
        float y = VISIBSIZE.height/2;
        if(GETADS_NO==false)
            return Vec2(x,y+VISIBSIZE.height*0.078);
        else
            return Vec2(x,y);
    }
    else if(VISIBSIZE.width <= VISIBSIZE.height)//竖屏
    {
        float y = (VISIBSIZE.height-VISIBSIZE.width)/5*3 + VISIBSIZE.height/2;
        float x = VISIBSIZE.width/2;
        return Vec2(x,y);
    }
    return Vec2(VISIBSIZE.width/2-540,585);
}
void ControlLayer::showHint(int gid)
{
    
}
void ControlLayer::upOrDownstairs(int stairNum,Vec2 pos)
{
    if(this->stairNum==0)
        Audio::getInstance()->playBGM(Audio::bgm1);
    else if(stairNum==0)
        Audio::getInstance()->playBGM(Audio::bgm0);
    //Vec2 heroPos = pos;
    gameLayer->removeFromParentAndCleanup(true);
    gameLayer = GameLayer::create(stairNum,pos);
    addChild(gameLayer);
    gameLayer->setPosition(gamePos);
    //gameLayer->initHero(heroPos);
    this->stairNum = stairNum;  //楼层值记住
}
void ControlLayer::upOrDownSpeStair(int stairNum,int gid)
{
    int speStair = 101;
    Vec2 pos(5,10);
    if(gid == e_doorUp2)
    {
        switch (stairNum) {
            case 10:
                speStair = 110;
                break;
            case 17:
                speStair = 101;
                break;
            case -9:
                speStair = 106;
                break;
            case -17:
                speStair = 107;
                break;
            case -25:
                speStair = 108;
                break;
            case -22:
                speStair = 109;
                break;
            default:
                speStair = stairNum + 1;
                pos = gameLayer->heroNowTilePos;
                break;
        }
    }
    else if (gid == e_doorDown2)
    {
        switch (stairNum) {
            case 110:
                speStair = 10;
                pos.set(1,0);
                break;
            case 101:
                speStair = 17;
                pos.set(2,0);
                break;
            case 106:
                speStair = -9;
                pos.set(4,0);
                break;
            case 107:
                speStair = -17;
                pos.set(10,10);
                break;
            case 108:
                speStair = -25;
                break;
            case 109:
                speStair = -22;
                pos.set(10,0);
                break;
            default:
                speStair = stairNum-1;
                pos = gameLayer->heroNowTilePos;
                break;
        }
    }
    upOrDownstairs(speStair,pos);
}
bool ControlLayer::scenarioDet(int stairNum,Vec2 pos)
{
    if(stairNum==0 && pos==Vec2(5,8))
    {
        if(Attribute::getInstance()->attr_map["firstGame"].asBool()==true)//第一次来
        {
            meetNPC(8, gameLayer->heroTarTilePos);
            Attribute::getInstance()->attr_map["firstGame"] = false;
        }
    }
//    else if()
//    {
//    
//    }
    return false;
}
void ControlLayer::logicDoorDet(Vec2 pos)
{
    if(stairNum==-22)   //-22的门
    {
        if(pos.x==10 && (pos.y<=4 || pos.y>=1))
        {
            if(Props::getInstance()->getPropByGid(e_draft)>0)
            {
                gameLayer->removeDoor(pos);
                Props::getInstance()->addOnePropByGid(e_draft,-1);
            }
        }
    }
    else if(stairNum==12)
    {
        if(pos==Vec2(8,7))
        {
            if(gameLayer->enemy_layer->getTileGIDAt(Vec2(9,7))==0 && gameLayer->enemy_layer->getTileGIDAt(Vec2(10,7))==0)
            {
                if(gameLayer->enemy_layer->getTileGIDAt(Vec2(9,8))==0 && gameLayer->enemy_layer->getTileGIDAt(Vec2(10,8))==0)
                {
                    gameLayer->removeDoor(pos);
                }
            }
        }
    }
    else if(stairNum == -11)
    {
        if(pos==Vec2(9,3))
        {
            if(gameLayer->enemy_layer->getTileGIDAt(Vec2(8,4))==0 && gameLayer->enemy_layer->getTileGIDAt(Vec2(10,4))==0)
            {
                gameLayer->removeDoor(pos);
            }
        }
    }
    else if(stairNum == -12)
    {
        if(pos==Vec2(7,2))
        {
            if(gameLayer->enemy_layer->getTileGIDAt(Vec2(6,3))==0 && gameLayer->enemy_layer->getTileGIDAt(Vec2(8,3))==0)
            {
                gameLayer->removeDoor(pos);
            }
        }
    }
    else if(stairNum==-18)
    {
        if(pos==Vec2(5,1))
        {
            if(gameLayer->enemy_layer->getTileGIDAt(Vec2(0,0))==0 && gameLayer->enemy_layer->getTileGIDAt(Vec2(10,0))==0)
            {
                if(gameLayer->enemy_layer->getTileGIDAt(Vec2(0,10))==0 && gameLayer->enemy_layer->getTileGIDAt(Vec2(10,10))==0)
                {
                    gameLayer->removeDoor(pos);
                }
            }
        }
    }
}
void ControlLayer::logicFoeDet(Vec2 pos)
{
    if(stairNum==20 && pos == Vec2(5,0))
    {
        GameScene::controlLayer->gameLayer->prop_layer = GameScene::controlLayer->gameLayer->tmx->getLayer("prop2");
        GameScene::controlLayer->gameLayer->prop_layer->setVisible(true);
        GameScene::controlLayer->gameLayer->wall_layer->setTileGID(0, Vec2(5,3));
        GameScene::controlLayer->gameLayer->door_layer->setTileGID(e_doorDown, Vec2(4,10));
        GameScene::controlLayer->gameLayer->door_layer->setTileGID(e_doorDown, Vec2(6,10));
        Attribute::getInstance()->attr_map["20GZIsDie"] = true;
        
        auto dialog = Dialog::create();
        gameLayer->tmx->addChild(dialog,20);
        auto tmxSize = gameLayer->tmx->getContentSize();
        dialog->setPosition(tmxSize.width/2,tmxSize.height/2);
        dialog->showDialog(stairNum, 5, 5);
    }
}
void ControlLayer::meetNPC(int npcId,Vec2 tarTilePos)
{
    std::string npcKey;
    npcKey = StringUtils::format("NPC%d_%d",stairNum,npcId);
    log("vv:%s",npcKey.c_str());
    int npcState = Archive::getInstance()->getStairNpc_state(tarTilePos,stairNum);//npc状态
    if(npcState==0)
        npcState = 1;
    auto dialog = Dialog::create();
    gameLayer->tmx->addChild(dialog,20);
    auto tmxSize = gameLayer->tmx->getContentSize();
    dialog->setPosition(tmxSize.width/2,tmxSize.height/2);
    dialog->showDialog(stairNum, npcId, npcState);
    //meetNPCDeal(npcKey,eventTag,npcId,npcState);
}
void ControlLayer::getPropDeal(int gid)
{
    switch (gid) {
        case e_attGem:
            addAttack(2);
            break;
        case e_defGem:
            addDefen(2);
            break;
        case e_agile:
            addAgile(1);
            break;
        case e_HPBot1:
            addHP(150);
            break;
        case e_HPBot2:
            addHP(400);
            break;
        case e_potion:  //圣水
            addHP(Attribute::getInstance()->getHP());
            break;
        case e_key1:
            addHeroKey1(1);
            break;
        case e_key2:
            addHeroKey2(1);
            break;
        case e_key3:
            addHeroKey3(1);
            break;
        case e_bigKey1:
            addHeroKey1(1);
            addHeroKey2(1);
            addHeroKey3(1);
            break;
        case e_manual://怪物手册
            propsFace->but_foeData->setVisible(true);
            break;
        case e_coin:
            addGold(200);
            break;
        case e_draft:
            propsFace->props->addOnePropByGid(gid);
            break;
        case e_draft2:
            propsFace->props->addOnePropByGid(gid);
            break;
        case e_iceMagic:
            propsFace->props->addOnePropByGid(gid);
            break;
        case e_flight:  //升级
            addHP(400);
            addAttack(5);
            addDefen(5);
            break;
        case e_flightBig:  //大升级
            propsFace->but_flight->setVisible(true);
            propsFace->props->setPropByGid(e_flightBig, 1);
            break;
        case e_cross:
            propsFace->props->setPropByGid(e_cross, 1);
            break;
        case e_dagger:  //神圣之证
            propsFace->getHoly();
            meetNPC(9, Vec2(5,2));
            break;
        case e_magicRune:
            propsFace->props->setPropByGid(e_magicRune, 1);
            meetNPC(9, gameLayer->heroNowTilePos);
            break;
        case e_sword1:
            addAttack(8);
            break;
        case e_sword2:
            addAttack(16);
            break;
        case e_sword3:
            addAttack(30);
            break;
        case e_sword4:
            addAttack(40);
            break;
        case e_sword5:
            addAttack(50);
            break;
        case e_shield1:
            addDefen(7);
            break;
        case e_shield2:
            addDefen(13);
            break;
        case e_shield3:
            addDefen(22);
            break;
        case e_shield4:
            addDefen(35);
            break;
        case e_shield5:
            addDefen(50);
            break;
        case e_wand1:
            break;
        case e_wand2:
            upBaZhe();
            break;
        case e_wand3:
            upYongZhe();
            break;
        default:
            break;
    }
}
std::string ControlLayer::getStairStr(int stair)
{
    std::string str;
    if(stair>=0 && stair<=20)
    {
        str = "主塔  ";
    }
    else if(stair<0 && stair >= -25)
    {
        str = "地下塔  ";
    }
    else if(stair>100 && stair <= 110)
    {
        str = "神秘塔  ";
        stair = stair % 100;
    }
    else
        str = "";
    str.append(StringUtils::format("%dF",stair));
    return str;
}
void ControlLayer::upBaZhe() //霸者
{
    int n = propsFace->props->getPropByGid(e_wand2);
    if(n==0)   //升级第一级
    {
        gameLayer->hero->changeSkin(2);
        propsFace->props->setPropByGid(e_wand2,1);
        attriFace->state_lab->setString("霸者1级");
        attriFace->hero_sp->setTexture("hero2.png");
        attriFace->hero_sp->setTextureRect(Rect(0,0,32,32));
        if(stairNum==105)
        {
            gameLayer->wall_layer->setTileGID(4, Vec2(10,3));
            Archive::getInstance()->setStairNpc_map(Vec2(5,5),4 , -2);
        }
    }
    else if(n==1)
    {
        propsFace->props->setPropByGid(e_wand2,2);
        attriFace->state_lab->setString("霸者2级");
    }
    else if(n==2)
    {
        propsFace->props->setPropByGid(e_wand2,3);
        attriFace->state_lab->setString("霸者3级");
    }
    else if(n==3)
    {
        gameLayer->showHint(111);
    }
    return;
}
void ControlLayer::upYongZhe()  //勇者
{
    int n = propsFace->props->getPropByGid(e_wand3);
    if(n==0)    //升级第一级
    {
        gameLayer->hero->changeSkin(3);
        propsFace->props->setPropByGid(e_wand3,1);
        attriFace->state_lab->setString("勇者1级");
        attriFace->hero_sp->setTexture("hero3.png");
        attriFace->hero_sp->setTextureRect(Rect(0,0,32,32));
        if(stairNum==105)
        {
            gameLayer->wall_layer->setTileGID(4, Vec2(5,3));
            Archive::getInstance()->setStairNpc_map(Vec2(5,5),4 , -2);
        }
    }
    else if(n==1)
    {
        attriFace->state_lab->setString("勇者2级");
        Attribute::getInstance()->attr_map["attackTime"] = 2;
        propsFace->props->setPropByGid(e_wand3,2);
    }
    else if(n==2)
    {
        attriFace->state_lab->setString("勇者3级");
        propsFace->props->setPropByGid(e_wand3,3);
    }
    else
    {
        gameLayer->showHint(112);
    }
    return;
}
//属性增减
void ControlLayer::addAttack(int num)
{
    attriFace->addAttack(num);
}
void ControlLayer::addDefen(int num)
{
    attriFace->addDefen(num);
}
void ControlLayer::addAgile(int num)
{
    attriFace->addAgile(num);
}
void ControlLayer::addHP(int num)
{
    attriFace->addHP(num);
}
void ControlLayer::setAttack(int num)   //设置攻击
{
    attriFace->setAttack(num);
}
void ControlLayer::setDefen(int num)    //设置防御
{
    attriFace->setDefen(num);
}
void ControlLayer::setHP(int num)    //设置血量
{
    attriFace->setHP(num);
}
bool ControlLayer::useGold(int num)
{
    return attriFace->useGold(num);
}
void ControlLayer::addGold(int num)
{
    attriFace->addGold(num);
}
bool ControlLayer::useExp(int num)
{
    return attriFace->useExp(num);
}
void ControlLayer::addExp(int num)
{
    attriFace->addExp(num);
}
void ControlLayer::redOneKeyNumByVar(E_Door doorVar)    //减少key的数量
{
    propsFace->redOneKeyNumByVar(doorVar);
}
void ControlLayer::addHeroKey1(int num)
{
    propsFace->addHeroKey1(num);
}
void ControlLayer::addHeroKey2(int num)
{
    propsFace->addHeroKey2(num);
}
void ControlLayer::addHeroKey3(int num)
{
    propsFace->addHeroKey3(num);
}