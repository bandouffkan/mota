//
//  HomeLayer.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/29.
//
//

#ifndef HomeLayer_hpp
#define HomeLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class HomeScene : public Layer
{
public:
    bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(HomeScene);
    
    
    void onClickBut_begin(Ref* p);
    void onClickBut_read(Ref* p);
    void onClickBut_set(Ref* p);
    void onClickBut_about(Ref* p);
    void onClickBut_setSound(Ref* p);
    void onClickBut_setBGM(Ref* p);
    
    Layout* voiceBg_lay;
    Sprite* gouSound;
    Sprite* gouBGM;
    
    bool isSoundOpen;
    bool isBGMOpen;
};

#endif /* HomeLayer_hpp */
