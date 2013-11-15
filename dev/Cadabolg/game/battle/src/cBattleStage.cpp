//====================================================================================
// @Title:      BATTLE STAGE
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cBattleStage.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cBattleStage.h"
#include "../../../prolix/framework/include/cGame.h"

//====================================================================================
//                                                                        cBattleStage
//====================================================================================
cBattleStage::cBattleStage()
{
    LogMgr->Write(INFO, "cBattleStage::cBattleStage >>>> Created Battle Stage");
}

void cBattleStage::Draw()
{
    int y;
    for (y=0; y < SCREEN_HEIGHT; y += AssetMgr->Load<Texture>("grass.png")->dim.h)
    {
        for (int x=0; x < SCREEN_WIDTH; x += AssetMgr->Load<Texture>("grass.png")->dim.w)
        {
            AssetMgr->Load<Texture>("grass.png")->Draw(Point(x,y));
        }
    }

    y -= 32;
    for (int x=0; x < SCREEN_WIDTH; x += AssetMgr->Load<Texture>("dirt.png")->dim.w)
    {
        AssetMgr->Load<Texture>("dirt.png")->Draw(Point(x,y));
    }
}

cBattleStage::~cBattleStage()
{
}