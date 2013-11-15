//====================================================================================
// @Title:      APPLICATION DRIVER
//------------------------------------------------------------------------------------
// @Location:   /appDriver.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//   Serves as a primary test environment and game init area
//
//====================================================================================
#include <SDL.h>
#include <iostream>
#include "libDriver.h"

using namespace std;

//====================================================================================
//                                                                     MAIN DEFINITION
//====================================================================================
int main (int argc, char **argv) 
{
    cGame::GetInstance();

	Engine->SetCaptionAndIcon("Application appCore", "../assets/img/logo.png");
	
	Engine->Input->Mouse->Cursor = new cCursor;

	// indicate start of game application
	LogMgr->Write(INFO, "main >>>> Game application started");
	
    cBattle *Battle = new cBattle; // create stage

    cEffect *CursorEffect = new cEffect(new cSprite("cursoreffect.png", 4, 4));

    /******************* GAME LOOP *************************/
	while (cGame::GetInstance()->Loop())
    {
        Battle->Update();

        CursorEffect->Generate(PrlxEngine::GetInstance()->Input->Mouse->pos - 
            Point(CursorEffect->Sprite()->spriteset[0].dim.w/2, CursorEffect->Sprite()->spriteset[0].dim.h/2), 20);

        CursorEffect->Play();
	}

	return 0;
}