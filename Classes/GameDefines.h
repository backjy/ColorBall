//
//  GameDefines.h
//  ColorBall
//
//  Created by shine on 13-10-25.
//
//

#ifndef ColorBall_GameDefines_h
#define ColorBall_GameDefines_h



typedef enum //定义所需的球的类型
{
    color_green     = 1,
    color_blue      = 2,
    color_pink      = 3,
    color_purple    = 4,
    color_yellow    = 5,
    color_deepGray  = 0
} BallTypes;

typedef enum 
{
    ball_selected = 0,
    ball_idle,
}BallState;

#endif
