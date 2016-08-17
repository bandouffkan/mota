//
//  GameMenu.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/24.
//
//

#ifndef GameMenu_hpp
#define GameMenu_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class GameMenu : public Node
{
public:
    bool init();
    CREATE_FUNC(GameMenu);
    void onClickBut_continue(Ref* p);
    void onClickBut_save(Ref* p);
    void onClickBut_read(Ref* p);
    void onClickBut_retHome(Ref* p);
    void onClickBut_shop(Ref* p);   //点击商店按钮
    
    
    Button* continue_but;
    Button* save_but;
    Button* read_but;
    Button* retHome_but;
    Button* shop_but;

};

#endif /* GameMenu_hpp */
