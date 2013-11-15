//====================================================================================
// @Title:      HUD MANAGER
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cBattleHudMgr.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  This class manages comrade battle HUDs.
//
//====================================================================================
#ifndef __GAME_BATTLE_HUD_MANAGER_H__
#define __GAME_BATTLE_HUD_MANAGER_H__

#include <vector>
#include "../../../prolix/common/include/cCartesian.h"
#include "../../../prolix/engine/include/PrlxInput.h"

class cBattleHud;

//====================================================================================
//                                                                       cBattleHudMgr
//====================================================================================
class cBattleHudMgr
{
    friend class cBattleHud;

    std::vector<cBattleHud *> mBattleHudList;

  public:

    void Initialize();
    void Promote(int index);
    void Update();

    cBattleHudMgr();
    ~cBattleHudMgr();
};

#endif