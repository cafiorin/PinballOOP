#include "..\\OOP\\defines.h"
#include "Subject.h"
#include "Observer.h"

//-------------------------------------------------------//
Subject::Subject(EventType event, byte value)
//-------------------------------------------------------//
{
    headObserver = nullptr;
    m_eventType = event;
    m_value = value;
}

//-------------------------------------------------------//
void Subject::registerObserver(Observer* observer)
//-------------------------------------------------------//
{
    if (headObserver == nullptr)
    {
        headObserver = observer;
    }
    else
    {
        headObserver->nextObserver = headObserver;
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

