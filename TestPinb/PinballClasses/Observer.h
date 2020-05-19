#if !defined(Observer__INCLUDED_)
#define Observer__INCLUDED_
#include "defines.h"
#include "EventType.h"

class Subject;

class Observer 
{
public:
    Observer();
    virtual ~Observer() {}
    void attachSubject(Subject* subject);
    virtual void onNotifySubject(EventType event, byte value) = 0;
    Observer* nextObserver;
};

#endif