//
//  ColorBallScene.h
//  ColorBall
//
//  Created by shine on 13-10-25.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _ColorBallScene_H
#define _ColorBallScene_H

#include "cocos2d.h"

#include "GameDefines.h"

USING_NS_CC;

using namespace std;

class ColorBall;

class ColorBallScene :public Layer 
{
    float               m_fRadius;
    int                 m_iLevel;
    vector<BallTypes>   m_eFindBalls;
    Array              *m_pAryAllBalls;
    ColorBall          *m_pCurSelect;
public:
    
    ColorBallScene();
    virtual ~ColorBallScene();
    
    static Scene * create(int level);
    
    virtual bool init(void);
    virtual void onEnter(void);
    virtual void onExit(void);
    virtual void onEnterTransitionDidFinish(void);
    
    void reloadGame(int level);
    bool touchBegin(Point &pos);
    void touchMove(Point &pos);
    void touchEnd(Point &pos);
private:
    
    void initFindBalls(int level);
    void initSpriteBalls();
    void initFindBallsPosition();
    
    void update(float delta);

    ColorBall * getBallOnTouchPosition(Point &pos);
};

#endif