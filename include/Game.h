#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include "Renderer.h"
#include "Time.h"

namespace DragonSpineGameEngine {

    class Game
    {
        public:
            Game();
            virtual ~Game();

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
            Time time;
    };

}

#endif // GAME_H
