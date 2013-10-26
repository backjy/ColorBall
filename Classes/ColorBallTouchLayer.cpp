//
//  ColorBallTouchLayer.cpp
//  ColorBall
//
//  Created by shine on 13-10-26.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "ColorBallTouchLayer.h"

#include "ColorBallScene.h"

ColorBallTouchLayer::ColorBallTouchLayer():
m_pCtrl(NULL)
{
    
}

ColorBallTouchLayer::~ColorBallTouchLayer()
{
}


bool ColorBallTouchLayer::init(void)
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    return true;
}

void ColorBallTouchLayer::onEnter(void)
{
    CCLayer::onEnter();
    
    //set touch enable = yes,and delegate is oneByone
    this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    this->setTouchEnabled(true);
}

void ColorBallTouchLayer::onExit(void)
{
    CCLayer::onExit();

    m_pCtrl = NULL;
}

bool ColorBallTouchLayer::ccTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (!m_pCtrl)
    {
        return false;
    }
    Point touchLocation = pTouch->getLocation();
    return m_pCtrl->touchBegin(touchLocation);
}

void ColorBallTouchLayer::ccTouchMoved(Touch *pTouch, Event *pEvent)
{
    if (!m_pCtrl)
    {
        return;
    }
    Point touchLocation = pTouch->getLocation();
    m_pCtrl->touchMove(touchLocation);
}

void ColorBallTouchLayer::ccTouchEnded(Touch *pTouch, Event *pEvent)
{
    if (!m_pCtrl)
    {
        return;
    }
    Point touchLocation = pTouch->getLocation();
    m_pCtrl->touchEnd(touchLocation);

}

void ColorBallTouchLayer::ccTouchCancelled(Touch *pTouch, Event *pEvent)
{
    if (!m_pCtrl)
    {
        return;
    }
    Point touchLocation = pTouch->getLocation();
    m_pCtrl->touchEnd(touchLocation);

}

