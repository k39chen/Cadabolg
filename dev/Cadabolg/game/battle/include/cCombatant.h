//====================================================================================
// @Title:      COMBATANT
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cCombatant.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  General class combatant for fighting units during a battle. Can be of either
//  adversary or comrade.
//
//====================================================================================
#ifndef __GAME_BATTLE_COMBATANT_H__
#define __GAME_BATTLE_COMBATANT_H__

#include "../../../prolix/common/include/cEntity.h"

// forward declaration
class cBattle;

//====================================================================================
//                                                                          cCombatant
//====================================================================================
class cCombatant : public cEntity
{
  protected:
    cSpriteGroup *HealthBar;
    cSpriteGroup *ManaBar;
    
  public:

    int health;
    int maxhealth;

    cBattle *Battle;

    void Update();

    cCombatant(cBattle *rBattle);
};

#endif