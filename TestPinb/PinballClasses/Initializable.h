#ifndef Initializable__INCLUDED_
#define Initializable__INCLUDED_

class Initializable
{
    private:
        static Initializable* headInitializable;
        Initializable* nextInitializable;

    public:
        Initializable();
        virtual void init() = 0;
        static void initAll();
};

#endif