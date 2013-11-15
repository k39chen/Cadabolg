//====================================================================================
// @Title:      BATTLE HUD
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cBattleHud.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <cmath>
#include "../include/cBattleHud.h"
#include "../include/cBattleHudMgr.h"
#include "../include/cCombatant.h"
#include "../../../prolix/common/include/cBaseObject.h"
#include "../../../prolix/engine/include/PrlxEngine.h"
#include "../../../prolix/framework/include/cAssetMgr.h"

//====================================================================================
//                                                                          cBattleHud
//====================================================================================
cBattleHud::cBattleHud()
{
    mBattleHudMgr = NULL;
    mCombatant = NULL;
    mIsExtended = false;

    Initialize();
}

cBattleHud::cBattleHud(cBattleHudMgr *rBattleHudMgr, cCombatant *rCombatant, bool IsExtended):
    cBaseObject()
{
    mBattleHudMgr = rBattleHudMgr;
    mCombatant = rCombatant;
    mIsExtended = IsExtended;

    Initialize();
}

void cBattleHud::Initialize()
{
    Source(AssetMgr->Load<Texture>("hud_b_frame.png"));

	mMugshot = new cMugshot(AssetMgr->Load<Texture>("hud_b_mug_back.png"));

	mHealthBar = new cBaseObject(AssetMgr->Load<Texture>("hud_b_health.png"));
	mManaBar = new cBaseObject(AssetMgr->Load<Texture>("hud_b_mana.png"));
	mMask = new cBaseObject(AssetMgr->Load<Texture>("hud_b_mask.png"));

	mHealthPct = 1.00f;
	mManaPct = 1.00f;

	mMugshot->SetParent(this);
	mHealthBar->SetParent(this);
	mManaBar->SetParent(this);
	mMask->SetParent(this);

	AddChild(mMugshot);
	AddChild(mHealthBar);
	AddChild(mManaBar);
	AddChild(mMask);

	mHealthLabel = new cLabel(DEFAULT_FONT, "HP: ");
	mManaLabel = new cLabel(DEFAULT_FONT, "MP: ");
}

cBattleHud::cMugshot::cMugshot(cTexture *rSpritesheet):
	cBaseObject()
{
	Source(rSpritesheet);
	mSprite = new cSprite(mSource, 1, 1);		// THE NUM OF PARTITIONS ARE STILL HARDCODED! NEED TO STANDARDIZE!

	ChangeState(NEUTRAL);
}

void cBattleHud::cMugshot::ChangeState(cBattleHud::cMugshot::MugshotState newState)
{
	mState = newState;
}

void cBattleHud::cMugshot::Display()
{
	cBaseObject::Display();
}

void cBattleHud::Update()
{
    this->Display();
}

float cBattleHud::CalculateLieuSpace()
{
	return 2.0f - mHealthPct - mManaPct;
}

float cBattleHud::ApplyGaugeSnap(float val)
{
	return (BATTLE_HUD_ENABLE_SNAPPING) ? (float)((int)(val/BATTLE_HUD_SNAP_PRECISION)*BATTLE_HUD_SNAP_PRECISION) : val;
}

void cBattleHud::DrawVital(VitalType vitalType, float rotation)
{
	switch (vitalType)
	{
		case HEALTH:
			mHealthBar->Rotation(ApplyGaugeSnap(rotation));
			mHealthBar->Display();
			break;
		case MANA:
			mManaBar->Rotation(ApplyGaugeSnap(rotation));
			mManaBar->Display();
			break;
		case MASK:
			mMask->Rotation(ApplyGaugeSnap(rotation));
			mMask->Display();
			break;
		default:
			break;
	}
}

void cBattleHud::Display()
{
    if (mSource == NULL) return;

    if (mVisible) 
    {	
		int magnitude = 1;

		if (PrlxEngine::GetInstance()->Input->KeyState[SDLK_LEFT])
		{	
			mHealthPct -= 0.01f;
		}
		if (PrlxEngine::GetInstance()->Input->KeyState[SDLK_RIGHT])
		{
			mHealthPct += 0.01f;
		}
		if (PrlxEngine::GetInstance()->Input->KeyState[SDLK_DOWN])
		{
			mManaPct -= 0.01f;
		}
		if (PrlxEngine::GetInstance()->Input->KeyState[SDLK_UP])
		{
			mManaPct += 0.01f;
		}

		// health is overhealed
		if (mHealthPct > 1.0f)
		{
			DrawVital(MANA,		0.0f);
			DrawVital(MANA,		90.0f);
			DrawVital(MASK,		mManaPct * 180.0f);
			DrawVital(MASK,		90.0f + mManaPct * 180.0f);
			DrawVital(HEALTH,	180.0f - (mHealthPct - 1.0f) * 180.0f);
			DrawVital(HEALTH,	270.0f - (mHealthPct - 1.0f) * 180.0f);
			DrawVital(HEALTH,	180.0f);
			DrawVital(HEALTH,	270.0f);
		}
		// mana is overhealed
		else if (mManaPct > 1.0f)
		{
			DrawVital(HEALTH,	180.0f);
			DrawVital(HEALTH,	270.0f);
			DrawVital(MASK,		(1.0f - mHealthPct) * 180.0f - 360.0f);
			DrawVital(MASK,		(1.0f - mHealthPct) * 180.0f - 360.0f + 90.0f);
			DrawVital(MANA,		mManaPct * 180.0f - 180.0f);
			DrawVital(MANA,		mManaPct * 180.0f - 90.0f);
			DrawVital(MANA,		0.0f);
			DrawVital(MANA,		90.0f);
		}
		// no overhealing has occurred
		else
		{
			float lieuSpace = CalculateLieuSpace();
			if (lieuSpace < 0.5f)
			{
				DrawVital(MANA,		0.0f);
				DrawVital(MANA,		90.0f);
				DrawVital(MASK,		mManaPct * 180.0f);
				DrawVital(HEALTH,	360.0f - mHealthPct * 180.0f);
				DrawVital(HEALTH,	360.0f - mHealthPct * 180.0f + 90.0f);
				DrawVital(MANA,		0.0f);
			}
			else if (lieuSpace < 1.0f)
			{
				DrawVital(HEALTH,	180.0f);
				DrawVital(HEALTH,	270.0f);
				DrawVital(MANA,		0.0f);
				DrawVital(MANA,		90.0f);
				DrawVital(MASK,		mManaPct * 180.0f);
				DrawVital(MASK,		360.0f - 90.0f - mHealthPct * 180.0f);
			}
			else // lieuSpace >= 1.0f
			{
				DrawVital(HEALTH,	180.0f);
				DrawVital(HEALTH,	270.0f);
				DrawVital(MANA,		0.0f);
				DrawVital(MANA,		90.0f);
				DrawVital(MASK,		mManaPct * 180.0f);
				DrawVital(MASK,		mManaPct * 180.0f + 90.0f);
				DrawVital(MASK,		180.0f -mHealthPct * 180.0f);
				DrawVital(MASK,		270.0f -mHealthPct * 180.0f);
			}
		}

		mMugshot->Display();
		cBaseObject::Display();	// draw the frame

		//--------------------------------------- DEBUG INFO
		(mHealthPct >= 0.5f)
			? mHealthLabel->Font(cFont("droid.ttf", 20, PRLX_White))
			: mHealthLabel->Font(cFont("droid.ttf", 20, PRLX_Red));

		(mManaPct >= 0.5f)
			? mManaLabel->Font(cFont("droid.ttf", 20, PRLX_White))
			: mManaLabel->Font(cFont("droid.ttf", 20, PRLX_Red));

		mHealthLabel->Message("HP: " + toString(mHealthPct * 100) + "%");
		mHealthLabel->Render(Point(500,300));
		mManaLabel->Message("MP: " + toString(mManaPct * 100) + "%");
		mManaLabel->Render(Point(500,330));
	}
}

bool cBattleHud::IsExtended() const {return mIsExtended;}
void cBattleHud::IsExtended(bool newExtendedState) {mIsExtended = newExtendedState;}

cBattleHud::~cBattleHud()
{
}

cBattleHud::cMugshot::~cMugshot()
{
}