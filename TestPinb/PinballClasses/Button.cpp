#include "..\\OOP\\defines.h"
#include "..\\OOP\\utils.h"
#include "Button.h"

//------------------------------------------------//
Button::Button(byte attachTo)
//------------------------------------------------//
{
    m_pin = attachTo;
    m_state = HIGH;

    #ifdef ARDUINOLIB
    pinMode(m_pin, INPUT_PULLUP);
    m_state = digitalRead(pin);
    #endif
}

//------------------------------------------------//
int Button::GetInput()
//------------------------------------------------//
{
    #ifdef ARDUINOLIB
    m_state = digitalRead(m_pin);
    #endif

    return m_state;
}


//------------------------------------------------//
void Button::loop()
//------------------------------------------------//
{
      int prevState = m_state;
      m_state = GetInput();
      if (prevState == HIGH && m_state == LOW) 
      {
            buttonDownMs = Millis();
      }
      else if (prevState == LOW && m_state == HIGH) 
      {
            if (Millis() - buttonDownMs < 50) 
            {
              // ignore this for debounce
            }
            else if (Millis() - buttonDownMs < 250) 
            {
              shortClick();
            }
            else  
            {
              longClick();
            }
      }
}

