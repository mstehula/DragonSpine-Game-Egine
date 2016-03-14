#ifndef TIME_H
#define TIME_H


namespace DragonSpineGameEngine {

    class Time
    {
        public:
            Time();
            virtual ~Time();

            Time update();
            double getTime();
        protected:

        private:
            double now;
    };

}

#endif // TIME_H
