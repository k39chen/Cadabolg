//====================================================================================
// @Title:      METASYNC GAUGE
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cMetasyncGauge.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cMetasyncGauge.h"
#include "../include/cBattle.h"
#include "../../../prolix/framework/include/cAssetMgr.h"

//====================================================================================
//                                                                      cMetasyncGauge
//====================================================================================
cMetasyncGauge::cMetasyncGauge(cBattle *rBattle):
	cBaseObject()
{
    mBattle = rBattle;

	LogMgr->Write(INFO, "cMetasyncGauge::cMetasyncGauge >>>> Metasync Gauge Initialized");

	Initialize();
}

void cMetasyncGauge::Initialize()
{
	cBaseObject::Initialize();

	Position(10,10);
	
	Source(AssetMgr->Load<Texture>("metasync_full.png"));
	mFill = new cBaseObject(this, AssetMgr->Load<Texture>("metasync_empty.png"));

	AddChild(mFill);

	mPercentage = 0.0f;

	mNumX = 1;
	mNumY = 10;
}

void cMetasyncGauge::Display()
{
	if (PrlxEngine::GetInstance()->Input->KeyState[SDLK_z])	{(mPercentage >= 1.0f)? mPercentage = 1.0f : mPercentage += 0.001f;}
	if (PrlxEngine::GetInstance()->Input->KeyState[SDLK_x])	{(mPercentage <= 0.0f)? mPercentage = 0.0f : mPercentage -= 0.001f;}

	cBaseObject::Display();

	mFill->Display(Point(0,0), 
		new PRLX_Rect(Point(0,0), 
		Dimensions(mFill->Source()->dim.w, (int)(mFill->Source()->dim.h * (1.0f - mPercentage))), mNumX, mNumY));
}

void cMetasyncGauge::Update()
{
	Display();
}

cMetasyncGauge::~cMetasyncGauge()
{
}