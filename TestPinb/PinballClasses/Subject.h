#if !defined(Subject__INCLUDED_)
#define Subject__INCLUDED_
#include "..\\OOP\\defines.h"
#include "EventType.h"
class Observer;

class Subject 
{
public:
    Subject(EventType event, byte value);
    void registerObserver(Observer*);
    void notifyObserver();

private:
    Observer* headObserver;
    EventType m_eventType;
    byte m_value;

};

#endif