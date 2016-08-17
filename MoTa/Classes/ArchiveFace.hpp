//
//  ArchiveFace.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/24.
//
//

#ifndef ArchiveFace_hpp
#define ArchiveFace_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Archive.hpp"
USING_NS_CC;
using namespace ui;
class ArchiveFace : public Node
{
public:
    typedef enum
    {
        e_read = 0,
        e_save,
    } E_Type;
    bool init(E_Type type_e);
    static ArchiveFace* create(E_Type type_e);
    void onClickBut_saveGame(Ref* p);   //保存存档
    void onClickBut_closeSave(Ref* p);  //关闭保存存档界面
    void onClickBut_readGame(Ref* p);   //保存存档
    void onClickBut_closeRead(Ref* p);  //关闭保存存档界面
    
    void saveFaceShow();
    void readFaceShow();
    
    Archive* archive;
    
    Layout* saveBg_lay;
    Button* save1_but;
    Button* save2_but;
    Button* save3_but;
    Button* save4_but;
    
    Layout* readBg_lay;
    Button* read1_but;
    Button* read2_but;
    Button* read3_but;
    Button* read4_but;
    
};


#endif /* ArchiveFace_hpp */
