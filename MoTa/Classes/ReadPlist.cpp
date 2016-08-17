//
//  ReadPlist.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/14.
//
//

#include "ReadPlist.hpp"

ReadPlist* ReadPlist::instance = NULL;

ReadPlist::ReadPlist()
{
    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    if(currentLanguageType==LanguageType::ENGLISH)
    {
        languageType = kEnglish;
    }
    else
    {
        languageType = kChinese;
    }
}
ReadPlist::~ReadPlist()
{}
ReadPlist* ReadPlist::getInstance()
{
    if(instance == NULL)
    {
        instance = new ReadPlist();
    }
    return instance;
}
void ReadPlist::release()
{
    if(instance != NULL)
    {
        delete instance;
        instance = NULL;
    }
}
ValueMap* ReadPlist::getEnemyMap()  //得到敌人的信息map
{
    if(enemyAttr_Map.empty()==true)
    {
        //if(languageType==kChinese) //是中文
            enemyAttr_Map = FileUtils::getInstance()->getValueMapFromFile("plist/enemyAttr.plist");
//        else
//            enemyAttr_Map = FileUtils::getInstance()->getValueMapFromFile("plist/enemyAttrEng.plist");
        
    }
    return &enemyAttr_Map;
}

ValueMap* ReadPlist::getNPCTalkMap()    //得到NPC说话的信息map
{
    if(NPCTalk_map.empty()==true)
    {
        //if(languageType==kChinese) //是中文
            NPCTalk_map =  FileUtils::getInstance()->getValueMapFromFile("plist/NPCTalk.plist");
//        else
//            NPCTalk_map =  FileUtils::getInstance()->getValueMapFromFile("plist/NPCTalkEng.plist");
    }
    return &NPCTalk_map;
}

ValueMap* ReadPlist::getinterfaceMap()
{
    if(interface_map.empty()==true)
    {
//        if(languageType==kChinese) //是中文
            interface_map = FileUtils::getInstance()->getValueMapFromFile("plist/InterfaceText.plist");
//        else
//            interface_map = FileUtils::getInstance()->getValueMapFromFile("plist/InterfaceTextEng.plist");
    }
    return &interface_map;
}
ValueMap* ReadPlist::getHintInfoMap()
{
    if(hintInfo_map.empty()==true)
    {
//        if(languageType==kChinese) //是中文
            hintInfo_map = FileUtils::getInstance()->getValueMapFromFile("plist/hintInfo.plist");
//        else
//            hintInfo_map = FileUtils::getInstance()->getValueMapFromFile("plist/hintInfoEng.plist");
    }
    return &hintInfo_map;
}

std::string ReadPlist::getStringOnNPCMap(std::string NPCKey,std::string talkKey)
{
    getNPCTalkMap();
    return NPCTalk_map[NPCKey.c_str()].asValueMap()[talkKey.c_str()].asString();
}
ValueMap* ReadPlist::getPropGetHintMap()
{
    if(propGetHint_map.empty()==true)
    {
//        if(languageType==kChinese)
//        {
            propGetHint_map = FileUtils::getInstance()->getValueMapFromFile("plist/propGetHint.plist");
//        }
//        else
//        {
//            propGetHint_map = FileUtils::getInstance()->getValueMapFromFile("plist/propGetHintEng.plist");
//        }
    }
    return &propGetHint_map;
}
ValueMap* ReadPlist::getSwordInfoMap()
{
    if(swordInfo_Map.empty()==true)
    {
//        if(languageType==kChinese) //是中文
//        {
            swordInfo_Map = FileUtils::getInstance()->getValueMapFromFile("plist/swordText.plist");
//        }
//        else
//        {
//            swordInfo_Map = FileUtils::getInstance()->getValueMapFromFile("plist/swordTextEng.plist");
//        }
    }
    return &swordInfo_Map;
}