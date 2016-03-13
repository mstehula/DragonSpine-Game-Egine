#ifndef GAME_H
#define GAME_H

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
            void run();
    };

}

#endif // GAME_H
