
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Game.h"

using namespace dragonspinegameengine;

namespace dragonspinegameengine {

    int entry(int argc, char** argv)
    {
        if(!glfwInit())
        {
            glfwTerminate();
            perror("Error initializing GLFW, exiting swiftly\n");
        }

        debug(kDebugCritical, "Welcome to the DragonSpine Game Engine");
        debug(kDebugAll, "Starting...");

        Game game;
        game.start();

        debug(kDebugAll, "Engine spinning down");
        debug(kDebugCritical, "Thank you for using the DragonSpine Game Engine");

        glfwTerminate();

        return 0;
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
    void debug(int debug_level, const char* output)
    {
        if(debug_level <= game_debug_level)
        {
            fprintf(stdout, "[%c][%f] %s\n", kDebugSymbolTable[debug_level], getTime(), output);
        }
    }

    void debug_buffer(int debug_level, const char * format, ...)
    {
        va_list argptr;
        va_start(argptr, format);
        fprintf(stdout, "[%c][%f] ", kDebugSymbolTable[debug_level], getTime());
        vfprintf(stdout, format, argptr);
        fprintf(stdout, "\n");
        va_end(argptr);
    }

    //Prints out the char* output to stderr
    void error(const char* output)
    {
        fprintf(stderr, output);
    }

    //Sets debug level of the program - changed most notibly in the command line
    void setDebugLevel(int debug_level)
    {
        game_debug_level = debug_level;
    }

}
