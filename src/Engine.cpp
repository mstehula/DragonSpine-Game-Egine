#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "Engine.h"
#include "GraphicsEngine.h"
#include "InputEngine.h"
#include "PhysicsEngine.h"

using namespace dragonspinegameengine;

namespace dragonspinegameengine {

    Engine* Engine::engine_;

    Engine* Engine::GetEngine()
    {
        if(Engine::engine_ == nullptr)
        {
            Engine::engine_ = new Engine();
        }
        return engine_;
    }

    void Engine::ConfigureEngine(struct EngineConfig config)
    {
        config_ = config;

        if(config_.graphics_engine_ == true && graphics_engine_ == nullptr)
        {
            graphics_engine_ = new GraphicsEngine();
            graphics_engine_->CreateContext();
        }
        else if(config_.graphics_engine_ == false && graphics_engine_ != nullptr)
        {
            debug(kDebugWarning, "Warning: Graphics engine already initialized before you changed configurations");
        }
        else
        {
            if(!glfwInit())
            {
                fprintf(stderr, "Error initializing glfw");
                exit(EXIT_FAILURE);
            }
        }

        if(config_.physics_engine_ == true && graphics_engine_ == nullptr)
        {
            physics_engine_ = new PhysicsEngine();
        }
        else if(config_.physics_engine_ == false && physics_engine_ != nullptr)
        {
            debug(kDebugWarning, "Warning: Physics engine already initialized before you changed configurations");
        }
    }

    struct Engine::EngineConfig Engine::GetConfig()
    {
        return config_;
    }

    //To prevent starting again, use a boolean switch that
    //only starts the engine if it is not running
    void Engine::Start()
    {
        if(running_) return;
        running_ = true;

        Run();
    }

    void Engine::Stop()
    {
        if(!running_) return;
        running_ = false;
    }

    void Engine::RegisterObect(EngineObject* object)
    {
        if(config_.graphics_engine_)
        {
            graphics_engine_->RegisterObject(dynamic_cast<GraphicsObject*>(object));
        }
        if(config_.physics_engine_)
        {
            physics_engine_->RegisterObject(dynamic_cast<PhysicsObject*>(object));
        }
    }

    void Engine::UnregisterObject(EngineObject* object)
    {
        if(config_.graphics_engine_)
        {
            graphics_engine_->UnregisterObject(dynamic_cast<GraphicsObject*>(object));
        }
        if(config_.physics_engine_)
        {
            physics_engine_->UnregisterObject(dynamic_cast<PhysicsObject*>(object));
        }
    }

    void Engine::Run()
    {
        debug(kDebugAll, "Engine Run called");

        const float game_skip_ticks = 1.0f/config_.ticks_per_second_;
        const float fps_skip_ticks = 1.0f;

        double next_game_tick = getTime();
        double next_fps_tick = getTime();
        int loops;
        float interpolation;

        int frames = 0;
        int ticks = 0;

        if(config_.graphics_engine_ == true)
        {
            graphics_engine_->ShowWindow(true);
            graphics_engine_->SetWindowSize(700, 500);
            graphics_engine_->SetupShaders();
        }

        while(running_)
        {
            loops = 0;
            while(getTime() > next_game_tick && loops < config_.max_frame_skips_)
            {
                input_engine_->PollInput();
                if(config_.physics_engine_ == true)
                {
                    physics_engine_->SimulatePhysics();
                }
                if(config_.graphics_engine_ == true)
                {
                    graphics_engine_->CheckCloseState();
                }
                ticks++;
                loops++;
                next_game_tick += game_skip_ticks;
            }

            //Interpolation is how much of a second has passed by since the last game tick;
            interpolation = (float) ((getTime() + game_skip_ticks - next_game_tick) / game_skip_ticks);
            frames++;

            if(config_.graphics_engine_)
            {
                graphics_engine_->PreRender();
                graphics_engine_->Render();
                graphics_engine_->PostRender();
            }

            if(getTime() > next_fps_tick)
            {
                debug(kDebugAll, "FPS:[%d] TPS:[%d]", frames, ticks);
                frames = 0;
                ticks = 0;
                next_fps_tick += fps_skip_ticks;
            }
        }
    }

    void ResourceLoader::LoadShader(const char* shader_filename, char** shader_file, int* shader_file_size)
    {
        debug(3, "Opening shader file: %s", shader_filename);
        FILE* shader = fopen(shader_filename, "r");
        if(shader == nullptr)
        {
            error("Cannot open file for shader: %s", shader_filename);
            exit(1);
        }

        fseek(shader, 0, SEEK_END);
        *shader_file_size = ftell(shader);
        rewind(shader);

        *shader_file = (char*) malloc(*shader_file_size * sizeof(char));
        if(*shader_file == nullptr)
        {
            error("malloc failed");
            exit(EXIT_FAILURE);
        }

        fread(*shader_file, sizeof(char), *shader_file_size, shader);

        fclose(shader);
    }

    //Returns the time since the start of glfw or since int in setTime(int)
    double getTime()
    {
        return glfwGetTime();
    }

    //Holds the value of the debug level. Consists of 4 levels
    // - 1: Prints only the critical warning or errors
    // - 2: Prints out any other warnings not covered by 1
    // - 3: Prints out things that the developers should know
    // - 4: Prints out all debugging values
    int game_debug_level = kDebugAll;

    //Prints out char* output if debug_level is less then the current
    //game debug_level
    void debug(int debug_level, const char * format, ...)
    {
        if(debug_level <= game_debug_level)
        {
            va_list argptr;
            va_start(argptr, format);
            fprintf(stdout, "[%c][%f] ", kDebugSymbolTable[debug_level], getTime());
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
        fprintf(stdout, "[E][%f] ", getTime());
        vfprintf(stdout, format, argptr);
        fprintf(stdout, "\n");
        va_end(argptr);
    }

    //Sets debug level of the program - changed most notibly in the command line
    void setDebugLevel(int debug_level)
    {
        game_debug_level = debug_level;
    }

}
