//
//  PropsFace.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/24.
//
//

#ifndef PropsFace_hpp
#define PropsFace_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Props.hpp"
USING_NS_CC;
using namespace ui;
class PropsFace : public Node
{
public:
    bool init();
    CREATE_FUNC(PropsFace);
    void updateByMap();
    
    //钥匙的增加，买了钥匙或捡了钥匙
    void redOneKeyNumByVar(E_Door doorVar);    //减少key的数量
    void addHeroKey1(int num);
    void addHeroKey2(int num);
    void addHeroKey3(int num);
    
    void getSpDoor();   //得到任意门
    void getHoly(); //得到神圣之证
    
    //道具的点击函数
    void onClickBut_foeData(Ref* p);   //手册，查看怪物信息的按钮点击
    void onClickBut_flight(Ref* p);     //楼层飞行器
    
    Label* key1Num_lab;
    Label* key2Num_lab;
    Label* key3Num_lab;
    
    Button* but_foeData;    //怪物手册书
    Button* but_flight;
    Button* speDoor_but;    //任意门
    Button* holy_but;   //神圣之证
    
    cocos2d::Size face_size; //本界面的尺寸
    
    Props* props;//物品
};

#endif /* PropsFace_hpp */
