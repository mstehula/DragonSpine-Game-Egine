#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/Engine.h"

namespace engine {

    Engine::Engine()
    {

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

        engine::debug(engine::k_debug_all_, "Engine starting");

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
        engine::debug(engine::k_debug_all_, "This is the exit");

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
                debug(k_debug_all_, "FPS:[%d] TPS:[%d], OBJ FACT SIZE ", frames, ticks);
                frames = 0;
                ticks = 0;
                frame_accumulator -= fps_skip_ticks;
            }

            if(!glfwGetCurrentContext())
            {
                engine::error("Cannot get current context, exiting");
                Stop();
            }
            else if(glfwWindowShouldClose(glfwGetCurrentContext()))
            {
                engine::debug(engine::k_debug_all_, "Window should be closing now!");
                Stop();
            }
        }

        engine::debug(engine::k_debug_all_, "Ending");
    }

    int game_debug_level_ = k_debug_all_;

    //Prints out char* output if debug_level is less then the current
    //game debug_level
    void debug(int debug_level, const char * format, ...)
    {
        if(debug_level <= game_debug_level_)
        {
            va_list argptr;
            va_start(argptr, format);
            fprintf(stdout, "[%c][%f] ", debug_symbol_table_[debug_level], glfwGetTime());
            vfprintf(stdout, format, argptr);
            fprintf(stdout, "\n");
            va_end(argptr);
        }
    }

    //Prints out the char* output to stderr
    void error(const char* format, ...)
    {
        va_list argptr;
        va_start(argptr, format);
        fprintf(stdout, "[E][%f] ", glfwGetTime());
        vfprintf(stdout, format, argptr);
        fprintf(stdout, "\n");
        va_end(argptr);
    }

    //Sets debug level of the program - changed most notibly in the command line
    void setDebugLevel(int debug_level)
    {
        game_debug_level_ = debug_level;
    }

}
