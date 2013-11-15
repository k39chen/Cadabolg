//====================================================================================
// @Title:      BATTLE
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cBattle.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The battle is the focus of Cadabolg. This module will focus on initializing,
//  mainitaining, and recording the states, progress, and results of battle.
//
//====================================================================================
#ifndef __GAME_BATTLE_H__
#define __GAME_BATTLE_H__

#include "../include/cBattleStage.h"
#include "../include/cAdversary.h"
#include "../include/cComrade.h"
#include "../../../prolix/common/include/cLabel.h"

class cBattleHudMgr;
class cMetasyncGauge;

//====================================================================================
//                                                                             cBattle
//====================================================================================
class cBattle
{    
    cTimer mTimer;                          // battle timer
    cBattleStage *mStage;                   // the battle stage
    std::vector<cAdversary *> mAdversaries; // list of adversaries
    std::vector<cComrade *> mComrades;      // list of comrades

    cBattleHudMgr *mBattleHudMgr;

    cMetasyncGauge *mMetasyncGauge;

  public:
    // accessors for comrades
    std::vector<cComrade *> GetComrades();
    cComrade *GetComradeById(int id);

    // accessors for adversaries
    std::vector<cAdversary *> GetAdversaries();
    cAdversary *GetAdversaryById(int id);

    void Start();       // start the battle
    void Update();      // update the battle
    void Finish();      // finish the battle

    cBattle();  // Constructor
    ~cBattle(); // Destructor
};

#endif