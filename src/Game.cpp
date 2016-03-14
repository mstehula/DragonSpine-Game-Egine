
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "Debug.h"
#include "Game.h"
#include "Input.h"
#include "Renderer.h"

using namespace DragonSpineGameEngine;

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
        debug("run\n");

        const int kFramePerSecond = 20;
        const float kGameSkipTicks = 1.0f/kFramePerSecond;
        const float kFPSSkipTicks = 1.0f;
        const int kMaxFrameskip = 5;

        double next_game_tick = time.update().getTime();
        double next_fps_tick = time.getTime();
        int loops;
        float interpolation;

        int frames = 0;
        int ticks = 0;

        renderer.openWindow();
        while(running)
        {
            char buffer[100];

            loops = 0;
            while(time.update().getTime() > next_game_tick && loops < kMaxFrameskip)
            {
                //tick();
                ticks++;
                loops++;
                next_game_tick += kGameSkipTicks;
            }

            if(time.update().getTime() > next_fps_tick)
            {
                sprintf(buffer, "%d %d\n", frames, ticks);
                debug(buffer);
                frames = 0;
                ticks = 0;
                next_fps_tick += kFPSSkipTicks;
            }

            //Interpolation is how much of a second has passed by since the last render tick;
            interpolation = (float) ((time.update().getTime() + kGameSkipTicks - next_game_tick) / kGameSkipTicks);
            //render();
            frames++;
        }
        renderer.closeWindow();
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
