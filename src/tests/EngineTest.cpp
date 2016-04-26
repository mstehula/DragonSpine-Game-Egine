#include "engine/Engine.h"

int main(int argc, char** argv)
{
    engine::Engine* engine = new engine::Engine();
    engine->Start();
    return 0;
}
