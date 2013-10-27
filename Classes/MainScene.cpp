//
//  MainScene.cpp
//  ColorBall
//
//  Created by shine on 13-10-26.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "MainScene.h"

#include "ColorBallScene.h"

Scene * MainScene::getMainScene()
{
    Scene * mainScene = Scene::create();
    MainScene * layer = MainScene::create();
    mainScene->addChild(layer);
    return mainScene;
}

MainScene::MainScene()
{
    
}

MainScene::~MainScene()
{
    
}


bool MainScene::init(void)
{
    if (!CCLayer::init())
    {
        return false;
    }

    LayerColor * background = LayerColor::create(Color4B(230, 230, 230, 255));
    addChild(background);

    return true;
}

void MainScene::onEnter(void)
{

    CCLayer::onEnter();

//    LabelTTF * ttfReload = LabelTTF::create("迷你简卡通", "迷你简卡通", 40);
//    ttfReload->setPosition(Point(300, 200));
//    addChild(ttfReload);


    MenuItemFont * preLoad = MenuItemFont::create("单机 达人");
    preLoad->setFontName("迷你简卡通");
    preLoad->setFontSize(42);// 发现3.0 bug menuitemfont 设置字体的第一次无效

    MenuItemFont * startLabel = MenuItemFont::create("单机 达人", CC_CALLBACK_1(MainScene::callfuncSinglePlay  , this));
    startLabel->setFontName("迷你简卡通");
    startLabel->setFontSize(42);
    startLabel->setColor(Color3B(0, 0, 0));

    MenuItemFont * mutableLab = MenuItemFont::create("PK 达人", CC_CALLBACK_1(MainScene::callfuncMutablPlay  , this));
    mutableLab->setFontName("迷你简卡通");
    mutableLab->setFontSize(42);
    mutableLab->setColor(Color3B(0, 0, 0));

    MenuItemFont * aboutMe = MenuItemFont::create("About 我", CC_CALLBACK_1(MainScene::callfuncAboutMe  , this));
    aboutMe->setFontName("迷你简卡通");
    aboutMe->setFontSize(42);
    aboutMe->setColor(Color3B(0, 0, 0));

    Menu * menu = Menu::create(startLabel, mutableLab, aboutMe, NULL);
    menu->setAnchorPoint(Point(0, 0));
    menu->setPosition(Point(0, 0));
    addChild(menu);

    createMoveAction(2, startLabel);
    createMoveAction(1, mutableLab);
    createMoveAction(0, aboutMe);
}

void MainScene::createMoveAction(int count, cocos2d::Node *node)
{
    Size wS = Director::getInstance()->getWinSize();
    float heigh = wS.height/7 *(2+count) + 50;
    node->setPosition(Point(wS.width/2, wS.height + 50));

    MoveTo * moveTo1 = MoveTo::create(0.3, Point(wS.width/2, heigh - 50));
    MoveTo * moveTo2 = MoveTo::create(0.1, Point(wS.width/2, heigh));
    Sequence * seq   = Sequence::create(moveTo1, moveTo2, NULL);
    DelayTime * delay= DelayTime::create(0.25*count);
    node->runAction(Sequence::create(delay, EaseBackInOut::create(seq), NULL));
}

void MainScene::onEnterTransitionDidFinish(void)
{
    CCLayer::onEnterTransitionDidFinish();
}

void MainScene::onExit(void)
{
    CCLayer::onExit();
}

void MainScene::callfuncSinglePlay(cocos2d::Object *sender)
{
    Scene * scene = ColorBallScene::create(10);
    Director::getInstance()->pushScene(scene);
}

void MainScene::callfuncMutablPlay(cocos2d::Object *sender)
{

}

void MainScene::callfuncAboutMe(cocos2d::Object *sender)
{

}