#ifndef Runnable__INCLUDED_
#define Runnable__INCLUDED_

class Runnable
{
    private:
        static Runnable* headRunnable;
        Runnable* nextRunnable;

    public:
        Runnable();
        virtual void loop() = 0;
        static void loopAll();
};

#endif