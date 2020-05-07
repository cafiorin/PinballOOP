#ifndef Button__INCLUDED_
#define Button__INCLUDED_

#include "Runnable.h"
#include "..\\OOP\\defines.h"


class Button : public Runnable 
{
    byte m_pin;
    uint8_t m_state;

    unsigned long buttonDownMs;

  protected:
    virtual void shortClick() = 0;
    virtual void longClick() = 0;

  public:
    Button(byte attachTo);
    void loop();
    int GetInput();
    void SetState(uint8_t state) { m_state = state; }

};

#endif