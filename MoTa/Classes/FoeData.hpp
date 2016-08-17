//
//  FoeData.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/27.
//
//

#ifndef FoeData_hpp
#define FoeData_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

class FoeData : public Node
{
public:
    bool init();
    CREATE_FUNC(FoeData);
    void foeDataShow();
    void foeDataNoShow();
    
    ListView* foeData_list;
    
};

#endif /* FoeData_hpp */
