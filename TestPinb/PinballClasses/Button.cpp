#include "..\\OOP\\defines.h"
#include "..\\OOP\\utils.h"
#include "Button.h"
#include "Observer.h"
#include "Subject.h"

//------------------------------------------------//
Button::Button(byte attachTo)
//------------------------------------------------//
{
    m_pin = attachTo;
    m_state = LOW;
    m_EventPressed = NULL;

    #ifdef ARDUINOLIB
    pinMode(m_pin, INPUT_PULLUP);
    m_state = digitalRead(pin);
    #endif
}

//------------------------------------------------//
void Button::AddObserverToEdgePositive(Observer* observer)
//------------------------------------------------//
{
    if (m_EventPressed == NULL)
    {
        m_EventPressed = new Subject(EventType::Pressed, m_pin);
    }

    m_EventPressed->registerObserver(observer);
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
    if (m_EventPressed == NULL)
        return;

      int prevState = m_state;
      m_state = GetInput();
      if (prevState == HIGH && m_state == LOW) 
      {
            buttonDownMs = Millis();
      }
      else if (prevState == LOW && m_state == HIGH) 
      {
            if (Millis() - buttonDownMs < 250) 
            {
              // ignore this for debounce
            }
            else 
            {
                m_EventPressed->notifyObserver();
            }
      }
}

