#ifndef Button__INCLUDED_
#define Button__INCLUDED_

#include "Runnable.h"
#include "..\\OOP\\defines.h"

class Subject;
class Observer;

class Button : public Runnable
{
private:
    byte m_pin;
    uint8_t m_state;

    unsigned long buttonDownMs;
    void Initialize(byte attachTo);

protected:
    Subject* m_EventPressed;

public:
    Button(byte attachTo);
    Button(byte attachTo, Observer* observer);
    ~Button();

    void AddObserverToEdgePositive(Observer* observer);

    void loop();
    int GetInput();
    void SetState(uint8_t state) { m_state = state; }

};

#endif