//
//  ReadPlist.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#ifndef ReadPlist_hpp
#define ReadPlist_hpp

#include "cocos2d.h"
USING_NS_CC;
class ReadPlist
{
public:
    enum
    {
        kChinese = 0,
        kEnglish,
    };
    ReadPlist();
    ~ReadPlist();
    static ReadPlist* instance;
    static ReadPlist * getInstance();
    void release();
    
    //每个plist文件对应一个函数，用它来读取并返回valueMap
    ValueMap* getEnemyMap();
    ValueMap* getNPCTalkMap();
    ValueMap* getinterfaceMap();
    ValueMap* getHintInfoMap(); //得到提示的map
    ValueMap* getPropGetHintMap();  //得到物品时的提示
    ValueMap* getSwordInfoMap();
    
    std::string getStringOnNPCMap(std::string NPCKey,std::string talkKey);
    
    //每有一个plist文件就加一个valueMap变量
    ValueMap enemyAttr_Map;
    ValueMap NPCTalk_map;
    ValueMap interface_map;
    ValueMap hintInfo_map;
    ValueMap propGetHint_map;
    ValueMap swordInfo_Map;
    
    int languageType;    //表示语言的类别,0中文，1英文
};

#endif /* ReadPlist_hpp */
