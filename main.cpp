
#include "Debug.h"
#include "Game.h"

using namespace DragonSpineGameEngine;

int main()
{
    setDebugLevel(DEBUG_ALL);

    debug("Welcome to DragonSpine Game Engine\n");
    debug("DragonSpine Game Engine initializing...\n");

    debug("DragonSpine Game Engine shutting down...\n");
    debug("DragonSpine Game Engine complete\n");
    return 0;
}
