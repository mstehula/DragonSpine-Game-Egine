#ifndef TIME_H
#define TIME_H


namespace DragonSpineGameEngine {

    class Time
    {
        public:
            Time();
            virtual ~Time();

            void update();
            long getTime();
            long getDelta();
        protected:

        private:
            long last;
            long now;
            long delta;
    };

}

#endif // TIME_H
