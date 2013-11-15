//====================================================================================
// @Title:      BATTLE HUD MANAGER
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cBattleHudMgr.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cBattleHudMgr.h"
#include "../include/cBattleHud.h"
#include "../../../prolix/framework/include/cAssetMgr.h"

//====================================================================================
//                                                                       cBattleHudMgr
//====================================================================================
cBattleHudMgr::cBattleHudMgr()
{
    Initialize();
}

void cBattleHudMgr::Initialize()
{
    mBattleHudList.resize(3);

	for (unsigned int i=0; i<mBattleHudList.size(); i++)
	{
		mBattleHudList[i] = new cBattleHud(this, NULL, i == 0);
		mBattleHudList[i]->Position(SCREEN_WIDTH - mBattleHudList[i]->Source()->dim.w, i * mBattleHudList[i]->Source()->dim.h - ((i > 0)? 20 * i : 0));
	}
}

void cBattleHudMgr::Promote(int index)
{
}

void cBattleHudMgr::Update()
{    
    for each (cBattleHud *BattleHud in mBattleHudList)
    {
        BattleHud->Update();
    }
}

cBattleHudMgr::~cBattleHudMgr()
{
}