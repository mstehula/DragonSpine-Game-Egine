#ifndef DEBUG_H
#define DEBUG_H

namespace DragonSpineGameEngine {

    const int DEBUG_CRITICAL = 1;
    const int DEBUG_WARNING = 2;
    const int DEBUG_ADVISORY = 3;
    const int DEBUG_ALL = 4;

    void debug(char* output, int debug_level = 4);
    void error(char* output);

    void setDebugLevel(int debug_level);

} //Namespace

#endif // DEBUG_H
