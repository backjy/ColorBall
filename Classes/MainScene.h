//
//  MainScene.h
//  ColorBall
//
//  Created by shine on 13-10-26.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _MainScene_H
#define _MainScene_H

#include "cocos2d.h"

using namespace cocos2d;


class MainScene :public Layer
{
    
    
public:
    MainScene();
    virtual ~MainScene();

    static Scene * getMainScene();
    
    virtual bool init(void);
    virtual void onEnter(void);
    virtual void onExit(void);
    virtual void onEnterTransitionDidFinish(void);

    CREATE_FUNC(MainScene);
    void createMoveAction(int count,Node *node);

    void callfuncSinglePlay(Object * sender);
    void callfuncMutablPlay(Object * sender);
    void callfuncAboutMe(Object * sender);
};

#endif