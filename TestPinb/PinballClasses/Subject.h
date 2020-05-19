#if !defined(Subject__INCLUDED_)
#define Subject__INCLUDED_
#include "defines.h"
#include "EventType.h"
class Observer;

class Subject 
{
public:
    Subject(EventType event, byte value=0);
    ~Subject();


    void registerObserver(Observer*);
    void notifyObserver(byte value=0);

private:
    Observer* headObserver;
    EventType m_eventType;
    byte m_value;

};

#endif