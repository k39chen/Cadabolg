//====================================================================================
// @Title:      BATTLE STAGE
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cBattleStage.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The battle stage is the map where actors are to conduct their battles. This
//  module will maintain location tracking of each actor and terrain objects.
//
//====================================================================================
#ifndef __GAME_BATTLE_STAGE_H__
#define __GAME_BATTLE_STAGE_H__

//====================================================================================
//                                                                        cBattleStage
//====================================================================================
class cBattleStage
{
  public:
    // draw the stage
    void Draw();

    // Constructor
    cBattleStage();

    // Destructor
    ~cBattleStage();
};

#endif