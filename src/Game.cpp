#include "Game.h"
#include "Renderer.h"

namespace DragonSpineGameEngine {

    Game::Game()
    {
        //ctor
    }

    Game::~Game()
    {
        //dtor
    }

    void Game::start()
    {
        run();
    }

    void Game::stop()
    {

    }

    void Game::run()
    {
        Renderer renderer;
        renderer.testWindow();
    }

    void Game::tick()
    {

    }

    void Game::render()
    {

    }
}
