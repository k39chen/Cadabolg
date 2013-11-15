//====================================================================================
// @Title:      METASYNC GAUGE
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cMetasyncGauge.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  This class handles the behaviour and rendering of the battle's metasync gauge.
//
//====================================================================================
#ifndef __GAME_BATTLE_METASYNC_GAUGE_H__
#define __GAME_BATTLE_METASYNC_GAUGE_H__

#include "../../../prolix/common/include/cCartesian.h"
#include "../../../prolix/common/include/cBaseObject.h"

class cBattle;
class cTexture;

static const bool METASYNC_GAUGE_ENABLE_SNAPPING = true;
static const float METASYNC_GAUGE_SNAP_PRECISION = 4.7f;

//====================================================================================
//                                                                      cMetasyncGauge
//====================================================================================
class cMetasyncGauge : cBaseObject
{
    cBattle *mBattle;

	cBaseObject *mFill;

	float mPercentage;

	int mNumX;
	int mNumY;

  public:
    cMetasyncGauge(cBattle *Battle);

    virtual void Initialize();
    virtual void Display();
	virtual void Update();

    ~cMetasyncGauge();
};

#endif