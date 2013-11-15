//====================================================================================
// @Title:      BATTLE
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cBattle.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cBattle.h"
#include "../include/cBattleHudMgr.h"
#include "../include/cMetasyncGauge.h"
#include "../../../prolix/framework/include/cGame.h"

//====================================================================================
//                                                                             cBattle
//====================================================================================
cBattle::cBattle()
{
    mStage = new cBattleStage;

    LogMgr->Write(VERBOSE, "cBattle::cBattle >>>> Successfully created battle instance");

    cSpriteGroup *Enemy1SpriteGroup = new cSpriteGroup();
    cSpriteGroup *Enemy2SpriteGroup = new cSpriteGroup();
    cSpriteGroup *Ally1SpriteGroup = new cSpriteGroup();

    //Enemy1SpriteGroup->AddSprite("dragon", new cSprite("dragon.png", 3, 4));
    Enemy2SpriteGroup->AddSprite("dragon", new cSprite("adversary.png", 3, 4));
    Ally1SpriteGroup->AddSprite("fighter", new cSprite("comrade.png", 3, 4));

    //mEnemies.push_back(new cEnemy(this, Enemy1SpriteGroup));
    mAdversaries.push_back(new cAdversary(this, Enemy2SpriteGroup));

    mComrades.push_back(new cComrade(this, Ally1SpriteGroup));

    mBattleHudMgr = new cBattleHudMgr;

    mMetasyncGauge = new cMetasyncGauge(this);

    Start();
}

void cBattle::Start()
{
    LogMgr->Write(INFO, "cBattle::Start >>>> Started battle");
    mTimer.Start();
}

void cBattle::Update()
{
    //AssetMgr->Load<Texture>("gradient.png")->Draw();

    mBattleHudMgr->Update();
    mMetasyncGauge->Update();

    /*
    mStage->Draw();

    for each (cAdversary *Adversary in mAdversaries)
    {
        Adversary->Update();
    }
    
    for each (cComrade *Comrade in mComrades)
    {
        Comrade->Update();
    }

    mBattleHudMgr->Update();
    */
    //PrlxEngine::GetInstance()->Text->Write(cFont("euphorig.ttf", 40, PRLX_White), mTimer.Format(), Point(0,0), true);

    //PrlxEngine::GetInstance()->Graphics->Draw(&mAllies[0]->coll_rect, 1.00f, cColor(255,255,255,100));
    //PrlxEngine::GetInstance()->Graphics->Draw(&mEnemies[0]->coll_rect, 1.00f, cColor(255,255,255,100));
}

std::vector<cComrade *> cBattle::GetComrades()
{
    return mComrades;
}

cComrade *cBattle::GetComradeById(int id)
{
    // assert the comrade exists
    if ((unsigned)id > mComrades.size() - 1)
    {
        LogMgr->Write(INFO, "cBattle::GetComradeById >>>> Attempted to access inexistent comrade of id: " + toString(id));
        return NULL;
    }
    // return instance of comrade with given id
    return mComrades[id];
}

std::vector<cAdversary *> cBattle::GetAdversaries()
{
    return mAdversaries;
}

cAdversary *cBattle::GetAdversaryById(int id)
{
    // assert enemy exists
    if ((unsigned)id > mAdversaries.size() - 1)
    {
        LogMgr->Write(INFO, "cBattle::GetAdversaryById >>>> Attempted to access inexistent adversary of id: " + toString(id));
        return NULL;
    }
    // return instance of comrade with given id
    return mAdversaries[id];
}

void cBattle::Finish()
{
    LogMgr->Write(INFO, "cBattle::Finish >>>> Battle completed");
}

cBattle::~cBattle()
{
    LogMgr->Write(VERBOSE, "cBattle::~cBattle >>>> Deleted battle instance");
}