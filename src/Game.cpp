


#include "Debug.h"
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
    //To prevent starting again, use a boolean switch that
    //only starts the engine if it is not running
    {
        if(running) return;
        running = true;

        run();
    }

    void Game::stop()
    {
        if(!running) return;
        running = false;
    }

    void Game::run()
    {
        Renderer renderer;
        //renderer.testWindow();

        renderer.openWindow();
        while(running)
        {
            renderer.render();
        }
        renderer.closeWindow();
    }

    void Game::tick()
    {

    }

    void Game::render()
    {

    }
}
