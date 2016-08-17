//
//  Dialog.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/27.
//
//

#ifndef Dialog_hpp
#define Dialog_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

class Dialog : public Node
{
public:
    bool init();
    CREATE_FUNC(Dialog);
    void onClickBut_exit(Ref* p);
    
    void showDialog(int stair,int id,int state);
    void showDialog_NPC(int stair,int id,int state);
    void showDialog_store(int stair,int id,int state);
    
    void showDialogHoly();  //神剑之证的使用窗口
    void showDialogSpDoor();  //任意门的使用窗口
    
    void dilagExit();
    
    //卖东西商人的处理
    void npc2_2();
    void npc4_4();
    void npc5_4();
    void npc15_4();
    void npc3_6(); //金币商店
    void npc7_7();  //经验商店
    void npc_2_1();
    void npc_5_6(); //-5层金币商店
    void npc_7_7(); //经验商店
    void npc_14_3();   //任意门买
    void npc_16_4();
    void npc_1_BaZhe();
    void npc_1_YongZhe();
    
    int stair;
    int npcId;
    int npcState;
    
    float boxWide;
    std::string npcKey;
    Size bg_size;
    ImageView* bg_image;
    
    //对话框的一些布置参数
    int itemWith;   //选项间隔
    int itemLabSize;    //现象字体大小
    
//    bool holyIsShow;    //变形的窗口显示
//    bool SpDoorIsShow;  //任意门窗口显示
};

#endif /* Dialog_hpp */
