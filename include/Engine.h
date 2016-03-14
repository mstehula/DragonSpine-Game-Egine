#ifndef ENGINE_H
#define ENGINE_H

namespace dragonspinegameengine {

    int entry(int argc, char** argv);

    double getTime();

    const int kDebugCritical = 0;
    const int kDebugWarning = 1;
    const int kDebugAdvisory = 2;
    const int kDebugAll = 3;

    const char kDebugSymbolTable[] = {'!', 'W', 'A', '='};

    void debug(int debug_level, const char* output);
    void debug_buffer(int debug_level, const char* format, ...);

    void error(const char* output);

    void setDebugLevel(int debug_level);
}

#endif // ENGINE_H
