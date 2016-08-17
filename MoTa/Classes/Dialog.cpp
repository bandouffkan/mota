//
//  Dialog.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/27.
//
//

#include "Dialog.hpp"
#include "NPC.hpp"
#include "Archive.hpp"
#include "GameConstants.h"
#include "ReadPlist.hpp"
#include "GameScene.h"
bool Dialog::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    boxWide = 3;
    
    GameScene::controlLayer->gameLayer->hero->isDialog = true;
    
    return true;
}
void Dialog::showDialog(int stair,int id,int state)
{
    this->stair = stair;
    this->npcId = id;
    this->npcState = state;
    int npcType = 0;    //npc的类型，0表示对话npc，1表示商店npc
    switch (stair) {
        case 0:
            if(id==2)
            {
                showDialog_store(2,2,1);
                return;
            }
            break;
        case 2:
            if(id==2 && state==1 && Props::getInstance()->getPropByGid(e_draft2)==0)
                npcType = 1;
            else if(id==2 && Props::getInstance()->getPropByGid(e_draft2)>0)
            {
                npcType = 0;
                state = 2;
            }
            break;
        case 4:
            if(id==4 && state==1)
            {
                npcType = 1;
            }
            break;
        case 5:
            if(id==4 && state==1)
            {
                npcType = 1;
            }
            break;
        case 15:
            if(id==4 && state==1)
            {
                npcType = 1;
            }
            break;
        case 3:
            if(id==6 && state==1)
            {
                npcType = 1;
            }
            break;
        case 7:
            if(id==7 && state==1)
            {
                npcType = 1;
            }
            break;
        case -1:
            if(id==3)
            {
                int wand2 = Props::getInstance()->getPropByGid(e_wand2);
                int wand3 = Props::getInstance()->getPropByGid(e_wand3);
                if((wand2>=1 && wand2<3) || (wand3>=1 && wand3<3))
                    npcType = 1;
                else if(wand2==3 || wand3==3)
                {
                    npcType = 0;
                    state = 6;
                }
            }
            break;
        case -5:
            if(id==6 && state==1)
            {
                npcType = 1;
            }
            break;
        case -7:
            if(id==7 && state==1)
            {
                npcType = 1;
            }
            break;
        case -14:
            if(id==3)
            {
                npcType = 1;
            }
        case -16:
            if(id==4 && state==1)
            {
                npcType = 1;
            }
            break;
        default:
            break;
    }
    if(npcType == 0)    //普通对话
    {
        showDialog_NPC(stair,id,state);
    }
    else if(npcType == 1)   //商店npc
    {
        showDialog_store(stair,id,state);
    }
}
void Dialog::showDialog_NPC(int stair,int id,int state)
{
    //底框
    bg_image = ImageView::create("dialog/dialog.png");
    addChild(bg_image);
    bg_image->setAnchorPoint(Vec2(0.5,0.5));
    bg_image->setPosition(Vec2(0,0));
    bg_size = bg_image->getContentSize();
    
    //npc的框
    auto npcBox_sp = Sprite::create("dialog/npcBox.png");
    bg_image->addChild(npcBox_sp);
    npcBox_sp->setPosition(bg_size.width*0.12,bg_size.height*0.82);
    
    //npc的图
    auto npc = NPC::create();
    bg_image->addChild(npc);
    npc->initById(id);
    npc->npcSprite->setAnchorPoint(Vec2(0.5,0.5));
    npc->setPosition(npcBox_sp->getPosition());
    
    if(stair==-10 && id==9)
    {
        npc->removeFromParent();
        auto sp = Sprite::create("dagger.png");
        bg_image->addChild(sp);
        sp->setPosition(npcBox_sp->getPosition());
    }
    else if(stair==-16 && id==9)
    {
        npc->removeFromParent();
        auto sp = Sprite::create("rune.png");
        bg_image->addChild(sp);
        sp->setPosition(npcBox_sp->getPosition());
    }
    else if(stair==20 && (state==1 || state==3))   //20层的
    {
        npc->removeFromParent();
        auto sp = Sprite::create("hero.png",Rect(0,0,32,32));
        bg_image->addChild(sp);
        sp->setPosition(npcBox_sp->getPosition());
    }
    else if(stair==-25 && id==5)
    {
        npc->removeFromParent();
        auto sp = Sprite::create("hero.png",Rect(0,0,32,32));
        bg_image->addChild(sp);
        sp->setPosition(npcBox_sp->getPosition());
    }
    else if(stair==108 && id==5)
    {
        npc->removeFromParent();
        auto sp = Sprite::create("hero.png",Rect(0,0,32,32));
        bg_image->addChild(sp);
        sp->setPosition(npcBox_sp->getPosition());
    }
    
    //退出按钮
    auto exit_but = Button::create("dialog/but.png");
    bg_image->addChild(exit_but);
    auto exit_size = exit_but->getContentSize();
    exit_but->setPosition(Vec2(bg_size.width-exit_size.width/2,exit_size.height/2));
    exit_but->addClickEventListener(CC_CALLBACK_1(Dialog::onClickBut_exit,this));
    
    //退出按钮上的字
    auto exit_lab = Label::createWithSystemFont("-点击-", "", 20);
    bg_image->addChild(exit_lab);
    exit_lab->setPosition(Vec2(bg_size.width-exit_size.width/2,exit_size.height/2));
    auto blink = Blink::create(100,80);
    exit_lab->runAction(blink);
    
    //npc的称呼
    std::string call_str;
    switch (id) {
        case 1:
            call_str = "仙子";
            break;
        case 2:
            call_str = "小偷";
            break;
        case 3:
            call_str = "老人";
            break;
        case 4:
            call_str = "商人";
            break;
        case 5:
            if(stair==20 && state>=4)
                call_str = "假公主";
            else
                call_str = "公主";
            break;
        default:
            break;
    }
    auto call_lab = Label::createWithSystemFont(call_str, "", 19);
    bg_image->addChild(call_lab);
    call_lab->setPosition(bg_size.width*0.55,bg_size.height*0.89);
    
    //npc的key
    if(stair>=0)
    {
        npcKey = StringUtils::format("NPC%d_%d",stair,id);
        log("vv1:%s",npcKey.c_str());
    }
    else
    {
        int s = abs(stair);
        npcKey = StringUtils::format("NPC_%d_%d",s,id);
    }
    //npc的话
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    ValueMap aamap = (*NPCTalk_map)[npcKey.c_str()].asValueMap();
    
    std::string strTalk = (*NPCTalk_map)[npcKey.c_str()].asValueMap()[StringUtils::format("talk%d",state).c_str()].asString();
    auto talk_lab = Label::createWithSystemFont(strTalk,"", 18);
    talk_lab->setWidth(175);
    bg_image->addChild(talk_lab);
    talk_lab->setPosition(Vec2(bg_size.width*0.55,bg_size.height*0.52));
}
void Dialog::showDialog_store(int stair,int id,int state)
{
    itemWith = 20;
    itemLabSize = 20;
    //底框
    bg_image = ImageView::create("dialog/storeBg.png");
    addChild(bg_image);
    bg_image->setAnchorPoint(Vec2(0.5,0.5));
    bg_image->setPosition(Vec2(0,0));
    bg_size = bg_image->getContentSize();
    
    //npc的框
    auto npcBox_sp = Sprite::create("dialog/npcBox.png");
    bg_image->addChild(npcBox_sp);
    npcBox_sp->setPosition(bg_size.width*0.12,bg_size.height*0.85);
    
    //npc的图
    auto npc = NPC::create();
    bg_image->addChild(npc);
    npc->initById(id);
    npc->npcSprite->setAnchorPoint(Vec2(0.5,0.5));
    npc->setPosition(npcBox_sp->getPosition());
    
//    //退出按钮
//    auto exit_but = Button::create("dialog/but.png");
//    bg_image->addChild(exit_but);
//    auto exit_size = exit_but->getContentSize();
//    exit_but->setPosition(Vec2(bg_size.width-exit_size.width/2,exit_size.height/2));
//    exit_but->addClickEventListener(CC_CALLBACK_1(Dialog::onClickBut_exit,this));
    
//    //退出按钮上的字
//    auto exit_lab = Label::createWithSystemFont("-Enter-", "", 20);
//    bg_image->addChild(exit_lab);
//    exit_lab->setPosition(Vec2(bg_size.width-exit_size.width/2,exit_size.height/2));
//    auto blink = Blink::create(100,80);
//    exit_lab->runAction(blink);
    
    //npc的称呼
    std::string call_str;
    switch (id) {
        case 1:
            call_str = "仙子";
            break;
        case 2:
            call_str = "小偷";
            break;
        case 3:
            call_str = "老人";
            break;
        case 4:
            call_str = "商人";
            break;
        case 5:
            call_str = "公主";
            break;
        case 6:
            call_str = "贪婪之神";
            break;
        case 7:
            call_str = "战斗之神";
            break;
        default:
            break;
    }
    auto call_lab = Label::createWithSystemFont(call_str, "", 17);
    bg_image->addChild(call_lab);
    call_lab->setPosition(bg_size.width*0.55,bg_size.height*0.94);
    
    //npc的key
    if(stair>=0)
        npcKey = StringUtils::format("NPC%d_%d",stair,id);
    else
    {
        int s = abs(stair);
        npcKey = StringUtils::format("NPC_%d_%d",s,id);
    }
    //npc的话
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    ValueMap aamap = (*NPCTalk_map)[npcKey.c_str()].asValueMap();
    std::string strTalk = (*NPCTalk_map)[npcKey.c_str()].asValueMap()[StringUtils::format("talk%d",state).c_str()].asString();
    auto talk_lab = Label::createWithSystemFont(strTalk,"", 16);
    talk_lab->setWidth(175);
    bg_image->addChild(talk_lab,0,"talk");
    talk_lab->setPosition(Vec2(bg_size.width*0.6,bg_size.height*0.8));
    
    switch (stair) {
        case 2:
            if(id==2 && state==1)
                npc2_2();
            break;
        case 4:
            if(id==4 && state==1)
            {
                npc4_4();
            }
            break;
        case 5:
            if(id==4 && state==1)
            {
                npc5_4();
            }
            break;
        case 15:
            if(id==4 && state==1)
            {
                npc15_4();
            }
            break;
        case 3:
            if(id==6 && state==1 && Attribute::getInstance()->getIsUseStore2()==false)
            {
                npc3_6();
            }
            else if(id==6 && Attribute::getInstance()->getIsUseStore2()==true)
            {
                npc_5_6();
            }
                break;
        case 7:
            if(id==7 && state==1)
            {
                npc7_7();
            }
            break;
        case -1:
            if(id==3 && Props::getInstance()->getPropByGid(e_wand2))//霸者
            {
                npc_1_BaZhe();
            }
            else if(id==3 && Props::getInstance()->getPropByGid(e_wand3))//勇者
            {
                npc_1_YongZhe();
            }
            break;
        case -5:
            if(id==6 && state==1)
            {
                npc_5_6();
            }
            break;
        case -7:
            if(id==7 && state==1)
            {
                npc_7_7();
            }
            break;
        case -14:
            if(id==3)
                npc_14_3();
            break;
        case -16:
            if(id==4 && state==1)
            {
                npc_16_4();
            }
            break;
        default:
            break;
    }
}
void Dialog::onClickBut_exit(Ref* p)
{
    if(stair == -2 && npcId==1)   //仙子
    {
        npcState++;
        if(npcState==1)
            npcState++;
        else if(npcState==4 && (Props::getInstance()->getPropByGid(e_wand2)==0 && Props::getInstance()->getPropByGid(e_wand3)==0))
        {
            this->removeFromParent();
            GameScene::controlLayer->gameLayer->hero->isDialog = false;
            if(Props::getInstance()->getPropByGid(e_key5)==0)
            {
                Props::getInstance()->setPropByGid(e_key5,1);
                GameScene::controlLayer->gameLayer->showHint(20);
            }
            return;
        }
        else if(npcState==5 && (Props::getInstance()->getPropByGid(e_wand2)>0 || Props::getInstance()->getPropByGid(e_wand3)>0))
        {
            //得到一个章了
            GameScene::controlLayer->gameLayer->door_layer->setTileGID(e_doorDown, Vec2(0,0));
        }
        else if(npcState==6)    //话说完
        {
            this->removeFromParent();
            GameScene::controlLayer->gameLayer->hero->isDialog = false;
            return;
        }
        Archive::getInstance()->setStairNpc_map(Vec2(5,5),npcState,stair);
        auto dialog = Dialog::create();
        GameScene::controlLayer->gameLayer->tmx->addChild(dialog,20);
        auto tmxSize = GameScene::controlLayer->gameLayer->tmx->getContentSize();
        dialog->setPosition(tmxSize.width/2,tmxSize.height/2);
        dialog->showDialog(stair, npcId, npcState);
        this->removeFromParent();
    }
    else if(stair == -7 && npcId == 3)  //-7层送任意门
    {
        GameScene::controlLayer->propsFace->getSpDoor();
        GameScene::controlLayer->gameLayer->removeNPC(Vec2(3,7));
        this->removeFromParentAndCleanup(true);
        GameScene::controlLayer->gameLayer->hero->isDialog = false;
    }
    else if(stair==20)  //20层的公主
    {
        if(npcState<3)
        {
            npcState++;
            Archive::getInstance()->setStairNpc_map(Vec2(5,5),npcState,stair);
            auto dialog = Dialog::create();
            GameScene::controlLayer->gameLayer->tmx->addChild(dialog,20);
            auto tmxSize = GameScene::controlLayer->gameLayer->tmx->getContentSize();
            dialog->setPosition(tmxSize.width/2,tmxSize.height/2);
            dialog->showDialog(stair, npcId, npcState);
            this->removeFromParent();
        }
        else if(npcState==3)
        {
            GameScene::controlLayer->gameLayer->wall_layer->setTileGID(3, Vec2(5,3));
            npcState++;
            Archive::getInstance()->setStairNpc_map(Vec2(5,5),npcState,stair);
            auto dialog = Dialog::create();
            GameScene::controlLayer->gameLayer->tmx->addChild(dialog,20);
            auto tmxSize = GameScene::controlLayer->gameLayer->tmx->getContentSize();
            dialog->setPosition(tmxSize.width/2,tmxSize.height/2);
            dialog->showDialog(stair, npcId, npcState);
            this->removeFromParentAndCleanup(true);
        }
        else if(npcState==4)    //假公主变形
        {
            GameScene::controlLayer->gameLayer->removeNPC(Vec2(5,0));
            GameScene::controlLayer->gameLayer->enemy_layer->setTileGID(121,Vec2(5,0));
            
            this->removeFromParent();
            GameScene::controlLayer->gameLayer->hero->isDialog = false;
        }
        else if(npcState==5)
        {
//            GameScene::controlLayer->gameLayer->prop_layer = GameScene::controlLayer->gameLayer->tmx->getLayer("prop2");
//            GameScene::controlLayer->gameLayer->prop_layer->setVisible(true);
            this->removeFromParentAndCleanup(true);
            GameScene::controlLayer->gameLayer->hero->isDialog = false;
        }
        else
        {
            this->removeFromParentAndCleanup(true);
            GameScene::controlLayer->gameLayer->hero->isDialog = false;
        }
    }
    else if(stair==2 && npcId==2 && Props::getInstance()->getPropByGid(e_draft2)>0)   //2层小偷
    {
        Attribute::getInstance()->attr_map["downIsOpen"] = true;
        GameScene::controlLayer->gameLayer->removeNPC(Vec2(5,1));
        this->removeFromParentAndCleanup(true);
        GameScene::controlLayer->gameLayer->hero->isDialog = false;
    }
    else if(stair == 105 && npcState==1)
    {
        npcState++;
        Archive::getInstance()->setStairNpc_map(Vec2(0,10),npcState,stair);
        auto dialog = Dialog::create();
        GameScene::controlLayer->gameLayer->tmx->addChild(dialog,20);
        auto tmxSize = GameScene::controlLayer->gameLayer->tmx->getContentSize();
        dialog->setPosition(tmxSize.width/2,tmxSize.height/2);
        dialog->showDialog(stair, npcId, npcState);
        this->removeFromParentAndCleanup(true);
    }
    else if(stair == -25 && npcId==5)
    {
        dilagExit();
        GameScene::controlLayer->gameOver1();
    }
    else if(stair == 108 && npcId==5)
    {
        dilagExit();
        GameScene::controlLayer->gameOver2();
    }
    else
    {
        this->removeFromParentAndCleanup(true);
        GameScene::controlLayer->gameLayer->hero->isDialog = false;
    }
}
void Dialog::showDialogHoly()   //神剑之证
{
    //底框
    bg_image = ImageView::create("dialog/dialog2.png");
    addChild(bg_image);
    bg_image->setAnchorPoint(Vec2(0.5,0.5));
    bg_image->setPosition(Vec2(0,0));
    bg_size = bg_image->getContentSize();
    
    auto sp = Sprite::create("dagger.png");
    bg_image->addChild(sp);
    sp->setPosition(bg_size.width*0.4,bg_size.height*0.8);
    
    int num = Props::getInstance()->getPropByGid(e_dagger);
    auto num_lab = Label::createWithSystemFont(StringUtils::format("X %d",num), "", 20);
    bg_image->addChild(num_lab);
    num_lab->setPosition(bg_size.width*0.6,bg_size.height*0.8);
    
    auto expl_lab = Label::createWithSystemFont("对怪物使用,使他变成史莱姆","",20);
    bg_image->addChild(expl_lab);
    expl_lab->setPosition(bg_size.width*0.5,bg_size.height*0.5);
    
    auto yes_but = Button::create("dialog/yes.png");
    bg_image->addChild(yes_but);
    yes_but->setPosition(Vec2(bg_size.width*0.2,bg_size.height*0.2));
    yes_but->addClickEventListener([=](Ref* p){
        if(Props::getInstance()->getPropByGid(e_dagger)>0)
        {
            GameScene::controlLayer->gameLayer->changeEnemyToSLM();
        }
        dilagExit();
    });
    
    auto no_but = Button::create("dialog/no.png");
    bg_image->addChild(no_but);
    no_but->setPosition(Vec2(bg_size.width*0.8,bg_size.height*0.2));
    no_but->addClickEventListener([=](Ref* p){
        dilagExit();
    });
}
void Dialog::showDialogSpDoor() //任意门
{
    //底框
    bg_image = ImageView::create("dialog/dialog2.png");
    addChild(bg_image);
    bg_image->setAnchorPoint(Vec2(0.5,0.5));
    bg_image->setPosition(Vec2(0,0));
    bg_size = bg_image->getContentSize();
    
    auto sp = Sprite::create("speDoor.png");
    bg_image->addChild(sp);
    sp->setPosition(bg_size.width*0.4,bg_size.height*0.8);
    
    int num = Props::getInstance()->getPropByGid(e_speDoor);
    auto num_lab = Label::createWithSystemFont(StringUtils::format("X %d",num), "", 20);
    bg_image->addChild(num_lab);
    num_lab->setPosition(bg_size.width*0.6,bg_size.height*0.8);
    
    auto expl_lab = Label::createWithSystemFont("使墙变成黄门","",20);
    bg_image->addChild(expl_lab);
    expl_lab->setPosition(bg_size.width*0.5,bg_size.height*0.5);
    
    auto yes_but = Button::create("dialog/yes.png");
    bg_image->addChild(yes_but);
    yes_but->setPosition(Vec2(bg_size.width*0.2,bg_size.height*0.2));
    yes_but->addClickEventListener([=](Ref* p){
        if(Props::getInstance()->getPropByGid(e_speDoor)>=1)
        {
            GameScene::controlLayer->gameLayer->changeWallToDoor();
            dilagExit();
        }
        else
        {
            GameScene::controlLayer->gameLayer->showHint(105);
        }
    });
    
    auto no_but = Button::create("dialog/no.png");
    bg_image->addChild(no_but);
    no_but->setPosition(Vec2(bg_size.width*0.8,bg_size.height*0.2));
    no_but->addClickEventListener([=](Ref* p){
        dilagExit();
    });
}
void Dialog::dilagExit()
{
    GameScene::controlLayer->gameLayer->hero->isDialog = false;
    this->removeFromParentAndCleanup(true);
}
void Dialog::npc2_2()
{
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    std::string strGoods1 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods1"].asString();
    std::string strGoods2 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods2"].asString();
    std::string strCancel = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["cancel"].asString();
    auto goods1_lab = Label::createWithSystemFont(strGoods1, "", itemLabSize);
    auto goods2_lab = Label::createWithSystemFont(strGoods2, "", itemLabSize);
    auto cancel_lab = Label::createWithSystemFont(strCancel, "", itemLabSize);
    MenuItemLabel* menuItem1 = MenuItemLabel::create(goods1_lab, [=](Ref* pSender){
        if(GameScene::controlLayer->useGold(20))
        {
            GameScene::controlLayer->addHeroKey1(1);
        }
    });
    MenuItemLabel* menuItem2 = MenuItemLabel::create(goods2_lab, [=](Ref* pSender){
        if(GameScene::controlLayer->useGold(80))
        {
            GameScene::controlLayer->addHeroKey2(1);
        }
    });
    MenuItemLabel* menuItem3 = MenuItemLabel::create(cancel_lab, [=](Ref* pSender){
        dilagExit();
    });
    Menu* pMenu =Menu::create(menuItem1,menuItem2,menuItem3,nullptr);
    bg_image->addChild(pMenu);
    pMenu->alignItemsVerticallyWithPadding(itemWith);
    pMenu->setPosition(bg_size.width/2,bg_size.height*0.35);
}
void Dialog::npc4_4()
{
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    std::string strGoods1 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods1"].asString();
    std::string strGoods2 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["cancel"].asString();
    auto goods1_lab = Label::createWithSystemFont(strGoods1, "", itemLabSize);
    auto goods2_lab = Label::createWithSystemFont(strGoods2, "", itemLabSize);
    MenuItemLabel* menuItem1 = MenuItemLabel::create(goods1_lab, [=](Ref* pSender){
        if(GameScene::controlLayer->useGold(15))
        {
            GameScene::controlLayer->addHP(200);
            GameScene::controlLayer->gameLayer->removeNPC(Vec2(6,3));
            dilagExit();
        }
    });
    MenuItemLabel* menuItem2 = MenuItemLabel::create(goods2_lab, [=](Ref* pSender){
        dilagExit();
    });
    Menu* pMenu =Menu::create(menuItem1,menuItem2,nullptr);
    bg_image->addChild(pMenu);
    pMenu->alignItemsVerticallyWithPadding(itemWith);
    pMenu->setPosition(bg_size.width/2,bg_size.height*0.35);
}
void Dialog::npc5_4()
{
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    std::string strGoods1 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods1"].asString();
    std::string strGoods2 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["cancel"].asString();
    auto goods1_lab = Label::createWithSystemFont(strGoods1, "", itemLabSize);
    auto goods2_lab = Label::createWithSystemFont(strGoods2, "", itemLabSize);
    MenuItemLabel* menuItem1 = MenuItemLabel::create(goods1_lab, [=](Ref* pSender){
        if(GameScene::controlLayer->useGold(40))
        {
            GameScene::controlLayer->addAttack(4);
            GameScene::controlLayer->gameLayer->showHint(107);
            GameScene::controlLayer->gameLayer->removeNPC(Vec2(7,0));
            dilagExit();
        }
    });
    MenuItemLabel* menuItem2 = MenuItemLabel::create(goods2_lab, [=](Ref* pSender){
        dilagExit();
    });
    Menu* pMenu =Menu::create(menuItem1,menuItem2,nullptr);
    bg_image->addChild(pMenu);
    pMenu->alignItemsVerticallyWithPadding(itemWith);
    pMenu->setPosition(bg_size.width/2,bg_size.height*0.35);
}
void Dialog::npc15_4()
{
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    std::string strGoods1 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods1"].asString();
    std::string strGoods2 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods2"].asString();
    std::string strGoods3 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods3"].asString();
    std::string strCancel = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["cancel"].asString();
    auto goods1_lab = Label::createWithSystemFont(strGoods1, "", itemLabSize);
    auto goods2_lab = Label::createWithSystemFont(strGoods2, "", itemLabSize);
    auto goods3_lab = Label::createWithSystemFont(strGoods3, "", itemLabSize);
    auto cancel_lab = Label::createWithSystemFont(strCancel, "", itemLabSize);
    MenuItemLabel* menuItem1 = MenuItemLabel::create(goods1_lab, [=](Ref* pSender){
        if(Props::getInstance()->getKey1Num()>0)
        {
            GameScene::controlLayer->addGold(10);
            GameScene::controlLayer->propsFace->redOneKeyNumByVar(e_door1);
        }
    });
    MenuItemLabel* menuItem2 = MenuItemLabel::create(goods2_lab, [=](Ref* pSender){
        if(Props::getInstance()->getKey2Num()>0)
        {
            GameScene::controlLayer->addGold(40);
            GameScene::controlLayer->propsFace->redOneKeyNumByVar(e_door2);
        }
    });
    MenuItemLabel* menuItem3 = MenuItemLabel::create(goods3_lab, [=](Ref* pSender){
        if(Props::getInstance()->getKey3Num()>0)
        {
            GameScene::controlLayer->addGold(250);
            GameScene::controlLayer->propsFace->redOneKeyNumByVar(e_door3);
        }
    });
    MenuItemLabel* menuItem4 = MenuItemLabel::create(cancel_lab, [=](Ref* pSender){
        dilagExit();
    });
    Menu* pMenu =Menu::create(menuItem1,menuItem2,menuItem3,menuItem4,nullptr);
    bg_image->addChild(pMenu);
    pMenu->alignItemsVerticallyWithPadding(itemWith);
    pMenu->setPosition(bg_size.width/2,bg_size.height*0.35);
}
void Dialog::npc3_6()
{
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    int costGold = Attribute::getInstance()->getStore1Price();
    int hp = 500;
    int atta = 3;
    int defen = 3;
    std::string talk_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["talk1"].asString();
    std::string HP_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goodsHP"].asString();
    std::string atta_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goodsAtta"].asString();
    std::string defen_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goodsDefen"].asString();
    std::string cancel_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["cancel"].asString();
    auto talk_lab = bg_image->getChildByName<Label*>("talk");
    talk_lab->setString(StringUtils::format(talk_str.c_str(),costGold));
    auto labelHP = Label::createWithSystemFont(StringUtils::format(HP_str.c_str(),hp), "", itemLabSize);
    auto labelAttack = Label::createWithSystemFont(StringUtils::format(atta_str.c_str(),atta), "", itemLabSize);
    auto labelDefen = Label::createWithSystemFont(StringUtils::format(defen_str.c_str(),defen), "", itemLabSize);
    auto labelCancel = Label::createWithSystemFont(cancel_str, "", itemLabSize);
    MenuItemLabel* menuItem1 = MenuItemLabel::create(labelHP, [=](Ref* pSender){
        if(GameScene::controlLayer->useGold(costGold))
        {
            GameScene::controlLayer->attriFace->addHP(hp);
            Attribute::getInstance()->addStore1Price(1);
            int cost = Attribute::getInstance()->getStore1Price();
            talk_lab->setString(StringUtils::format(talk_str.c_str(),cost));
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem2 = MenuItemLabel::create(labelAttack, [=](Ref* pSender){
        if(GameScene::controlLayer->useGold(costGold))
        {
            GameScene::controlLayer->attriFace->addAttack(atta);
            Attribute::getInstance()->addStore1Price(1);
            int cost = Attribute::getInstance()->getStore1Price();
            talk_lab->setString(StringUtils::format(talk_str.c_str(),cost));
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem3 = MenuItemLabel::create(labelDefen, [=](Ref* pSender){
        if(GameScene::controlLayer->useGold(costGold))
        {
            GameScene::controlLayer->attriFace->addDefen(defen);
            Attribute::getInstance()->addStore1Price(1);
            int cost = Attribute::getInstance()->getStore1Price();
            talk_lab->setString(StringUtils::format(talk_str.c_str(),cost));
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem4 = MenuItemLabel::create(labelCancel, [=](Ref* pSender){
        dilagExit();
        //Audio::getInstance()->playSound(Audio::LEAVENPC);
    });
    Menu* pMenu = Menu::create(menuItem1,menuItem2,menuItem3,menuItem4,nullptr);
    bg_image->addChild(pMenu);
    pMenu->alignItemsVerticallyWithPadding(itemWith);
    pMenu->setPosition(bg_size.width/2,bg_size.height*0.35);
}
void Dialog::npc7_7()  //经验商店
{
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    std::string talk_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["talk1"].asString();
    std::string HP_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods1"].asString();
    std::string atta_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods2"].asString();
    std::string defen_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods3"].asString();
    std::string cancel_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["cancel"].asString();
    auto HP_lab = Label::createWithSystemFont(StringUtils::format(HP_str.c_str(),1), "", itemLabSize);
    auto atta_lab = Label::createWithSystemFont(StringUtils::format(atta_str.c_str(),1), "", itemLabSize);
    auto defe_lab = Label::createWithSystemFont(StringUtils::format(defen_str.c_str(),2), "", itemLabSize);
    auto cancel_lab = Label::createWithSystemFont(cancel_str, "", itemLabSize);
    MenuItemLabel* menuItem1 = MenuItemLabel::create(HP_lab, [=](Ref* pSender){
        if(GameScene::controlLayer->useExp(70))
        {
            GameScene::controlLayer->attriFace->addLevel(1);
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem2 = MenuItemLabel::create(atta_lab, [=](Ref* pSender){
        if(GameScene::controlLayer->useExp(20))
        {
            GameScene::controlLayer->attriFace->addAttack(1);
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem3 = MenuItemLabel::create(defe_lab, [=](Ref* pSender){
        if(GameScene::controlLayer->useExp(20))
        {
            GameScene::controlLayer->attriFace->addDefen(2);
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem4 = MenuItemLabel::create(cancel_lab, [=](Ref* pSender){
        dilagExit();
        //Audio::getInstance()->playSound(Audio::LEAVENPC);
    });
    Menu* pMenu = Menu::create(menuItem1,menuItem2,menuItem3,menuItem4,nullptr);
    bg_image->addChild(pMenu);
    pMenu->alignItemsVerticallyWithPadding(itemWith);
    pMenu->setPosition(bg_size.width/2,bg_size.height*0.35);
}
void Dialog::npc_2_1()
{
    
}
void Dialog::npc_5_6() //-5层金币商店
{
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    int costGold;
    if(Attribute::getInstance()->getIsUseStore2() == false)
    {
        costGold = 50;
        Attribute::getInstance()->setIsUseStore2(true);
        Attribute::getInstance()->setStore1Price(costGold);
    }
    else
    {
        costGold = Attribute::getInstance()->getStore1Price();
    }
    int hp = 800;
    int atta = 6;
    int defen = 6;
    std::string talk_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["talk1"].asString();
    std::string HP_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goodsHP"].asString();
    std::string atta_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goodsAtta"].asString();
    std::string defen_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goodsDefen"].asString();
    std::string cancel_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["cancel"].asString();
    auto talk_lab = bg_image->getChildByName<Label*>("talk");
    talk_lab->setString(StringUtils::format(talk_str.c_str(),costGold));
    auto labelHP = Label::createWithSystemFont(StringUtils::format(HP_str.c_str(),hp), "", itemLabSize);
    auto labelAttack = Label::createWithSystemFont(StringUtils::format(atta_str.c_str(),atta), "", itemLabSize);
    auto labelDefen = Label::createWithSystemFont(StringUtils::format(defen_str.c_str(),defen), "", itemLabSize);
    auto labelCancel = Label::createWithSystemFont(cancel_str, "", itemLabSize);
    MenuItemLabel* menuItem1 = MenuItemLabel::create(labelHP, [=](Ref* pSender){
        if(GameScene::controlLayer->useGold(costGold))
        {
            GameScene::controlLayer->attriFace->addHP(hp);
            Attribute::getInstance()->addStore1Price(2);
            int cost = Attribute::getInstance()->getStore1Price();
            talk_lab->setString(StringUtils::format(talk_str.c_str(),cost));
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem2 = MenuItemLabel::create(labelAttack, [=](Ref* pSender){
        if(GameScene::controlLayer->useGold(costGold))
        {
            GameScene::controlLayer->attriFace->addAttack(atta);
            Attribute::getInstance()->addStore1Price(2);
            int cost = Attribute::getInstance()->getStore1Price();
            talk_lab->setString(StringUtils::format(talk_str.c_str(),cost));
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem3 = MenuItemLabel::create(labelDefen, [=](Ref* pSender){
        if(GameScene::controlLayer->useGold(costGold))
        {
            GameScene::controlLayer->attriFace->addDefen(defen);
            Attribute::getInstance()->addStore1Price(2);
            int cost = Attribute::getInstance()->getStore1Price();
            talk_lab->setString(StringUtils::format(talk_str.c_str(),cost));
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem4 = MenuItemLabel::create(labelCancel, [=](Ref* pSender){
        dilagExit();
        //Audio::getInstance()->playSound(Audio::LEAVENPC);
    });
    Menu* pMenu = Menu::create(menuItem1,menuItem2,menuItem3,menuItem4,nullptr);
    bg_image->addChild(pMenu);
    pMenu->alignItemsVerticallyWithPadding(itemWith);
    pMenu->setPosition(bg_size.width/2,bg_size.height*0.35);
}
void Dialog::npc_7_7()
{
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    std::string talk_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["talk1"].asString();
    std::string HP_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods1"].asString();
    std::string atta_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods2"].asString();
    std::string defen_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods3"].asString();
    std::string cancel_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["cancel"].asString();
    auto HP_lab = Label::createWithSystemFont(StringUtils::format(HP_str.c_str(),3), "", itemLabSize);
    auto atta_lab = Label::createWithSystemFont(StringUtils::format(atta_str.c_str(),3), "", itemLabSize);
    auto defe_lab = Label::createWithSystemFont(StringUtils::format(defen_str.c_str(),5), "", itemLabSize);
    auto cancel_lab = Label::createWithSystemFont(cancel_str, "", itemLabSize);
    MenuItemLabel* menuItem1 = MenuItemLabel::create(HP_lab, [=](Ref* pSender){
        if(GameScene::controlLayer->useExp(190))
        {
            GameScene::controlLayer->attriFace->addLevel(3);
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem2 = MenuItemLabel::create(atta_lab, [=](Ref* pSender){
        if(GameScene::controlLayer->useExp(50))
        {
            GameScene::controlLayer->attriFace->addAttack(3);
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem3 = MenuItemLabel::create(defe_lab, [=](Ref* pSender){
        if(GameScene::controlLayer->useExp(50))
        {
            GameScene::controlLayer->attriFace->addDefen(5);
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem4 = MenuItemLabel::create(cancel_lab, [=](Ref* pSender){
        dilagExit();
        //Audio::getInstance()->playSound(Audio::LEAVENPC);
    });
    Menu* pMenu = Menu::create(menuItem1,menuItem2,menuItem3,menuItem4,nullptr);
    bg_image->addChild(pMenu);
    pMenu->alignItemsVerticallyWithPadding(itemWith);
    pMenu->setPosition(bg_size.width/2,bg_size.height*0.35);
}
void Dialog::npc_14_3()
{
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    int costGold;
    if(Attribute::getInstance()->getIsUseStore2() == false)
    {
        costGold = 150;
        Attribute::getInstance()->setIsUseStore2(true);
    }
    else
    {
        costGold = Attribute::getInstance()->getStore1Price();
    }
    std::string talk_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["talk1"].asString();
//    std::string HP_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goodsHP"].asString();
//    std::string atta_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goodsAtta"].asString();
//    std::string defen_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goodsDefen"].asString();
//    std::string cancel_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["cancel"].asString();
    auto talk_lab = bg_image->getChildByName<Label*>("talk");
    talk_lab->setString(StringUtils::format(talk_str.c_str(),costGold));
    auto goods1_lab = Label::createWithSystemFont("好", "", itemLabSize);
    auto cancel_lab = Label::createWithSystemFont("不了", "", itemLabSize);
    MenuItemLabel* menuItem1 = MenuItemLabel::create(goods1_lab, [=](Ref* pSender){
        if(GameScene::controlLayer->useGold(costGold))
        {
            Props::getInstance()->addOnePropByGid(e_speDoor);
            GameScene::controlLayer->gameLayer->showHint(106);
            //Audio::getInstance()->playSound(Audio::BUYSUCCE);
        }
        //else
        //Audio::getInstance()->playSound(Audio::BUYFAIL);
    });
    MenuItemLabel* menuItem2 = MenuItemLabel::create(cancel_lab, [=](Ref* pSender){
        dilagExit();
    });
    Menu* pMenu = Menu::create(menuItem1,menuItem2,nullptr);
    bg_image->addChild(pMenu);
    pMenu->alignItemsVerticallyWithPadding(itemWith*2);
    pMenu->setPosition(bg_size.width/2,bg_size.height*0.35);
}
void Dialog::npc_16_4()
{
    
}
void Dialog::npc_1_BaZhe()
{
    int wand2 = Props::getInstance()->getPropByGid(e_wand2);
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    std::string talk_str;
    if(wand2==1)
        talk_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["talk2"].asString();
    else if(wand2==2)
        talk_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["talk3"].asString();
    else if(wand2==3)
        return;
    auto talk_lab = bg_image->getChildByName<Label*>("talk");
    talk_lab->setString(talk_str);
    std::string strGoods1 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods1"].asString();
    std::string strGoods2 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["cancel"].asString();
    auto goods1_lab = Label::createWithSystemFont(strGoods1, "", itemLabSize);
    auto goods2_lab = Label::createWithSystemFont(strGoods2, "", itemLabSize);
    MenuItemLabel* menuItem1 = MenuItemLabel::create(goods1_lab, [=](Ref* pSender){
        if(wand2==1)
        {
            if(Attribute::getInstance()->getGrade()>=20)
            {
                Props::getInstance()->setPropByGid(e_wand2,2);
                GameScene::controlLayer->attriFace->state_lab->setString("霸者2级");
                GameScene::controlLayer->gameLayer->showHint(110);
            }
            else
                GameScene::controlLayer->gameLayer->showHint(109);
        }
        else if(wand2==2)
        {
            if(Attribute::getInstance()->getGrade()>=40 && GameScene::controlLayer->useExp(100))
            {
                Props::getInstance()->setPropByGid(e_wand2,3);
                GameScene::controlLayer->attriFace->state_lab->setString("霸者3级");
                GameScene::controlLayer->gameLayer->showHint(110);
            }
            else
                GameScene::controlLayer->gameLayer->showHint(109);
        }
        dilagExit();
    });
    MenuItemLabel* menuItem2 = MenuItemLabel::create(goods2_lab, [=](Ref* pSender){
        dilagExit();
    });
    Menu* pMenu =Menu::create(menuItem1,menuItem2,nullptr);
    bg_image->addChild(pMenu);
    pMenu->alignItemsVerticallyWithPadding(itemWith);
    pMenu->setPosition(bg_size.width/2,bg_size.height*0.35);
}
void Dialog::npc_1_YongZhe()
{
    int wand3 = Props::getInstance()->getPropByGid(e_wand3);
    ValueMap* NPCTalk_map = ReadPlist::getInstance()->getNPCTalkMap();
    std::string talk_str;
    if(wand3==1)
        talk_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["talk4"].asString();
    else if(wand3==2)
        talk_str = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["talk5"].asString();
    else if(wand3==3)
        return;
    auto talk_lab = bg_image->getChildByName<Label*>("talk");
    talk_lab->setString(talk_str);
    std::string strGoods1 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["goods1"].asString();
    std::string strGoods2 = (*NPCTalk_map)[npcKey.c_str()].asValueMap()["cancel"].asString();
    auto goods1_lab = Label::createWithSystemFont(strGoods1, "", itemLabSize);
    auto goods2_lab = Label::createWithSystemFont(strGoods2, "", itemLabSize);
    MenuItemLabel* menuItem1 = MenuItemLabel::create(goods1_lab, [=](Ref* pSender){
        if(wand3==1)
        {
            if(Attribute::getInstance()->getGrade()>=20 && GameScene::controlLayer->useGold(500))
            {
                Attribute::getInstance()->attr_map["attackTime"] = 2;
                Props::getInstance()->setPropByGid(e_wand3,2);
                GameScene::controlLayer->attriFace->state_lab->setString("勇者2级");
                GameScene::controlLayer->gameLayer->showHint(110);
            }
            else
                GameScene::controlLayer->gameLayer->showHint(109);
        }
        else if(wand3==2)
        {
            if(Attribute::getInstance()->getGrade()>=40)
            {
                Props::getInstance()->setPropByGid(e_wand3,3);
                GameScene::controlLayer->attriFace->state_lab->setString("勇者3级");
                GameScene::controlLayer->gameLayer->showHint(110);
            }
            else
                GameScene::controlLayer->gameLayer->showHint(109);
        }
        dilagExit();
    });
    MenuItemLabel* menuItem2 = MenuItemLabel::create(goods2_lab, [=](Ref* pSender){
        dilagExit();
    });
    Menu* pMenu =Menu::create(menuItem1,menuItem2,nullptr);
    bg_image->addChild(pMenu);
    pMenu->alignItemsVerticallyWithPadding(itemWith);
    pMenu->setPosition(bg_size.width/2,bg_size.height*0.35);
}