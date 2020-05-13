#include "..\\OOP\\defines.h"
#include "Subject.h"
#include "Observer.h"

//-------------------------------------------------------//
Subject::Subject(EventType event, byte value)
//-------------------------------------------------------//
{
    headObserver = NULL;
    m_eventType = event;
    m_value = value;
}

//-------------------------------------------------------//
Subject::~Subject()
//-------------------------------------------------------//
{
    Observer* observer = headObserver;
    while (observer != NULL)
    {
        Observer* next = observer->nextObserver;
        delete observer;
        observer = next;
    }
}

//-------------------------------------------------------//
void Subject::registerObserver(Observer* observer)
//-------------------------------------------------------//
{
    if (headObserver == NULL)
    {
        headObserver = observer;
    }
    else
    {
        observer->nextObserver = headObserver;
        headObserver = observer;
    }
}

//-------------------------------------------------------//
void Subject::notifyObserver()
//-------------------------------------------------------//
{
    for (Observer* observer = headObserver; observer; observer = observer->nextObserver)
    {
        observer->onNotifySubject(this,m_eventType,m_value);
    }
}

