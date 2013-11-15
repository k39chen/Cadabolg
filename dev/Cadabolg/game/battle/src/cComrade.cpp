 //====================================================================================
// @Title:      COMRADE
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cComrade.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cComrade.h"
#include "../include/cBattle.h"
#include "../../../prolix/common/include/xVector.h"
#include "../../../prolix/framework/include/cGame.h"

//====================================================================================
//                                                                            cComrade
//====================================================================================
cComrade::cComrade(cBattle *rBattle, cSpriteGroup *rSpriteGroup):
    cCombatant(rBattle)
{
    health = maxhealth = 100;

    selected = true;

    mSpriteGroup = rSpriteGroup;

    Commands = new cCommandGroup();
    Commands->AddCommand(MOVE_LEFT,     new cCommand(SDLK_LEFT, 0, true));
    Commands->AddCommand(MOVE_RIGHT,    new cCommand(SDLK_RIGHT, 0, true));
    Commands->AddCommand(MOVE_UP,       new cCommand(SDLK_UP, 0, true));
    Commands->AddCommand(MOVE_DOWN,     new cCommand(SDLK_DOWN, 0, true));

    SpriteGroup->AddSprite("fighter", new cSprite("comrade.png", 3, 4));

    cSprite *WalkingSprite = SpriteGroup->GetSprite("fighter");

    dim = Dimensions(
        WalkingSprite->spritesheet->dim.w / WalkingSprite->numX,
        WalkingSprite->spritesheet->dim.h / WalkingSprite->numY);

    // initialize frameset vector for walking
    int arr[] = {0,1,2,1};
    std::vector<int> frameset = arrayToVector(arr, sizeof(arr)/sizeof(int));

    // create walking animations
    for (unsigned int i=0; i<frameset.size(); frameset[i] = arr[i] + FRONT * WalkingSprite->numX, i++);
    AnimationGroup->AddAnimation("walking_forward", new cAnimation(WalkingSprite, frameset));

    for (unsigned int i=0; i<frameset.size(); frameset[i] = arr[i] + LEFT * WalkingSprite->numX, i++);
    AnimationGroup->AddAnimation("walking_left", new cAnimation(WalkingSprite, frameset));

    for (unsigned int i=0; i<frameset.size(); frameset[i] = arr[i] + RIGHT * WalkingSprite->numX, i++);
    AnimationGroup->AddAnimation("walking_right", new cAnimation(WalkingSprite, frameset));

    for (unsigned int i=0; i<frameset.size(); frameset[i] = arr[i] + BACK * WalkingSprite->numX, i++);
    AnimationGroup->AddAnimation("walking_backward", new cAnimation(WalkingSprite, frameset));

    // initialize frameset vector for idle
    frameset.clear();
    frameset.resize(1);

    // create idle animations
    frameset[0] = FRONT * WalkingSprite->numX + 1;
    AnimationGroup->AddAnimation("idle_front", new cAnimation(WalkingSprite, frameset));
    
    frameset[0] = LEFT * WalkingSprite->numX + 1;
    AnimationGroup->AddAnimation("idle_left", new cAnimation(WalkingSprite, frameset));

    frameset[0] = RIGHT * WalkingSprite->numX + 1;
    AnimationGroup->AddAnimation("idle_right", new cAnimation(WalkingSprite, frameset));

    frameset[0] = BACK * WalkingSprite->numX + 1;
    AnimationGroup->AddAnimation("idle_back", new cAnimation(WalkingSprite, frameset));

    frameset.clear();

    coll_rect = PRLX_Rect(Point(motion.pos.x, motion.pos.y), 
        Dimensions(WalkingSprite->spritesheet->dim.w/WalkingSprite->numX,
                   WalkingSprite->spritesheet->dim.h/WalkingSprite->numY));

    motion.pos.x = SCREEN_WIDTH/2;
    motion.pos.y = SCREEN_HEIGHT/2;

    direction = FRONT;
}

void cComrade::Draw()
{
    switch (direction)
    {
        case FRONT:
           (motion.vel.y == 0)
                ? AnimationGroup->GetAnimation("idle_front")->Play(Point(motion.pos.x, motion.pos.y))
                : AnimationGroup->GetAnimation("walking_forward")->Play(Point(motion.pos.x, motion.pos.y), 150);
            break;

        case LEFT:
            (motion.vel.x == 0)
                ? AnimationGroup->GetAnimation("idle_left")->Play(Point(motion.pos.x, motion.pos.y))
                : AnimationGroup->GetAnimation("walking_left")->Play(Point(motion.pos.x, motion.pos.y), 150);
            break;
        
        case RIGHT:
            (motion.vel.x == 0)
                ? AnimationGroup->GetAnimation("idle_right")->Play(Point(motion.pos.x, motion.pos.y))
                : AnimationGroup->GetAnimation("walking_right")->Play(Point(motion.pos.x, motion.pos.y), 150);
            break;

        case BACK:
            (motion.vel.y == 0)
                ? AnimationGroup->GetAnimation("idle_back")->Play(Point(motion.pos.x, motion.pos.y))
                : AnimationGroup->GetAnimation("walking_backward")->Play(Point(motion.pos.x, motion.pos.y), 150);
            break;

        default:
            break;
    }

    if (health >= 0)
    {
        int xoffset = (int)motion.pos.x - (HealthBar->GetSprite("negative")->spritesheet->dim.w - SpriteGroup->GetSprite("fighter")->spriteset[0].dim.w)/2;
        int yoffset = (int)motion.pos.y - (HealthBar->GetSprite("negative")->spritesheet->dim.h + 5);

        HealthBar->GetSprite("negative")->DrawFrame(0, Point(xoffset,yoffset));
        
        for (int frame=xoffset; frame - xoffset< HealthBar->GetSprite("positive")->spritesheet->dim.w * ((float)health/(float)maxhealth); frame++)
        {
            HealthBar->GetSprite("positive")->DrawFrame(frame - xoffset, Point(frame * HealthBar->GetSprite("positive")->spriteset[0].dim.w, yoffset));
        }
    }
}

void cComrade::Move()
{
    float xvel = 1.0f;
    float yvel = 1.0f;
    float xfric = 0.18f;
    float yfric = 0.18f;

    if (selected)
    {
        #pragma region PLAYER KEYBOARD INPUT

        // check for keyboard input and act accordingly
        // NOTE: We have support for multi-directional and easing movement to reflect AI fluidity
        
        // handle left-movement key
        if (Commands->GetCommand(MOVE_LEFT)->Pollable())
        {
            direction = LEFT;
            motion.vel.x = -xvel;
        }
        // handle right-movement key
        else if (Commands->GetCommand(MOVE_RIGHT)->Pollable())
        {
            direction = RIGHT;
            motion.vel.x = xvel;
        }
        else
        {
            motion.vel.x = 0;
        }

        // handle up-movement key
        if (Commands->GetCommand(MOVE_UP)->Pollable())
        {
            direction = BACK;
            motion.vel.y = -yvel;
        }
        // handle down-movement key
        else if (Commands->GetCommand(MOVE_DOWN)->Pollable())
        {
            direction = FRONT;
            motion.vel.y = yvel;
        }
        // disable vertical movement (with easing)
        else
        {
            motion.vel.y = 0;
        }

        #pragma endregion
    }
    else
    {
        #pragma region AI MOVEMENT
        // do some AI work.
        #pragma endregion
    }

    coll_rect.pos = Point(motion.pos.x, motion.pos.y);

    // do the physics
    cEntity::Move();
}

void cComrade::Update()
{
    Draw();
    Move();
}

void cComrade::Select()
{
    selected = true;
}

cComrade::~cComrade()
{
    LogMgr->Write(INFO, "cComrade::~cComrade >>>> Comrade vanquished");
}