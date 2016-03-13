
#include "Debug.h"
#include "Game.h"

using namespace DragonSpineGameEngine;

int kWidth = 640;
int kHeight = 480;

int main()
{
    setDebugLevel(DEBUG_ALL);

    debug("Welcome to DragonSpine Game Engine\n");
    debug("DragonSpine Game Engine initializing...\n");

    Game game;
    game.start();

    debug("DragonSpine Game Engine shutting down...\n");
    debug("DragonSpine Game Engine complete\n");
    return 0;
}
