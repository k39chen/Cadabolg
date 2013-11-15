//====================================================================================
// @Title:      COMBATANT
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cCombatant.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cCombatant.h"
#include "../../../prolix/framework/include/cGame.h"

//====================================================================================
//                                                                          cCombatant
//====================================================================================
cCombatant::cCombatant(cBattle *rBattle):
    cEntity()
{
    Battle = rBattle;

    HealthBar = new cSpriteGroup();
    ManaBar = new cSpriteGroup();

    HealthBar->AddSprite("negative", new cSprite("health_bar_red.png", 1, 1));
    HealthBar->AddSprite("positive", new cSprite("health_bar_green.png", AssetMgr->Load<Texture>("health_bar_green.png")->dim.w, 1));
}

void cCombatant::Update()
{
}