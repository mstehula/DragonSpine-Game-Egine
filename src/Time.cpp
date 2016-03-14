
#include <GLFW/glfw3.h>

#include "Time.h"

namespace DragonSpineGameEngine {

    Time::Time()
    {
        now = glfwGetTime();
    }

    Time::~Time()
    {
        //dtor
    }

    Time Time::update()
    //Updates time standings
    {
        now = glfwGetTime();

        return *this;
    }

    double Time::getTime()
    //Returns the time since the start of glfw or since int in setTime(int)
    {
        return now;
    }

}
