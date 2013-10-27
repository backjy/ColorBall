//
//  ColorBall.cpp
//  ColorBall
//
//  Created by shine on 13-10-25.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "ColorBall.h"

static SpriteFrame * spriteFrameByType(BallTypes type)
{
    std::string fileName;
    switch (type) {
        case color_deepGray:
            fileName = "deepGray.png";
            break;
        case color_blue:
            fileName = "blue.png";
            break;
        case color_green:
            fileName = "green.png";
            break;
        case color_pink:
            fileName = "pink.png";
            break;
        case color_purple:
            fileName = "purple.png";
            break;
        case color_yellow:
            fileName = "yellow.png";
            break;
        default:
            CCLOG("----:ball CreateSpriteFrame failed");
            break;
    }
    Texture2D * texture = TextureCache::getInstance()->addImage(fileName.c_str());
    if (!texture)
    {
        CCLOG("----: texture is NULL");
    }
    Rect rect = Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
    SpriteFrame * frame = SpriteFrame::createWithTexture(texture, rect);
    
    return frame;
}

ColorBall::ColorBall():
m_eType(color_deepGray),
m_pSprite(NULL),
m_eState(ball_idle)
{
    
}

ColorBall::~ColorBall()
{
    
}

bool ColorBall::init()
{
    if (!CCNode::init()) 
    {
        return false;
    }
    
    m_pSprite = Sprite::createWithSpriteFrame(spriteFrameByType(m_eType));
    m_pSprite->setScale(0.6);// 图片太大了 要缩小 
    addChild(m_pSprite);

    m_pSprite->setVisible(false);
    
    return true;
}
void ColorBall::onEnter()
{
    CCNode::onEnter();
    
}

void ColorBall::onEnterTransitionDidFinish()
{
    CCNode::onEnterTransitionDidFinish();
}

void ColorBall::onExit()
{
    CCNode::onExit();
}

void ColorBall::resetType(BallTypes type)
{
    if (m_pSprite)
    {
        m_pSprite->setDisplayFrame(spriteFrameByType(type));
    }
    m_eType = type;
}

void ColorBall::tintBackColor()
{
    if (m_pSprite)
    {
        m_pSprite->setDisplayFrame(spriteFrameByType(m_eType));
    }
}

void ColorBall::tintToDeepGreey()
{
    if (m_pSprite)
    {
        m_pSprite->setDisplayFrame(spriteFrameByType(color_deepGray));
    }
}

void ColorBall::fadeIn(int wait)
{
    DelayTime * delay = DelayTime::create(wait*0.1);
    m_pSprite->setVisible(true);
    m_pSprite->setScale(0.1);
    ScaleTo * scale1 = ScaleTo::create(0.3, 0.9);
    ScaleTo * scale2 = ScaleTo::create(0.3, 0.6);
    ActionInterval * seq = EaseSineInOut::create(Sequence::create(scale1, scale2, NULL));
    m_pSprite->runAction(Sequence::create(delay, seq, NULL));
}


void ColorBall::selected()
{
    m_pSprite->stopAllActions();
    ScaleTo * scale = ScaleTo::create(0.1, 0.9);
    m_pSprite->runAction(EaseBackInOut::create(scale));
}

void ColorBall::unselected()
{

    m_pSprite->stopAllActions();
    ScaleTo * scale = ScaleTo::create(0.1, 0.6);
    m_pSprite->runAction(EaseBackInOut::create(scale));
}