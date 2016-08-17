//
//  AttributeFace.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/24.
//
//

#ifndef AttributeFace_hpp
#define AttributeFace_hpp
//属性显示的界面类
#include "cocos2d.h"
#include "Attribute.hpp"
USING_NS_CC;

class AttributeFace : public Node
{
public:
    bool init();
    CREATE_FUNC(AttributeFace);
    void updateByMap();
    void uploadScore(); //上传分数
    
    void addLevel(int num); //增加一级
    //增加和减少属性
    void addAttack(int num);   //增加攻击
    void addDefen(int num);    //增加防御
    void addAgile(int num);
    void addHP(int num);    //增加血量
    //设置属性
    void setAttack(int num);   //设置攻击
    void setDefen(int num);    //设置防御
    void setHP(int num);    //设置血量
    //使用或增加金币
    bool useGold(int num);
    void addGold(int num);  //增加金钱
    //使用和增加经验
    bool useExp(int num);
    void addExp(int num);
    
    Attribute* attri;//勇士属性
    
    Sprite* hero_sp;
    //英雄属性的显示的Label
    Label* state_lab;
    Label* HP_lab;
    Label* attack_lab;
    Label* defense_lab;
    Label* agile_lab;
    Label* gold_lab;
    Label* exp_lab;
    Label* grade_lab;
    Label* stair_lab;
    
    cocos2d::Size face_size; //本属性界面的尺寸
};

#endif /* AttributeFace_hpp */
