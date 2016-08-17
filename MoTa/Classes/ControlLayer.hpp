//
//  ControlLayer.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/12.
//
//

#ifndef ControlLayer_hpp
#define ControlLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameConstants.h"
#include "Attribute.hpp"
#include "GameLayer.hpp"
#include "Sword.hpp"
#include "ControlHandle.hpp"
#include "AttributeFace.hpp"
#include "PropsFace.hpp"
#include "StairFlight.hpp"
#include "GameMenu.hpp"
#include "ArchiveFace.hpp"
#include "FoeData.hpp"
#include "ShopFace.hpp"
USING_NS_CC;
using namespace ui;

class ControlLayer : public Layer
{
public:
    bool init();
    CREATE_FUNC(ControlLayer);
    //void onTouchButMove(Ref *pSender, ui::Widget::TouchEventType type);    //移动按键的点击事件
    //void changeControlPic(E_HeroDir dir);//改变控制器的图片
    void readArchive(int num);
    void readAfterUpdate();    //读取存档更新显示的数据的函数
    void loadStair();   //读取存档时，载入楼层和英雄位子
    void switchStair(int num);
    void HeroDie();
    void gameOver1(); //结局1
    void gameOver2(); //结局2，真结局
    
    void onClickBut_menu(Ref* p);
    //void onClickLayout_black(Ref* p);
    void onClickBut_foeData(Ref* p);   //手册，查看怪物信息的按钮点击
    void onClickBut_flight(Ref* p);     //楼层飞行器
    void onClickBut_speDoor(Ref* p); //任意门
    void onClickBut_holy(Ref* p);   //神圣之证
    
    void getPropDeal(int gid);//道具的处理
    std::string getStairStr(int stair);//根据楼层得到表示字符传
    
    //npc的处理
    void meetNPC(int npcId,Vec2 tarTilePos);
    
    //void showFoeData();
    Vec2 getGamePosByScreen();
    
    //显示提示信息
    void showHint(int gid);
    //上下楼梯
    void upOrDownstairs(int stairNum,Vec2 pos);
    void upOrDownSpeStair(int stairNum,int gid);    //上下神秘魔塔楼梯
    bool scenarioDet(int stairNum,Vec2 pos); //情景检测函数
    void logicDoorDet(Vec2 pos);    //逻辑门检测
    void logicFoeDet(Vec2 pos); //逻辑怪物的检测
    
    //霸者和勇者的升级
    void upBaZhe(); //霸者
    void upYongZhe();  //勇者
    //钥匙的增加，买了钥匙或捡了钥匙
    void redOneKeyNumByVar(E_Door doorVar);    //减少key的数量
    void addHeroKey1(int num);
    void addHeroKey2(int num);
    void addHeroKey3(int num);

    //增加和减少属性
    void addAttack(int num);   //增加攻击
    void addDefen(int num);    //增加防御
    void addAgile(int num);    //增加敏捷
    void addHP(int num);    //增加血量
    //设置属性
    void setAttack(int num);   //设置攻击
    void setDefen(int num);    //设置防御
    void setHP(int num);    //设置血量
    //使用或增加金币
    bool useGold(int num);
    void addGold(int num);  //增加金钱
    
    bool useExp(int num);//使用经验
    void addExp(int num);//增加经验
    
    int stairNum;//楼层值
    
    PropsFace* propsFace;
    AttributeFace* attriFace;
    StairFlight* stairFlight;
    
    Vec2 gamePos;
    GameLayer* gameLayer;//游戏层
    Sword* sword;
    ControlHandle* handle;//控制手柄
    GameMenu* menu;//菜单
    ArchiveFace* arcSaveFace;
    ArchiveFace* arcReadFace;
    FoeData* foeData;
    ShopFace* shopFace;
    //一些属性的显示
    //钥匙数量显示的Label
    Label* key1Num_lab;
    Label* key2Num_lab;
    Label* key3Num_lab;
    
    //显示魔塔层数的
    Sprite* stair_sp;
    Label* stair_lab;
//    //英雄属性的显示的Text
//    Label* HP_lab;
//    Label* attack_lab;
//    Label* defense_lab;
//    Label* gold_lab;
//    Label* exp_lab;
//    Label* grade_lab;
    bool heroIsDie;
private:
    Sprite* control_Sp; //显示控制图的精灵
    Node* cotroLayer_csb;
    
    Button* up_but;
    Button* down_but;
    Button* left_but;
    Button* right_but;
    
};

#endif /* ControlLayer_hpp */
