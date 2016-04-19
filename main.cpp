///TEST CLASS FOR DRAGON SPINE GAME ENGINE

#include <assert.h>

#include "engine\Engine.h"
#include "systems\ISystem.h"
#include "systems\ObjectSystem.h"
#include "systems\WindowSystem.h"
#include "systems\GraphicsSystem.h"
#include "main.h"

int main(int argc, char** argv)
{
    engine::Engine* new_engine = new engine::Engine();
    new_engine->Start();
}
