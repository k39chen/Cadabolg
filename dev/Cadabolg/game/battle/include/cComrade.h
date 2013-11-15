//====================================================================================
// @Title:      COMRADE
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cComrade.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The data structure controlling the actions and maintenance for an arbitrary
//  comrade. Is dervied from the entity class.
//
//====================================================================================
#ifndef __GAME_BATTLE_COMRADE_H__
#define __GAME_BATTLE_COMRADE_H__

#include "../include/cCombatant.h"
#include "../include/cEffect.h"
#include "../../../prolix/engine/include/PrlxInput.h"

// forward declaration
class cBattle;

static const std::string MOVE_LEFT = "Move Left";
static const std::string MOVE_RIGHT = "Move Right";
static const std::string MOVE_UP = "Move Up";
static const std::string MOVE_DOWN = "Move Down";

//====================================================================================
//                                                                            cComrade
//====================================================================================
class cComrade : public cCombatant
{
    cSpriteGroup *mSpriteGroup;
    cEffect *mCollEffect;

  public:
    bool selected;
    cCommandGroup *Commands;

    void Select();

    void Draw();        // draw the enemy
    void Move();        // move the enemy
    void Update();      // draw and move the enemy

    // Constructor
    cComrade(cBattle *Battle, cSpriteGroup *rSpriteGroup);

    // Destructor
    virtual ~cComrade();
};

#endif