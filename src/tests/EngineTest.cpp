
#include <stdio.h>

#include "engine/Engine.h"


int main(int argc, char** argv)
{
    printf("Welcome to the DragonSpine Game Engine!\n");
    engine::Engine* engine = new engine::Engine();
    engine->Start();
    delete engine;
    return 0;
}
