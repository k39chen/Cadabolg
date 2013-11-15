//====================================================================================
// @Title:      BATTLE HUD
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cBattleHud.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The battle HUD presents vital information of a comrade's state of health. This
//  class provides both the visual component and the class behaviour and definition.
//
//====================================================================================
#ifndef __GAME_BATTLE_HUD_H__
#define __GAME_BATTLE_HUD_H__

#include "../../../prolix/common/include/cBaseObject.h"
#include "../../../prolix/common/include/cLabel.h"
#include "../../../prolix/common/include/cSprite.h"
#include "../../../prolix/common/include/cTween.h"
#include "../../../prolix/engine/include/PrlxInput.h"

class cBaseObject;
class cCombatant;
class cBattleHudMgr;

static const bool BATTLE_HUD_ALLOW_OVERHEALING	= true;
static const bool BATTLE_HUD_ENABLE_SNAPPING	= true;
static const float BATTLE_HUD_SNAP_PRECISION	= 4.5f;

//====================================================================================
//                                                                          cBattleHud
//====================================================================================
class cBattleHud : public cBaseObject
{
    friend class cBattleHudMgr;

	// class for mugshot functions
	class cMugshot : public cBaseObject
	{
		// Consider exposing these states in the DB
		enum MugshotState {	// ordered by priority (lowest to highest)

			NEUTRAL,			// unbiased state
			
			/****** Emotional States ******/
			HAPPY,				// happy guy :)
			CONFIDENT,			// confident/cocky face
			EMBARRASSED,		// tsundere confession face
			SAD,				// very sad :(
			AFRAID,				// afraid face
			WORRIED,			// worried/nervous face
			ANGRY,				// angry face
			OUTRAGED,			// extremely angry face
			
			/****** Chat States ******/
			MUTTERING,			// muttering state
			SPEAK,				// normal talking state
			YELL,				// yelling state
			SCREAM,				// screaming state

			/****** Event States ******/
			HEALED,				// heal spell cast on actor
			DAMAGED,			// damage received

			/****** Vital States ******/
			BUFFED,				// powered up by a buff
			AFFLICTED,			// afflicted with a negative condition
			DANGER,				// if in danger of dying
			FAINTED				// asserted when dead
		} mState;

		/* if we want to have animated faces as opposed to static ones
		 *
		 * cAnimationGroup *mAnimStates;
		 * std::string mAnimId;	// currently playing animation group
		 */
		cSprite *mSprite;
	  public:
		virtual void Display();

		void ChangeState(MugshotState newState);

		cMugshot(cTexture *Spritesheet);
		~cMugshot();
	};

	enum VitalType{HEALTH, MANA, MASK};

	float mHealthPct;
	float mManaPct;

	cBaseObject *mHealthBar;
	cBaseObject *mManaBar;
	cBaseObject *mMask;

	void DrawVital(VitalType vitalType, float rotation);
	float ApplyGaugeSnap(float val);

	float CalculateLieuSpace();
    
    cBattleHudMgr *mBattleHudMgr;   // parent battle HUD manager
    cCombatant *mCombatant;     // the parent combatant (grab info from here)
    
	bool mIsExtended;           // if the HUD is the extended version

	cMugshot *mMugshot;

	cLabel *mHealthLabel;
	cLabel *mManaLabel;

  public:
    // Default constructor
    cBattleHud();
    
    // Constructor
    cBattleHud(cBattleHudMgr *BattleHudMgr, cCombatant *Combatant, bool IsExtended = false);
    
    virtual void Initialize();
    virtual void Display();

    void Update();

    // Destructor
    ~cBattleHud();

    bool IsExtended() const;
    void IsExtended(bool newExtendedState);
};

#endif