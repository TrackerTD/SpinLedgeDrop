#include "Player.h"
#include "../GameAPI/C/GameAPI/Game.h"

ObjectPlayer *Player;

int32 storedFrame;
int32 storedTimer;
bool32 isSpindash;

bool32 Player_State_Air_Pre(bool32 skipped)
{
    if (skipped)
        return false; // most mods aren't implementing skip cases already; this is what should be done
    RSDK_THIS(Player);

    isSpindash = false;
    if (!self->onGround && self->animator.animationID == ANI_SPINDASH) {
        isSpindash  = true;
        storedFrame = self->animator.frameID;
        storedTimer = self->animator.timer;

    }
    return false;
}

void Player_State_Air_Post(bool32 skipped)
{
    if (skipped)
        return;
    RSDK_THIS(Player);

    if (isSpindash) {
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_SPINDASH, &self->animator, false, storedFrame);
        self->animator.timer  = storedTimer;
        self->nextGroundState = Player_Action_Spindash;
    }
}

void Player_Action_Spindash_Hook(bool32 skipped)
{
    if (skipped)
        return;
    RSDK_THIS(Player);
    self->groundVel = 0;
    self->nextAirState = Player_State_Air;
}

