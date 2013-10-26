//
//  ColorBallTouchLayer.h
//  ColorBall
//
//  Created by shine on 13-10-26.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _ColorBallTouchLayer_H
#define _ColorBallTouchLayer_H

#include "cocos2d.h"

using namespace cocos2d;

class ColorBallScene;

class ColorBallTouchLayer :public Layer 
{
    
    ColorBallScene  *m_pCtrl;
public:
    ColorBallTouchLayer();
    virtual ~ColorBallTouchLayer();
    
    
    virtual bool init(void);
    virtual void onEnter(void);
    virtual void onExit(void);
    
    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void ccTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void ccTouchEnded(Touch *pTouch, Event *pEvent) override;
    virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent) override;
    
    CREATE_FUNC(ColorBallTouchLayer);
    
    void setCtrol(ColorBallScene * ctrl)
    {
        m_pCtrl = ctrl;
    }
    
};

#endif