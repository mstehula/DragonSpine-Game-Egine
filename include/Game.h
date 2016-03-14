#ifndef GAME_H
#define GAME_H

#include "Engine.h"
#include "Input.h"
#include "Renderer.h"

namespace dragonspinegameengine {

    class Game
    {
        public:
            void start();
            void stop();

            void tick();
            void render();
        protected:

        private:
            bool running = false;
            void run();

            Renderer renderer;
            Input input;
    };

}

#endif // GAME_H
