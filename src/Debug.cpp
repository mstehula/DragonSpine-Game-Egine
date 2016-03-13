#include "Debug.h"
#include <stdio.h>

namespace DragonSpineGameEngine {

    //Holds the value of the debug level. Consists of 4 levels
    // - 1: Prints only the critical warning or errors
    // - 2: Prints out any other warnings not covered by 1
    // - 3: Prints out things that the developers should know
    // - 4: Prints out all debugging values
    int game_debug_level = DEBUG_ALL;

    //Prints out char* output if debug_level is less then the current
    //game debug_level
    void debug(const char* output, int debug_level)
    {
        if(debug_level <= game_debug_level)
        {
            fprintf(stdout, "[%d] ", game_debug_level);
            fprintf(stdout, output);
        }
    }

    //Prints out the char* output to stderr
    void error(const char* output)
    {
        fprintf(stderr, output);
    }

    void setDebugLevel(int debug_level)
    {
        game_debug_level = debug_level;
    }

}
