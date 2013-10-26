//
//  ColorBall.h
//  ColorBall
//
//  Created by shine on 13-10-25.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _ColorBall_H
#define _ColorBall_H

#include "cocos2d.h"

#include "GameDefines.h"

using namespace cocos2d;


class ColorBall :public Node {
    
    BallTypes   m_eType;
    
    Sprite     *m_pSprite;
    
    BallState   m_eState;
public:
    ColorBall();
    virtual ~ColorBall();
    
    virtual bool init(void);
    virtual void onEnter(void);
    virtual void onExit(void);
    virtual void onEnterTransitionDidFinish(void);
    CREATE_FUNC(ColorBall);
    
    void resetType(BallTypes type);
    void tintToDeepGreey();
    void tintBackColor();
    
    void selected();
    void unselected();
    
    BallTypes getType()
    {
        return m_eType;
    }
    BallState getState()
    {
        return m_eState;
    }
};

#endif