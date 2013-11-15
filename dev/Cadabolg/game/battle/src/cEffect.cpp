//====================================================================================
// @Title:      EFFECT
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cEffect.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//
//====================================================================================
#include "../include/cEffect.h"
#include <iostream>

//====================================================================================
//                                                                             cEffect
//====================================================================================
cEffect::cEffect(cSprite *rSprite)
{
    Init();

    mSprite = rSprite;

    std::vector<int> frameset(0);
    for (int i=0; i<mSprite->numX * mSprite->numY; i++)
    {
        frameset.push_back(i);
    }
    mAnimation = new cAnimation(mSprite, frameset);
}

cEffect::cEffect(cAnimation *rAnimation)
{
    Init();

    mSprite = rAnimation->Sprite;
    mAnimation = rAnimation;
}

void cEffect::Init()
{
    mIsPlaying = false;
    mPos = Point(0,0);
    mSpeed = 0;
    mLoop = false;
}

cSprite *cEffect::Sprite()
{
    return mSprite;
}

bool cEffect::IsPlaying()
{
    return mIsPlaying;
}

void cEffect::Generate(Point pos, int speed, bool loop)
{
    mIsPlaying = true;
    mPos = pos;
    mSpeed = speed;
    mLoop = loop;
}

void cEffect::Play()
{
    if (mIsPlaying)
    {
        if (mLoop)
        {
            mAnimation->Play(mPos, mSpeed);
        }
        else
        {
            mAnimation->PlayOnce(mPos, mSpeed);
            if (!mAnimation->IsPlaying())
            {
                Stop();
            }
        }
    }
}

void cEffect::Stop()
{
    mIsPlaying = false;
    mAnimation->Stop();
}