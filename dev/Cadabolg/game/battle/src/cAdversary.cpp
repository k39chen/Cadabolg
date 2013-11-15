//====================================================================================
// @Title:      ADVERSARY
//------------------------------------------------------------------------------------
// @Location:   /game/battle/include/cAdversary.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <cmath>
#include "../include/cAdversary.h"
#include "../include/cBattle.h"
#include "../../../prolix/common/include/xVector.h"
#include "../../../prolix/framework/include/cGame.h"

//====================================================================================
//                                                                          cAdversary
//====================================================================================
cAdversary::cAdversary(cBattle *rBattle, cSpriteGroup *rSpriteGroup):
    cCombatant(rBattle)
{
    mSpriteGroup = rSpriteGroup;
    
    cSprite *WalkingSprite = mSpriteGroup->GetSprite("dragon");

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

    direction = FRONT;
    motion.pos.x = (float)(rand()%100 + 100);
    motion.pos.y = (float)(rand()%200 + 100);
    motion.pos.Center(dim);
    
    mCollEffect = new cEffect(new cSprite("effect.png", 5, 4));
}

void cAdversary::Draw()
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
}

void cAdversary::Move()
{
    float xvel = 0.4f;
    float yvel = 0.5f;

    cCombatant *Target = Battle->GetComradeById(0);

    // determine horizontal movement
    (Target->motion.pos.x + Target->dim.w/2 < motion.pos.x + dim.w/2) 
        ? motion.vel.x = -xvel
        : motion.vel.x = +xvel;
    
    // determine vertical movement
    (Target->motion.pos.y + Target->dim.h < motion.pos.y + dim.h)
        ? motion.vel.y = -yvel
        : motion.vel.y = +yvel;

    // determine horizontal orientation
    if (std::abs(Target->motion.pos.x - motion.pos.x) > std::abs(Target->motion.pos.y - motion.pos.y))
    {
        (Target->motion.pos.x + Target->dim.w/2 < motion.pos.x + dim.h/2)
            ? direction = LEFT
            : direction = RIGHT;
    } 
    // determine vertical orientation
    else
    {   
        (Target->motion.pos.y + Target->dim.h/2 < motion.pos.y + dim.h/2)
            ? direction = BACK
            : direction = FRONT;
    }

    coll_rect.pos = Point(motion.pos.x, motion.pos.y);

    // if collides with target
    if (PrlxEngine::GetInstance()->Physics->HitTest(coll_rect, Target->coll_rect))
    {
        Target->health--;

        motion.Stop();
        mCollEffect->Generate(
            Point(motion.pos.x, motion.pos.y) - 
            Point(mCollEffect->Sprite()->frameDim.w/4, mCollEffect->Sprite()->frameDim.h/4 - 10), 
            0, false);
    }

    mCollEffect->Play();    // should usually be in renderer

    motion.Move();
}

void cAdversary::Update()
{
    Draw();
    Move();
}

cAdversary::~cAdversary()
{
    LogMgr->Write(INFO, "cAdversary::~cAdversary >>>> Vanquished adversary");
}