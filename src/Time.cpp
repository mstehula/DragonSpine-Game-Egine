
#include <GLFW/glfw3.h>

#include "Time.h"

namespace DragonSpineGameEngine {

    const long kSecond = 1000000;

    Time::Time()
    {
        last = (long) (glfwGetTime() * kSecond);
    }

    Time::~Time()
    {
        //dtor
    }

    void Time::update()
    {
        now = (long) (glfwGetTime() * kSecond);
        delta = now - last;
        last = now;
    }

    long Time::getTime()
    {
        return now;
    }

    long Time::getDelta()
    {
        return delta;
    }

}
