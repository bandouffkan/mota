//
//  Audio.hpp
//  MoTa
//
//  Created by xcode31 on 16/6/29.
//
//

#ifndef Audio_hpp
#define Audio_hpp

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
using namespace CocosDenshion;

#define PlaySound(__TYPE__) Audio::getInstance()->playSound(__TYPE__)
#define PlayBGM(__TYPE__) Audio::getInstance()->playBGM(__TYPE__)

class Audio{
public:
    enum E_voice{
        daji_e,
        daoji_e,
        bigDaji_e,
        daji0_e,
        miss_e,
        hongji_e,
        chiProp_e,
        door_e,
        swordOver_e,
        //bgm
        die_e,
        bgm0,
        bgm1,   //地上楼
        bgmSucce,
    };
    Audio();
    static Audio* getInstance();
    bool init();
    void release();
    void playSound(int type);
    void playBGM(int type);
    void setSoundType(bool type);
    void setBGMType(bool type);
    bool isOpenSound();
    bool isOpenBGM();
private:
    static Audio* audio;
    bool SoundState;
    bool BGMState;
    E_voice BGMType;
};

#endif /* Audio_hpp */
