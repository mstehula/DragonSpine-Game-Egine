
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>

#include "Engine.h"
#include "Renderer.h"

using namespace dragonspinegameengine;

namespace dragonspinegameengine {

    int entry(int argc, char** argv)
    {
/*        if(!glfwInit())
        {
            glfwTerminate();
            perror("Error initializing GLFW, exiting swiftly\n");
            exit(EXIT_FAILURE);
        }
*/
        debug(3, "GLFW and GLEW initiailzed");

        debug(kDebugCritical, "Welcome to the DragonSpine Game Engine");
        debug(kDebugAll, "Starting...");

        Engine::GetInstance()->start();

        debug(kDebugAll, "Engine spinning down");
        debug(kDebugCritical, "Thank you for using the DragonSpine Game Engine");

        glfwTerminate();

        return 0;
    }

    Engine* Engine::instance_ = 0;

    Engine* Engine::GetInstance()
    {
        if(Engine::instance_ == nullptr)
        {
            Engine::instance_ = new Engine();
        }
        return instance_;
    }

    void Engine::start()
    //To prevent starting again, use a boolean switch that
    //only starts the engine if it is not running
    {
        if(running) return;
        running = true;

        run();
    }

    void Engine::stop()
    {
        if(!running) return;
        running = false;
    }

    void Engine::run()
    {
        const int ticks_per_second = 20;
        const float game_skip_ticks = 1.0f/ticks_per_second;
        const float fps_skip_ticks = 1.0f;
        const int max_frame_skips = 5;

        double next_game_tick = getTime();
        double next_fps_tick = getTime();
        int loops;
        float interpolation;

        int frames = 0;
        int ticks = 0;

        renderer.InitWindow();

        test_mesh_ = new Mesh();
        test_mesh_->AddVertices();

        test_shader_ = new Shader();
        test_shader_->AddVertexShader("resources/shaders/basicVertex.vs");
        test_shader_->AddFragmentShader("resources/shaders/basicFragment.fs");

        while(running)
        {
            loops = 0;
            while(getTime() > next_game_tick && loops < max_frame_skips)
            {
                tick();
                ticks++;
                loops++;
                next_game_tick += game_skip_ticks;
            }

            if(getTime() > next_fps_tick)
            {
                debug(kDebugAll, "FPS:[%d] TPS:[%d]", frames, ticks);
                frames = 0;
                ticks = 0;
                next_fps_tick += fps_skip_ticks;
            }

            //Interpolation is how much of a second has passed by since the last render tick;
            interpolation = (float) ((getTime() + game_skip_ticks - next_game_tick) / game_skip_ticks);
            render();
            frames++;
        }
    }

    void Engine::tick()
    {
        glfwPollEvents();
    }

    void Engine::render()
    {
        test_shader_->Bind();
        test_mesh_->Draw();
        renderer.Render();
    }

    void Util::CreateVertexPosArray(Vertex* vertices, int vertices_size, GLfloat** vertex_buffer, int* vertex_buffer_size)
    {
        for(int i = 0; i < vertices_size; i+=1)
        {
            *vertex_buffer[i*Vertex::kSize] = vertices[i].GetPos().x;
            *vertex_buffer[i*Vertex::kSize+1] = vertices[i].GetPos().y;
            *vertex_buffer[i*Vertex::kSize+2] = vertices[i].GetPos().z;
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
