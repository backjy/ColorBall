//
//  ColorBallScene.cpp
//  ColorBall
//
//  Created by shine on 13-10-25.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "ColorBallScene.h"

#include "ColorBall.h"

#include "ColorBallTouchLayer.h"

Scene * ColorBallScene::create(int level)
{
    Scene * scene = Scene::create();
    ColorBallScene * layer = new ColorBallScene();
    layer->autorelease();
    layer->init();
    scene->addChild(layer);
    layer->initFindBalls(level);
    return scene;
}

ColorBallScene::ColorBallScene():
m_pAryAllBalls(NULL),
m_iLevel(1),
m_pCurSelect(NULL)
{
    
}

ColorBallScene::~ColorBallScene()
{
    if (m_pAryAllBalls) 
    {
        m_pAryAllBalls->release();
    }
}


bool ColorBallScene::init(void)
{
    if (!Layer::init())
    {
        return false;
    }
    
    Layer * background = LayerColor::create(Color4B(255, 255, 255, 255));
    addChild(background);
    
    m_pAryAllBalls = Array::create();
    m_pAryAllBalls->retain();
    
    return true;
}

void ColorBallScene::onEnter(void)
{
    Layer::onEnter();
    initSpriteBalls();// 初始化
    initFindBallsPosition();
//    add touch layer
    ColorBallTouchLayer * touchLayer = ColorBallTouchLayer::create();
    touchLayer->setCtrol(this);
    addChild(touchLayer);

    Size wS = Director::getInstance()->getWinSize();
    Point midPos = Point(wS.width/2, wS.height/2);

    String * levelStr = String::createWithFormat("第 %d 关",m_iLevel);

    LabelTTF * levelGuid = LabelTTF::create(levelStr->getCString(), "迷你简卡通", 50);
    levelGuid->setPosition(Point(midPos.x * 2.1, midPos.y));
    addChild(levelGuid);
    levelGuid->setColor(Color3B(0,0,0));

    MoveTo * moveTo1 = MoveTo::create(0.3, Point(midPos.x - 50,midPos.y));
    MoveTo * moveTo2 = MoveTo::create(0.1, Point(midPos));
    EaseBackInOut * ease = EaseBackInOut::create(Sequence::create(moveTo1, moveTo2, NULL));
    CallFunc * callShowAll = CallFunc::create(CC_CALLBACK_0(ColorBallScene::callFuncShowAllBalls,this));
    CallFunc * callGuidEnd = CallFunc::create(CC_CALLBACK_0(ColorBallScene::callFuncGuidEnd,this));

    ScaleTo * scaleTo = ScaleTo::create(0.3, 6);
    FadeOut * fadeOut = FadeOut::create(0.3);
    Spawn * spawn = Spawn::create(scaleTo, fadeOut, NULL);
    RemoveSelf * removeSelf = RemoveSelf::create();
    levelGuid->runAction(Sequence::create(ease, callShowAll, DelayTime::create(0.3),spawn, callGuidEnd, removeSelf, NULL));
}

void ColorBallScene::onEnterTransitionDidFinish(void)
{
    Layer::onEnterTransitionDidFinish();
}

void ColorBallScene::callFuncShowAllBalls()
{

    Object * obj = NULL;
    int i=0;
    CCARRAY_FOREACH(m_pAryAllBalls, obj)
    {
        ColorBall * ball = (ColorBall*)obj;

        ball->fadeIn(i/m_iCells);
        i++;
    }
}

void ColorBallScene::callFuncGuidEnd()
{
    log("guid end");
}

void ColorBallScene::onExit(void)
{
    Layer::onExit();
    m_pAryAllBalls->removeAllObjects();
}

void ColorBallScene::update(float delta)
{
    
}

void ColorBallScene::initFindBalls(int level)//初始化要找那些球球
{
    if (m_eFindBalls.size()!=0)// 
    {
        m_eFindBalls.clear();
    }
    
    for (int i=0; i<level + 1; i++)
    {
        
        int randType = (arc4random() % 4) + 1;
        
        m_eFindBalls.push_back((BallTypes)randType);
    }
    m_iLevel = level;
}

void ColorBallScene::initSpriteBalls()
{
    int cells       = m_iLevel / 4 + 3;// 关卡一共有多少个球按照 3 的倍数来初始化矩阵

    m_iCells = cells;

    float base      = 640.0f/cells;

    m_fRadius = base/2;
    
    float cellWidth = cells * base;
    float cellHeigh = cells * base;
    
    Point center(cellWidth/2,cellHeigh/2);
    
    Point leftTop(center.x - cellWidth/2 + base / 2, center.y + cellHeigh / 2 - base / 2);
    
    for (int y = 1; y < cells; y++)
    {
        for (int x = 0; x < cells; x++)
        {
            
            ColorBall * ball = ColorBall::create();
            ball->setPosition(Point(leftTop.x + x * base, leftTop.y - y * base));
            addChild(ball);
            
            m_pAryAllBalls->addObject(ball);
        }
    }
}

void ColorBallScene::initFindBallsPosition()
{
    int balls   = m_pAryAllBalls->count();
//    CCLOG("will setposition balls count-- :%d",m_eFindBalls.size());
    for (int i = 0; i < m_eFindBalls.size(); i++) 
    {
        int randPos = arc4random()%balls;
        while (true)
        {
            ColorBall * obj = (ColorBall*)m_pAryAllBalls->objectAtIndex(randPos);
            if (obj->getType() == color_deepGray)
            {
                obj->resetType((BallTypes)m_eFindBalls[i]);
                obj->tintBackColor();
                break;
            }
            else
            {
                randPos++;
                randPos = randPos>=balls?(0):randPos;
            }
        }
    }
}

bool ColorBallScene::touchBegin(Point &pos)
{
    m_pCurSelect = getBallOnTouchPosition(pos);
    if (m_pCurSelect)
    {
        m_pCurSelect->selected();
        return true;
    }
    return false;
}

void ColorBallScene::touchMove(Point &pos)
{
    if (m_pCurSelect)
    {
        float distance = pos.getDistance(m_pCurSelect->getPosition());
        if (distance >= m_fRadius)
        {
            m_pCurSelect->unselected();
            m_pCurSelect = NULL;
            return;
        }
    }
    else
    {
        m_pCurSelect = getBallOnTouchPosition(pos);
        if (m_pCurSelect)
        {
            m_pCurSelect->selected();
        }
    }
}

void ColorBallScene::touchEnd(Point &pos)
{
    if (m_pCurSelect)
    {
        m_pCurSelect->unselected();
        m_pCurSelect->tintBackColor();
        m_pCurSelect = NULL;
    }
}

ColorBall * ColorBallScene::getBallOnTouchPosition(cocos2d::Point &pos)
{

    Object * obj = NULL;
    CCARRAY_FOREACH(m_pAryAllBalls, obj)
    {
        ColorBall * ball = (ColorBall*)obj;
        float distance = pos.getDistance(ball->getPosition());
        if (distance <= m_fRadius)
        {

            return ball;
        }
    }
    return NULL;
}















