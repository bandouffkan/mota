#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PropsFace.hpp"
#include "Audio.hpp"
USING_NS_CC;

using namespace cocostudio::timeline;
ControlLayer* GameScene::controlLayer = NULL;
Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();

    scene->addChild(layer);

    return scene;
}
Scene* GameScene::createArcScene(int num)
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();

    scene->addChild(layer);
    
    layer->controlLayer->readArchive(num);

    return scene;
}
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //背景
    auto bg_sp = Sprite::create("bg.png");
    auto bg_size = bg_sp->getContentSize();
    bg_size = bg_size * 1.5;
    int bg_x = ceil(VISIBSIZE.width/bg_size.width);
    int bg_y = ceil(VISIBSIZE.height/bg_size.height);
    for(int y=0;y<bg_y;y++)
    {
        for(int x=0;x<bg_x;x++)
        {
            auto sp = Sprite::create("bg.png");
            sp->setScale(1.5);
            addChild(sp);
            sp->setPosition(x*bg_size.width+bg_size.width/2,y*bg_size.height+bg_size.height/2);
        }
    }
    
    controlLayer = ControlLayer::create();
    addChild(controlLayer);
    
    //怪物的数据显示
    auto foeData = FoeData::create();
    controlLayer->addChild(foeData,10);
    Vec2 pos = controlLayer->gameLayer->getPosition();
    foeData->setPosition(pos.x-controlLayer->gameLayer->tmxSize.width/2,pos.y-controlLayer->gameLayer->tmxSize.height/2);
    foeData->setVisible(false);
    controlLayer->foeData = foeData;
    
    //道具里钥匙UI
    auto propsFace = PropsFace::create();
    controlLayer->addChild(propsFace,10);
    controlLayer->propsFace = propsFace;
    propsFace->setPosition(VISIBSIZE.width*0.83,VISIBSIZE.height*0.7);
    if(GETADS_NO==false)
    {
        propsFace->setPosition(VISIBSIZE.width*0.83,VISIBSIZE.height*0.77);
    }
        
    auto stairFlight = StairFlight::create();
    controlLayer->addChild(stairFlight,10);
    controlLayer->stairFlight = stairFlight;
    stairFlight->setPosition(0,0);
    stairFlight->setVisible(false);
    
    //商店
    auto shopFace = ShopFace::create();
    addChild(shopFace,10);
    shopFace->setPosition(controlLayer->gamePos);
    shopFace->setVisible(false);
    controlLayer->shopFace = shopFace;
    
    Audio::getInstance()->playBGM(Audio::bgm0);
    
    
    return true;
}
