
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "Debug.h"
#include "Game.h"
#include "Input.h"
#include "Renderer.h"

namespace DragonSpineGameEngine {

    Game::Game()
    {
        debug("Game - constructor\n");
        if(!glfwInit())
        {
            error("Cannot init glfw, exiting\n");
            exit(EXIT_FAILURE);
        }
        debug("Game - constructor complete\n");
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
        //renderer.testWindow();

        time.update();

        //renderer.openWindow();
        while(running)
        {
            bool canTick;

            char* buffer;
            sprintf(buffer, "%u\n", (long) (time.getDelta()));
            debug(buffer);
            //tick();



            if(canTick)
            {
                //tick();
                canTick = false;
            }
        }
        //renderer.closeWindow();
    }

    void Game::tick()
    {
        input.update();
    }

    void Game::render()
    {
        renderer.render();
    }
}
