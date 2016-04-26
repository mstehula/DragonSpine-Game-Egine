#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/Engine.h"

namespace engine {

    Engine::Engine()
    {
        running_ = false;
    }

    Engine::~Engine()
    {
        glfwTerminate();
    }

    void Engine::Init()
    {
        window_input_system_.Init();
        object_system_.Init();
        graphics_system_.Init();
    }

    //To prevent starting again, use a boolean switch that
    //only starts the engine if it is not running
    void Engine::Start()
    {
        if(running_) return;
        running_ = true;

        this->Init();
        this->Run();
    }

    void Engine::Tick(float dt)
    {
        object_system_.Update(dt, object_system_);
        window_input_system_.Update(dt, object_system_);
    }

    void Engine::Render(float dt)
    {
        graphics_system_.Update(dt, object_system_);
    }

    void Engine::Stop()
    {
        if(!running_) return;
        running_ = false;
    }

    void Engine::Run()
    {
        const float ticks_per_second = 50;
        const float max_frame_skip = 10;
        const float game_skip_ticks = 1.0f/ticks_per_second;
        const float fps_skip_ticks = 1.0f;

        double last_time = glfwGetTime();
        double tick_accumulator = 0.0f;
        double frame_accumulator = 0.0f;

        int frames = 0;
        int ticks = 0;

        while(running_ && glfwGetCurrentContext())
        {
            int loops = 0;
            double now = glfwGetTime();
            double frame_time = now - last_time;

            if(frame_time > .25) frame_time = .25;
            last_time = now;

            tick_accumulator += frame_time;
            frame_accumulator += frame_time;

            while(tick_accumulator > game_skip_ticks && loops < max_frame_skip)
            {
                Tick(game_skip_ticks);
                tick_accumulator -= game_skip_ticks;
                ticks++;
                loops++;
            }

            Render(tick_accumulator);
            frames++;

            if(frame_accumulator > fps_skip_ticks)
            {
                frames = 0;
                ticks = 0;
                frame_accumulator -= fps_skip_ticks;
            }

            if(!glfwGetCurrentContext())
            {
                Stop();
            }
            else if(glfwWindowShouldClose(glfwGetCurrentContext()))
            {
                Stop();
            }
        }
    }
}
