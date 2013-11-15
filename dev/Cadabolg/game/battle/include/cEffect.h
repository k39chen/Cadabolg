//====================================================================================
// @Title:      EFFECT
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cEffect.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Effects are particles used during the battle. This class is a single instance of
//  an effect to be played by an animation given a sprite.
//
//====================================================================================
#ifndef __GAME_BATTLE_EFFECT_H__
#define __GAME_BATTLE_EFFECT_H__

#include "../../../prolix/common/include/cSprite.h"
#include "../../../prolix/common/include/cAnimation.h"

//====================================================================================
//                                                                             cEffect
//====================================================================================
class cEffect
{
    cSprite *mSprite;
    cAnimation *mAnimation;
    bool mIsPlaying;             // flag to indicate whether or not the effect is playing
    int mSpeed;
    Point mPos;
    bool mLoop;

    void Init();    // initalize fields

  public:
    cSprite *Sprite();
    bool IsPlaying();

    // sets fields for playing the effect (must be called before playing an effect)
    void Generate(Point pos, int speed = 0, bool loop = false);
    void Play();
    void Stop();

    cEffect(cSprite *rSprite);          // Construct effect uisng sprite (uses all frames in order)
    cEffect(cAnimation *rAnimation);    // Construct effect using animation (custom frames)
};

#endif