//
//  ShopFace.hpp
//  MoTa
//
//  Created by xcode31 on 16/8/5.
//
//

#ifndef ShopFace_hpp
#define ShopFace_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class ShopFace : public Node
{
public:
    bool init();
    CREATE_FUNC(ShopFace);
    void onClickBlack_lay(Ref* p);
    void onClickBut_buy1(Ref* p);
    void onClickBut_buy2(Ref* p);
    void judgeResponseFromBuy1(float dt);
    void judgeResponseFromBuy2(float dt);
    
    static bool isResulted;
    static int buyResults;
};

#endif /* ShopFace_hpp */
