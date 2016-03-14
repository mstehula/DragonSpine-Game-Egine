
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "Game.h"
#include "Input.h"
#include "Renderer.h"

namespace dragonspinegameengine {

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

        const int kFramePerSecond = 20;
        const float kGameSkipTicks = 1.0f/kFramePerSecond;
        const float kFPSSkipTicks = 1.0f;
        const int kMaxFrameskip = 5;

        double next_game_tick = getTime();
        double next_fps_tick = getTime();
        int loops;
        float interpolation;

        int frames = 0;
        int ticks = 0;

        renderer.openWindow();
        while(running)
        {
            char buffer[100];

            loops = 0;
            while(getTime() > next_game_tick && loops < kMaxFrameskip)
            {
                //tick();
                ticks++;
                loops++;
                next_game_tick += kGameSkipTicks;
            }

            if(getTime() > next_fps_tick)
            {
                debug_buffer(kDebugAll, "FPS:[%d] TPS:[%d]", frames, ticks);
                frames = 0;
                ticks = 0;
                next_fps_tick += kFPSSkipTicks;
            }

            //Interpolation is how much of a second has passed by since the last render tick;
            interpolation = (float) ((getTime() + kGameSkipTicks - next_game_tick) / kGameSkipTicks);
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
