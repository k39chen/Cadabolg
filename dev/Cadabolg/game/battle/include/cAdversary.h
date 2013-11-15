//====================================================================================
// @Title:      ADVERSARY
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cAdversary.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The data structure controlling the actions and maintenance for an arbitrary
//  adversary. Is dervied from the entity class.
//
//====================================================================================
#ifndef __GAME_BATTLE_ADVERSARY_H__
#define __GAME_BATTLE_ADVERSARY_H__

#include "../include/cCombatant.h"
#include "../include/cEffect.h"

// forward declaration
class cBattle;

//====================================================================================
//                                                                          cAdversary
//====================================================================================
class cAdversary : public cCombatant
{
    cSpriteGroup *mSpriteGroup;
    cEffect *mCollEffect;

  public:
    void Draw();        // draw the enemy
    void Move();        // move the enemy
    void Update();      // draw and move the enemy

    // Constructor
    cAdversary(cBattle *Battle, cSpriteGroup *rSpriteGroup);

    // Destructor
    virtual ~cAdversary();
};

#endif