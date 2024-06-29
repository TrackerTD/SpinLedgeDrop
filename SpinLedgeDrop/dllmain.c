#include "../GameAPI/C/GameAPI/Game.h"
#include "../SpinLedgeDrop/Player.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    Player_Action_Spindash     = Mod.GetPublicFunction(NULL, "Player_Action_Spindash");
    Player_State_Air           = Mod.GetPublicFunction(NULL, "Player_State_Air");
    Mod.RegisterStateHook(Player_State_Air, Player_State_Air_Pre, true);
    Mod.RegisterStateHook(Player_State_Air, Player_State_Air_Post, false);
    Mod.RegisterStateHook(Player_Action_Spindash, Player_Action_Spindash_Hook, false);
}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
}
#endif