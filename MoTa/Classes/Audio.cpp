//
//  Audio.cpp
//  MoTa
//
//  Created by xcode31 on 16/6/29.
//
//

#include "Audio.hpp"
USING_NS_CC;

Audio::Audio(){
    SoundState = true;
    BGMState = true;
}
Audio* Audio::audio = NULL;
Audio* Audio::getInstance(){
    if(audio == NULL){
        audio = new Audio();
        audio->init();
        return audio;
    }else{
        return audio;
    }
}
void Audio::release()
{
    if(audio != NULL)
    {
        delete audio;
        audio = NULL;
    }
}
bool Audio::init()
{
    SimpleAudioEngine::getInstance()->preloadEffect("audio/daji.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("audio/daoji.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("audio/bigDaji.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("audio/daji0.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("audio/miss.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("audio/25hongji.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("audio/chiProp.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("audio/openDoor.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("audio/swordOver.mp3");
    
    return true;
}
void Audio::playSound(int type){
    if (this->isOpenSound()){
        SimpleAudioEngine::getInstance()->stopAllEffects();
        switch (type)
        {
            case daji_e:
                SimpleAudioEngine::getInstance()->playEffect("audio/daji.mp3");
                break;
            case daoji_e:
                SimpleAudioEngine::getInstance()->playEffect("audio/daoji.mp3");
                break;
            case bigDaji_e:
                SimpleAudioEngine::getInstance()->playEffect("audio/bigDaji.mp3");
                break;
            case daji0_e:
                SimpleAudioEngine::getInstance()->playEffect("audio/daji0.mp3");
                break;
            case miss_e:
                SimpleAudioEngine::getInstance()->playEffect("audio/miss.mp3");
                break;
            case hongji_e:
                SimpleAudioEngine::getInstance()->playEffect("audio/25hongji.mp3");
                break;
            case chiProp_e:
                SimpleAudioEngine::getInstance()->playEffect("audio/chiProp.mp3");
                break;
            case door_e:
                SimpleAudioEngine::getInstance()->playEffect("audio/openDoor.mp3");
                break;
            case swordOver_e:
                SimpleAudioEngine::getInstance()->playEffect("audio/swordOver.mp3");
                break;
        }
    } else {
        SimpleAudioEngine::getInstance()->pauseAllEffects();
    }
}
void Audio::playBGM(int type)
{
    if (this->isOpenBGM())
    {
//        if(BGMType==type)
//            return;
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
        switch (type)
        {
            case die_e:
                SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/die.mp3",true);
                break;
            case bgm0:
                SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm0.mp3",true);
                break;
            case bgm1:
                SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm1.mp3",true);
                break;
            case bgmSucce:
                SimpleAudioEngine::getInstance()->playEffect("audio/bgmSucce.mp3");
                break;
        }
        //BGMType = (E_voice)type;
    } else {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
}
void Audio::setSoundType(bool type){
    SoundState = type;
//    this->playSound(0);
}
void Audio::setBGMType(bool type)
{
    BGMState = type;
    this->playBGM(bgm0);
}
bool Audio::isOpenBGM()
{
    return BGMState;
}
bool Audio::isOpenSound()
{
    return SoundState;
}

